int fsrPin = A0; //change pin 
int motorPin = D5; //change pin

void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int fsrValue = analogRead(fsrPin);
  Serial.println(fsrValue);

  // Map your real values (adjust if needed)
  int speed = map(fsrValue, 15, 300, 0, 255);

  // Limit values
  speed = constrain(speed, 0, 255);

  // Remove noise (no press)
  if (fsrValue < 20) {
    speed = 0;
  }

  analogWrite(motorPin, speed);

  delay(20);
}