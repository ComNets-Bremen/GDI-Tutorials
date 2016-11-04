int leds[]= {9, 10, 11};

void setup()
{
  for (int i=0; i<3; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  int defcon= analogRead(A0);

  analogWrite(leds[0], max(255-abs(256-defcon), 0));
  analogWrite(leds[1], max(255-abs(512-defcon), 0));
  analogWrite(leds[2], max(255-abs(768-defcon), 0));
}
