import numpy as np
import math
def GaussianFilterCreater(sigma, x):
    PI = 3.1415926
    return 1 / ((2 * PI) ** 0.5 * sigma) * math.exp(-((x ** 2) / (2 * (sigma ** 2))))
if __name__ == "__main__":
    for i in range(20):
        print(GaussianFilterCreater(20, i))
        print(",")