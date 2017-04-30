<!--

                  Copyright (C)  2017  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

Calc'ing and plotting
=====================

Fast and elegant numeric calulations in python using numpy
and easy plotting using matplotlib

![Taylor expansion of a cosine](images/18_taylor_expansion.svg)

---

_But first:_

solutions to the last homework

---

Guessing game
=============

    !Python
    if cmd == '1':
        bound_upper= guess
    elif cmd == '2':
        bound_lower= guess
    elif cmd == '3':
        # Leave the loop
        break

[…][code_guess_game]

---

Fixed tic tac toe game
======================

    !Python
    # Check rows
    if self.field[0][0]==player and self.field[1][0]…
        return True

    if self.field[0][1]==player and self.field[1][1]…
        return True

[…][code_ttt_basic]

---

Optimized tic tac toe game
==========================

    !Python
    # Check if player owns all the fields in a row
    for col in range(3):
        if all(
            self.field[row][col] == player
            for row in range(3)):

            return True

[…][code_ttt]

---

_Back to numpy & matplotlib_

---

Importing numpy and matplotlib
==============================

Open an interactive python session by
running `python3` / `python` on the commandline
and enter the import statements below:

    !Python
    >>> import numpy as np
    >>> import matplotlib.pyplot as plt


The statements above tell the interpreter
that we want to use the `numpy` and `matplotlib.pyplot`
modules and that we want to use `np` and `plt`
as a shorthand for them

---

Everything is a vector
======================

numpy is centered around a similar concept as
Matlab: everything is a vector

To find out what that means we will create a
vector for our x-axis

    !Python
    >>> x= np.linspace(-10, 10, 1024)

The statement above will create an array of 1024-elements
between `-10` and `10`

    !Python
    >>> print(x)
    [-10. -9.98044966 ..., 9.98044966  10.]
    >>> print(len(x), x[0], x[-1])
    1024 -10.0 10.0

---

Plotting
========

To get an idea of what `x` looks like we
can plot it over itself

![X over X](images/18_x_over_x.svg)

    !Python
    >>> plt.plot(x, x) # Plot x over x
    >>> plt.show()     # Show the plot in a window

---

Everything is a vector
======================

Numpy lets us work with vectors as if
they were numbers

![X² over X](images/18_xsq_over_x.svg)

    !Python
    >>> plt.plot(x, x**2) # Plot x² over x
    >>> plt.show()

`x**2` calculates x² for every element of x

---

Working with vectors
====================

The "everything is a vector" concept
lets us express complex problems
with little code

    !Python
    >>> y= x**2
    >>> y_deriv= y[1:] - y[:-1]
    >>> plt.plot(x[1:], y_deriv)
    >>> plt.show()

What is the purpose of the snippet above?

---

Choose your track
=================

Based on your programming experience you can now
decide how you want to continue this tutorial:

- [<span style="color: rgb(161, 206, 76);">Green</span>][track_green] track  - a
  simple example demonstrating the taylor-expansion

- [<span style="color: rgb(234, 58, 58);">Red</span>][track_red] track - a
  more complex example that performs basic digital signal processing on
  an actual radio signal

To learn how to use numpy and matplotlib you should follow
the green track

---

<span style="color: rgb(161, 206, 76);">Green</span> track
==========================================================

The [taylor expansion][wiki_taylor] is a method to approximate
some function using polynomials

![Taylor skeleton](images/18_taylor_skeleton.svg)

We want to plot the taylor expansion of a cosine

Download the [skeleton code][code_taylor_skeleton]
that plots a cosine and run it

---

Taylor expansion
================

Look up the taylor expansion of a cosine on
[wikipedia][wiki_taylor_trig]

and continue the expansion started in the
[skeleton code][code_taylor_skeleton]

    !Python
    f_t1= 1 * x**0
    f_t2= f_t1 - 1/2 * x**2
    f_t3= 0 # TODO
    f_t4= 0 # TODO

---

Multiple plots
==============

In order to plot multiple plots into the same window
you can pass multiple x/y-data pairs to the `.plot`
function

    !Python
    plt.plot(
        x, f_cos,
        x, f_t1,
        x, f_t2,
        x, f_t3,
        x, f_t4
    )

---

Solution
========

![Taylor expansion](images/18_taylor_manual.svg)

    !Python
    f_t1= 1 * x**0
    f_t2= f_t1 - 1/2 * x**2
    f_t3= f_t2 + 1/24 * x**4
    f_t4= f_t3 - 1/720 * x**6

[…][code_taylor_manual]

---

Higher order
============

Manual expansion becomes tedious for higher orders

Download the skeleton code below and implement the
cosine taylor expansion using a for-loop

    !Python
    for n in range(10):
        f_taylor+= x # TODO

[…][code_taylor_for_skeleton]

_Hint:_ use the `math.factorial` function

---

Solution
========

![Taylor expansion](images/18_taylor_for.svg)

    !Python
    for n in range(10):
        f_taylor+= (
            ((-1)**n)/math.factorial(2*n) * x**(2*n)
        )

[…][code_taylor_for]

---

