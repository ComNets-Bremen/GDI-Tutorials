uint32_t factorial(uint32_t n)
{
  if(n==0) return(1);

  return(n*factorial(n-1));
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for(uint32_t i=0; i<=12; i++) {
    Serial.print(i);
    Serial.print("! = ");
    Serial.println(factorial(i));
  }

  delay(5000);
}
