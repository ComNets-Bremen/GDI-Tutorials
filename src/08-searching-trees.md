Searching trees
===============

Find tree structures and
use them to access data more
elegantly

---

But first:

possible solutions
for the last assignment

---

Task 1
======

An array of strings
-------------------

    !C
    char *month_names[]= {
      "January",
      "February",
      "March",
      ...
    }

[…][code_assignment_3_1]

---

Task 2
======

An array of structs
-------------------

    !C
    struct month_info_t {
      char *name;
      uint8_t num_days;
    };

    struct month_info_t month_info[]= {
      {.name= "January",   .num_days= 31},
      …
    }

[…][code_assignment_3_2]

---

Task 3
======

Birthday countdown
------------------

    !C
    struct date_t pivot;
    struct date_t birthday;

    for(;;) {
      uint16_t days_next_bd=
        date_days_between(&pivot, &birthday);
      date_print(&pivot);
      date_increment(&pivot);
    }

[…][code_assignment_3_3]

---

Task 4
======

Pointerized countdown

    !C
    struct date_t {
      uint8_t day_of_month;
      struct month_info_t *month;
    };

[…][code_assignment_3_4]

---

Back to the trees

---

Guess game
==========

    !C
    if(num_cur_guess == num_to_guess)
      Serial.print("Your guess is correct!");

    if(num_cur_guess < num_to_guess)
      Serial.print("too small");

    if(num_cur_guess > num_to_guess)
      Serial.print("too big");


[…][code_guess_game]

Upload the example above and follow
the instructions in the [serial monitor][serial_monitor]

_Hint:_ Add a `.` or another symbol
after the numbers you enter

_Hint:_ The number is between 0 and 31

---

Strategy #1
===========

<pre style="font-size:0.7em">
Enter an estimate for the random number:
Your guess (1) is too small try again
Enter an estimate for the random number:
Your guess (2) is too small try again
Enter an estimate for the random number:
Your guess (3) is too small try again
Enter an estimate for the random number:
Your guess (4) is too small try again
…
</pre>

---

Strategy #1
===========

Can take up to `n` tries for
a range of `n` numbers.

Can we do better?

---

Strategy #2
===========

<pre style="font-size:0.6em">
Your guess (16) is too big try again
Enter an estimate for the random number:
Your guess (8) is too big try again
Enter an estimate for the random number:
Your guess (4) is too small try again
Enter an estimate for the random number:
Your guess (6) is too small try again
Enter an estimate for the random number:
Your guess is correct! The number was:7
You needed 5 steps to find the number
</pre>

Split the interval into two
subintervals per step

---

Strategy #2
===========

First Guess: 16

<pre style="font-size:0.7em">
 ╭─(>16)─┄
─┤
 ╰─(<16)─┄
</pre>

---

Strategy #2
===========

`Your guess (16) is too big, try again`

Second Guess: 8

<pre style="font-size:0.7em">
 ╭─(>16)─┄
─┤
 │       ╭─(>8)─┄
 ╰─(<16)─┤
         ╰─(<8)─┄
</pre>

---

Strategy #2
===========

`Your guess (8) is too big, try again`

Third Guess: 4

<pre style="font-size:0.7em">
 ╭─(>16)─┄
─┤
 │       ╭─(>8)─┄
 ╰─(<16)─┤
         │      ╭─(>4)─┄
         ╰─(<8)─┤
                ╰─(<4)─┄
</pre>

---

Strategy #2
===========

`Your guess (4) is too small, try again`

Fourth Guess: 6

<pre style="font-size:0.7em">
 ╭─(>16)─┄
─┤
 │       ╭─(>8)─┄
 ╰─(<16)─┤             ╭─(>6)─┄
         │      ╭─(>4)─┤
         ╰─(<8)─┤      ╰─(<6)─┄
                │
                ╰─(<4)─┄
</pre>

---

Strategy #2
===========

`Your guess (6) is too small, try again`

