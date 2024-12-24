#include "GameView.h"

GameView *NewGameView(const sf::Vector2i &windowSize)
{
    GameView *pView = new GameView;
    pView->windowSize = windowSize;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    pView->window.create(sf::VideoMode(windowSize.x, windowSize.y),
                         "Better than Baldur's Gate",
                         sf::Style::Close, settings);
    pView->window.setFramerateLimit(60);

    pView->camera.reset(sf::FloatRect(0.0f, 0.0f, windowSize.x, windowSize.y));
    pView->camera.setViewport(sf::FloatRect(0.0f, 0.0f, 2.0f, 2.0f));

    return pView;
}

void EnterGameLoop(GameView &view, OnUpdate onUpdate, OnDraw onDraw, void *pData)
{
    while (view.window.isOpen())
    {
        sf::Event event;
        while (view.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                view.window.close();
                break;
            }
        }

        const sf::Time elapsedTime = view.clock.getElapsedTime();
        view.clock.restart();
        onUpdate(pData, view, elapsedTime.asSeconds());

        view.window.clear();
        onDraw(pData, view);
        view.window.display();
    }
}

void DestroyGameView(GameView *&pView)
{
    delete pView;
    pView = nullptr;
}

void SetCameraCenter(GameView &view, const sf::Vector2f &center)
{
    view.camera.setCenter(center.x, center.y);
    view.window.setView(view.camera);
}
