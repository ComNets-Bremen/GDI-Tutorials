#include <SoftwareSerial.h>
#include "DumbServer.h"

SoftwareSerial esp_serial(3, 2);
EspServer esp_server;

void setup()
{
  Serial.begin(9600);
  esp_serial.begin(9600);

  Serial.println("Staring server...");
  esp_server.begin(&esp_serial, "ssid", "pwd", 30303);
  Serial.println("...server is running");

  char ip[16];
  esp_server.my_ip(ip);

  Serial.print("My ip: ");
  Serial.println(ip);
}

void loop()
{
  if(esp_server.available()) {
    String command= esp_server.readStringUntil('\n');

    esp_server.print(">");
    esp_server.println(command);
  }
}
