<!--

                  Copyright (C)  2017  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

Serial io
=========

Using serial communication to
talk to the Arduino

---

_But first:_

solutions to the last assignment

---

Morse tree
==========

<p>
  <video poster="images/11_morse_flash.jpg" controls loop preload="none">
    <source src="images/11_morse_flash.mp4" type="video/mp4">
    <source src="images/11_morse_flash.webm" type="video/webm">
  </video>
</p>

[…][code_morse_sender]

The code above sends some special characters
to test the tree based decoder

---

Morse tree
==========

    !C
    struct morse_tree tree_N_with_donald_hair =
      {"Ñ", NULL, NULL};
    struct morse_tree tree_funny_hat_G =
      {"Ĝ", NULL, NULL};
    struct morse_tree tree_tick =
      {"'", NULL, NULL};

[…][code_morse_receiver]

The code above receives the morse code
and decodes it

---

LED Tree
========

    !C
    uint32_t now= millis();
    if(now >= next_tree) {
      …
      cur_node= random(2) ?
        cur_node->child_l : cur_node->child_r;
      digitalWrite(cur_node->pin, HIGH);
      …
    }

[…][code_humbug_tree]

Uses `millis()` instead of `delay()` to
meet timing requirements

---

_Back to serial io_

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
  <video poster="images/11_echo_conversation.jpg" controls preload="none">
    <source src="images/11_echo_conversation.mp4" type="video/mp4">
    <source src="images/11_echo_conversation.webm" type="video/webm">
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
  <video poster="images/11_reverse_conversation.jpg" controls preload="none">
    <source src="images/11_reverse_conversation.mp4" type="video/mp4">
    <source src="images/11_reverse_conversation.webm" type="video/webm">
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
  <video poster="images/11_rot13_conversation.jpg" controls preload="none">
    <source src="images/11_rot13_conversation.mp4" type="video/mp4">
    <source src="images/11_rot13_conversation.webm" type="video/webm">
  </video>
</p>

---

Regular expressions
===================

`[Mm][Aa]{1,10}(tch|gic)`

<span style="color: #859900">Maaaagic</span>
<span style="color: #997C00">match</span>ing machine

---

Regular expressions
===================

    Michael Corner, @edgesncorners
    Dean Thomas, @magic_dean
    Sue Li, @sureli
    Demelza Robins, dem@magic.com
    Susan Bones, sbones@minimagic.gov.uk

[…][file_students]

The list above contains Names and different kinds of contact
informations

---

Terminal basics
===============

Open a terminal/console/powershell window

<p>
  <video poster="images/11_wget.jpg" controls preload="none">
    <source src="images/11_wget.mp4" type="video/mp4">
    <source src="images/11_wget.webm" type="video/webm">
  </video>
</p>

Use wget to download the file linked in the previos
slide

---

grep
====

On Linux/macOS the [`grep`][man_grep]
command can be used to find lines in files that match
a regular expression

Windows users can try the [`sls`][man_sls] command
or a web based regular expression tester

---

grep
====

The general syntax is

Linux/macOS: `$ grep -E "regular expression" filename`

Windows: `PS C:\> sls "regular expression" filename`

<p>
  <video poster="images/11_grep.jpg" controls preload="none">
    <source src="images/11_grep.mp4" type="video/mp4">
    <source src="images/11_grep.webm" type="video/webm">
  </video>
</p>

The example above searches for all lines that contain
a twitter handle as contact info

---

grep
====

Using the lecture slides and other ressources
write regular expressions that match on lines
that contain …

- … an email address
- … a telephone number
- … an UK based telephone number
- … surnames between 1 and 5 characters long
- … email address on a .uk domain


[code_morse_sender]: examples/11_morse_sender.ino
[code_morse_receiver]: examples/11_morse_receiver.ino

[code_humbug_tree]: examples/11_humbug_tree.ino

[code_echo]: examples/11_echo.ino
[code_reverse]: examples/11_reverse.ino
[code_rot13]: examples/11_rot13.ino

[file_students]: examples/11_students.txt

[man_grep]: https://linux.die.net/man/1/grep
[man_sls]: https://msdn.microsoft.com/en-us/powershell/reference/5.1/microsoft.powershell.utility/select-string
