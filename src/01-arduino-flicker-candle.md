Arduino flicker Candle
======================

A LED controlled by an Arduino
to flicker like a candle.

---

First steps
===========

Connecting the LED and making it blink.

---

Connecting the LED
==================

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
it to the Arduino pin D11 instead.

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
`analogWrite`, `random` and `delay`
functions to create a nice looking
Candle animation.

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