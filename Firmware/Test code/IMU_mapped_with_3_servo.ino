//1 imu yaw/roll/pitch mapped with 3 servo test
#include <Wire.h>
#include <Servo.h>

#define MPU 0x68

// ===== Servo objects =====
Servo servoYaw;
Servo servoPitch;
Servo servoRoll;

// ===== Raw sensor data =====
int16_t ax, ay, az;
int16_t gx, gy, gz;

// ===== Angles =====
float accPitch, accRoll;
float gyroPitch = 0, gyroRoll = 0, gyroYaw = 0;
float pitch = 90, roll = 90, yaw = 90;

// Smoothed servo angles
float sPitch = 90, sRoll = 90, sYaw = 90;

unsigned long prevTime;

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);   // SDA, SCL

  // Attach servos
  servoYaw.attach(D5);
  servoPitch.attach(D6);
  servoRoll.attach(D7);

  // Wake MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  delay(2000);  // keep IMU still

  prevTime = millis();
}

void loop() {
  // ===== Read MPU6050 =====
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);

  ax = Wire.read()<<8 | Wire.read();
  ay = Wire.read()<<8 | Wire.read();
  az = Wire.read()<<8 | Wire.read();

  Wire.read(); Wire.read(); // skip temp

  gx = Wire.read()<<8 | Wire.read();
  gy = Wire.read()<<8 | Wire.read();
  gz = Wire.read()<<8 | Wire.read();

  // ===== Time =====
  float dt = (millis() - prevTime) / 1000.0;
  prevTime = millis();

  // ===== Accelerometer angles =====
  accPitch = atan2(ax, sqrt(ay*ay + az*az)) * 57.2958;
  accRoll  = atan2(ay, sqrt(ax*ax + az*az)) * 57.2958;

  // ===== Gyro integration =====
  gyroPitch += (gx / 131.0) * dt;
  gyroRoll  += (gy / 131.0) * dt;
  gyroYaw   += (gz / 131.0) * dt;

  // ===== Complementary filter =====
  pitch = 0.98 * gyroPitch + 0.02 * accPitch;
  roll  = 0.98 * gyroRoll  + 0.02 * accRoll;
  yaw   = gyroYaw; // yaw has no accel correction

  // ===== Map IMU → Servo (0–180) =====
  float targetPitch = constrain(map(pitch, -90, 90, 0, 180), 0, 180);
  float targetRoll  = constrain(map(roll,  -90, 90, 0, 180), 0, 180);
  float targetYaw   = constrain(map(yaw,  -180, 180, 0, 180), 0, 180);

  // ===== Servo smoothing (LOW-PASS FILTER) =====
  sPitch = 0.85 * sPitch + 0.15 * targetPitch;
  sRoll  = 0.85 * sRoll  + 0.15 * targetRoll;
  sYaw   = 0.85 * sYaw   + 0.15 * targetYaw;

  // ===== Drive servos =====
  servoPitch.write(sPitch);
  servoRoll.write(sRoll);
  servoYaw.write(sYaw);

  // ===== Serial Plotter =====
  Serial.print(pitch); Serial.print(" ");
  Serial.print(roll);  Serial.print(" ");
  Serial.print(yaw);   Serial.print(" ");
  Serial.print(sPitch);Serial.print(" ");
  Serial.print(sRoll); Serial.print(" ");
  Serial.println(sYaw);

  delay(20);
}