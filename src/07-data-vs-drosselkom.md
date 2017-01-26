Data vs. Drosselkom
===================

Using huffman coding and trees
to compress and decompress data

---

Backstory
=========

You are the new intern at a company
that collects sensor data from
remote places

Your company pays a lot of money per byte to
transfer the sensor data into your
datacenter

To impress your new boss you want to reduce
the amount of data that has to be transfered

---

Huffman coding
===============

Huffman coding is a method that
uses a known probability distribution of symbols
to encode messages with as few bits as possible

To generate the encodings of a huffman code
a binary tree structure is used

A Binary tree is a tree where each node
has exactly two children

On the next slide you will see the general
algorithm to generate a huffman tree

---

Huffman coding
==============

Sort the symbols by the probability of occurrence

<pre style="font-size:0.7em">
─(17.4%)─╼ 'E'
─(9.78%)─╼ 'N'
─(4.76%)─╼ 'H'
─(4.35%)─╼ 'U'
</pre>

---

Huffman coding
==============

Take the the two lowest ranking symbols and
combine them into a tree node

<pre style="font-size:0.7em">
─(17.4%)─╼ 'E'
─(9.78%)─╼ 'N'
         ╭─(4.76%)─╼ 'H'
─(9.11%)─┤
         ╰─(4.35%)─╼ 'U'
</pre>

---

Huffman coding
==============

Threat the node like a single symbol,
resort the list and create a new node

<pre style="font-size:0.7em">
          ╭─(9.78%)─╼ 'N'
─(18.89%)─┤
          │         ╭─(4.76%)─╼ 'H'
          ╰─(9.11%)─┤
                    ╰─(4.35%)─╼ 'U'
─(17.4%)─╼ 'E'
</pre>

---


Huffman coding
==============

Continue combining the lowest
ranking nodes

<pre style="font-size:0.7em">
                     ╭─(9.78%)─╼ 'N'
          ╭─(18.89%)─┤
          │          │         ╭─(4.76%)─╼ 'H'
          │          ╰─(9.11%)─┤
          │                    ╰─(4.35%)─╼ 'U'
─(36.29%)─┤
          ╰─(17.4%)─╼ 'E'
</pre>

---

Huffman coding
==============

Until you are left with a single
root node

<pre style="font-size:0.18em">
                                            ╭─(9.78%)─╼ 'N'
                                 ╭─(18.89%)─┤
                                 │          │         ╭─(4.76%)─╼ 'H'
                                 │          ╰─(9.11%)─┤
                                 │                    ╰─(4.35%)─╼ 'U'
                      ╭─(36.29%)─┤
                      │          ╰─(17.4%)─╼ 'E'
           ╭─(65.47%)─┤
           │          │                     ╭─(7.55%)─╼ 'I'
           │          │          ╭─(14.91%)─┤
           │          │          │          │                             ╭─(1.13%)─╼ 'Z'
           │          │          │          │                   ╭─(1.92%)─┤
           │          │          │          │                   │         ╰─(0.79%)─╼ 'P'
           │          │          │          │         ╭─(3.81%)─┤
           │          │          │          │         │         ╰─(1.89%)─╼ 'W'
           │          │          │          ╰─(7.36%)─┤
           │          │          │                    │         ╭─(1.89%)─╼ 'B'
           │          │          │                    ╰─(3.55%)─┤
           │          │          │                              ╰─(1.66%)─╼ 'F'
           │          ╰─(29.18%)─┤
           │                     │          ╭─(7.27%)─╼ 'S'
           │                     ╰─(14.27%)─┤
           │                                ╰─(7.0%)─╼ 'R'
─(110.31%)─┤
           │                                ╭─(6.51%)─╼ 'A'
           │                     ╭─(13.01%)─┤
           │                     │          │         ╭─(3.44%)─╼ 'L'
           │                     │          ╰─(6.50%)─┤
           │                     │                    ╰─(3.06%)─╼ 'C'
           │          ╭─(24.72%)─┤
           │          │          │          ╭─(6.15%)─╼ 'T'
           │          │          ╰─(11.71%)─┤
           │          │                     │         ╭─(3.01%)─╼ 'G'
           │          │                     ╰─(5.56%)─┤
           │          │                               │                   ╭─(0.67%)─╼ 'V'
           │          │                               │         ╭─(1.34%)─┤
           │          │                               │         │         │                   ╭─(0.27%)─╼ 'J'
           │          │                               │         │         │         ╭─(0.36%)─┤
           │          │                               │         │         │         │         │                   ╭─(0.03%)─╼ 'X'
           │          │                               │         │         │         │         │         ╭─(0.05%)─┤
           │          │                               │         │         │         │         │         │         ╰─(0.02%)─╼ 'Q'
           │          │                               │         │         │         │         ╰─(0.09%)─┤
           │          │                               │         │         │         │                   ╰─(0.04%)─╼ 'Y'
           │          │                               │         │         ╰─(0.67%)─┤
           │          │                               │         │                   ╰─(0.31%)─╼ 'ß'
           │          │                               ╰─(2.55%)─┤
           │          │                                         ╰─(1.21%)─╼ 'K'
           ╰─(44.84%)─┤
                      │                     ╭─(5.08%)─╼ 'D'
                      │          ╭─(10.12%)─┤
                      │          │          │         ╭─(2.53%)─╼ 'M'
                      │          │          ╰─(5.04%)─┤
                      │          │                    ╰─(2.51%)─╼ 'O'
                      ╰─(20.12%)─┤
                                 ╰─(10.0%)─╼ ' '
