#include <SoftwareSerial.h>

SoftwareSerial SSerial(8, 7); // Arduino RX, Arduino TX

// the setup routine runs once when you press reset:
void setup()
{
  // initialize serial communication at 9600 bits per second:
  SSerial.begin(9600);  // software serial port
}

// the loop routine runs over and over again forever:
void loop()
{
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  // print out the value you read:
  SSerial.write(sensorValue/4);
  delay(1);        // delay in between reads for stability
}
