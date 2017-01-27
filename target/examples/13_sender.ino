#include <SoftwareSerial.h>

SoftwareSerial duino_net(2, 3);

void setup()
{
  duino_net.begin(9600);
}

void loop()
{
  int defcon= analogRead(A0);

  duino_net.write(defcon/4);
  
  delay(10);
}
