import numpy as np
import matplotlib.pyplot as plt

class AntColony:
    def __init__(self, num_cities, n_ants, n_iterations, alpha, beta, rho):
        self.num_cities = num_cities      # число городов
        self.n_ants = n_ants              # число муравьев
        self.n_iterations = n_iterations  # число итераций
        self.alpha = alpha                # вес феромона
        self.beta = beta                  # вес эвристики (дистанции)
        self.rho = rho                    # скорость испарения феромона
        
        # Сгенерировать города: случайные 2D-точки
        self.points = np.random.rand(num_cities, 2)
        
        # Матрица евклидовых расстояний между городами
        self.distances = np.zeros((num_cities, num_cities))
        for i in range(num_cities):
            for j in range(num_cities):
                if i == j:
                    self.distances[i][j] = np.inf  # присваиваем бесконечность на диагонали
                else:
                    dx = self.points[i][0] - self.points[j][0]
                    dy = self.points[i][1] - self.points[j][1]
                    self.distances[i][j] = np.sqrt(dx*dx + dy*dy)
        
        # Инициализация матрицы феромонов (единицы)
        self.pheromone = np.ones((num_cities, num_cities))
        
        # Лучшая найдённая длина и маршрут
        self.best_path = None
        self.best_length = np.inf
        
        # Настроить интерактивный график для визуализации
        plt.ion()
        self.fig, self.ax = plt.subplots(figsize=(6,6))
        self.ax.set_title("ACO – итерация 0")
        # Нарисовать города (точки)
        self.ax.scatter(self.points[:,0], self.points[:,1], c='black')
    
    def run(self):
        """Запустить алгоритм ACO."""
        for iteration in range(1, self.n_iterations+1):
            all_paths = []    # маршруты всех муравьёв в этой итерации
            all_lengths = []  # соответствующие длины маршрутов
            
            # Каждый муравей строит свой маршрут
            for ant in range(self.n_ants):
                start = np.random.randint(self.num_cities)  # случайный стартовый город
                visited = [start]     # список посещённых городов
                length = 0
                current = start
                # Пока не посещены все города
                while len(visited) < self.num_cities:
                    probabilities = np.zeros(self.num_cities)
                    denom = 0
                    # Вычисляем знаменатель для формулы вероятностей
                    for j in range(self.num_cities):
                        if j not in visited:
                            # комбинированный фактор феромона и эвристики
                            denom += (self.pheromone[current][j]**self.alpha) * ((1.0/self.distances[current][j])**self.beta)
                    # Рассчитываем вероятность перехода в каждый новый город
                    for j in range(self.num_cities):
                        if j not in visited:
                            num = (self.pheromone[current][j]**self.alpha) * ((1.0/self.distances[current][j])**self.beta)
                            probabilities[j] = num / denom
                    probabilities = probabilities / np.sum(probabilities)
                    # Выбираем следующий город согласно распределению вероятностей
                    next_city = np.random.choice(range(self.num_cities), p=probabilities)
                    visited.append(next_city)
                    length += self.distances[current][next_city]
                    current = next_city
                # Возврат в стартовый город, замыкая цикл
                length += self.distances[current][start]
                visited.append(start)
                
                all_paths.append(visited)
                all_lengths.append(length)
                # Обновление лучшего маршрута
                if length < self.best_length:
                    self.best_length = length
                    self.best_path = visited
            
            # Этап испарения феромона
            self.pheromone *= (1 - self.rho)
            # Нанесение феромона вдоль каждого пройденного маршрута (Q=1)
            for path, length in zip(all_paths, all_lengths):
                deposit = 1.0 / length
                for i in range(len(path)-1):
                    a, b = path[i], path[i+1]
                    self.pheromone[a][b] += deposit
                    self.pheromone[b][a] += deposit
            
            # Обновление визуализации после итерации
            self._plot_iteration(iteration)
        
        # Завершаем интерактивный режим и показываем финальный результат
        plt.ioff()
        plt.show()
    
    def _plot_iteration(self, iteration):
        """Отрисовка текущего состояния: феромонные тропы и лучший маршрут."""
        self.ax.clear()
        # Рисуем города
        self.ax.scatter(self.points[:,0], self.points[:,1], c='black')
        # Рисуем ребра с интенсивностью феромона
        max_ph = np.max(self.pheromone)
        for i in range(self.num_cities):
            for j in range(i+1, self.num_cities):
                if self.pheromone[i][j] > 0:
                    alpha_val = self.pheromone[i][j] / max_ph  # нормализация для прозрачности
                    self.ax.plot([self.points[i,0], self.points[j,0]],
                                 [self.points[i,1], self.points[j,1]],
                                 c='red', alpha=alpha_val)
        # Рисуем лучший путь (зелёный)
        if self.best_path:
            for k in range(len(self.best_path)-1):
                i = self.best_path[k]
                j = self.best_path[k+1]
                self.ax.plot([self.points[i,0], self.points[j,0]],
                             [self.points[i,1], self.points[j,1]],
                             c='green', linewidth=2)
        # Обновляем заголовок с номером итерации и длиной лучшего пути
        self.ax.set_title(f"Итерация {iteration}/{self.n_iterations}, "
                          f"лучший путь = {self.best_length:.2f}")
        plt.pause(0.25)


if __name__ == "__main__":
    num_cities = int(input("Введите число городов: "))
    n_ants     = int(input("Введите число муравьёв: "))
    n_iter     = int(input("Введите число итераций: "))
    alpha      = float(input("Введите α (влияние феромона): "))
    beta       = float(input("Введите β (влияние расстояния): "))
    rho        = float(input("Введите ρ (скорость испарения): "))
    
    colony = AntColony(num_cities, n_ants, n_iter, alpha, beta, rho)
    colony.run()

