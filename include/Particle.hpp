/**
 * @file Particle.hpp
 * @brief Declaration of the Particle class for individual particles in the particle system
 * @date 2025-06-15
 * @version 1.0
 * @author Oussama amara
 */
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