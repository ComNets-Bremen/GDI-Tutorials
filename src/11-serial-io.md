Serial io
=========

Using serial communication to
talk to the Arduino

---

The serial port
===============

![Arduino UART-USB](images/11_arduino_uart_layout.svg)

Pins `0(RX)` and `1(TX)` are connected to
an USB-Serial converter

---

The serial port
===============

    high ─┐ ┌─────┐     ┌────────────┐ ┌───┐           ┌─
          │ │     │     │            │ │   │           │
    low   └─┘     └─────┘            └─┘   └───────────┘
    bit#   S 0 1 2 3 4 5 6 7 E        S 0 1 2 3 4 5 6 7 E

UART (Serial) is a simple communication protocol

it uses one wire to receive data (`RX`) and one wire
to transmit data (`TX`)

---

Serial.read()
=============

We used `Serial.print` and `Serial.println`
for Arduino ► Computer communication
(on the `TX` line)

Now we will use `Serial.read` for
Computer ► Arduino communication
(on the `RX` line)

`Serial.read()` returns a single character
or `-1` if no character was received

---

Echo
====

    !C
    void loop() {
      char buffer[256]= {'\0'};
      /* TODO */
      Serial.print(buffer);
    }

[…][code_echo]

The code linked above contains a `read_line` function
that reads a complete line from the serial port

---

Echo
====

use `read_line` to enable conversations like
the following:

<p>
  <video poster="images/11_echo_conversation.jpg" controls>
    <source src="images/11_echo_conversation.mp4" type="video/mp4">
  </video>
</p>

_Hint_: Configure serial monitor to send
newline characters

---

resrever txet
=============

    !C
    void reverse_string(char *orig, char*rev)
    {
      size_t orig_len= strlen(orig);
      size_t rev_idx= 0;
      size_t fwd_idx= orig_len-1;

      // TODO
    }

[…][code_reverse]

The code above contains a broken
`reverse_string` function

---

resrever txet
=============

repair `reverse_string` to enable conversations like
the following:

<p>
  <video poster="images/11_reverse_conversation.jpg" controls>
    <source src="images/11_reverse_conversation.mp4" type="video/mp4">
  </video>
</p>

---

rot13 pelcgb
============

    !C
    void rot13_string(char *orig)
    {
      for(size_t idx=0 ; orig[idx]; idx++) {
        char l= orig[idx];

        if(l >= 'a' && l <= 'z') {
          // TODO
        }
    }

[…][code_rot13]

The code above contains a broken rot13
"encryption" function

---

rot13 pelcgb
============

In rot13 every letter is replaced by
the letter 13 letters later in the alphabet

<p>
 <code>
  abcdefghijklmnopqrstuvwxyz<br/>
  ▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾<br/>
  nopqrstuvwxyzabcdefghijklm<br/>
 </code>
 <br/>
 <code>
  ABCDEFGHIJKLMNOPQRSTUVWXYZ<br/>
  ▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾▾<br/>
  NOPQRSTUVWXYZABCDEFGHIJKLM<br/>
 </code>
</p>

If applied twice rot13 yields the
original text

---

rot13 pelcgb
============

Fix the `rot13_string` function to enable conversations like
the following:

<p>
  <video poster="images/11_rot13_conversation.jpg" controls>
    <source src="images/11_rot13_conversation.mp4" type="video/mp4">
  </video>
</p>

---

Regular expressions
===================

`[Mm][Aa]{1,10}(tch|gic)`

<span style="color: #859900">Maaaagic</span>
<span style="color: #997C00">match</span>ing machine

[code_echo]: examples/11_echo.ino
[code_reverse]: examples/11_reverse.ino
[code_rot13]: examples/11_rot13.ino
