<!--

                  Copyright (C)  2017  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

ATuino
======

In this tutorial we are going to remotely
control an Arduino from a python-script

The hardware-components will be modeled in
an object-oriented manner to provide a
nice and reusable interface

---

atuino.ino
==========

In order to remotely control the Arduino
it has to be flashed with a firmware that accepts
and executes commands

    !C
    at_commands[] = {
      {.name= "AT",            .cb= atcb_at},
      {.name= "AT+SET_OUT",    .cb= atcb_setout},
      {.name= "AT+SET_IN",     .cb= atcb_setin},
      …
      {.name= NULL, .cb=NULL}
    };

[…][code_atuino_ino]

The sketch above accepts AT-style commands
that can be used to read and write digital pins

---

atuino.ino
==========

Upload the sketch from the previous slide to
your Arduino and configure the
[serial monitor][ref_serial_monitor]
to send a carriage return `␍` and a newline `␊`
character at the end of each line, and to
use a speed of `115200 Baud`

    AT+SET_OUT=13
    AT+WRITE_HIGH=13

Enter the commands above into the serial monitor
to turn on the Arduino on-board LED

The Arduino should
acknowledge both commands with an `OK`
and turn on the LED

---

atuino.ino
==========

Study the commands in the `at_commands` array

find the commands that let you read out the
`HIGH` or `LOW` state of pin `10`

Use a piece of wire to change the state of pin `10`

---

atduino.py
==========

    !Python
    duino= Arduino('/dev/ttyACM0')

    key1= InputPin(duino, 10, True)
    #led1= OutputPin(duino, 13)

[…][code_atuino_py]

The code above contains class definitions
that model the connection to an Arduino
and its input pins

Change `'/dev/ttyACM0'` to the name of
your serial port, run the program and
observe its output

_Hint:_ You can use the
[Arduino IDE][img_port_name] to find the
name of your serial port

---

class OutputPin
===============

Write a class `OutputPin` that, analogous to
the class `InputPin`, models an output pin

The class should provide a method
`set_state` that turns the output
on or off

When you are done, uncomment the commented-out lines,
to verify that your implementation
works as expected

_Hint:_ you can use the interactive commandline
to test your implementation `python3 -i 16_atuino.py`

---

Complete Example
================

    !Python
    class OutputPin(object):
        def set_state(self, state):
            self.arduino.exec_cmd(
                'WRITE_HIGH' if state else 'WRITE_LOW',
                self.pin_no
            )

[…][code_atuino_complete_py]

[code_atuino_ino]: examples/16_atuino.ino
[code_atuino_py]: examples/16_atuino.py
[code_atuino_complete_py]: examples/16_atuino_complete.py

[img_port_name]: images/16_port_name.png

[ref_serial_monitor]: 11-serial-io.html#slide_11
