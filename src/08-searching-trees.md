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

_Observation:_ By splitting the interval in half for
each iteration we are actually following a
binary tree structure

For `n` elements we need at most `log_2(n)` steps
to find the correct element

[code_guess_game]: examples/08_guess_game.ino

[serial_monitor]: 03-traffic-lights.html#slide_12

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
      struct student_t *child_gt:
    };

---
