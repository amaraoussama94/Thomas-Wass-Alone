#include "Engine.hpp"
#include "Logger.hpp"  
#include <SFML/Graphics/Rect.hpp> 

bool Engine::detectCollisions(PlayableCharacter& character)
{
    bool reachedGoal = false;

    sf::FloatRect detectionZone = character.getPosition();
    Logger::Log("Engine", "Detection zone: (" +
        std::to_string(detectionZone.left) + ", " +
        std::to_string(detectionZone.top) + ", " +
        std::to_string(detectionZone.width) + ", " +
        std::to_string(detectionZone.height) + ")");

    sf::FloatRect block({0.f, 0.f}, {TILE_SIZE, TILE_SIZE});

    int startX = static_cast<int>(detectionZone.left / TILE_SIZE) - 1;
    int startY = static_cast<int>(detectionZone.top / TILE_SIZE) - 1;
    int endX   = static_cast<int>(detectionZone.left / TILE_SIZE) + 2;
    int endY   = static_cast<int>(detectionZone.top / TILE_SIZE) + 3;

    startX = std::max(startX, 0);
    startY = std::max(startY, 0);
    endX = std::min(endX, m_LM.getLevelSize().x);
    endY = std::min(endY, m_LM.getLevelSize().y);

    sf::FloatRect level({0.f, 0.f}, {
        m_LM.getLevelSize().x * TILE_SIZE,
        m_LM.getLevelSize().y * TILE_SIZE });

    if (!detectionZone.findIntersection(level).has_value())
    {
        Logger::Log("Engine", "Character out of bounds. Respawning...");
        character.spawn(m_LM.getStartPosition(), GRAVITY);
    }

    for (int x = startX; x < endX; ++x)
    {
        for (int y = startY; y < endY; ++y)
        {
            block.left = x * TILE_SIZE;
            block.top = y * TILE_SIZE;
            int tile = m_ArrayLevel[y][x];

            if ((tile == 2 || tile == 3) &&
                character.getHead().findIntersection(block).has_value())
            {
                Logger::Log("Engine", "Hazard detected at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
                character.spawn(m_LM.getStartPosition(), GRAVITY);

                if (tile == 2)
                    m_SM.playFallInFire();
                else
                    m_SM.playFallInWater();
            }

            if (tile == 1)
            {
                if (character.getRight().findIntersection(block).has_value())
                {
                    character.stopRight(block.left);
                    Logger::Log("Engine", "Wall collision → stopRight at X=" + std::to_string(block.left));
                }
                else if (character.getLeft().findIntersection(block).has_value())
                {
                    character.stopLeft(block.left);
                    Logger::Log("Engine", "Wall collision → stopLeft at X=" + std::to_string(block.left));
                }

                if (character.getFeet().findIntersection(block).has_value())
                {
                    character.stopFalling(block.top);
                    Logger::Log("Engine", "Ground detected → stopFalling at Y=" + std::to_string(block.top));
                }
                else if (character.getHead().findIntersection(block).has_value())
                {
                    character.stopJump();
                    Logger::Log("Engine", "Ceiling collision → stopJump");
                }
            }

            if (!m_PS.running() &&
                (tile == 2 || tile == 3) &&
                character.getFeet().findIntersection(block).has_value())
            {
                Logger::Log("Engine", "Particle emission triggered at center");
                m_PS.emitParticles(character.getCenter());
            }

            if (tile == 4)
            {
                reachedGoal = true;
                Logger::Log("Engine", "Goal reached at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
            }
        }
    }

    return reachedGoal;
}
