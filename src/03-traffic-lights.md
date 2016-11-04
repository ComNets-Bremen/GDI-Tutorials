<!--

                  Copyright (C)  2016  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

Arduino traffic lights
======================

A colorful status indicator using
three LEDs and an Arduino.

---

Connecting the LEDs
===================

We will be using the PWM enabled(~) Arduino pins
9, 10, 11.

![LED Setup](schematic/03_three_leds.svg)

---

Initializing the LEDs (naively)
===============================

How we would have initialized the
LED in the previous tutorial.

    !C
    void setup() {
      pinMode(9, OUTPUT);
      pinMode(10, OUTPUT);
      pinMode(11, OUTPUT);
    }

Three nearly identical lines?
What a waste of space!

---

Initializing the LEDs (cleverly)
================================

    !C
    int leds[]= {9, 10, 11};

    void setup() {
      for (int i=0; i<3; i++) {
        /* TODO */
      }
    }

Replace `/* TODO */` with a line
of code so that all leds will be set as output.

Use the `leds` array!

---

Initializing the LEDs (cleverly)
================================

    !C
    int leds[]= {9, 10, 11};

    void setup() {
      for (int i=0; i<3; i++) {
        pinMode(leds[i], OUTPUT);
      }
    }

Now the LED initialization only uses
four lines.

A reduction by -1 line!

---

Loops in loops
==============

    !C
    void loop()
    {
      for (int phase=0; phase<4; phase++) {
        for (int lnum=0; lnum<3; lnum++) {
          digitalWrite(leds[lnum], states[phase][lnum]);
        }

        delay(3000);
      }
    }

[…][code_loopinloop]

---

Arrays in arrays
================

    !C
    boolean states[4][3]= {
      {true,  true,  true},
      {false, false, true},
      {false, true,  false},
      {false, false, false}
    };

[…][code_loopinloop]

Download the .ino file above

Edit the `states` array to make
the LEDs light up in the following order:

<span style="color: red">red</span>
->
<span style="color: red">red</span>
and
<span style="color: yellow">yellow</span>
->
<span style="color: green">green</span>
->
<span style="color: yellow">yellow</span>

---

Traffic control (optional)
==========================

The phases on a traffic light are
not equally long.

Use the following array to control
the phase durations:

`int state_durations[]= {5000, 500, 2000, 1000};`

---

Code red! Code red!
===================

Traffic light like indicators can
also be used for more general
status signaling:

- <span style="color: green">Okay</span>
- <span style="color: yellow">Non critical failure</span>
- <span style="color: red">Shits on fire</span>

---

Rotary input
============

We will use a potentiometer as input
for our status indicator.

![Potentiometer](schematic/03_potentiometer.svg)

---

Analog read
===========

To read an analog value as produced by the
potentiometer `analogRead` can be used.

![Potentiometer](images/03_analogread_example.png)

To learn how `analogRead` works upload the
AnalogInOutSerial example to your Arduino.

---

Serial Monitor
==============

The example sends text output to the computer.

To view the output you can use Arduinos
Serial monitor.

![Serial monitor](images/03_serial_monitor_menu.png)

---

Analog read
===========

What does the example teach us?
-------------------------------

- Analog pin names are special: use A0 - A5 instead of e.g. 13
- `analogRead` returns values between 0 and 1023

---

Status indicator
================

Implement the following
`analogRead` value <-> led color
mapping:

- 0 - 255: <span style="color: green">green</span>
- 256 - 767: <span style="color: yellow">yellow</span>
- 768 - 1023: <span style="color: red">red</span>

Use an `int` variable to store the `analogRead` value.

Use `if` statements to to check the range
the value is in.

*Bonus*: Use `analogWrite` to gradually fade between
the led colors.

---

Working example
===============

    !C
    int defcon= analogRead(A0);

    if (defcon <= 255) {
      digitalWrite(leds[0], HIGH);
    }
    else {
      digitalWrite(leds[0], LOW);
    }

[…][code_defcon]

[(more compact example)][code_defcon_compact]

[(fading example)][code_defcon_fade]

---

Using serial communication
==========================

To use serial communication in your
program the Serial library has to be set up.

    !C
    void setup() {
      Serial.begin(9600);
    }

9600 is the transfer speed in
[Baud][wiki_baud].

9600 Baud is a safe (and super slow) default you should
use in your code.

---

Serial.print{,ln}
=================

To send text to the computer
you ca use the `Serial.print` and
`Serial.println` functions.

- `Serial.print()` - Send text or a value
- `Serial.println()` - Send text or a value and start a new line

---

Serial.print{,ln}
=================

Write a program in which you initialize the following
variables to your birthday:

`int year`, `int month`, `int day`.

Also initialize the variable `float my_pi`
to your estimation of the number π (3.14…).

Use statements like `Serial.print("Text")` and
`Serial.println(year)` to print a message in the
following format:

    I am <Name>,
    born <day>.<month>.<year>
    Pi is: <my_pi>

---

Working example
===============

    !C
    Serial.println("I am Max Mustermann");

    Serial.print("born: ");
    Serial.print(day);
    Serial.print(".");

[…][code_serial]

[wiki_baud]: https://en.wikipedia.org/wiki/Baud
[code_loopinloop]: examples/03_loopinloop.ino
[code_defcon]: examples/03_defcon.ino
[code_defcon_compact]: examples/03_defcon_compact.ino
[code_defcon_fade]: examples/03_defcon_fade.ino
[code_serial]: examples/03_serial.ino
