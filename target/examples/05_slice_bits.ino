int led_segments[]= {2, 3, 4, 5, 6, 7, 8, 9};
int binary_number= 0b10101010;

void setup()
{
  for (int i=0; i<8; i++) {
    pinMode(led_segments[i], OUTPUT);
  }
}

void loop()
{
  for (int i=0; i<8; i++) {
    digitalWrite(led_segments[i], binary_number /*TODO*/ (1<<i));
  }

  binary_number^= 0x80;
  delay(500);
}
