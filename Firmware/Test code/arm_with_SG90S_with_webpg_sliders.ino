//robotic arm with sg90s proto using web page slider 

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_PWMServoDriver.h>

// PCA9685 object
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver();

// WiFi credentials
const char* ssid = "Enter Hotspot Name";
const char* password = "12345678";

// Web server
ESP8266WebServer server(80);

// Servo limits
#define SERVOMIN 120
#define SERVOMAX 520

// Convert angle (0–180) to PWM
int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

// HTML Page
String webpage = R"====(
<!DOCTYPE html>
<html>
<head>
  <title>5DOF Robot Arm</title>
</head>
<body style="text-align:center;">
<h2>5 DOF Robot Arm Control</h2>

<script>
function send(val, ch){
  var xhttp = new XMLHttpRequest();
  xhttp.open("GET", "/set?ch=" + ch + "&val=" + val, true);
  xhttp.send();
}
</script>

Base:<br>
<input type="range" min="0" max="180" value="90" oninput="send(this.value,0)"><br><br>

Shoulder:<br>
<input type="range" min="0" max="180" value="90" oninput="send(this.value,1)"><br><br>

Elbow:<br>
<input type="range" min="0" max="180" value="90" oninput="send(this.value,2)"><br><br>

Wrist:<br>
<input type="range" min="0" max="180" value="90" oninput="send(this.value,3)"><br><br>

Gripper:<br>
<input type="range" min="0" max="180" value="90" oninput="send(this.value,4)"><br><br>

</body>
</html>
)====";

// Root page
void handleRoot() {
  server.send(200, "text/html", webpage);
}

// Handle servo movement
void handleServo() {
  if (server.hasArg("ch") && server.hasArg("val")) {
    int ch = server.arg("ch").toInt();
    int val = server.arg("val").toInt();

    val = constrain(val, 0, 180);

    int pulse = angleToPulse(val);
    pca.setPWM(ch, 0, pulse);
  }

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  // I2C
  Wire.begin(D2, D1);

  // PCA9685
  pca.begin();
  pca.setPWMFreq(50);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Web routes
  server.on("/", handleRoot);
  server.on("/set", handleServo);

  server.begin();
}

void loop() {
  server.handleClient();
}