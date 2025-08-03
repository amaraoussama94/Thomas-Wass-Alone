#include "PlayableCharacter.hpp"
#include "Logger.hpp"  

void PlayableCharacter::spawn(sf::Vector2f startPosition, float gravity)
{
    m_Position = startPosition;
    m_Gravity = gravity;
    m_Sprite.setPosition(m_Position);

    Logger::Log("PlayableCharacter", "Spawned at (" +
        std::to_string(startPosition.x) + ", " +
        std::to_string(startPosition.y) + "), gravity = " +
        std::to_string(gravity));
}

void PlayableCharacter::update(float elapsedTime)
{
    bool moved = false;

    if (m_RightPressed)
    {
        m_Position.x += m_Speed * elapsedTime;
        moved = true;
        Logger::Log("PlayableCharacter", "Moving right → new X: " + std::to_string(m_Position.x));
    }

    if (m_LeftPressed)
    {
        m_Position.x -= m_Speed * elapsedTime;
        moved = true;
        Logger::Log("PlayableCharacter", "Moving left ← new X: " + std::to_string(m_Position.x));
    }

    if (m_IsJumping)
    {
        m_TimeThisJump += elapsedTime;

        if (m_TimeThisJump < m_JumpDuration)
        {
            m_Position.y -= m_Gravity * 2 * elapsedTime;
            Logger::Log("PlayableCharacter", "Jumping ↑ time: " + std::to_string(m_TimeThisJump) +
                ", Y: " + std::to_string(m_Position.y));
        }
        else
        {
            m_IsJumping = false;
            m_IsFalling = true;
            Logger::Log("PlayableCharacter", "Jump ended → falling begins");
        }
    }

    if (m_IsFalling)
    {
        m_Position.y += m_Gravity * elapsedTime;
        Logger::Log("PlayableCharacter", "Falling ↓ updated Y: " + std::to_string(m_Position.y));
    }

    sf::FloatRect r = m_Sprite.getGlobalBounds();

    // Feet
    m_Feet.position.x = r.left + 3;
    m_Feet.position.y = r.top + r.height - 1;
    m_Feet.width = r.width - 6;
    m_Feet.height = 1;

    // Head
    m_Head.position.x = r.left;
    m_Head.position.y = r.top + (r.height * 0.3f);
    m_Head.width = r.width;
    m_Head.height = 1;

    // Right
    m_Right.position.x = r.left + r.width - 2;
    m_Right.position.y = r.top + r.height * 0.35f;
    m_Right.width = 1;
    m_Right.height = r.height * 0.3f;

    // Left
    m_Left.position.x = r.left;
    m_Left.position.y = r.top + r.height * 0.5f;
    m_Left.width = 1;
    m_Left.height = r.height * 0.3f;

    if (moved || m_IsJumping || m_IsFalling)
        Logger::Log("PlayableCharacter", "Updated position to: (" + std::to_string(m_Position.x) +
            ", " + std::to_string(m_Position.y) + ")");

    m_Sprite.setPosition(m_Position);
}

sf::FloatRect PlayableCharacter::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

sf::Vector2f PlayableCharacter::getCenter()
{
    sf::FloatRect bounds = m_Sprite.getGlobalBounds();
    return sf::Vector2f(
        m_Position.x + bounds.width / 2,
        m_Position.y + bounds.height / 2
    );
}

sf::FloatRect PlayableCharacter::getFeet()  { return m_Feet; }
sf::FloatRect PlayableCharacter::getHead()  { return m_Head; }
sf::FloatRect PlayableCharacter::getLeft()  { return m_Left; }
sf::FloatRect PlayableCharacter::getRight() { return m_Right; }
sf::Sprite PlayableCharacter::getSprite()   { return m_Sprite; }

void PlayableCharacter::stopFalling(float position)
{
    sf::FloatRect bounds = getPosition();
    m_Position.y = position - bounds.height;
    m_Sprite.setPosition(m_Position);
    m_IsFalling = false;

    Logger::Log("PlayableCharacter", "Stopped falling at Y = " + std::to_string(m_Position.y));
}

void PlayableCharacter::stopRight(float position)
{
    sf::FloatRect bounds = m_Sprite.getGlobalBounds();
    m_Position.x = position - bounds.width;
    m_Sprite.setPosition(m_Position);

    Logger::Log("PlayableCharacter", "Stopped moving right at X = " + std::to_string(m_Position.x));
}

void PlayableCharacter::stopLeft(float position)
{
    sf::FloatRect bounds = m_Sprite.getGlobalBounds();
    m_Position.x = position + bounds.width;
    m_Sprite.setPosition(m_Position);

    Logger::Log("PlayableCharacter", "Stopped moving left at X = " + std::to_string(m_Position.x));
}

void PlayableCharacter::stopJump()
{
    m_IsJumping = false;
    m_IsFalling = true;

    Logger::Log("PlayableCharacter", "Jump cancelled → falling resumed");
}
