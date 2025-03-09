#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Размер окна и матрицы
    const int windowSize = 500;
    const int n = 10;           // размерность матрицы (10x10)
    const int cellSize = windowSize / n; // размер ячейки для равномерного распределения по окну

    // Создание окна
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Matrix Visualization");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Очистка окна перед новой отрисовкой
        window.clear(sf::Color::White);

        // Двойной цикл для отрисовки каждой ячейки в сетке n x n
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);

                // Устанавливаем цвет рамки и заливки
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);

                // Логика закрашивания диагоналей
                int diagonalIndex = i + j - (n - 1); // Индекс параллельной диагонали относительно побочной
                if (diagonalIndex > 0 && diagonalIndex % 2 == 0) { // Только для чётных индексов ниже побочной
                    cell.setFillColor(sf::Color::Green); // Закрашиваем зелёным
                }
                else {
                    cell.setFillColor(sf::Color::White); // Остальные клетки остаются белыми
                }

                // Отрисовка ячейки
                window.draw(cell);
            }
        }

        // Отображение результата
        window.display();
    }

    return 0;
}

