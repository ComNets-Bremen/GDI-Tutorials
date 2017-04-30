#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import math

x= np.linspace(-10, 10, 1024)

f_cos= np.cos(x)

f_t1= 1 * x**0
f_t2= f_t1 - 1/2 * x**2
f_t3= 0 # TODO
f_t4= 0 # TODO

plt.plot(
    x, f_cos
)

plt.ylim((-2, 2))
plt.show()
