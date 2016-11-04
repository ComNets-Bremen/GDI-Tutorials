void setup()
{
  Serial.begin(9600);

  int day= 1;
  int month= 1;
  int year= 1970;

  float my_pi= 3.1416;

  Serial.println("I am Max Mustermann");

  Serial.print("born: ");
  Serial.print(day);
  Serial.print(".");
  Serial.print(month);
  Serial.print(".");
  Serial.println(year);

  Serial.print("Pi is: ");
  Serial.println(my_pi);
}

void loop()
{
}
