import matplotlib.pyplot as plt
from matplotlib.widgets import Button
import math, random, time

print("Муравьиный алгоритм (Ant Colony Optimization) для задачи коммивояжера")
print("Режимы:")
print("1 - Случайная генерация городов")
print("2 - Ручная расстановка городов (максимум 50 точек)")
mode = input("Выберите режим (1 или 2): ").strip()
cities = []

if mode == '1':
    # Генерация случайных городов
    n = int(input("Введите количество городов: "))
    cities = [(random.uniform(0, 100), random.uniform(0, 100)) for _ in range(n)]

elif mode == '2':
    # Ручная расстановка точек
    max_points = 50
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.set_title("Нажмите ЛКМ для добавления города (макс. 50). Нажмите кнопку 'Готово' для старта.")
    plt.subplots_adjust(bottom=0.2)
    ax.set_xlim(0, 100); ax.set_ylim(0, 100)

    class CityPlacer:
        def __init__(self, ax):
            self.ax = ax
            self.points = []
            self.done = False
        def on_click(self, event):
            # Обрабатываем клик мыши: добавляем точку
            if self.done: return
            if event.inaxes == self.ax and len(self.points) < max_points:
                self.points.append((event.xdata, event.ydata))
                self.ax.plot(event.xdata, event.ydata, 'bo')
                plt.draw()
        def on_done(self, event):
            # Обрабатываем нажатие кнопки "Готово"
            self.done = True
    
    placer = CityPlacer(ax)

    # Создаём кнопку "Готово"
    button_ax = plt.axes([0.8, 0.02, 0.1, 0.05])
    button = Button(button_ax, 'Готово')
    button.on_clicked(placer.on_done)
    cid = fig.canvas.mpl_connect('button_press_event', placer.on_click)
    plt.show(block=False)

    # Ждем нажатия кнопки
    while not placer.done:
        plt.pause(0.1)
    plt.close(fig)
    cities = placer.points

else:
    print("Неверный режим. Завершение.")
    exit()

n = len(cities)
if n == 0:
    print("Города не заданы, выход.")
    exit()

# Ввод параметров алгоритма с контролем диапазона
while True:
    num_ants = int(input("Введите число муравьёв (от 1 до 100): "))
    if 1 <= num_ants <= 100: break
    print("Ошибка: от 1 до 100.")
while True:
    num_iterations = int(input("Введите число итераций (от 1 до 1000): "))
    if 1 <= num_iterations <= 1000: break
    print("Ошибка: от 1 до 1000.")
while True:
    alpha = float(input("Введите alpha (коэффициент важности феромона, обычно от 0 до 5): "))
    if alpha >= 0: break
    print("Ошибка: alpha должно быть >= 0.")
while True:
    beta = float(input("Введите beta (коэффициент важности эвристики, обычно от 0 до 5): "))
    if beta >= 0: break
    print("Ошибка: beta должно быть >= 0.")
while True:
    rho = float(input("Введите rho (коэффициент испарения феромона, от 0 до 1): "))
    if 0 <= rho <= 1: break
    print("Ошибка: rho должно быть в [0, 1].")

# Матрица расстояний между городами
dist = [[0]*n for _ in range(n)]
for i in range(n):
    for j in range(n):
        dx = cities[i][0] - cities[j][0]
        dy = cities[i][1] - cities[j][1]
        d = math.hypot(dx, dy)
        dist[i][j] = d if d != 0 else 1e-6  # чтобы не делить на ноль

# Инициализация феромона (1.0 по умолчанию на всех рёбрах)
pheromone = [[1.0]*n for _ in range(n)]
best_route = None
best_length = float('inf')

# Подготовка окна для визуализации
fig2 = plt.figure()
ax2 = fig2.add_subplot(111)
ax2.set_xlim(0, 100); ax2.set_ylim(0, 100)

# Основной цикл итераций ACO
for iteration in range(num_iterations):
    all_routes = []
    all_lengths = []

    # Каждый муравей строит маршрут
    for ant in range(num_ants):
        start = random.randrange(n)
        route = [start]
        visited = {start}

        # Строим маршрут, пока не посетим все города
        while len(route) < n:
            current = route[-1]
            candidates = [j for j in range(n) if j not in visited]
            probs = []
            for j in candidates:
                tau = pheromone[current][j]**alpha
                eta = (1.0 / dist[current][j])**beta
                probs.append(tau * eta)
            if sum(probs) == 0:
                next_city = random.choice(candidates)
            else:
                next_city = random.choices(candidates, weights=probs, k=1)[0]
            route.append(next_city)
            visited.add(next_city)
        route.append(route[0])  # возвращаемся в стартовый город
        length = sum(dist[route[i]][route[i+1]] for i in range(len(route)-1))
        all_routes.append(route)
        all_lengths.append(length)

        # Обновление лучшего найденного маршрута
        if length < best_length:
            best_length = length
            best_route = route

    # Испарение феромона
    for i in range(n):
        for j in range(n):
            pheromone[i][j] *= (1 - rho)
            if pheromone[i][j] < 1e-6:
                pheromone[i][j] = 1e-6

    # Пополнение феромона по маршрутам всех муравьёв
    for route, length in zip(all_routes, all_lengths):
        deposit = 1.0 / length
        for k in range(len(route)-1):
            i = route[k]; j = route[k+1]
            pheromone[i][j] += deposit
            pheromone[j][i] += deposit

    # Визуализация текущего состояния
    ax2.clear()
    ax2.set_xlim(0, 100); ax2.set_ylim(0, 100)

    # Рисуем города чёрными точками
    xs = [c[0] for c in cities]; ys = [c[1] for c in cities]
    ax2.scatter(xs, ys, c='black')

    # Рисуем рёбра с феромоном красными линиями
    max_ph = max(max(row) for row in pheromone) or 1.0
    for i in range(n):
        for j in range(i+1, n):
            alpha_val = 0.1 + 0.9*(pheromone[i][j]/max_ph)
            ax2.plot([cities[i][0], cities[j][0]], [cities[i][1], cities[j][1]],
                     color='red', alpha=alpha_val)
            
    # Рисуем текущий лучший маршрут зелёной линией
    if best_route:
        rx = [cities[i][0] for i in best_route]
        ry = [cities[i][1] for i in best_route]
        ax2.plot(rx, ry, color='green', linewidth=2)
    ax2.set_title(f"Итерация {iteration+1}/{num_iterations}, длина лучшего = {best_length:.2f}")
    plt.draw()
    plt.pause(0.001)
    time.sleep(0.3)

print(f"Лучший маршрут: {best_route}, длина: {best_length:.2f}")
ax2.set_title("Готово! Закройте окно визуализации для выхода.")
plt.show()
