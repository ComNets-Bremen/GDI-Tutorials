<!--

                  Copyright (C)  2017  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

Iterating
=========

Using generators/iterators in python

---

Generators
==========

    !Python
    def cubes(n):
        for i in range(n):
            yield(i*i*i)

    for c in cubes(11):
        print(c)

generators

- produce a stream of values
- do not produce complete result at once
- stop execution after producing a value

---

Generators
==========

Extend the previous example with `print` statements
before and after the `yield` statement to better understand
the program flow

---

Fibonacci
=========

    !Python
    a= 0
    b= 1

    print(a, b)

    for i in range(10):
        (a, b)= (b, a+b)

        print(b)

The program above prints the first 12 fibonacci
numbers

Write a generator function `def fibonacci(n)` that `yield`s the
first `n` fibonacci numbers

---

List(iter)
==========

In Python generators can be used in many places,
not just `for` loops.

You can, for example, use `list(fibonacci(n))` to get a list
of every value the generator yields

Calculate and print a list of the first 12 fibonacci numbers

There is also a `sum` function that calculates the sum of all
the values a generator yields

Use `sum` to print the sum of the first 12 fibonacci numbers

---

a for a in b
============

    !Python
    list(a*a for a in range(10))

    list(a for a in range(10) if a%2)

If a generator function can be expressed in a single line
it can be written as a list comprehension

Execute the list comprehensions above and find out what they do

---

checksum
========

Uni Bremen matriculation numbers contain a checksum
to detect typos

If you consider the digits

`a|b|c|d|e|f|s`<br/>
`4|0|2|9|6|8|5`

the checksum is calculated like this:

`s= (1*a + 2*b + 3*c + 4*d + 5*e + 6*f)%11`

---

checksum
========

    !Python
    num= 4019661
    dgts= list((num//10**i)%10 for i in range(6, -1, -1))

Using you newly-earned knowledge of list comprehensions:

what is the purpose of the above two lines?

---

checksum
========

    !Python
    acc= 0

    for (i, n) in enumerate(dgts[:6]):
        acc+= (i+1)*n

Given the for-loop above, that calulates the checksum:

use `sum` to write a list comprehension that calculates
the same result

---

checksum
========

    !Python
    def checksum(mat):
        digits= list(
            (mat//10**i)%10 for i in range(6, -1, -1)
        )

        csum= sum(
            (i+1)*n
            for (i, n)
            in enumerate(digits[:6])
        )%11

        return(csum == digits[-1])

The function above takes a matriculation number,
calculates the checksum and compares it to the one
in the number

---

csv
===

    !Python
    import csv

    reader= csv.reader(
        open('25_student_list.csv', 'r'),
        delimiter= ';'
    )

    for entry in reader:
        print(entry)

Download the [student list][data_student_list]
and run the above script in the same directory

Use `int` to convert the matriculation number field to
an integer and only print those lines that contain
a valid matriculation number

---

hexdump
=======

<pre style="font-size:0.6em">
Address   Hex                                               ASCII
00000000  0c 94 5f 00 0c 94 87 00  0c 94 87 00 0c 94 87 00  |.._.............|
00000010  0c 94 87 00 0c 94 87 00  0c 94 87 00 0c 94 87 00  |................|
00000020  0c 94 87 00 0c 94 87 00  0c 94 87 00 0c 94 87 00  |................|
00000030  0c 94 87 00 0c 94 87 00  0c 94 87 00 0c 94 87 00  |................|
00000040  0c 94 71 08 0c 94 87 00  0c 94 fa 02 0c 94 3d 03  |..q...........=.|
00000050  0c 94 87 00 0c 94 87 00  0c 94 87 00 0c 94 87 00  |................|
</pre>

When analyzing binary files hexdumps are an useful tool

they show the hexadecimal representation of every byte
in the file

---

HTML hexdump
=============

    !Python
    for (index, chunk) in to_chunks(binary, 16):
        as_hex= ' '.join(
            '{:02x}'.format(byte) for byte in chunk
        )

[…][code_html_hexdump]

Run the program above with this [binary file][data_binary]
and view the file it outputs

Look at the function `read_binary` and check the documentation
of `open` to find out what the parameters to the `open` call
mean and why they are used

Edit the program, so that 32 bytes are printed per line
instead of 16

Edit the program, so that the decimal representation of
each byte is printed instead of the hexadecimal representation

[data_student_list]: examples/25_student_list.csv
[code_html_hexdump]: examples/25_html_hexdump.py
[data_binary]: examples/25_flash_dump.bin
