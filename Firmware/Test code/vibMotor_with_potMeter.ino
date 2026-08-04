
/*VIBTRATION MOTOR WITH POTENTIOMETER 

--------------------WIRING CONNECTION----------------------- 

Connect like this potentiometer :

Pot pin	Connect to
Pin 1	3.3V
Pin 2 (middle)	A0
Pin 3	GND

D5 → 1k resistor → transistor base  
Emitter → GND  
Collector → Motor –  
Motor + → 5V  
Diode across motor

*/


#define MOTOR_PIN D5
#define POT_PIN A0

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
  int potValue = analogRead(POT_PIN);   // 0–1023
  int pwmValue = map(potValue, 0, 1023, 0, 1023);

  analogWrite(MOTOR_PIN, pwmValue);     // PWM to motor
  delay(10);
}