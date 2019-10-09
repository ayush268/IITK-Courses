import os
import sys
import numpy as np
import matplotlib.pyplot as plt

y = np.arange(1, 50)
# plt.plot(y)		# By default x starts from 0
# plt.show()

# plt.plot(y*y)		# By default x starts from 0
# plt.show()

x = np.arange(1, 50)
# plt.plot(x, y*y)
# plt.show()

# plt.plot(x, y*y, 'r')
# plt.show()

# plt.plot(x, y*y, 'go')
# plt.show()

# plt.plot(x, y, 'r', x, y*y, 'b')
# plt.show()

# plt.plot(x, y, 'r', x, y*y, 'b^', linewidth=2)
# plt.show()

# plt.plot(x, y, 'r^', label='y=x')
# plt.plot(x, y*y, 'bx', label='y=x^2')
# plt.title('y=x and y=x^2')
# plt.legend()
# plt.xlabel('x - AXIS')
# plt.ylabel('y - AXIS')
# plt.show()

t1 = np.arange(0.0, 5.0, 0.05)
t2 = np.arange(0.0, 5.0, 0.1)

plt.figure(1)
plt.subplot(211)
plt.plot(t1, np.sin(2*np.pi*t1), 'bo', t1, np.sin(2*np.pi*t1), 'k')

plt.subplot(212)
plt.plot(t2, np.cos(2*np.pi*t2), 'r^', t2, np.cos(2*np.pi*t2), 'k')
# plt.show()
plt.savefig('saved_plot.png')