#include <ESP8266WiFi.h>

const char* ssid = "Sus";
const char* password = "12345678";

WiFiServer server(80);

int motorPin = D5;
int prevSpeed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');

  int index = request.indexOf("value=");
  if (index != -1) {
    int fsrValue = request.substring(index + 6).toInt();

    Serial.print("Received: ");
    Serial.println(fsrValue);

    int speed = 0;

    // YOUR calibrated ranges
    if (fsrValue < 30) {
      speed = 0;
    }
    else if (fsrValue < 100) {
      speed = 80;
    }
    else if (fsrValue < 300) {
      speed = 150;
    }
    else {
      speed = 255;
    }

    // smoothing
    speed = (speed + prevSpeed) / 2;
    prevSpeed = speed;

    analogWrite(motorPin, speed);
  }

  client.flush();
}