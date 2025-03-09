#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

/// Структура, абстрагирующая работу с окном и камерой.
///  Код ниже намеренно написан в процедурном стиле:
///  - используются структуры
///  - используются указатели на функции
///  - используется явный вызов new и delete.

struct GameView
{
    sf::RenderWindow window;
    sf::View camera;
    sf::Vector2i windowSize;
    sf::Clock clock;
};

/// Объявляем типы указателей на функции-колбеки (callback),
///  вызываемые из основного цикла игры для совершения игровой логики.
/// Параметр userData - произвольный указатель на внешние данные того,
///  кто предоставляет колбек.
using OnUpdate = void (*)(void* pData, GameView& view, float deltaSec);
using OnDraw = void (*)(void* pData, GameView& view);

/// Создаёт новое окно игры.
GameView* NewGameView(const sf::Vector2i& windowSize);

/// Входит в основной цикл игры и возвращается, когда цикл завершён.
void EnterGameLoop(GameView& view, OnUpdate onUpdate, OnDraw onDraw, void* pData);

/// Центрирует камеру в заданной точке
void SetCameraCenter(GameView& view, const sf::Vector2f& center);

/// Разрушает окно игры и очищает его данные.
void DestroyGameView(GameView*& pView);
