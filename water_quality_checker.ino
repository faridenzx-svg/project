#define PH_PIN 34
#define TDS_PIN 35

#define VREF 3.3
#define ADC_RES 4096

float phValue = 0;
float tdsValue = 0;
String waterQuality = "";

void setup() {
  Serial.begin(9600);

  analogReadResolution(12);
  
  Serial.println("=================================");
  Serial.println("ระบบตรวจสอบคุณภาพน้ำบ่อปลา ESP32");
  Serial.println("=================================");
  delay(2000);
}

void loop() {
  phValue = readPH();
  tdsValue = readTDS();
  

  checkWaterQuality(phValue, tdsValue);
  
  displayResults();
  
  delay(2000);
}

float readPH() {
  int analogValue = analogRead(PH_PIN);
  float voltage = analogValue * (VREF / ADC_RES);
  
  // แปลงค่าแรงดันเป็น pH (ปรับสูตรตาม sensor ที่ใช้)
  // สูตรนี้เป็นตัวอย่าง ต้องปรับ calibrate ตาม sensor จริง
  float ph = 7.0 + ((2.5 - voltage) / 0.18);
  
  return ph;
}

// ฟังก์ชันอ่านค่า TDS
float readTDS() {
  int analogValue = analogRead(TDS_PIN);
  float voltage = analogValue * (VREF / ADC_RES);
  
  // แปลงค่าแรงดันเป็น TDS (ppm)
  // สูตรนี้เป็นตัวอย่าง ต้องปรับ calibrate ตาม sensor จริง
  float tds = (133.42 * voltage * voltage * voltage 
               - 255.86 * voltage * voltage 
               + 857.39 * voltage) * 0.5;
  
  return tds;
}

void checkWaterQuality(float ph, float tds) {
  bool phOK = false;
  bool tdsOK = false;
  
  // ตรวจสอบค่า pH (6.5-8.0 = ดีมาก, 6.0-8.5 = พอใช้)
  if (ph >= 6.5 && ph <= 8.0) {
    phOK = true;
  } else if (ph >= 6.0 && ph <= 8.5) {
    phOK = false; // พอใช้
  }
  
  // ตรวจสอบค่า TDS (100-400 = ดีมาก, 400-800 = พอใช้)
  if (tds >= 100 && tds <= 400) {
    tdsOK = true;
  } else if (tds > 400 && tds <= 800) {
    tdsOK = false; // พอใช้
  }
  
  if (phOK && tdsOK) {
    waterQuality = "น้ำสะอาดมาก";
  } else if ((phOK && !tdsOK) || (!phOK && tdsOK)) {
    waterQuality = "น้ำค่อนข้างสะอาด";
  } else {
    waterQuality = "น้ำไม่สะอาด";
  }
}

void displayResults() {
  Serial.println("\n========== ผลการตรวจสอบ ==========");
  
  // แสดงค่า pH
  Serial.print("pH: ");
  Serial.print(phValue, 2);
  if (phValue >= 6.5 && phValue <= 8.0) {
    Serial.println(" ✓ (ดีมาก)");
  } else if (phValue >= 6.0 && phValue <= 8.5) {
    Serial.println(" ⚠ (พอใช้)");
  } else {
    Serial.println(" ✗ (ผิดปกติ)");
  }
  
  // แสดงค่า TDS
  Serial.print("TDS: ");
  Serial.print(tdsValue, 0);
  Serial.print(" ppm");
  if (tdsValue >= 100 && tdsValue <= 400) {
    Serial.println(" ✓ (ดีมาก)");
  } else if (tdsValue > 400 && tdsValue <= 800) {
    Serial.println(" ⚠ (พอใช้)");
  } else {
    Serial.println(" ✗ (ผิดปกติ)");
  }

  Serial.println("Water: " + waterQuality;
  Serial.println("===================================\n");
}
