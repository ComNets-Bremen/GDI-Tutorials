#include <SoftwareSerial.h>

SoftwareSerial duino_net(2, 3);

int leds[]= {9, 10, 11};

void setup()
{
  for (int i=0; i<3; i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  duino_net.begin(9600);
}

void loop()
{
  if(duino_net.available()) {
    int defcon= duino_net.read() * 4;
    
    analogWrite(leds[0], max(255-abs(256-defcon), 0));
    analogWrite(leds[1], max(255-abs(512-defcon), 0));
    analogWrite(leds[2], max(255-abs(768-defcon), 0));
  }
}