Fifth Guess: 7

<pre style="font-size:0.7em">
 ╭─(>16)─┄
─┤
 │       ╭─(>8)─┄
 ╰─(<16)─┤             ╭─(>6)─╼ 7
         │      ╭─(>4)─┤
         ╰─(<8)─┤      ╰─(<6)─┄
                │
                ╰─(<4)─┄
</pre>

---

Complete decision tree

<pre style="font-size:0.3em">
                      ╭─(&lt;)──╼ 1
               ╭─(&lt;)──┤ 2
               │      ╰─(&gt;)──╼ 3
        ╭─(&lt;)──┤ 4
        │      │      ╭─(&lt;)──╼ 5
        │      ╰─(&gt;)──┤ 6
        │             ╰─(&gt;)──╼ 7
 ╭─(&lt;)──┤ 8
 │      │             ╭─(&lt;)──╼ 9
 │      │      ╭─(&lt;)──┤ 10
 │      │      │      ╰─(&gt;)──╼ 11
 │      ╰─(&gt;)──┤ 12
 │             │      ╭─(&lt;)──╼ 13
 │             ╰─(&gt;)──┤ 14
 │                    ╰─(&gt;)──╼ 15
─┤ 16
 │                    ╭─(&lt;)──╼ 17
 │             ╭─(&lt;)──┤ 18
 │             │      ╰─(&gt;)──╼ 19
 │      ╭─(&lt;)──┤ 20
 │      │      │      ╭─(&lt;)──╼ 21
 │      │      ╰─(&gt;)──┤ 22
 │      │             ╰─(&gt;)──╼ 23
 ╰─(&gt;)──┤ 24
        │             ╭─(&lt;)──╼ 25
        │      ╭─(&lt;)──┤ 26
        │      │      ╰─(&gt;)──╼ 27
        ╰─(&gt;)──┤ 28
               │      ╭─(&lt;)──╼ 29
               ╰─(&gt;)──┤ 30
                      ╰─(&gt;)──╼ 31
</pre>

[…][output_decision_tree]
[.py][code_decision_tree]

---

Strategy #2
===========

_Observation:_ By splitting the interval in half for
each iteration we are actually following a
binary tree structure

For `n` elements we need at most `log_2(n)` steps
to find the correct element

---

Using that observation

---

Student register
================

As part of a student database we need
a way to search for names by
matriculation number

---

Student register (flat)
=======================

    !C
    struct student_t {
      char *name;
      uint32_t mat_num;
    };

    struct student_t student_register[MAX_STUDENTS];

One way to structure the data is to
use a simple array

This is a flat structure

---

Student lookup (flat)
=====================

    !C
    struct student_t *
    sr_flat_lookup(struct student_t *flat,
                   uint32_t mat_num)

Download the [database sourcecode][code_student_register_flat]
and find the `sr_flat_lookup` function

Use a `for` loop to iterate through all elements of `flat[]`
while checking if the matriculation number matches `mat_num`

Return the current array element if the matriculation
number matches

Test your implementation in the serial monitor

_Hint:_ Add a `.` or another symbol
after the numbers you enter into the monitor

---

Student lookup (flat)
=======================

    !C
    for(size_t i=0; flat[i].name; i++) {
      if(flat[i].mat_num == mat_num)
        return(&flat[i]);
    }

In the worst case (student not in database)
we would have to look at every single entry

Can we do better?

---

Student register (tree)
=======================

    !C
    struct student_t {
      char *name;
      uint32_t mat_num;
      struct student_t *child_lt;
      struct student_t *child_gt;
    };

[…][code_student_register_tree]

To make lookups more efficient we can
hook the database entries into
a tree structure

---

Student register (tree)
=======================

    !C
    void sr_print_subtree(struct student_t *root,
                          uint16_t indent)
    {
      sr_print_subtree(root->child_lt, indent+1);
      Serial.print(root->name);
      sr_print_subtree(root->child_gt, indent+1);
    }

