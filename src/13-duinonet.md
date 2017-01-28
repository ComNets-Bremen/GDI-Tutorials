<!--

                  Copyright (C)  2017  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

Arduino Network
===============

Connecting Arduinos using
`SoftwareSerial`

---

Remote status monitor
=====================

![LED Setup](schematic/03_three_leds.svg)

In [tutorial three][ref_tut3] we used
three LEDs, a potentiometer and an Arduino
as a status indicator

Now we want to implement the same
functionality using two Arduinos

---

Preparation
===========

![Potentiometer](schematic/03_potentiometer.svg)

Connect the LEDs and Potentiometer
as described in [tutorial three][ref_tut3]

Verify that the hardware setup works
using one of the working [code examples][ref_tut3_status]

---

Two Arduinos
============

![Two Arduinos](schematic/13_two_arduinos.svg)

For the next tasks we will need two Arduinos

Assemble in groups and decide who will
write code for the
[sending][jmp_sender] /
[receiving][jmp_receiver] unit

---

The Sender
==========

The sending unit should take the
analog values from the potentiometer,
encode them and transfer them using
`SoftwareSerial` on pins `2` and `3`

Use the code from [tutorial three][ref_tut3_status]
and the code from the [lecture][code_soft_writer]
as a reference

_Hint_: You can still use `Serial.print`
for debugging

---

The Receiver
============

The receiving unit should read values
using `SoftwareSerial` on pins `2` and `3`,
decode them and turn
on the corresponding LEDs

Use the code from [tutorial three][ref_tut3_status]
and the code from the [lecture][code_soft_reader]
as a reference

_Hint_: You can still use `Serial.print`
for debugging

---

Working Example
===============

<p>
  <video poster="images/13_two_arduino_demo.jpg" controls loop preload="none">
    <source src="images/13_two_arduino_demo.mp4" type="video/mp4">
  </video>
</p>

[Sender][code_sender] / [Receiver][code_receiver]

---

DIY Serial.write (optional)
---------------------------

    high ─┐ ┌─────┐     ┌──────
          │ │     │     │
    low   └─┘     └─────┘
    bit#   S 0 1 2 3 4 5 6 7 E

The baud rate is the number of symbols
that are transmitted per second

A symbol can be the start bit, a data bit,
a stop bit or a parity bit

The defaults are 9600Bd, one start bit, eight data
bits, no parity bit and one stop bit

---

DIY Serial.write
================

    high ─┐ ┌─────┐     ┌──────
          │ │     │     │
    low   └─┘     └─────┘
    bit#   S 0 1 2 3 4 5 6 7 E

Write a sender that uses `digitalWrite` and
`delayMicroseconds` to transfer the data

_Hint_: The following slides contain more hints
should you get stuck

---

Hint #1
=======

    !C
    pinMode(3, OUTPUT);
    digitalWrite(3, s);

The software serial port
used pin 3 as `TX` line,

this is where data should be sent

---

Hint #2
=======

    !C
    void uart_bit_send(boolean s)
    {
      digitalWrite(3, s);
      delayMicroseconds(104);
    }

9600 Symbols are transmitted per second,

this means that the transmission of one
symbol takes 1s/9600 ≈ 104µs

---

Hint #3:
========

    !C
    uart_bit_send(LOW);
    // Transfer data
    uart_bit_send(HIGH);

The transmissions start with a 0 (start bit)
and ends with a 1 (stop bit)

---

Working example
===============

    !C
    uart_bit_send(LOW);
    for(uint8_t b=0; b<8; b++) {
      uart_bit_send(defcon & 0x01);
      defcon>>=1;
    }
    uart_bit_send(HIGH);

[…][code_diy_sender]

[ref_tut3]: 03-traffic-lights.html
[ref_tut3_status]: 03-traffic-lights.html#slide_15

[jmp_sender]: #slide_5
[jmp_receiver]: #slide_6

[code_soft_writer]: examples/13_soft_serial_writer.ino
[code_soft_reader]: examples/13_soft_serial_reader.ino

[code_sender]: examples/13_sender.ino
[code_receiver]: examples/13_receiver.ino
[code_diy_sender]: examples/13_diy_sender.ino
