<!--

                  Copyright (C)  2017  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

WiFi
====

Connecting Arduinos to the internet

---

ESP8266
=======

To connect the Arduinos to a WiFi network
we will be using ESP8266 shields

We will be using [AT commands][www_espressiv_at]
to control the ESPs

The ESP8266 chips could also be programmed
directly as they contain a microcontroller that
is much more powerful than the Arduino

_Do not_ reflash the ESP shields provided
in the course

---

Testing the shields

---

Testing
=======

To check if your shield is working correctly
disconnect the USB-cable from your Arduino

    !C
    esp_client.begin(
        &esp_serial, "GDI", "password",
        "192.168.42.42", 30303
    );

and copy [this][code_rgb_ino] program into the
Arduino IDE, scroll down to the setup function
and adapt the IP address to one provided by
your tutor

---

Testing
=======

Connect the RGB-Led to the pins on the WiFi-shield
that will be plugged into the following Arduino pins:

<span style="color: rgb(234, 58, 58);">R</span> - 9 /
<span style="color: rgb(161, 206, 76);">G</span> - 10 /
<span style="color: rgb(53, 164, 225);">B</span>  - 11 /
GND - GND

Carefully plug the WiFi-shield into your Arduino
and reconnect the USB-cable

---

Testing
=======

    !Python
    self.coro= aio.start_server(
        self.handle_client,
        None,
        30303,
        loop= self.loop
    )

Your Tutor is running [this][code_rgb_py] program,
it provides a TCP-server for your Arduino to connect
to

It then sends periodic color updates to every
Arduino connected

---

The test code on the previous slides used a python server
and an Arduino client

`Arduino ---connects to--> Python`

To prevent issues with firewalls and [NAT][www_wiki_nat]s
from now on the Arduino will act as a server
and the python code will connect to it

`Python ---connects to--> Arduino`

---

The following slides will provide you with an
Arduino library to use the WiFi shield as a
Server

The library allows exactly one connection
and does not perform any error checking,
this is why it is called `DumbServer`

---

DumbServer.cpp
==============

![Arduino new Tab](images/22_arduino_new_tab.png)

Use the "New Tab" option in the Arduino IDE to create
the files `DumbServer.h` and `DumbServer.cpp`

Paste the contents of [`DumbServer.h`][code_dumb_server_h] /
[`DumbServer.cpp`][code_dumb_server_cpp] into the respective
files

Paste the content of [`ServerExample.ino`][code_server_example]
into the main sketch file

---

DumbServer.cpp
==============

Flash the sketch to your Arduino and open the Serial Monitor

`Starting server...`

`...server is running`

`My ip: 192.168.42.123`

If the ESP was able to connect to the WiFi access point
the Serial Monitor should display a message like the one above

We will be needing the IP-address that is shown later on

---

socket.py
=========

Open an interactive python session and
enter the following commands

Replace the IP-address with the one
found previously

    !Python
    import socket

    s= socket.socket()
    s.connect(('192.168.42.123', 30303))
    s.setblocking(False)

    s.send(b'Hello World\n')

    s.recv(1024)

Check if the observed behaviour matches
the Arduino sketch

---

On the following slides you will see
an example on how to work with
sockets in a graphical program

---

sockets & GUIs
==============

    !C
    if(esp_server.available()) {
        String command= esp_server.readStringUntil('\n');
        digitalWrite(13, (command == "on") ? HIGH : LOW);
    }

[…][code_lc_ino]

Flash the code above onto your Arduino

Connect Arduino pin 13 to an LED and pin 12
to GND

_Note:_ `DumbServer.h`/`.cpp` are needed to compile
the program

---

sockets & GUIs
==============

<img style="height: 5em" alt="Light Center" src="images/22_light_center.png" />

    $ python3 22_light_center.py
    Hostname: 192.168.42.123
    Port: 30303

Run the [GUI code][code_lc_py] and provide
it with the correct IP-address



[code_rgb_ino]: examples/22_rgb_demo.ino
[code_rgb_py]: examples/22_rgb_demo.py

[code_dumb_server_h]: examples/22_dumb_server.h
[code_dumb_server_cpp]: examples/22_dumb_server.cpp
[code_server_example]: examples/22_server_example.ino

[code_lc_ino]: examples/22_light_center.ino
[code_lc_py]: examples/22_light_center.py

[www_espressiv_at]: https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
[www_wiki_nat]: https://en.wikipedia.org/wiki/Network_address_translation
