<!--

                  Copyright (C)  2017  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

Classy GUIs
===========

Using object oriented programming to
write better GUIs

---

OO GUI programming
==================

    !Python
    class ButtonsWindow(object):
        def __init__(self):
            self.setup_buttons()

        def run(self):
            self.window.mainloop()

[…][code_buttons_skeleton]

The code above contains an object oriented approach
to GUI programming

but it also contains a few errors and unimplemented
functionality

fix the program so that whenever a button is pressed
the corrseponding text is `print()`ed on the terminal

---

Working example
===============

    !Python
    class PrintingButton(object):
        def __init__(self, window, label):
            self.label= label
            self.button= tk.Button(
                window, text=label,
                command= self.on_pressed
            )
            self.button.pack()

        def on_pressed(self):
            print(self.label)

[…][code_buttons]

---

ATduino library
===============

Download and flash the atuino Arduino sketch
introduced in [tutorial 16][ref_atuino_ino]

Copy the content of the
[atuino python code][code_atuino_py]
into a file called `atuino.py`

Open a terminal, `cd` into the directory where
you saved the `atuino.py` file and type

`python` (on Windows) / `python3` (everywhere else)
to start an interactive python session

---

ATduino library
===============

    !Python
    >>> import atuino
    >>> arduino= atuino.Arduino('/dev/ttyACM0')
    >>> led= atuino.OutputPin(arduino, 13)
    >>> led.turn_on()
    >>> led.turn_off()

Enter the python statements above into the
interactive session, remember to replace
`/dev/ttyACM0` with the actual name of your
serial port

The `led.turn_on`/`led.turn_off` statements
should turn the on-board LED on/off

_Hint:_ You can use the
[Arduino IDE][img_port_name] to find the
name of your serial port

---

Port selector
=============

![Port selector UI](images/21_port_selector.png)

[This][code_lc_selector] program should provide a
drop-down menu to select a serial port
but some parts are missing, fix them

Once the program is fixed and you select the correct
port, the LEDs on your Arduino should flash

---

LED Buttons
===========

![LED Buttons](images/21_led_buttons.png)

[This][code_lc_button] program contains a working
drop-down list and displays buttons to control
the LEDs attached to the Arduino

The LED controlling part does not
work, find out why and fix the problem

---

Working example
===============

![LED Buttons](images/21_led_buttons.png)

[…][code_lc]

[code_buttons_skeleton]: examples/21_printing_buttons_skeleton.py
[code_buttons]: examples/21_printing_buttons.py
[code_atuino_py]: examples/21_atuino.py
[code_lc_selector]: examples/21_light_center_selector.py
[code_lc_button]: examples/21_light_center_button.py
[code_lc]: examples/21_light_center.py

[img_port_name]: images/16_port_name.png

[ref_atuino_ino]: 16-snekduino.html#slide_2
