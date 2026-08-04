#include <Wire.h>

#define MPU1 0x68
#define MPU2 0x69

int16_t gx1, gy1, gz1;
int16_t gx2, gy2, gz2;

void wakeMPU(uint8_t addr) {
  Wire.beginTransmission(addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
}

void readGyro(uint8_t addr, int16_t &gx, int16_t &gy, int16_t &gz) {
  Wire.beginTransmission(addr);
  Wire.write(0x43);           // GYRO_XOUT_H
  Wire.endTransmission(false);
  Wire.requestFrom(addr, 6, true);

  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);

  wakeMPU(MPU1);
  wakeMPU(MPU2);

  delay(2000);  // stabilize
}

void loop() {
  readGyro(MPU1, gx1, gy1, gz1);
  readGyro(MPU2, gx2, gy2, gz2);

  // Convert to deg/sec (±250 dps → 131 LSB)
  float g1x = gx1 / 131.0;
  float g1y = gy1 / 131.0;
  float g1z = gz1 / 131.0;

  float g2x = gx2 / 131.0;
  float g2y = gy2 / 131.0;
  float g2z = gz2 / 131.0;

  // ===== SERIAL PLOTTER (NUMBERS ONLY) =====
  Serial.print(g1x); Serial.print(" ");
  Serial.print(g1y); Serial.print(" ");
  Serial.print(g1z); Serial.print(" ");
  Serial.print(g2x); Serial.print(" ");
  Serial.print(g2y); Serial.print(" ");
  Serial.println(g2z);

  delay(20);
}