# 𝑇(𝑛)=𝑇(𝑛−1)+𝑛
import matplotlib.pyplot as plt
import math
import numpy as np

xpoints = np.array(range(900))


def yarray(k):
    if(k <= 1):
        return 1
    else:
        return yarray(k-1)+k


ypoints = []

for i in xpoints:
    # print(i)
    ypoints.append(yarray(i))

plt.plot(xpoints, ypoints)
plt.show()

# 𝑇(𝑛)=𝑇(𝑛−1)+𝑛^2

xpoints = np.array(range(900))


def yarray(k):
    if(k <= 1):
        return 1
    else:
        return yarray(k-1)+(k*k)


ypoints = []

for i in xpoints:
    ypoints.append(yarray(i))

plt.plot(xpoints, ypoints)
plt.show()

# 𝑇(𝑛)=𝑇(𝑛−1)+𝑙𝑜𝑔𝑛

xpoints = np.array(range(100))


def yarray(k):
    if(k <= 1):
        return 1
    else:
        return yarray(k-1)+math.log(k, 2)


ypoints = []

for i in xpoints:
    ypoints.append(yarray(i))

plt.plot(xpoints, ypoints)
plt.show()

# 𝑇(𝑛) = 𝑇(𝑛/2) + 𝑙𝑜𝑔𝑛

xpoints = np.array(range(100))


def yarray(k):
    if(k <= 1):
        return 1
    else:
        return yarray(k/2)+math.log(k, 2)


ypoints = []

for i in xpoints:
    ypoints.append(yarray(i))

plt.plot(xpoints, ypoints)
plt.show()

# 𝑇(𝑛) = 𝑇 (√𝑛) +𝑙𝑜𝑔𝑛

xpoints = np.array(range(100))


def yarray(k):
    if(k <= 1):
        return 1
    else:
        return yarray(math.sqrt(k))+math.log(k, 2)


ypoints = []

for i in xpoints:
    ypoints.append(yarray(i))

plt.plot(xpoints, ypoints)
plt.show()
