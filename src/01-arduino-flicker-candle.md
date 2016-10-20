<!--

                  Copyright (C)  2016  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

Arduino flicker Candle
======================

A LED controlled by an Arduino
to flicker like a candle.

And can be turned on an off by a button.

---

Connecting an LED
=================

Put together the following circuit on your breadboards:

- Connect the Arduino 5V pin to one lead of a 1kΩ resistor.
- Connect the other lead of the resistor to one lead of the LED.
- Connect the other lead of the LED to the Arduino GND pin.

If the LED does not light you should try swapping its leads
around.

---

Controlling the LED (hardware)
==============================

Remove the connection to the Arduino 5V pin and attach
it to the Arduino pin 11 instead.

---

Controlling the LED (software)
==============================

Open the Arduino IDE, configure your Board and
enter the following program:

    !C
    void setup() {
      pinMode(11, OUTPUT);
    }

    void loop() {
      digitalWrite(11, HIGH);
      delay(500);
      digitalWrite(11, LOW);
      delay(500);
    }

---

Controlling the LED
===================

After uploading the program, the LED should
blink with a frequency of 1Hz.

---

Blinking faster
===============

The statement `delay(500)` in the uploaded program
determines how long the microcontroller should
wait between the LED state changes.

In the case above it waits 500ms.

Lets see what happens if we decrease both delays
by a factor of 100.

---

Blinking faster
===============

The Human eye does no longer perceive the LED as
blinking.

Instead the LED seems to be lit less brightly
than before.

By varying the proportion between the LED
beeing on and the LED beeing of how
bright the LED seems to be lit.

---

PWM
===

The Process of varying the on/off proportion
to change the perceived brightness is called
pulse width modulation [(PWM)][wiki_pwm].

The Microcontroller used on the Arduino
can also do PWM in hardware.

The corresponding function is rather missleadingly
called [`analogWrite(pin, value)`][arduino_analogwrite].

---

Hardware PWM
============

The following program will cycle through
different led brightnesses.

    !C
    void setup() {
      pinMode(11, OUTPUT);
    }

    void loop() {
      analogWrite(11, 0); delay(1000);
      analogWrite(11, 63); delay(1000);
      analogWrite(11, 127); delay(1000);
      analogWrite(11, 191); delay(1000);
      analogWrite(11, 255); delay(1000);
    }

---

Connecting a button
===================

- Connect one pin of a button to a GND pin of the Arduino
- Connect the other pin on the same side of the button to Arduino pin 10

---

Using the button
================

    !C
    void setup() {
      pinMode(11, OUTPUT);
      pinMode(10, INPUT_PULLUP);
    }

    void loop() {
      if (digitalRead(10)) {
        analogWrite(11, 255);
      }
      else {
        analogWrite(11, 5);
      }
      delay(100);
    }

---

Not !
=====

The LED gets dimmer when the button is pressed!
It was supposed to be the other way around!

Executing `pinMode(10, INPUT_PULLUP)` connects an internal
resistor to pin 10 pulling the voltage up <br/>
(`digitalRead(10) == 1`).

When the button is pressed the button shorts pin 10
to 0V (GND) <br/>
(`digitalRead(10) == 0`).

To invert the return value of `digitalRead` use <br/>
`if (!digitalRead(10)) {`.

---

Using the button (correctly)
============================

    !C
    void setup() {
      pinMode(11, OUTPUT);
      pinMode(10, INPUT_PULLUP);
    }

    void loop() {
      if (!digitalRead(10)) {
        analogWrite(11, 255);
      }
      else {
        analogWrite(11, 5);
      }
      delay(100);
    }

---

Toggling between states
=======================

    !C
    boolean is_on= true;
    void loop() {
      if (!digitalRead(10)) {
        is_on= !is_on;
      }
      if (is_on) {
        analogWrite(11, 255);
      }
      else {
        analogWrite(11, 5);
      }
    }

[…][code_toggle1]

---

Toggling more slowly
====================

The LEDs toggle between on and off
while the button is pressed.

We only want it to toggle once each time the
button is pressed.

⇒ We need to track the last button state.

[…][code_toggle2]

---

Randomness
==========

To simulate the random flickering of an actual
candle we need a source of randomness.

The Arduino environement supplies the
[`random(min, max)`][arduino_random] function for this case.

---

Randomness
==========

In the program below `rand_var` is randomly
set to either 10, 11, 12, 13 or 14* each time
`loop` is executed.

    !C
    void setup() {
    }

    void loop() {
      int rand_var= random(10, 15);
    }

\* The lower bound is inclusive.
The upper bound is exclusive.

---

Combining the functions
=======================

You can now try to combine the
`analogWrite`, `analogRead`, `random` and `delay`
functions to create a nice looking
Candle animation.

