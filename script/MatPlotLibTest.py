import matplotlib.pyplot as plt
import numpy as np


# SIMPLE
plt.plot(np.arange(0, 12), np.arange(0, 12))
plt.plot([1,2,3,10],[2,1,3,4],'ro', [1,2],[10,11], 'g--')
plt.plot([1,2,3,10],[2,4,6,10], linestyle='-.', color='b')
plt.text(5,5,"YOYOYOYOYO")
plt.axis([-5,15,-12,20])
plt.show()

# Deuxieme figure test
def f(t):
    return np.exp(-t) * np.cos(2*np.pi*t)
t1 = np.arange(0.0, 5.0, 0.1)
t2 = np.arange(0.0, 5.0, 0.01)

plt.figure(2)
plt.plot([1,20])
plt.figure(1)
plt.subplot(221)
plt.plot(t1, f(t1), 'bo', t2, f(t2), 'k')
plt.subplot(222)
plt.plot(t2, np.cos(2*np.pi*t2), 'r--')
plt.subplot(2,2,4)
plt.plot([1,10])


plt.show()


# # set limits so that it no longer looks on screen to be 45 degrees
# plt.xlim([-10, 20])

# # Locations to plot text
# l1 = np.array((1, 1))
# l2 = np.array((5, 5))

# # Rotate angle
# angle = 45
# trans_angle = plt.gca().transData.transform_angles(np.array((45,)),
#                                                    l2.reshape((1, 2)))[0]

# # Plot text
# th1 = plt.text(l1[0], l1[1], 'text not rotated correctly', fontsize=16,
#                rotation=angle, rotation_mode='anchor')
# th2 = plt.text(l2[0], l2[1], 'text rotated correctly', fontsize=16,
#                rotation=trans_angle, rotation_mode='anchor')

plt.savefig("test")