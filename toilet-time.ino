#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE };
char serverName[] = "toilet-time.tools.getpebble.com";
int serverPort = 80;
char pathName[] = "/v1/update";
const int lockPin = 2;
const int ledPin = 13;
int lockState = 0;
boolean lastConnected = false;

EthernetClient client;

void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(lockPin, INPUT);
  Serial.print(F("Starting ethernet..."));
  if(!Ethernet.begin(mac)) {
    Serial.println(F("failed"));
  } else {
    Serial.println(Ethernet.localIP());
  }
  delay(2000);
  Serial.println(F("Ready"));
}

void loop(){
  Ethernet.maintain();

  // Get current state of lock sensor
  // Values are filtered due to erroneous voltage values
  // when the door is unlocked. This can cause a request
  // to be delayed by up to 1 second.
  lockState = 1;
  for (int i = 0; i < 50; ++i) {
    int value = analogRead(lockPin);
    if (value < 1000) {
      lockState = 0;
      break;
    }
    delay(20);
  }

  // Show lock status on Console/and Status LED
  if (lockState == 0){
    digitalWrite(ledPin, LOW);
    Serial.println("Unlocked");
  } else {
    digitalWrite(ledPin, HIGH);
    Serial.println("Locked");
  }

  // POST JSON encoded message with lockState to server
  if (client.connect(serverName,serverPort)){
    char data[32];
    char outBuf[64];
    sprintf(data,"{\"id\":0,\"locked\":%d}",lockState);
    sprintf(outBuf,"POST %s HTTP/1.1",pathName);
    client.println(outBuf);
    sprintf(outBuf,"Host: %s",serverName);
    client.println(outBuf);
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    sprintf(outBuf,"Content-Length: %u\r\n",strlen(data));
    client.println(outBuf);
    client.println(data);
  } else {
    Serial.println("Connection Failed.");  
  }
  
  client.stop();

  delay(2000);
}
