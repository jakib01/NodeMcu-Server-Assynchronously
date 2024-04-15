#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const byte redLED = D5;
const byte bazzar = D6;
const byte wifiAlert = D8;

const char *password = "Akib108064";
const char *ssid = "Akib's Personal";

// const char *password = "Akib108064";
// const char *ssid = "Akib's Personal";

// const char *password = "nsl@1122";
// const char *ssid = "Nogor-solutions-1";

ESP8266WebServer server(80);

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(bazzar, OUTPUT);
  pinMode(wifiAlert, OUTPUT);

  Serial.begin(115200);

  IPAddress ip(192, 168, 1, 200);      // Set your desired IP address
  IPAddress gateway(192, 168, 1, 1);   // Set your gateway IP address
  IPAddress subnet(255, 255, 255, 0);  // Set your subnet mask
  IPAddress dns(192, 168, 1, 1);       // Set your DNS server IP address

  // Set up the Wi-Fi connection with the fixed IP configuration
  WiFi.config(ip, gateway, subnet, dns);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(wifiAlert, HIGH); 

  // Route setup
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/plain", "Hello from NodeMCU!");
  });

  server.on("/control", HTTP_GET, []() {
    if (server.hasArg("control")) {
      int control = server.arg("control").toInt();
      if (control == 1) {
        digitalWrite(redLED, HIGH);  // Turn the light on
        digitalWrite(bazzar, HIGH);  // Turn the bazzar on
        server.send(200, "text/plain", "1");
        Serial.print("Turn the light on");
      } else if (control == 0) {
        digitalWrite(redLED, LOW);  // Turn the light off
        digitalWrite(bazzar, LOW);  // Turn the bazar off
        server.send(200, "text/plain", "0");
        Serial.print("Turn the light off");
      } else {
        server.send(400, "text/plain", "Invalid control value");
      }
    } else {
      server.send(400, "text/plain", "Control parameter not provided");
    }
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