</pre>

[…][full_de_tree]

[huffman_tree.py][code_tree_gen]

---

Huffman coding
==============

To get a binary encoding each side
of a branch is assigned a '0' or '1'

<pre style="font-size:0.7em">
       ╭─(1)─╼ 'N'
 ╭─(1)─┤
 │     │     ╭─(1)─╼ 'H'
 │     ╰─(0)─┤
 │           ╰─(0)─╼ 'U'
─┤
 ╰─(0)─╼ 'E'
</pre>

In the example above the encodings would be:

    'E': 0, 'N': 11, 'H': 101, 'U': 100

_Observation:_ No encoding is the prefix
of another encoding!

---

Compressing sensor data
=======================

Sensor data that is sampled often enough
is often mostly constant

![Sensor data](images/07_sensor_data.svg)

To store the values above we
would usually use a 16 bit wide variable
per sample

We want to reduce that for transfer

---

Compressing (Idea #1)
=====================

We only transfer the difference between
the current and the last value

![Sensor data Derivate](images/07_sensor_data_deriv.svg)

Now most values are very close to zero

---

Compressing (Idea #2)
=====================

We know that values close to zero
are more likely to occur

We can use huffman coding to
reduce the average number
of bits we have to transfer!

---

Difference compression
======================

Assume that the difference values
between two subsequent samples are known to have
the following probability distribution:

    Value │ Probability
    ──────┼────────────
       -2 │   9%
       -1 │  19%
        0 │  40%
        1 │  18%
        2 │  13%

Construct a huffman tree from the table
above (on paper)

---

Difference tree
===============


<pre style="font-size:0.7em">
                                ╭─(19%)─╼ -1
                     ╭─(37.00%)─┤
                     │          ╰─(18%)─╼ 1
          ╭─(59.00%)─┤
          │          │          ╭─(13%)─╼ 2
          │          ╰─(22.00%)─┤
          │                     ╰─(9%)─╼ -2
─(99.00%)─┤
          ╰─(40%)─╼ 0
</pre>

[…][full_difference_tree] [.py][code_tree_diff]

---

Assigning numbers
=================

<pre style="font-size:0.7em">
             ╭─(1)─╼ -1
       ╭─(1)─┤
       │     ╰─(0)─╼ 1
 ╭─(1)─┤
 │     │     ╭─(1)─╼ 2
 │     ╰─(0)─┤
 │           ╰─(0)─╼ -2
─┤
 ╰─(0)─╼ 0
</pre>

_Observation:_ For every measured value that does not differ
from the previous value (difference zero)
only a single bit has to be transfered

---

Using a tree in C
=================

To encode a tree structure in C
a `struct` like the following can be used

    !C
    struct hm_node_t {
      int16_t value;

      struct hm_node_t *child_0;
      struct hm_node_t *child_1;
    };

Each node can either have two children (branch node)
or a value (leaf node)

---

Using a tree in C
=================

    !C
    struct hm_node_t node_ch0 =
      {.value= 0,
       .child_0= NULL, .child_1= NULL};

    struct hm_node_t node_root =
      {.value= HM_NOVAL,
       .child_0= &node_ch0, .child_1= &node_ch1};

The tree structure is then encoded
using references to other nodes

[…][code_compression]

---

Using the huffman codes
=======================

Download the [example][code_compression]
program from the previous slide

Upload it to your arduino
and look at its output on the
[serial monitor][serial_monitor]

---

Using the huffman codes
=======================

Edit the `sequence` variable at the top
of the program so that the following output
is produced on the serial monitor:

    Start walking
    Accumulator: 0
    Accumulator: 2
    Accumulator: 4
    Accumulator: 3
    Accumulator: 2

_Hint:_ The program uses the encoding
developed on the previous slides

---

lshalfslide
===========

Permission is granted to copy, distribute and/or modify this
document under the terms of the GNU Free Documentation License,
Version 1.3 or any later version published by the Free Software
Foundation; with no Invariant Sections, no Front-Cover Texts, and
no Back-Cover Texts.

[source code](https://github.com/hnez/GdiTutorials)


[full_de_tree]: examples/07_huffman_tree.html
[code_tree_gen]: examples/07_huffman_tree.py

[full_difference_tree]: examples/07_difference_tree.html
[code_tree_diff]: examples/07_difference_tree.py

[code_compression]: examples/07_compression.ino

[serial_monitor]: 03-traffic-lights.html#slide_12
