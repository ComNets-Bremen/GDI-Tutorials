#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import math

x= np.linspace(-10, 10, 256)

f_taylor= 0

for n in range(10):
    f_taylor+= x # TODO

f_cos= np.cos(x)

axes= plt.plot(
    x, f_cos,
    x, f_taylor
)

plt.ylim((-2, 2))
plt.show()
