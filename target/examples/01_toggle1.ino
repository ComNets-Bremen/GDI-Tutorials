void setup()
{
  pinMode(11, OUTPUT);
  pinMode(10, INPUT_PULLUP);
}

void loop()
{
  if (!digitalRead(10)) {
    is_on= !is_on;
  }

  if (is_on) {
    analogWrite(11, 255);
  }
  else {
    analogWrite(11, 5);
  }
}
