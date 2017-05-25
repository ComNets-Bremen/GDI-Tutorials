#include <SoftwareSerial.h>
#include "DumbServer.h"

/* The WiFi shield is connected to
 * the Arduino pins 3 and 2, as the
 * Arduino has only one hardware serial
 * port (pins 0 and 1) we are using a
 * serial port emulated in software. */
SoftwareSerial esp_serial(3, 2);
EspServer esp_server;

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
   * to pin 0 of the other Arduino and use the Serial monitor
   * to see the Wifi commands and error-messages. */
  Serial.println("Staring server...");
  esp_server.begin(&esp_serial, "GDI", "password", 30303);
  Serial.println("...server is running");


  /* Get and print the IP-Address the python program
   * should connect to */
  char ip[16];
  esp_server.my_ip(ip, 16);

  Serial.print("My ip: ");
  Serial.println(ip);
}

void loop()
{
  // Check if the python program sent commands
  if(esp_server.available()) {
    // Read one line of commands
    String command= esp_server.readStringUntil('\n');

    // Echo back the command as-is
    esp_server.print(">");
    esp_server.println(command);
  }
}
