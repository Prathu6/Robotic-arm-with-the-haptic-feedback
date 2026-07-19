#include <Wire.h>
#include <MPU6050.h>
_test
MPU6050 mpu;

#define STEP_PIN D6
#define DIR_PIN  D5

const int STEPS_180 = 100;
int currentSteps = 0;

float yaw = 0;
unsigned long lastTime;

void stepOnce(bool dir) {
  digitalWrite(DIR_PIN, dir);
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(800);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(800);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 FAIL");
    while (1);
  }

  lastTime = millis();
  Serial.println("Yaw Motor");
}

void loop() {
  int16_t gx, gy, gz;
  mpu.getRotation(&gx, &gy, &gz);

  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;

  yaw += (gz / 131.0) * dt;
  yaw = constrain(yaw, 0, 180);

  int targetSteps = map((int)yaw, 0, 180, 0, STEPS_180);
  int diff = targetSteps - currentSteps;

  if (diff > 0) {
    stepOnce(HIGH);
    currentSteps++;
  } 
  else if (diff < 0) {
    stepOnce(LOW);
    currentSteps--;
  }

  Serial.print(yaw);
  Serial.print(" ");
  Serial.println(currentSteps * 1.8);

  delay(20);
}