<span style="color: rgb(234, 58, 58);">Red</span> track
=======================================================

The setup that generated the testdata consits of
the an Arduino, a 433MHz OOK RF-module and a
DVB-T stick that is abused to work as a software
defined radio

![Taylor expansion](images/18_rf_setup.jpg)

The Arduino generates data that is transmitted by the
RF-module

The SDR reveices the signal, does some processing and
passes the digitized signal to the PC

---

uart.bin
========

The SDR outputs two 8-bit unsigned values per sample,
the real and the imaginary part of a complex number

The SDR was configured to record samples at a rate
of 960kHz, meaning one sample every 1.04µs

The SDR was also configured to work at a center-frequency
of 433.8MHz, meaning that a signal at 433.8MHz on air
appears at 0Hz in the recorded file

The file below contains the raw samples as they were
transmitted to the computer

[18_sdr_uart_433.8MHz_960kHz.bin][data_sdr_uart]

---

uart_decoder.py
===============

The program below uses numpy to decode the data
that was transmitted by the Arduino while plotting
the signal at every processing step

    !Python
    baseband= samples * lo_sig

    plt.plot(abs(np.fft.fft(baseband[:2048])))
    plt.show()

[…][code_uart_decoder]

Save the code into the same directory as
[18_sdr_uart_433.8MHz_960kHz.bin][data_sdr_uart]
and run it

The following slides will guide you through the
output of the program

---

signal FFT
==========

![Signal fft](images/18_dsp_sig_fft.svg)

    !Python
    plt.plot(abs(np.fft.fft(samples[:2048])))
    plt.show()

To get an overview of an RF-signal it makes sense
to look at it in the frequency-domain

To get from the time-domain (samples) to the frequency
domain the fast fourier transform is applied to the
first 2048 samples

---

FFT
===

![Signal fft annotated](images/18_dsp_sig_fft_annot.svg)

The raw result of a fourier transformation has
a few unintuitive properties:

- There are negative frequencies (this makes sense when
  working with complex-valued signals)
- The negative frequencies occur in the right half
  of the output (the output is often reorganized
  for visualization so that 0Hz is in the middle)

---

Downmixing
==========

![Signal fft annotated](images/18_dsp_sig_fft_annot.svg)

The plot above shows a peak at 130kHz

As the center frequency of the receiver was at 433.8Mhz
this means, that the signal was originally sent at

433.8Mhz + 130kHz = 433.93MHz

For further analysis it makes sense to shift the
signal to 0Hz, a process called mixing

---

Downmixing
==========

![LO Signal](images/18_dsp_lo_fft.svg)

    !Python
    offset_freq= -130e3
    lo_sig= np.exp(2j * np.pi * offset_freq * t_hp)

To perform the mixing a signal with a frequency of -130kHz
has to be generated (complex numbers are fun)

---

Downmixing
==========

![Baseband](images/18_dsp_baseband_fft.svg)

    !Python
    # Perform the shift
    baseband= samples * lo_sig

The mixing is then performed by multiplying the receiver-signal
with the generated signal

The signal is now centered at 0Hz

---

Downsampling
============

After mixing the signal to 0Hz we can filter away
high frequencies and reduce the number of samples

    !Python
    lowpass= downsample(baseband)
    sample_rate_lp= sample_rate / 100

The downsample function performs the filtering
and keeps every 100th sample

---

Downsampling
============

![Baseband](images/18_dsp_downsampled.svg)

    !Python
    abssig= abs(lowpass)
    plt.plot(abssig)

After downsampling the signal is short enough
to be displayed on screen

one can already start to see the UART-encoded data
frames

---

Decoding
========

![Baseband](images/18_dsp_frame.svg)

To decode the frames one has to find the first
sample below a certain threshold

afterwards the bits are decoded by slicing the
frame into 10 symbols of equal length, according
to the baudrate

if a bit is, on average, below the threshold it
counts as `0`, otherwise as a `1`

---

Decoding
========

    !Python
    >>> decoded_message= decode_message(
    ...     abssig, 1200, 0.3)
    ... )
    >>> print('Message: {}'.format(decoded_message))
    Message: Numpy + Matplotlib

When the last frame was processed the complete message
is printed

_Numpy ❤️ Matplotlib_

[code_guess_game]: examples/18_guess_game.py
[code_ttt_basic]: examples/18_ttt_basic.py
[code_ttt]: examples/18_ttt.py


[track_green]: #slide_8
[track_red]: #slide_3

[wiki_taylor]: https://en.wikipedia.org/wiki/Taylor_series
[wiki_taylor_trig]: https://en.wikipedia.org/wiki/Taylor_series#Trigonometric_functions

[code_taylor_skeleton]: examples/18_taylor_skeleton.py
[code_taylor_manual]: examples/18_taylor_manual.py
[code_taylor_for_skeleton]: examples/18_taylor_for_skeleton.py
[code_taylor_for]: examples/18_taylor_for.py

[data_sdr_uart]: examples/18_sdr_uart_433.8MHz_960kHz.bin

[code_uart_decoder]: examples/18_dsp_uart_decoder.py
