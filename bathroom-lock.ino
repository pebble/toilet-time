#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
   
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE };
 
EthernetServer server(80);

const int lockPin = 2;
const int ledPin = 13;

int lockState = 0;

void setup(){
  Serial.begin(9600);
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
        lockState = digitalRead(lockPin);
        if (lockState == HIGH) {     
          // turn LED on:    
          digitalWrite(ledPin, HIGH);  
        }  else {
          // turn LED off:
          digitalWrite(ledPin, LOW); 
        }
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: application/json");
        client.println();
        client.print("{\"id\":0,\"locked\":");
        client.print(lockState);
        client.print("} ");
        hits = ++hits;
        break;
      }
    }
    client.stop();
  }
}
