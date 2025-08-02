#include "ParticleSystem.hpp"

void ParticleSystem::init(int numParticles)
{
    // Set the primitive type to Points (SFML 3.0 compliant)
    m_Vertices.setPrimitiveType(sf::PrimitiveType::Points);
    m_Vertices.resize(numParticles);

    // Create the particles with randomized directions
    for (int i = 0; i < numParticles; i++)
    {
        srand(static_cast<unsigned>(time(0)) + i);
        float angle = static_cast<float>((rand() % 360) * 3.14159 / 180.0);
        float speed = static_cast<float>((rand() % 600) + 600);
        sf::Vector2f direction(cos(angle) * speed, sin(angle) * speed);
        m_Particles.push_back(Particle(direction));
    }
}

void ParticleSystem::update(float dt)
{
    m_Duration -= dt;
    int currentVertex = 0;

    for (auto& particle : m_Particles)
    {
        particle.update(dt);
        m_Vertices[currentVertex++].position = particle.getPosition();
    }

    if (m_Duration < 0)
    {
        m_IsRunning = false;
    }
}

void ParticleSystem::emitParticles(sf::Vector2f startPosition)
{
    m_IsRunning = true;
    m_Duration = 2.0f;
    int currentVertex = 0;

    for (auto& particle : m_Particles)
    {
        m_Vertices[currentVertex++].color = sf::Color::Yellow;
        particle.setPosition(startPosition);
    }
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Vertices, states);
}

bool ParticleSystem::running()
{
    return m_IsRunning;
}
