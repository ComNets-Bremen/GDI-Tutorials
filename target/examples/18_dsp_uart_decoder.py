#!/usr/bin/env python3

import itertools as it
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

def read_samples(fname):
    'Perform some magic to read complex raw samples from a file'

    # Samples are stored as unsigned 8 bit integers
    # with a DC offset of 127.5
    raw_dat= np.fromfile(fname, np.uint8) - 127.5

    # Even elements are the real part of a complex number
    # the following odd element is the imagniary part.
    # Normalize the values to -1.0:1.0
    cplx_dat= (raw_dat[::2] + raw_dat[1::2]*1j) / 127.5

    return(cplx_dat)

# The samplerate and center frequency are
# parameters set at recording time
center_freq= 433.8e6
sample_rate= 960e3
samples= read_samples('18_sdr_uart_433.8MHz_960kHz.bin')

# Create a time-axis according to the sample times
t_hp= np.linspace(0, len(samples)/sample_rate, len(samples))

# Transform the first 2048 samples into the
# frequency domain and display the spectrum
plt.plot(abs(np.fft.fft(samples[:2048])))
plt.show()

# In order to decode the signal correctly it should
# be shifted from 130kHz to 0Hz.
offset_freq= -130e3
lo_sig= np.exp(2j * np.pi * offset_freq * t_hp)

# Display the signal that is used to shift
# the frequency
plt.plot(abs(np.fft.fft(lo_sig[:2048])))
plt.show()

# Perform the shift
baseband= samples * lo_sig

# Transform the first 2048 frequency-shifted samples
# into the frequency domain and display the spectrum
plt.plot(abs(np.fft.fft(baseband[:2048])))
plt.show()

def downsample(sig):
    'reduce the length of sig by factor of 100'

    d1= signal.decimate(sig, 10, zero_phase=True)
    d2= signal.decimate(d1, 10, zero_phase=True)

    return(d2)

# Reduce the amount of data that has to be
# processed by filtering away high frequencies
# and only keeping every 100th sample
lowpass= downsample(baseband)
sample_rate_lp= sample_rate / 100

# The signal is amplitude modulated
# in order to decode it take the absolute
abssig= abs(lowpass)

# After taking the absolute we can display
# the whole signal
plt.plot(abssig)
plt.show()

# The Data is transmitted using UART frames
# A Uart frame consits of 10 bits that are
# all equally long (1/baud_rate).
def decode_byte(sig, baud_rate, threshold):
    frame_time= 10/baud_rate  # Length of a uart frame in seconds
    next_time= 9.5/baud_rate  # Length to the middle of the stop bit

    # Find the start bit by searching for the first
    # sample below a certain threshold
    idx_start= np.nonzero(sig < threshold)[0][0]

    # Calculate the end index using the frame length
    # and sample rate
    idx_end= idx_start + round(frame_time*sample_rate_lp)
    idx_next= idx_start + round(next_time*sample_rate_lp)

    # Display the frame
    plt.plot(sig[idx_start:idx_end])

    for i in range(11):
        pos= (i*idx_start + (10-i)*idx_end)/10 - idx_start
        plt.axvline(x=pos, linestyle='dashed')

    plt.show()

    # Split the frame into the ten bits and check
    # for all of them if they are greater (1) or smaller (0)
    # than the threshold
    symbols= list(
        raw.mean() > threshold
        for raw in np.array_split(sig[idx_start:idx_end], 10)
    )

    # Take the bits from above and calulate the byte
    # they represent
    val= sum(
        (v * 2**e)
        for (v, e)
        in zip(symbols[1:9], range(8))
    )

    # Return the byte and the index at which the
    # search for the next frame should start
    return(bytes([val]), sig[idx_next:])

def decode_message(sig, baud_rate, threshold):
    'go through samples and decode the symbols'

    data= b''
    ptr= sig

    try:
        while True:
            byte, ptr= decode_byte(ptr, baud_rate, threshold)

            data+= byte
    except IndexError:
        pass

    return(data.decode('utf-8'))


decoded_message= decode_message(abssig, 1200, 0.3)

print('Message: {}'.format(decoded_message))