Download the tree based
[database sourcecode][code_student_register_tree]

Change the `DEBUG_TBUILD` and `DEBUG_LOOKUP` `#define`
at the top of the file from `false` to `true`

Watch the output in the serial monitor
and try to find out how new elements are inserted into the tree

---

Finding elements
================

Now enter some numbers into
the serial monitor and try
to find out how elements are
looked up in the tree

_Hint:_ Add a `.` or another symbol
after the numbers you enter

---

Comparing speed
===============

Change the `DEBUG_TBUILD` and `DEBUG_LOOKUP` `#define`
at the top of the file back from `true` to `false`

Copy your implementation of `sr_flat_lookup`
into the file

Compare the displayed runtimes for the
two lookup algorithms

How does the position of an entry in the array influence
the lookup times?

---

Tree balance
============

<pre style="font-size: 0.4em">
           ╭──┾ Denver Dolph(4037371)
        ╭──┾ Angela Applewhite(4034097)
     ╭──┾  Cyrus Carbonell(4031913)
     │  │        ╭──┾ Elois Edmond(4030462)
     │  │        │  ╰──┾ Norman Napoleon(4030020)
     │  │        │     │  ╭──┾ Tracey Thibodeau(4029685)
     │  │        │     ╰──┾ Rea Reineck(4027146)
     │  │     ╭──┾ Joshua June(4026817)
     │  │     │  ╰──┾ Matilde Micheal(4026688)
     │  │     │     ╰──┾ Magnolia Meader(4025231)
     │  │  ╭──┾ Clarisa Coulson(4023839)
     │  │  │  ╰──┾ Alix Alvarenga(4019661)
     │  ╰──┾ Janet Joynes(4015054)
  ╭──┾ Ona Odonoghue(4013096)
  │  ╰──┾ Song Sandler(4011005)
──┾ Clifford Calahan(4009336)
  │  ╭──┾ Juliet Jaquez(4007416)
  │  │  │  ╭──┾ Shelton Sarkisian(4006478)
  │  │  │  │  ╰──┾ Marilee Meng(4006268)
  │  │  ╰──┾ Tyree Troche(4004535)
  ╰──┾ Paulette Petrone(4001246)
</pre>

In the tree above you can see that there are
far more elements behind
the `child_lt`-branch of "Clifford Calahan"
than behind the `child_gt`-branch

This indicates that the tree is not well
balanced

Tree balance influences the lookup speed

---

Tree balance
============

    !C
    {.name= "Paulette Petrone",  .mat_num= 4001246, …
    {.name= "Juliet Jaquez",     .mat_num= 4007416, …
    {.name= "Clifford Calahan",  .mat_num= 4009336, …
    …

Edit the `student_register` array
so that the matriculation numbers of the
first eight entries are in ascending order

Do not change the other elements

`#define` `DEBUG_TBUILD` to be `true`

Does sorting the elements before inserting them
improve the balance of the tree?

---

lshalfslide
===========

Permission is granted to copy, distribute and/or modify this
document under the terms of the GNU Free Documentation License,
Version 1.3 or any later version published by the Free Software
Foundation; with no Invariant Sections, no Front-Cover Texts, and
no Back-Cover Texts.

[source code](https://github.com/hnez/GdiTutorials)


[code_assignment_3_1]: examples/08_assignment_3_1.ino
[code_assignment_3_2]: examples/08_assignment_3_2.ino
[code_assignment_3_3]: examples/08_assignment_3_3.ino
[code_assignment_3_4]: examples/08_assignment_3_4.ino

[output_decision_tree]: examples/08_decision_tree.html
[code_decision_tree]: examples/08_decision_tree.py

[code_guess_game]: examples/08_guess_game.ino
[code_student_register_flat]: examples/08_student_register_flat.ino
[code_student_register_tree]: examples/08_student_register_tree.ino

[serial_monitor]: 03-traffic-lights.html#slide_12
