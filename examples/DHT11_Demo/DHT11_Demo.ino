#include <DHT.h> // อ้างอิงไลบารี่ DHT

DHT dht; // สร้างคลาส dht เพื่อเริ่มใช้ไลบารี่

void setup() {
  Serial.begin(9600); // เปิดการใช้งานดีบัคผ่าน Serial
} 

void loop() {
  // อ่านข้อมูลจาก DHT11
  // รูปแบบฟังก์ชั่น bool dht.read(int pin, int type);
  // ค่าพารามิเตอร์:
  //   - pin : หมายเลขขา data ของ DHT ที่ต่อกับ Arduino
  //   - type : เบอร์ของ DHT มีให้เลือกดังนี้
  //            -> TYPE_DHT11
  //            -> TYPE_DHT22
  // การส่งค่ากลับ:
  //   ส่งค่ากลับข้อมูลชนิด bool หากอ่านค่าได้ จะให้ค่า true
  // หากไม่ได้ จะให้ค่า false
  bool ros = dht.read(5, TYPE_DHT11);

  if (ros == false) { // ถ้าอ่านค่าไม่ได้
    Serial.println("Read error.");
  } else { // ถ้าอ่านค่าได้
    Serial.println("Humidity: " + String(dht.humidity) + "%");
    Serial.println("Temp: " + String(dht.tempC) + "*C (" + String(dht.tempF) + "*F)");
    Serial.println();
  }
  delay(500);
}