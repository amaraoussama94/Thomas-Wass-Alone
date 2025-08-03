#include "Engine.hpp"
#include <SFML/Graphics/Rect.hpp> // For FloatRect and findIntersection
#include "logger.hpp"

bool Engine::detectCollisions(PlayableCharacter& character)
{
    Logger::Log("Collisions","Engine: Starting collision detection");
    bool reachedGoal = false;

    sf::FloatRect detectionZone = character.getPosition();
    Logger::Log("Collisions","Engine: detectionZone retrieved");

    sf::FloatRect block({0.f, 0.f}, {TILE_SIZE, TILE_SIZE});
    Logger::Log("Collisions","Engine: initialized block for collision");

    int startX = static_cast<int>(detectionZone.position.x / TILE_SIZE) - 1;
    int startY = static_cast<int>(detectionZone.position.y / TILE_SIZE) - 1;
    int endX   = static_cast<int>(detectionZone.position.x / TILE_SIZE) + 2;
    int endY   = static_cast<int>(detectionZone.position.y / TILE_SIZE) + 3;
    Logger::Log("Collisions","Engine: detection bounds calculated");

    startX = std::max(startX, 0);
    startY = std::max(startY, 0);
    endX = std::min(endX, static_cast<int>(m_LM.getLevelSize().x));
    endY = std::min(endY, static_cast<int>(m_LM.getLevelSize().y));
    Logger::Log("Collisions","Engine: clamped detection bounds");

    sf::FloatRect level({0.f, 0.f}, {
        m_LM.getLevelSize().x * TILE_SIZE,
        m_LM.getLevelSize().y * TILE_SIZE });

    if (!detectionZone.findIntersection(level).has_value())
    {
        Logger::Log("Collisions","Engine: Out of bounds — respawning character");
        character.spawn(m_LM.getStartPosition(), GRAVITY);
    }

    for (int x = startX; x < endX; ++x)
    {
        for (int y = startY; y < endY; ++y)
        {
            block.position.x = x * TILE_SIZE;
            block.position.y = y * TILE_SIZE;
            int tile = m_ArrayLevel[y][x];

            if ((tile == 2 || tile == 3) &&
                character.getHead().findIntersection(block).has_value())
            {
                Logger::Log("Collisions","Engine: Head collided with hazard at (" +
                    std::to_string(x) + ", " + std::to_string(y) + ")");
                character.spawn(m_LM.getStartPosition(), GRAVITY);

                if (tile == 2) m_SM.playFallInFire();
                else m_SM.playFallInWater();
            }

            if (tile == 1)
            {
                if (character.getRight().findIntersection(block).has_value())
                    Logger::Log("Collisions","Engine: Right wall collision at X = " + std::to_string(block.position.x));
                else if (character.getLeft().findIntersection(block).has_value())
                    Logger::Log("Collisions","Engine: Left wall collision at X = " + std::to_string(block.position.x));

                if (character.getFeet().findIntersection(block).has_value())
                    Logger::Log("Collisions","Engine: Landed on ground at Y = " + std::to_string(block.position.y));
                else if (character.getHead().findIntersection(block).has_value())
                    Logger::Log("Collisions","Engine: Hit ceiling, stopping jump");
            }

            if (!m_PS.running() &&
                (tile == 2 || tile == 3) &&
                character.getFeet().findIntersection(block).has_value())
            {
                Logger::Log("Collisions","Engine: Triggering particle effect at feet");
                m_PS.emitParticles(character.getCenter());
            }

            if (tile == 4)
            {
                reachedGoal = true;
                Logger::Log("Collisions","Engine: Goal reached at (" +
                    std::to_string(x) + ", " + std::to_string(y) + ")");
            }
        }
    }

    Logger::Log("Collisions","Engine: Collision detection complete");
    return reachedGoal;
}
