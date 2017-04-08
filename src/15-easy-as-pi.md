<!--

                  Copyright (C)  2017  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

As easy as pi.py
================

Calculations and loops in python

---

for python
==========

`for`-loops in python operate on so-called
iterables, this makes them very versatile

Python provides a lot of iterables.
For now we will focus on `list`s, `range`s
and `str`ings

---

for python
==========

    !Python
    >>> for elem in range(4):
    >>>    print(elem)
    0
    1
    2

Ranges start at `0` and do not include the end

---

for python
==========

    !Python
    >>> fruits= ['apples', 'bananas', 'strawberries']
    >>> for fruit in fruits:
    >>>    print(fruit)
    apples
    bananas
    strawberries

`for` can also iterate over the elements of a list

---

for python
==========

    !Python
    >>> for letter in 'café':
    >>>    print(letter)
    c
    a
    f
    é

Strings in python 3 can handle special unicode characters

Strings are also iterables

---

notepad.exe
===========

<p>
  <video poster="images/15_text_editor.jpg" controls preload="none">
    <source src="images/15_text_editor.mp4" type="video/mp4">
    <source src="images/15_text_editor.webm" type="video/webm">
  </video>
</p>

Open a text editor and save the content of
the next slide in a file called `count.py`

Make sure that the editor does not add
a filename-extension like `.txt`

---

count.py
========

    !Python
    #!/usr/bin/env python3

    for i in range(10):
        print(i)

---

cmd.exe
=======

<p>
  <video poster="images/15_terminal.jpg" controls preload="none">
    <source src="images/15_terminal.mp4" type="video/mp4">
    <source src="images/15_terminal.webm" type="video/webm">
  </video>
</p>

Open a terminal window and use `cd`
to navigate to the directory where you
stored `count.py`

Type `python count.py` (on Windows) /
`python3 count.py` (on Linux) and
hit _enter⏎_ to execute `count.py`

_Hint:_ Use the _Tab⭾_ key to automatically complete
directory/file/program names

---

Division 10
===========

Edit `count.py` so that it outputs
the numbers from `0.0` to `0.9` in
steps of `0.1`

`0.0`

`0.1`

`0.2`

`0.3`

`0.4`

`...`

---

for for
=======

Edit `count.py` so that its output looks like
[this][example_two_counters] example

    x   y
    0.0 0.4
    0.0 0.5
    0.0 0.6
    0.0 0.7
    0.0 0.8
    0.0 0.9
    0.1 0.0
    0.1 0.1

---

thagoras.py
===========

Python has an exponentiation operator `b**e`

A square root is an exponentiation by ½

Thus, in python, the distance `d` between two
points in a cartesian coordinate system can be calculated as
`d= (x**2 + y**2)**0.5`

---

pi.py
=====

Add a variable `inside=0` to `count.py` that
is incremented by one whenever `(x**2 + y**2)`
is smaller than `1`

At the end of the program `print(inside*4/100)`

---

pi.py
=====

Decrease the step size from `0.1` to `0.001`

At the end of the program `print(inside*4/(1000**2))`

Try to recognize the number and find out why
it is the result of the calculation

[…][code_working_example]

[example_two_counters]: examples/15_two_counters.txt
[code_working_example]: examples/15_pi.py
