from matplotlib import pyplot as plt
from math import pi, cos, sin
import random

def plot_segment(ax, x1, y1, z1, x2, y2, z2):
    ax.plot([x1, x2], [y1, y2], [z1, z2], 'g', linewidth=1.5)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

n = 20
m = 10
dr = [0.5 + i / n for i in range(n)]
dz = [-1 + i / n for i in range(n)]
z = [3.5 * (1 - i / n) for i in range(n)]
phi = [[2 * pi * (i / n + j / m) for j in range(m)] for i in range(n)]
dx = [[dr[i] * cos(phi[i][j]) for j in range(m)] for i in range(n)]
dy = [[dr[i] * sin(phi[i][j]) for j in range(m)] for i in range(n)]

colors = ['red', 'blue', 'gold', 'magenta', 'green', 'orange', 'purple', 'pink']

for i in range(n):
    for j in range(m):
        x = dx[i][j]
        y = dy[i][j]
        z1 = z[i]
        z2 = z[i] + dz[i]
        plot_segment(ax, 0, 0, z1, x, y, z2)

        # ставим шарик рандомно в ветку, но! не близко к ветке чтоб не было вырвиглаза
        t = random.uniform(0.3, 1.0)
        x_sphere = x * t
        y_sphere = y * t
        z_sphere = z1 + (z2 - z1) * t

        # s здесь отвечает за размер шарика, вроде норм выглядят :)
        ax.scatter(x_sphere, y_sphere, z_sphere, color=random.choice(colors), s=13) 

ax.set_box_aspect(aspect=(1, 1, 1.5))
plt.show()