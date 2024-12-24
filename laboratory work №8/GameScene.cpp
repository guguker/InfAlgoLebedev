#include "GameScene.h"
#include "GameView.h"
#include <float.h> // Константа FLT_EPSILON
#include <math.h>

// Добавим часто используемые идентификаторы в глобальное пространство имён.
using sf::Keyboard;
using sf::Vector2f;
using sf::Vector2i;

// Абсолютная скорость движения игрока.
static const float PLAYER_SPEED = 200;

// Выполняет нормализацию вектора (приведение к единичной длине).
static Vector2f Normalize(const Vector2f &value)
{
    const float length = std::hypotf(value.x, value.y);
    if (length < FLT_EPSILON)
    {
        return Vector2f(0, 0);
    }

    return value / length;
}

// Округляет компоненты вектора до ближайших целых чисел.
static Vector2f Round(const Vector2f &value)
{
    return Vector2f(roundf(value.x), roundf(value.y));
}

// Определяет состояние клавиатуры и выбирает направление движения.
// Возвращает нормализованный вектор направления игрока.
static Vector2f GetPlayerDirection()
{
    Vector2f direction;
    if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
    {
        direction.y = -1;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
    {
        direction.y = +1;
    }
    if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
    {
        direction.x = -1;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
    {
        direction.x = +1;
    }

    return Normalize(direction);
}

GameScene *NewGameScene()
{
    GameScene *pLogic = new GameScene;
    TmxLevel &level = pLogic->level;

    level.LoadFromFile("res/platformer.tmx");
    pLogic->player = level.GetFirstObject("player");
    pLogic->coins = level.GetAllObjects("coin");
    pLogic->enemies = level.GetAllObjects("enemy");
    pLogic->block = level.GetAllObjects("block");
    pLogic->startPosition = (pLogic->player.sprite.getPosition());


    return pLogic;
}

void UpdateGameScene(void *pData, GameView &view, float deltaSec)
{
    GameScene* pLogic = reinterpret_cast<GameScene*>(pData);
    (void)deltaSec;

    TmxObject& player = pLogic->player;
    const Vector2f movement = Round(GetPlayerDirection() * PLAYER_SPEED * deltaSec);

    const Vector2i windowSize = view.windowSize;
    SetCameraCenter(view, player.sprite.getPosition() + Vector2f(windowSize.x / 4, windowSize.y / 4));

    for (auto it = pLogic->coins.begin(); it != pLogic->coins.end();) {
        if (pLogic->player.sprite.getGlobalBounds().intersects(it->sprite.getGlobalBounds())) {
            it = pLogic->coins.erase(it);
        }
        else {
            ++it;
        }
    }


    for (auto it = pLogic->enemies.begin(); it != pLogic->enemies.end();) {
        if (pLogic->player.sprite.getGlobalBounds().intersects(it->sprite.getGlobalBounds())) {
            pLogic->player.sprite.setPosition(pLogic->startPosition);
        }
        else {
            ++it;
        }
    }

    int collision = false;
    sf::Vector2f oldPosition = pLogic->player.sprite.getPosition();
    for (auto it = pLogic->block.begin(); it != pLogic->block.end(); ++it) {
        sf::FloatRect playerRect = pLogic->player.sprite.getGlobalBounds();
        sf::FloatRect blockRect = it->rect;
        sf::FloatRect newPlayerRect = playerRect;
        newPlayerRect.left += movement.x;
        newPlayerRect.top += movement.y;
        if (newPlayerRect.intersects(blockRect)) {
            collision = true;
            pLogic->player.sprite.setPosition(oldPosition);
            break;

        }
    }
    if (!collision) {
        pLogic->player.sprite.move(movement);
    }
    else {
        pLogic->player.sprite.move(movement);
    }
}

void DrawGameScene(void *pData, GameView &view)
{
    // Извлекаем указатель на GameLogic, ранее переданный в игровой цикл.
    GameScene *pLogic = reinterpret_cast<GameScene *>(pData);
    sf::RenderTarget &target = view.window;

    pLogic->level.Draw(target);
    for (const TmxObject &coin : pLogic->coins)
    {
        target.draw(coin.sprite);
    }
    for (const TmxObject &enemy : pLogic->enemies)
    {
        target.draw(enemy.sprite);
    }
    target.draw(pLogic->player.sprite);
}

void DestroyGameScene(GameScene *&pScene)
{
    delete pScene;
    pScene = nullptr;
}
