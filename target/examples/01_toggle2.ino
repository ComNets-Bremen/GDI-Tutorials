boolean is_on= true;
boolean last_btn= true;

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(10, INPUT_PULLUP);
}

void loop()
{
  if (!digitalRead(10) && last_btn) {
    is_on= !is_on;
  }

  last_btn= digitalRead(10);

  if (is_on) {
    analogWrite(11, 255);
  }
  else {
    analogWrite(11, 5);
  }

  delay(20);
}
