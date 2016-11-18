<!--

                  Copyright (C)  2016  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

Action movie bomb
=================

Building an action movie like
detonator circuit countdown timer.

---

The concept
===========

Connect a seven segment display to
your Arduino.

Use binary operations to
encode symbols.

Display a hexadecimal countdown.

---

Connecting the display
======================

![Display Setup](schematic/05_seven_segments.svg)

Use 1kΩ resistors to limit the LED currents.

Make sure the pin numbers match
the ones in the diagram.

---

Slicing bits
============

    !C
    // 170 in binary:
    int binary_number= 0b10101010;

    void loop() {
      for (int i=0; i<8; i++) {
        digitalWrite(led_segments[i],
                     (binary_number /*TODO*/ (1<<i))!=0);
      }
    }

[…][code_slice_bits]

Replace `/*TODO*/` with an operator
so that the binary representation of
`binary_number` is displayed on the LEDs.

---


Observation:
============

The & (binary and) operator
can be used to apply a bit mask.

      0b01010101
    & 0b00001111
    = 0b00000101

      0x55
    & 0xf0
    = 0x50

---

Displaying Symbols
==================

Edit the constant `binary_number` in the previous program
so that the number `1` is displayed on the
seven segment display.

---

The final countdown
===================

On the following slides we will
build a hexadecimal countdown timer
using the segment encoding developed earlier.

    !C
    uint8_t hex_to_segments[]= {
      //.GFEDCBA
      0b00111111, // 0
      ...
      0b01110001, // F
    };

[…][code_seg_table]

---

The final countdown
===================

Download the skeleton program
on the previous slide.

Replace `/* TODO */` with
code that displays a hex countdown
on the display and stops at zero.

`F E D C A 9 8 … 2 1 0` … _BOOM?_

_Optional:_ when the countdown
is done display the following number sequence
in hexadecimal:
`13, 14, 10, 13`.

---

Wirecutter
==========

![Wire diagram](schematic/05_red_wire.svg)

Connect pins `A2` to `A5` to GND.

---

Wirecutter
==========

    !C
    if ( digitalRead(wire_pins[0]) &&
         digitalRead(wire_pins[1]) &&
         digitalRead(wire_pins[2]) &&
         digitalRead(wire_pins[3])) {
      sucess_animation();
    }

[…][code_u_dead]

Edit the program above according to
the comment in the loop function.

Use the reset button on the arduino
to restart the program.

[Working example][code_u_dead_simple]

---

Extra task
==========

Wirecutter 1337
---------------

    !C
    if (wires & 10) fail_animation();
    if (!(wires ^ 5)) sucess_animation();

[…][code_u_dead_pro]

Try beating the program above
_without dying_.

[code_slice_bits]: examples/05_slice_bits.ino
[code_seg_table]: examples/05_seg_table.ino
[code_u_dead]: examples/05_u_dead.ino
[code_u_dead_simple]: examples/05_u_dead_simple.ino
[code_u_dead_pro]: examples/05_u_dead_pro.ino