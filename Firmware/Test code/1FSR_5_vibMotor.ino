//--------------------1 fsr 5 vib motor wirelessly-------------------

//>>>>>>>>>>>>>SENDER ESP A with FSR sensor <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <ESP8266WiFi.h>

const char* ssid = "Your Hotspot Name";
const char* password = "password"; // change accordingly 

const char* host = "10.40.42.233";  // ESP B IP //change

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
}

void loop() {
  int fsrValue = analogRead(A0);

  Serial.print("FSR: ");
  Serial.println(fsrValue);

  WiFiClient client;

  if (client.connect(host, 80)) {
    client.print("GET /data?value=");
    client.print(fsrValue);
    client.print(" HTTP/1.1\r\nHost: ");
    client.print(host);
    client.print("\r\nConnection: close\r\n\r\n");
  }

  delay(100);
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>RECIEVER ESP B 5 vib motor<<<<<<<<<<<<<<<<<<<

#include <ESP8266WiFi.h>

const char* ssid = "Your Hotspot Name";
const char* password = "password"; // change accordingly 

WiFiServer server(80);

// 5 motor pins
int motors[5] = {D2, D3, D4, D5, D6};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 5; i++) {
    pinMode(motors[i], OUTPUT);
  }

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

  int fsrValue = 0;

  int index = request.indexOf("value=");
  if (index != -1) {
    String valStr = request.substring(index + 6);

    // Extract only number
    for (int i = 0; i < valStr.length(); i++) {
      if (!isDigit(valStr[i])) {
        valStr = valStr.substring(0, i);
        break;
      }
    }

    fsrValue = valStr.toInt();
  }

  Serial.print("Received: ");
  Serial.println(fsrValue);

  int activeMotors = 0;

  // Your calibrated ranges
  if (fsrValue < 30) activeMotors = 0;
  else if (fsrValue < 100) activeMotors = 1;
  else if (fsrValue < 200) activeMotors = 2;
  else if (fsrValue < 350) activeMotors = 3;
  else if (fsrValue < 450) activeMotors = 4;
  else activeMotors = 5;

  // Control motors
  for (int i = 0; i < 5; i++) {
    if (i < activeMotors) {
      analogWrite(motors[i], 200);  // ON
    } else {
      analogWrite(motors[i], 0);    // OFF
    }
  }

  client.flush();
}