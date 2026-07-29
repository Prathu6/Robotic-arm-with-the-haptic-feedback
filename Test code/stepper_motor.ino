//STEPPER MOTOR TESTING FOR ESP8266 TESING DONE
 
#define STEP_PIN D2   // GPIO4
#define DIR_PIN  D1   // GPIO5

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(DIR_PIN, HIGH); // direction
}

void loop() {
  for (int i = 0; i < 200; i++) {   // ~1 revolution
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(800);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(800);
  }

  delay(1000);

  digitalWrite(DIR_PIN, !digitalRead(DIR_PIN)); // change direction
  delay(500);
}

/*-----------------FOR 360 DEGREE ROTATION----------

#define STEP_PIN D2   // GPIO4
#define DIR_PIN  D1   // GPIO5

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(DIR_PIN, HIGH);   // set direction
}

void loop() {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(800);        // speed control
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(800);
}
*/