#include "SoundManager.hpp"
#include <iostream>

SoundManager::SoundManager()
{
    if (!m_FireBuffer.loadFromFile("audio/fire.wav") ||
        !m_FallInFireBuffer.loadFromFile("audio/fallinfire.wav") ||
        !m_FallInWaterBuffer.loadFromFile("audio/fallinwater.wav") ||
        !m_JumpBuffer.loadFromFile("audio/jump.wav") ||
        !m_ReachGoalBuffer.loadFromFile("audio/reachgoal.wav"))
    {
        std::cerr << "Error loading one or more sound files" << std::endl;
        return;
    }

    // Dynamically allocate sf::Sound with correct buffers
    m_Fire1Sound = new Sound(m_FireBuffer);
    m_Fire2Sound = new Sound(m_FireBuffer);
    m_Fire3Sound = new Sound(m_FireBuffer);
    m_FallInFireSound = new Sound(m_FallInFireBuffer);
    m_FallInWaterSound = new Sound(m_FallInWaterBuffer);
    m_JumpSound = new Sound(m_JumpBuffer);
    m_ReachGoalSound = new Sound(m_ReachGoalBuffer);

    // Enable looping for fire sounds
    m_Fire1Sound->setLooping(true);
    m_Fire2Sound->setLooping(true);
    m_Fire3Sound->setLooping(true);
}

SoundManager::~SoundManager()
{
    delete m_Fire1Sound;
    delete m_Fire2Sound;
    delete m_Fire3Sound;
    delete m_FallInFireSound;
    delete m_FallInWaterSound;
    delete m_JumpSound;
    delete m_ReachGoalSound;
}

void SoundManager::playFire(Vector2f emitterLocation, Vector2f listenerLocation)
{
    Listener::setPosition(Vector3f(listenerLocation.x, listenerLocation.y, 0.0f));
    Vector3f emitterPos(emitterLocation.x, emitterLocation.y, 0.0f);

    switch (m_NextSound)
    {
        case 1:
            m_Fire1Sound->setPosition(emitterPos);
            m_Fire1Sound->play();
            m_NextSound = 2;
            break;
        case 2:
            m_Fire2Sound->setPosition(emitterPos);
            m_Fire2Sound->play();
            m_NextSound = 3;
            break;
        case 3:
            m_Fire3Sound->setPosition(emitterPos);
            m_Fire3Sound->play();
            m_NextSound = 1;
            break;
    }
}

void SoundManager::playFallInFire()
{
    m_FallInFireSound->play();
}

void SoundManager::playFallInWater()
{
    m_FallInWaterSound->play();
}

void SoundManager::playJump()
{
    m_JumpSound->play();
}

void SoundManager::playReachGoal()
{
    m_ReachGoalSound->play();
}
