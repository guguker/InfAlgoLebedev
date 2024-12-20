#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Размер окна и матрицы
    const int windowSize = 500;
    const int n = 10;           // размерность матрицы (5x5)
    const int cellSize = windowSize / n; // размер ячейки для равномерного распределения по окну

    // Координаты закрашиваемых точек для варианта №2
    const std::vector<std::pair<int, int>> filledCells =
    {
        {3, 10}, {4, 9}, {5, 8}, {5, 10}, {6, 7}, {6, 9}, {7, 6}, {7, 8}, {7, 10},
        {8, 5}, {8, 7}, {8, 9}, {9, 4}, {9, 6}, {9, 8}, {9, 10}, {10, 3}, {10, 5}, {10, 7}, {10, 9}
    };

    // Создание окна
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Matrix Visualization");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Очистка окна перед новой отрисовкой
        window.clear(sf::Color::White);

        // Двойной цикл для отрисовки каждой ячейки в сетке n x n
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);

                // Устанавливаем цвет рамки и заливки
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);

                // Проверяем, должна ли клетка быть закрашена
                if (std::find(filledCells.begin(), filledCells.end(), std::make_pair(i + 1, j + 1)) != filledCells.end())
                {
                    cell.setFillColor(sf::Color::Green);
                }
                else
                {
                    cell.setFillColor(sf::Color::White);
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