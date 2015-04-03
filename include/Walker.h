#ifndef WALKER_H
#define WALKER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "RandomGenerator.h"

#ifndef _NOEXCEPT
#define _NOEXCEPT noexcept
#endif

typedef float FrameTime;

class Walker
{
public:

    static int sSelected;
    static RandomGenerator gen;

    Walker(float mX, float mY);
    virtual ~Walker();

    static void changeStrenght();
    void update(FrameTime ft, sf::RenderWindow& window);
    void draw(sf::RenderTarget& target);
    sf::Vector2f getPosition() const _NOEXCEPT;
    sf::Vector3f getColor() const _NOEXCEPT;
    float left()   const _NOEXCEPT;
    float right()  const _NOEXCEPT;
    float top()    const _NOEXCEPT;
    float bottom() const _NOEXCEPT;





protected:
private:
    const float walkerWidth = 8.f;
    const float walkerHeight = 8.f;
    const float walkerVelocity = 1.f;

    float strenghts[2];

    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Vector3f color;

    void generateRandomColor();
    int generateRandomChance();
    float generateVelocityFloat();
    void normalize(sf::Vector2f& source);
};

#endif // WALKER_H
