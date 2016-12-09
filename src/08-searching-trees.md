Searching trees
===============

Find tree structures and
use them to access data more
elegantly

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

In the example above: how many steps
would we need to find a student by its
matriculation number?

---

Student register (flat)
=======================

    !C
    for(size_t i=0; i<MAX_STUDENTS; i++) {
      if(student_register[i].mat_num == num_to_find) {
        return(i);
      }
    }

In the worst case (student not in database)
we would have to look at every single entry

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

[…][code_student_register]

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

Upload the [example code][code_student_register] to
your Arduino

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

There are far more elements behind
the `child_lt`-branch of "Clifford Calahan"
than behind the `child_gt`-branch

This indicates that the tree is not well
balanced

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

Does sorting the elements before inserting them
improve the balance of the tree?

[code_guess_game]: examples/08_guess_game.ino
[code_student_register]: examples/08_student_register.ino

[serial_monitor]: 03-traffic-lights.html#slide_12