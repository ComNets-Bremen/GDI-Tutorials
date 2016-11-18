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

A countdown timer that could
be used in bad action movies.

---

The concept
===========

- Connect a seven segment display to
  your Arduino.

- Use binary operations to
  encode segemnt states.

- Display a hexadecimal count down.

---

Connecting the display
======================

eeeh. TODO

---

Selecting bits in a number
==========================

    !C
    int binary_number= 0b10101010; // 170 in binary

    void loop() {
      for (int i=0; i<3; i++) {
        digitalWrite(led_segments[i], binary_number /*TODO*/ (1<<i));
      }
    }

[…][code_slice_bits]

Replace `/*TODO*/` with an operator
so that the binary representation of
`binary_number` is displayed on the LEDs.

---

Displaying Symbols
==================

Replace `0b10101010` in the previous program
so that the number `1` is displayed on the
seven segment display.


[…][code_seg_table]

[code_slice_bits]: examples/03_slice_bits.ino
[code_seg_table]: examples/03_seg_table.ino