#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE };

EthernetServer server(80);

const int lockPin = 2;
const int ledPin = 13;

int lockState = 0;
int hits = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Let's get this party started.");
  pinMode(ledPin, OUTPUT);
  pinMode(lockPin, INPUT);
  Ethernet.begin(mac);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        lockState = 1;
        // Values are filtered due to erroneous voltage values
        // when the door is unlocked. This can cause a request
        // to be delayed by up to 1 second.
        for (int i = 0; i < 50; ++i) {
          int value = analogRead(lockPin);
          if (value < 1000) {
            lockState = 0;
            break;
          }
          delay(20);
        }
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: application/json");
        client.println();
        client.print("{\"id\":0,\"locked\":");
        client.print(lockState);
        client.print("}");
        ++hits;
        break;
      }
    }
    client.stop();
  }
}
