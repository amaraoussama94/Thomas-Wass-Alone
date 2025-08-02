#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Particle.hpp"

using namespace sf;
using namespace std;
class ParticleSystem : public Drawable //inheriting from SFML's Drawable class
{
private:
    //his vector will hold each and every instance of Particle.
    vector<Particle> m_Particles;
    /*This will be used to draw all the particles
     in the form of a whole bunch of
    Point primitives*/
    VertexArray m_Vertices;
    //how long each effect will last.
    float m_Duration;
    //particle system is currently in use or not??
    bool m_IsRunning = false;
public:
    virtual void draw(RenderTarget& target, RenderStates states) const;
    void init(int count);
    void emitParticles(Vector2f position);
    void update(float elapsed);
    bool running();
};
/********************************/
/**ParticleSystem is a Drawable**/
/*******************************/