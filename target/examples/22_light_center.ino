#include <SoftwareSerial.h>
#include "DumbServer.h"

/* The WiFi shield is connected to
 * the Arduino pins 3 and 2, as the
 * Arduino has only one hardware serial
 * port (pins 0 and 1) we are using a
 * serial port emulated in software. */
SoftwareSerial esp_serial(3, 2);
EspServer esp_server;

bool last_button= false;
bool last_connected= false;

void setup()
{
  Serial.begin(9600);
  esp_serial.begin(9600);

  /* Connect to the wireless network with the name "GDI"
   * and password "password", change these to match
   * your wifi settings.
   *
   * If anything fails begin() will not return.
   *
   * To debug possible problems you can flash a second
   * Arduino with the "Bare Minimum" example,
   * connect the GNDs of the two Arduinos,
   * connect pin 3 or 2 of the Arduino with the Wifi-shield
   * to pin 1(TX) of the other Arduino and use the Serial monitor
   * to see the Wifi commands and error-messages. */
  Serial.println("Starting server...");
  esp_server.begin(&esp_serial, "GDI", "password", 30303);
  Serial.println("...server is running");


  /* Get and print the IP-Address the python program
   * should connect to */
  char ip[16];
  esp_server.my_ip(ip, 16);

  Serial.print("My ip: ");
  Serial.println(ip);

  pinMode(13, OUTPUT);
  pinMode(12, INPUT_PULLUP);
}

void loop()
{
  // Check if the python program sent commands
  while(esp_server.available()) {
    // Read one line of commands
    String command= esp_server.readStringUntil('\n');

    digitalWrite(13, (command == "on") ? HIGH : LOW);
  }

  bool cur_button= digitalRead(12);
  bool cur_connected= esp_server.connected();

  if(cur_connected && (cur_button != last_button || !last_connected)) {
    esp_server.println(cur_button ? "high" : "low");
  }

  last_button= cur_button;
  last_connected= cur_connected;
}
