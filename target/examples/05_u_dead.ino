const int segment_pins[]= {
  2, 3, 4, 5, 6, 7, 8, 9, 10
};

const int wire_pins[]= {
  A2, A3, A4, A5
};

const uint8_t fail_segments[]= {
  0b11111111,
  0b10000000,
  0b10111110,
  0b10000000,
  0b11011110,
  0b10110000,
  0b11111001,
  0b11011110,
  0b10000000,
  0b11111111,
  0b10000000
};

const uint8_t sucess_segments[]= {
  0b10111110,
  0b10000000,
  0b10111000,
  0b10110000,
  0b10011100,
  0b11111001,
  0b10000000
};

/*
 * Hexadecimal numbers encoded for display
 * on a seven segment display
 */
const uint8_t hex_to_segments[]= {
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
  0b01110001  // F
};

/**
 * Display the binary encoded segments
 * in seg
 */
void display_segments(uint8_t seg)
{
  for (int i=0; i<8; i++) {
    digitalWrite(segment_pins[i], seg & (1<<i));
  }
}

/**
 * Repeat the fail animation
 * until the reset button is pressed.
 */
void fail_animation()
{
  for(;;) {
    for(int i=0; i<11; i++) {
      display_segments(fail_segments[i]);
    
      delay(500);
    }
  }
}

/**
 * Repeat the sucess animation
 * until the reset button is pressed.
 */
void sucess_animation()
{
  for(;;) {
    for(int i=0; i<7; i++) {
      display_segments(sucess_segments[i]);
    
      delay(500);
    }
  }
}

void setup()
{
  for(int seg=0; seg<8; seg++) {
    pinMode(segment_pins[seg], OUTPUT);
  }
  
  for(int seg=0; seg<4; seg++) {
    pinMode(wire_pins[seg], INPUT_PULLUP);
  }
}

void loop()
{
  for (int i=15; i>=0; i--) {
    display_segments(hex_to_segments[i]);
    
    /* The code in the following if statement is executed
     * when all wires are disconnected from GND.
     * 
     * Test the program with all wires connected to GND.
     * Then test the program with all wires disconnected.
     *
     * Then change the statement so that it is only
     * executed when only the second and the fourth wire
     * are disconnected from GND
     */
    if ( digitalRead(wire_pins[0]) &&
         digitalRead(wire_pins[1]) &&
         digitalRead(wire_pins[2]) &&
         digitalRead(wire_pins[3])) {
      sucess_animation();
    }
    
    delay(1000);
  }

  fail_animation();
}
