int segment_pins[]= {
  2, 3, 4, 5, 6, 7, 8, 9, 10
};

uint8_t hex_to_segments[]= {
  //.GFEDCBA
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  0b01110111, // A
  0b01111100, // B
  0b00111001, // C
  0b01011110, // D
  0b01111001, // E
  0b01110001, // F
};

void display_segments(uint8_t seg)
{
  for (int i=0; i<8; i++) {
    digitalWrite(segment_pins[i], seg & (1<<i));
  }
}

void setup()
{
  for(int seg=0; seg<8; seg++) {
    pinMode(segment_pins[seg], OUTPUT);
  }
}

void loop()
{
  /* TODO */

  // display_segments(hex_to_segments[???]);
}
