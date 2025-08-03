#include "Engine.hpp"
#include "Logger.hpp"  

void Engine::loadLevel()
{
    Logger::Log("Engine", "Starting level load");

    m_Playing = false;

    Logger::Log("Engine", "Freeing previous level memory");
    for (int i = 0; i < m_LM.getLevelSize().y; ++i)
    {
        delete[] m_ArrayLevel[i];
    }
    delete[] m_ArrayLevel;

    Logger::Log("Engine", "Loading next level");
    m_ArrayLevel = m_LM.nextLevel(m_VALevel);

    Logger::Log("Engine", "Populating sound emitters");
    populateEmitters(m_FireEmitters, m_ArrayLevel);

    m_TimeRemaining = m_LM.getTimeLimit();
    Logger::Log("Engine", "Time remaining set: " + std::to_string(m_TimeRemaining));

    Logger::Log("Engine", "Spawning player characters");
    sf::Vector2f start = m_LM.getStartPosition();
    Logger::Log("Engine", "Start position: (" + std::to_string(start.x) + ", " + std::to_string(start.y) + ")");

    m_Thomas.spawn(start, GRAVITY);
    m_Bob.spawn(start, GRAVITY);

    m_NewLevelRequired = false;
    Logger::Log("Engine", "Level load complete");
}
