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

  digitalWrite(leds[0], defcon <= 255);
  digitalWrite(leds[1], defcon > 255 && defcon <= 767);
  digitalWrite(leds[2], defcon > 768);
}
