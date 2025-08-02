#include "SoundManager.hpp"
#include <SFML/Audio.hpp>

SoundManager::SoundManager()
{
    // Load sound buffers
    m_FireBuffer.loadFromFile("audio/fire.wav");
    m_JumpBuffer.loadFromFile("audio/jump.wav");

    // Assign buffers to sounds
    m_Fire1Sound.setBuffer(m_FireBuffer);
    m_Fire2Sound.setBuffer(m_FireBuffer);
    m_Fire3Sound.setBuffer(m_FireBuffer);
    m_JumpSound.setBuffer(m_JumpBuffer);

    // Enable looping for fire sounds
    m_Fire1Sound.setLooping(true);
    m_Fire2Sound.setLooping(true);
    m_Fire3Sound.setLooping(true);
}

void SoundManager::playJump()
{
    m_JumpSound.play();
}

void SoundManager::playFire(sf::Vector2f emitterLocation, sf::Vector2f listenerLocation)
{
    // Set listener position in 3D space
    sf::Listener::setPosition(sf::Vector3f(listenerLocation.x, listenerLocation.y, 0.0f));

    // Set emitter positions
    sf::Vector3f emitterPos(emitterLocation.x, emitterLocation.y, 0.0f);

    m_Fire1Sound.setPosition(emitterPos);
    m_Fire2Sound.setPosition(emitterPos);
    m_Fire3Sound.setPosition(emitterPos);

    // Play all fire sounds
    m_Fire1Sound.play();
    m_Fire2Sound.play();
    m_Fire3Sound.play();
}
