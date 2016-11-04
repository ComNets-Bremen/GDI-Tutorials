int leds[]= {9, 10, 11};

boolean states[4][3]= {
  {true,  true,  true},
  {false, false, true},
  {false, true,  false},
  {false, false, false}
};

void setup()
{
  for (int i=0; i<3; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  for (int phase=0; phase<4; phase++) {
    for (int lnum=0; lnum<3; lnum++) {
      digitalWrite(leds[lnum], states[phase][lnum]);
    }

    delay(3000);
  }
}
