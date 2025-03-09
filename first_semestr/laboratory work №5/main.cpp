#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x);

        float screenX = 400 + x * scaleX;
        float screenY = 150 - y * scaleY;

        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }
    window.draw(graph);
}

int main()
{
    RenderWindow window(VideoMode(800, 800), "Graph control");

    CircleShape userPoint(5);
    userPoint.setFillColor(Color::Red);
    bool userPointExists = false;

    Font font;
    font.loadFromFile("arial.ttf");

    Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setFillColor(Color::White);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setPosition(10, 10);

    sf::VertexArray xAxis(Lines, 2);
    xAxis[0].position = Vector2f(50, 150);
    xAxis[0].color = Color::White;
    xAxis[1].position = Vector2f(750, 150);
    xAxis[1].color = Color::White;

    sf::VertexArray yAxis(Lines, 2);
    yAxis[0].position = Vector2f(400, 50);
    yAxis[0].color = Color::White;
    yAxis[1].position = Vector2f(400, 750);
    yAxis[1].color = Color::White;

    string section;
    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {

                    Vector2i mousePos = Mouse::getPosition(window);

                    float mathX = (mousePos.x - 400) / 40.0f;
                    float mathY = -(mousePos.y - 150) / 40.0f;

                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true;

                    double y = round(mathY);
                    double x = round(mathX);

                    if ((y == -abs(x)) or (y == -5)) {
                        section = "Granica";
                    }
                    else {
                        if (y < -abs(x) and y < -5) {
                            section = "1";
                        }
                        else {
                            if (y < -abs(x) and y > -5) {
                                section = "2";
                            }
                            else {
                                if (y > -abs(x) and y < -5 and x > 5) {
                                    section = "3";
                                }
                                else {
                                    if (y > -abs(x) and y < -5 and x < -5) {
                                        section = "4";
                                    }
                                    else {
                                        if (y > -abs(x) and y > -5) {
                                            section = "5";
                                        }
                                    }
                                }
                            }
                        }
                    }

                    coordinatesText.setString("Coordinates: (" + std::to_string(mathX) + ", " + std::to_string(mathY) +")\n Zone : " + section);
                }

            }
        }

        window.clear();

        window.draw(xAxis);
        window.draw(yAxis);

        drawGraph(window, [](float x) { return -abs(x) * 1.0f; }, -8.5, 8.5, 40, 40, sf::Color::Blue);

        drawGraph(window, [](float x) { return -5 * 1.0f; }, -8.5, 8.5, 40, 40, sf::Color::Red);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }

        window.display();
    }

    return 0;
}