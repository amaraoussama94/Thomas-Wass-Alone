#include "Engine.hpp"
#include <SFML/Graphics/Rect.hpp> // For FloatRect and findIntersection

bool Engine::detectCollisions(PlayableCharacter& character)
{
    bool reachedGoal = false;

    sf::FloatRect detectionZone = character.getPosition();
    sf::FloatRect block({0.f, 0.f}, {TILE_SIZE, TILE_SIZE});

    int startX = static_cast<int>(detectionZone.position.x / TILE_SIZE) - 1;
    int startY = static_cast<int>(detectionZone.position.y / TILE_SIZE) - 1;
    int endX   = static_cast<int>(detectionZone.position.x / TILE_SIZE) + 2;
    int endY   = static_cast<int>(detectionZone.position.y / TILE_SIZE) + 3;

    startX = std::max(startX, 0);
    startY = std::max(startY, 0);
    endX = std::min(endX, static_cast<int>(m_LM.getLevelSize().x));
    endY = std::min(endY, static_cast<int>(m_LM.getLevelSize().y));

    sf::FloatRect level({0.f, 0.f}, {
        m_LM.getLevelSize().x * TILE_SIZE,
        m_LM.getLevelSize().y * TILE_SIZE });

    if (!detectionZone.findIntersection(level).has_value())
    {
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
                character.spawn(m_LM.getStartPosition(), GRAVITY);
                if (tile == 2)
                    m_SM.playFallInFire();
                else
                    m_SM.playFallInWater();
            }

            if (tile == 1)
            {
                if (character.getRight().findIntersection(block).has_value())
                    character.stopRight(block.position.x);
                else if (character.getLeft().findIntersection(block).has_value())
                    character.stopLeft(block.position.x);

                if (character.getFeet().findIntersection(block).has_value())
                    character.stopFalling(block.position.y);
                else if (character.getHead().findIntersection(block).has_value())
                    character.stopJump();
            }

            if (!m_PS.running() &&
                (tile == 2 || tile == 3) &&
                character.getFeet().findIntersection(block).has_value())
            {
                m_PS.emitParticles(character.getCenter());
            }

            if (tile == 4)
            {
                reachedGoal = true;
            }
        }
    }

    return reachedGoal;
}
