#include <WiFi.h>
#include <PubSubClient.h>

/* ---------- WiFi ---------- */
const char* ssid     = "SowroV";
const char* password = "Ektuobolbona";

/* ---------- ThingsBoard MQTT ---------- */
const char* mqttServer = "mqtt.thingsboard.cloud";
const int   mqttPort   = 1883;
const char* accessToken = "xTeBM0Vq0M9xvVOKZVVR"; 

/* ---------- Pins ---------- */
#define PH_PIN 34
// #define DO_PIN 35
#define SAMPLES 20

/* ---------- pH calibration (CHANGE after buffer test) ---------- */
float ph7Voltage = 1.38;
float ph4Voltage = 1.90;


WiFiClient espClient;
PubSubClient client(espClient);

/* ---------- Functions ---------- */
float readVoltage(uint8_t pin)
{
  float sum = 0;
  for (int i = 0; i < SAMPLES; i++) {
    sum += analogRead(pin);
    delay(5);
  }
  float adcAvg = sum / SAMPLES;
  return adcAvg * (3.3 / 4095.0);
}

float readPH()
{
  float v = readVoltage(PH_PIN);
  float slope = (7.0 - 4.0) / (ph7Voltage - ph4Voltage);
  float intercept = 7.0 - slope * ph7Voltage;
  float ph = slope * v + intercept;

  if (ph < 0) ph = 0;
  if (ph > 14) ph = 14;
  return ph;
}

/* ---------- MQTT ---------- */
void connectMQTT()
{
  while (!client.connected()) {
    if (client.connect("HydroponicsESP32", accessToken, NULL)) {
      Serial.println("Connected to ThingsBoard");
    } else {
      Serial.println("Retrying MQTT...");
      delay(2000);
    }
  }
}

/* ---------- Setup ---------- */
void setup()
{
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  client.setServer(mqttServer, mqttPort);
  Serial.println("\nSystem Ready");
}

/* ---------- Loop ---------- */
void loop()
{
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();

  float ph = readPH();

  Serial.print("pH = ");
  Serial.print(ph, 2);

  Serial.println(" mg/L");

  // ---- JSON Telemetry ----
  String payload = "{";
  payload += "\"ph\":" + String(ph, 2) + ",";
  payload += "}";

  client.publish("v1/devices/me/telemetry", payload.c_str());

  delay(5000);
}
