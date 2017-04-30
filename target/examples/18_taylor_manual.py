#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import math

x= np.linspace(-10, 10, 1024)

f_cos= np.cos(x)

f_t1= 1 * x**0
f_t2= f_t1 - 1/2 * x**2
f_t3= f_t2 + 1/24 * x**4
f_t4= f_t3 - 1/720 * x**6

plt.plot(
    x, f_cos,
    x, f_t1,
    x, f_t2,
    x, f_t3,
    x, f_t4,
)

plt.ylim((-2, 2))
plt.show()
