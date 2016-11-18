int led_segments[]= {3, 4, 5, 6, 7, 8, 9, 10};
int binary_number= 0b10101010;

void setup() {
  for (int i=0; i<4; i++) {
    pinMode(led_segments[i], OUTPUT);
  }
}

void loop() {
  for (int i=0; i<4; i++) {
    digitalWrite(led_segments[i], binary_number /*TODO*/ (1<<i));
  }
}
