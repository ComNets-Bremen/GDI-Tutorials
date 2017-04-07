<!--

                  Copyright (C)  2017  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

UART Regex
==========

Should match valid UART frames
in a sequence of ones and zeros

`"11111010101010011111111"`
`"10010011001100100011111"`
`"11111010101010101111111"`

The regular expressions should match
once in the first test sequence, twice in the
second and never in the third

---

UART Regex
==========

The regex consists of the following
parts:

    0       // Match exactly the start bit
    [01]{8} // Match on the eight data bits
    [01]    // Match on the parity bit (withou checking it)
    1       // Match exactly on the stop bit

There is no need to check for the presence of a second
stop bit as we are already in the accept state

The complete solution is:

`0[01]{8}[01]1`

---

UART Regex
==========

To get the actual data bits out of the
regular expression we can optionally
group them into a capuring group.

`0([01]{8})[01]1`

---

UART FSM
========

        ╔═══════════╗
        ║  Start    ║
        ╚════╤══════╝
             │
             ▼
        ╭────────────╮
    ┌─▶ │ test_start │◀────┐
    │   │            ├╼ 1 ╾┘
    │   ╰────┬───────╯

[…][code_uart_fsm]

---

Traffic light FSM
=================

    !C
    /*     ╭───────────╮
     *     │ Start     │
     *     ├┄┄┄┄┄┄┄┄┄┄┄┤
     *     │ ped:off   │
     *     │ car:off   │
     *     ╰────┬──────╯
     *          ▼        */

The FSM diagram is included as a comment
in the [source code][code_traffic_fsm]

The machine is designed to be a
[moore machine][wiki_moore_machine], every state
explicitly states the output values and following
state

---

Traffic light implementation
============================

    !C
    int isctn_step(int state_old)
    {
      switch(state_old) {
      case ISCTN_START:
        tl_car(TL_OFF);
        tl_pedestrian(TL_OFF);
        state_new= ISCTN_PED_GREEN;
        break;

[…][code_traffic_fsm]

The `isctn_step` function is the so called
transfer function, it takes the current state of
the machine and outputs the following state
based on the inputs and the time

A pure state machine can not use `delay`s in the
transfer function

---

Traffic light implementation
============================

As a little gimmick the implementation uses
an inductive coil in the "road" to detect cars

<p>
  <video poster="images/14_traffic_demo.jpg" controls preload="none">
    <source src="images/14_traffic_demo.mp4" type="video/mp4">
  </video>
</p>

The [source code][code_car_detect] contains a
schematic of the circuit used

[code_uart_fsm]: examples/14_uart_fsm.txt
[code_traffic_fsm]: examples/14_traffic_fsm.ino
[code_car_detect]: examples/14_car_detect.ino

[wiki_moore_machine]: https://en.wikipedia.org/wiki/Moore_machine
