#include <Wire.h>
#include <MPU6050.h>
#include <DFRobotDFPlayerMini.h>
#include <HardwareSerial.h>

MPU6050 mpu;

HardwareSerial mySerial(2);
DFRobotDFPlayerMini player;

void setup() {

  Serial.begin(115200);

  // MPU6050
  Wire.begin(21, 22);
  mpu.initialize();

  // DFPlayer
  mySerial.begin(9600, SERIAL_8N1, 16, 17);

  if (!player.begin(mySerial)) {
    Serial.println("DFPlayer Error");
    while(true);
  }

  player.volume(30);

  Serial.println("SYSTEM READY");
}

void loop() {

  // =========================
  // FLEX SENSORS
  // =========================

  int f1 = analogRead(39);
  int f2 = analogRead(34);
  int f3 = analogRead(32);
  int f4 = analogRead(33);

  if (f1 > 10) {
    Serial.println("Can you help me get to this place?");
    player.play(5);
    delay(2000);
    return;
  }

  else if (f2 > 10) {
    Serial.println("Where is the bus station?");
    player.play(2);
    delay(2000);
    return;
  }

  else if (f3 > 10) {
    Serial.println("I need help");
    player.play(3);
    delay(2000);
    return;
  }

  else if (f4 > 10) {
    Serial.println("I need my medicine");
    player.play(4);
    delay(2000);
    return;
  }

  // =========================
  // MPU6050
  // =========================

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Gesture 1
  if (
      abs(ax + 15800) < 1500 &&
      abs(ay + 1950) < 1500 &&
      abs(az - 850) < 3000
     )
  {
      Serial.println("Please call my family");
      player.play(6);
      delay(2000);
  }

  // Gesture 2
  else if (
      abs(ax + 3250) < 2500 &&
      abs(ay + 4600) < 2500 &&
      abs(az - 15250) < 2500
     )
  {
      Serial.println("Please call an ambulance");
      player.play(7);
      delay(2000);
  }

  // Gesture 3
  else if (
      abs(ax + 2200) < 2000 &&
      abs(ay - 16180) < 2000 &&
      abs(az - 2430) < 2000
     )
  {
      Serial.println("Hello!");
      player.play(8);
      delay(2000);
  }

  // Gesture 4
  else if (
      abs(ax - 2350) < 2500 &&
      abs(ay + 15730) < 2500 &&
      abs(az - 1520) < 2500
     )
  {
      Serial.println("How are you?");
      player.play(9);
      delay(2000);
  }

  // Gesture 5
  else if (
      abs(ax + 1260) < 2500 &&
      abs(ay + 15290) < 2500 &&
      abs(az + 4990) < 2500
     )
  {
      Serial.println("Nice to meet you!");
      player.play(10);
      delay(2000);
  }

  // Gesture 6
  else if (
      abs(ax + 2565) < 2500 &&
      abs(ay - 13565) < 2500 &&
      abs(az - 9260) < 2500
     )
  {
      Serial.println("Goodbye");
      player.play(11);
      delay(2000);
  }

  delay(100);
}