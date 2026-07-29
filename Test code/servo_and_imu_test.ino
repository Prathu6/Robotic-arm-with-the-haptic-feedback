#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Servo.h>

MPU6050 imu(0x68);
Servo testServo;

#define SERVO_PIN D5

float yaw, pitch, roll;

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);

  imu.initialize();
  testServo.attach(SERVO_PIN);

  Serial.println("Yaw,Pitch,Roll,Servo"); // Label line (optional)
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;

  imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // -------- Simple angle estimation --------
  roll  = atan2(ay, az) * 180 / PI;
  pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180 / PI;
  yaw   = map(gz, -17000, 17000, -180, 180);  // gyro approx

  // -------- Servo mapping --------
  int servoAngle = map(pitch, -90, 90, 0, 180);
  servoAngle = constrain(servoAngle, 0, 180);
  testServo.write(servoAngle);

  // -------- Serial Plotter Output --------
  Serial.print(yaw);
  Serial.print(",");
  Serial.print(pitch);
  Serial.print(",");
  Serial.print(roll);
  Serial.print(",");
  Serial.println(servoAngle);

  delay(20);
}