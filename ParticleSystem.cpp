#include "ParticleSystem.hpp"

void ParticleSystem::init(int numParticles)
{
    m_Vertices.setPrimitiveType(Points);
    m_Vertices.resize(numParticles);
    // Create the particles
    //creates random values for speed and angle
    for (int i = 0; i < numParticles; i++)
    {
        srand(time(0) + i);
        float angle = (rand() % 360) * 3.14f / 180.f;
        float speed = (rand() % 600) + 600.f;
        Vector2f direction;
        direction = Vector2f(cos(angle) * speed,sin(angle) * speed);
        m_Particles.push_back(Particle(direction));
    }
}

void ParticleSystem::update(float dt)
{
    m_Duration -= dt;//This is so we know when the two seconds have elapsed
    vector<Particle>::iterator i;
    int currentVertex = 0;
    for (i = m_Particles.begin(); i != m_Particles.end(); i++)
    {
        // Move the particle
        (*i).update(dt);
        // Update the vertex array
        m_Vertices[currentVertex++].position = i->getPosition();
    }
    /*If two seconds have elapsed, m_IsRunning is
    set to false*/
    if (m_Duration < 0)
    {
        m_IsRunning = false;
    }
}

void ParticleSystem::emitParticles(Vector2f startPosition)
{
    m_IsRunning = true;
    m_Duration = 2;
    int currentVertex = 0;
    for (auto it = m_Particles.begin();it != m_Particles.end();it++)
    {
        m_Vertices[currentVertex++].color = Color::Yellow;
        it->setPosition(startPosition);
    }
}