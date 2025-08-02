#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Particle
{
private:
    Vector2f m_Position;//horizontal and vertical coordinate
    Vector2f m_Velocity;//the horizontal and vertical speed

public:
    Particle(Vector2f direction);// direction/velocity
    void update(float dt);
    void setPosition(Vector2f position);
    Vector2f getPosition();
};