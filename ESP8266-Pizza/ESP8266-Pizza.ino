#include <ESP8266WiFi.h>

const char* ssid     = "airtelwifi";
const char* password = "12345678123";

const char* host = "kernel32.in";

const int BUTTON_REC = 4;
const int CONN_LED = 16;
const int DONE_LED = 5;




void setup() {
  pinMode(BUTTON_REC, INPUT_PULLUP);
  pinMode(DONE_LED, OUTPUT);
  pinMode(CONN_LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_REC), resetData, CHANGE);
  Serial.begin(115200);
  digitalWrite(CONN_LED, LOW);

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(CONN_LED, HIGH);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;
void loop() {
  if (value == 1) {

    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 3000;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      value = 0;
      return;
    }

    // We now create a URI for the request
    String url = "/send/data";


    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
        value = 0;
      }
      value = 0;
    }

    // Read all the lines of the reply from server and print them to Serial
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
      digitalWrite(DONE_LED, HIGH);
    }
    digitalWrite(DONE_LED, LOW);
    Serial.println();
    Serial.println("closing connection");
    delay(1000);

  }
}
void resetData() {
  value = 1;

}
