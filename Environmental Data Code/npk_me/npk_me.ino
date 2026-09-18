#include <SoftwareSerial.h>

#define RE 8
#define DE 7

// Modbus command frames
const byte nitro[] = {0x01,0x03,0x00,0x1E,0x00,0x01,0xE4,0x0C};
const byte phos[]  = {0x01,0x03,0x00,0x1F,0x00,0x01,0xB5,0xCC};
const byte pota[]  = {0x01,0x03,0x00,0x20,0x00,0x01,0x85,0xC0};

byte values[7];

// RX, TX
SoftwareSerial mod(2, 3);

void setup() {
  Serial.begin(9600);

  // Try 9600 first; if no response, change to 4800
  mod.begin(9600);

  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  digitalWrite(RE, LOW);
  digitalWrite(DE, LOW);

  Serial.println("NPK Sensor Test Started...");
  Serial.println("--------------------------------");
}

void loop() {
  byte n = readNPK(nitro, "Nitrogen");
  delay(300);

  byte p = readNPK(phos, "Phosphorous");
  delay(300);

  byte k = readNPK(pota, "Potassium");
  delay(300);

  Serial.println("========== RESULT ==========");
  Serial.print("Nitrogen    : "); Serial.print(n); Serial.println(" mg/kg");
  Serial.print("Phosphorous : "); Serial.print(p); Serial.println(" mg/kg");
  Serial.print("Potassium   : "); Serial.print(k); Serial.println(" mg/kg");
  Serial.println("============================\n");

  delay(2000);
}

// ===============================
// Generic NPK read function
// ===============================
byte readNPK(const byte *cmd, const char *name) {

  // Clear old data
  while (mod.available()) mod.read();

  // Enable transmit
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);

  mod.write(cmd, 8);
  mod.flush();

  // Switch to receive mode
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);

  delay(100);  // IMPORTANT: wait for sensor response

  if (!mod.available()) {
    Serial.print(name);
    Serial.println(" ❌ No response from sensor");
    return 0;
  }

  Serial.print(name);
  Serial.print(" response: ");

  byte index = 0;
  unsigned long startTime = millis();

  while ((millis() - startTime) < 500 && index < 7) {
    if (mod.available()) {
      values[index] = mod.read();
      Serial.print(values[index], HEX);
      Serial.print(" ");
      index++;
    }
  }
  Serial.println();

  if (index < 7) {
    Serial.print(name);
    Serial.println(" ⚠ Incomplete data received");
    return 0;
  }

  return values[4];  // Actual NPK value
}
