import numpy as np
import matplotlib.pyplot as plt
import math

eqn1 = []
eqn2 = []
eqn3 = []
print('Enter eqn1 _x1 + _x2 = _: ')
eqn1 = input()
print('Enter eqn2 _x1 + _x2 = _: ')
eqn2 = input()
print('Enter eqn3 _x1 + _x2 = _: ')
eqn3 = input()


lhs1 = np.array([[1, 1], [0, 1]])
rhs1 = np.array([6, 6])

lhs2 = np.array([[0, 1], [3, 2]])
rhs2 = np.array([6, 9])

lhs3 = np.array([[1, 1], [3, 2]])
rhs3 = np.array([6, 9])

ans1 = np.linalg.solve(lhs1, rhs1)
ans2 = np.linalg.solve(lhs2, rhs2)
ans3 = np.linalg.solve(lhs3, rhs3)

x = [int(ans1[0]), int(ans2[0]), int(ans3[0])]
y = [int(ans1[1]), int(ans2[1]), int(ans3[1])]

ans = math.ceil(max(2*ans1[0]+5*ans1[1], 2 * ans2[0] + 5*ans2[1], 2*ans3[0]+5*ans3[1]))

print() 
print('Optimal value: ' + str(ans))

plt.fill(x, y)
plt.show()