---

Working example
===============

    !C
    if (is_on) {
      analogWrite(11, random(10, 255));
      delay(random(0, 100));
    }
    else {
      analogWrite(11, 0);
    }

[…][code_candle]

---

Appendix
========

What happens when we click the _Upload_ button?

---

Compiling
=========

Firstly the textual representation of the
program is translated into a representation
the microcontroller understands.

    00000128 <main>:
    128:  87 b3   in      r24, 0x17       ; 23
    12a:  88 61   ori     r24, 0x18       ; 24
    12c:  87 bb   out     0x17, r24       ; 23
    12e:  30 d1   rcall   .+608           ; 0x390 <uart_init>

---

Uploading (Microcontroller)
===========================

Then the Computer instructs the microcontroller
on the Arduino to restart by setting the
special _RESET_ pin to 0V.

Upon startup a special program on the microcontroller
is executed.

This program is called the _bootloader_.
It flashes the LED on the Arduino board and
waits for programming instructions.

---

Uploading (Computer)
====================

The Computer then starts sending the compiled program
to the Arduino.

Once the upload is successfull the uploaded program
is started.

[wiki_pwm]: https://de.wikipedia.org/wiki/Pulsweitenmodulation#Aus_digitalen_Signalen "Wikipedia Pulsweitenmodulation"
[arduino_analogwrite]: https://www.arduino.cc/en/Reference/AnalogWrite
[arduino_random]: https://www.arduino.cc/en/Reference/Random
[code_toggle1]: data:text/plain;base64,Ym9vbGVhbiBpc19vbj0gdHJ1ZTsKCnZvaWQgc2V0dXAoKSB7CiAgcGluTW9kZSgxMSwgT1VUUFVUKTsKICBwaW5Nb2RlKDEwLCBJTlBVVF9QVUxMVVApOwp9Cgp2b2lkIGxvb3AoKSB7CiAgaWYgKCFkaWdpdGFsUmVhZCgxMCkpIHsKICAgIGlzX29uPSAhaXNfb247CiAgfQogIAogIGlmIChpc19vbikgewogICAgYW5hbG9nV3JpdGUoMTEsIDI1NSk7CiAgfQogIGVsc2UgewogICAgYW5hbG9nV3JpdGUoMTEsIDUpOwogIH0KfQ==
[code_toggle2]: data:text/plain;base64,Ym9vbGVhbiBpc19vbj0gdHJ1ZTsKYm9vbGVhbiBsYXN0X2J0bj0gdHJ1ZTsKCnZvaWQgc2V0dXAoKSB7CiAgcGluTW9kZSgxMSwgT1VUUFVUKTsKICBwaW5Nb2RlKDEwLCBJTlBVVF9QVUxMVVApOwp9Cgp2b2lkIGxvb3AoKSB7CiAgaWYgKCFkaWdpdGFsUmVhZCgxMCkgJiYgbGFzdF9idG4pIHsKICAgIGlzX29uPSAhaXNfb247CiAgfQogIAogIGxhc3RfYnRuPSBkaWdpdGFsUmVhZCgxMCk7CiAgCiAgaWYgKGlzX29uKSB7CiAgICBhbmFsb2dXcml0ZSgxMSwgMjU1KTsKICB9CiAgZWxzZSB7CiAgICBhbmFsb2dXcml0ZSgxMSwgNSk7CiAgfQogIAogIGRlbGF5KDIwKTsKfQ==
[code_candle]: data:text/plain;base64,Ym9vbGVhbiBpc19vbj0gdHJ1ZTsKYm9vbGVhbiBsYXN0X2J0bj0gdHJ1ZTsKCnZvaWQgc2V0dXAoKSB7CiAgcGluTW9kZSgxMSwgT1VUUFVUKTsKICBwaW5Nb2RlKDEwLCBJTlBVVF9QVUxMVVApOwp9Cgp2b2lkIGxvb3AoKSB7CiAgaWYgKCFkaWdpdGFsUmVhZCgxMCkgJiYgbGFzdF9idG4pIHsKICAgIGlzX29uPSAhaXNfb247CiAgfQogIAogIGxhc3RfYnRuPSBkaWdpdGFsUmVhZCgxMCk7CiAgCiAgaWYgKGlzX29uKSB7CiAgICBhbmFsb2dXcml0ZSgxMSwgcmFuZG9tKDEwLCAyNTUpKTsKICAgIGRlbGF5KHJhbmRvbSgwLCAxMDApKTsKICB9CiAgZWxzZSB7CiAgICBhbmFsb2dXcml0ZSgxMSwgMCk7CiAgfQogIAogIGRlbGF5KDIwKTsKfQ==
