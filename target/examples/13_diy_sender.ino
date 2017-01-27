void setup()
{
  pinMode(3, OUTPUT);
}

void uart_bit_send(boolean s)
{
  digitalWrite(3, s);
  delayMicroseconds(104);
}

void loop()
{
  uint8_t defcon= analogRead(A0) / 4;

  uart_bit_send(LOW);

  for(uint8_t b=0; b<8; b++) {
    uart_bit_send(defcon & 0x01);
    defcon>>=1;
  }
  
  uart_bit_send(HIGH);
  
  delay(10);
}
