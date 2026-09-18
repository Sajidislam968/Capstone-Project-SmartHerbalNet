#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// -------- PIN DEFINITIONS ----------
#define MQ2_PIN 32
#define MQ4_PIN 35
#define MQ135_PIN 34
#define SOIL_PIN 33

#define DHTPIN 27
#define DHTTYPE DHT22   // or DHT22

DHT dht(DHTPIN, DHTTYPE);

// -------- VARIABLES ----------
float mq2, mq4, soil;
float temperature, humidity;

const char* ssid = "SowroV";
const char* password = "Ektuobolbona";

const char* mqttServer = "mqtt.thingsboard.cloud";
const int mqttPort = 1883;
const char* accessToken = "kvrvcn5OZZh91RHdgloj";

WiFiClient espClient;
PubSubClient client(espClient);

void setupWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int timeout_counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    timeout_counter++;
    if (timeout_counter > 20) { // If it takes more than 10 seconds
      Serial.println("\nWiFi Failed! Check SSID/Password.");
      return; 
    }
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting ThingsBoard connection...");
    // Attempt to connect
    if (client.connect("HydroponicsESP32", accessToken, NULL)) {
      Serial.println("CONNECTED");
    } else {
      Serial.print("FAILED, rc=");
      Serial.print(client.state()); // This code tells you WHY it failed
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}


void setup() {
  Serial.begin(115200);
  setupWiFi();
  client.setServer(mqttServer, mqttPort);
  dht.begin();
  analogSetAttenuation(ADC_11db);  

  Serial.println("Environmental Monitoring System");
  Serial.println("--------------------------------");
}

void loop() {
if (!client.connected()) {
  reconnect();
}
client.loop();


// MQ-2
mq2 = analogRead(MQ2_PIN);
delay(500);

// MQ-4
mq4 = analogRead(MQ4_PIN);
delay(500);



// 4️⃣ DHT
humidity = dht.readHumidity();
temperature = dht.readTemperature();
delay(1000);

// 5️⃣ Soil Moisture
soil = analogRead(SOIL_PIN);
delay(1000);

  Serial.print("MQ-2 Gas          | ");
  Serial.println(mq2);

  Serial.print("MQ-4 Methane      | ");
  Serial.println(mq4);

  Serial.print("Temperature (C)   | ");
  Serial.println(temperature);

  Serial.print("Humidity (%)      | ");
  Serial.println(humidity);

  Serial.print("Soil Moisture     | ");
  Serial.println(soil);

  Serial.println("---------------------------------------------");

  String payload = "{";
  payload += "\"temperature\":" + String(temperature) + ",";
  payload += "\"humidity\":" + String(humidity) + ",";
  payload += "\"mq2\":" + String(mq2) + ",";
  payload += "\"mq4\":" + String(mq4) + ",";
  payload += "\"soil\":" + String(soil) + ",";
  payload += "}";

  // Attempt to publish and check for success
  if (client.publish("v1/devices/me/telemetry", payload.c_str())) {
    Serial.println("✅ Data sent successfully to ThingsBoard!");
  } else {
    Serial.println("❌ FAILED to send data! Checking connection...");
    
    // Check if the issue is MQTT or WiFi
    if (!client.connected()) {
      Serial.println("MQTT Connection Lost.");
    }
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi Connection Lost.");
    }
  }

  // ⏱ WAIT 5 MINUTE
  delay(5000);
}

