#include "PlayableCharacter.hpp"
#include "logger.hpp"

void PlayableCharacter::spawn(sf::Vector2f startPosition, float gravity)
{
    m_Position = startPosition;
    m_Gravity = gravity;
    m_Sprite.setPosition(m_Position);

    Logger::Log("PlayableCharacter", "Spawned at (" +
        std::to_string(startPosition.x) + ", " +
        std::to_string(startPosition.y) + ") with gravity = " +
        std::to_string(gravity));
}

void PlayableCharacter::update(float elapsedTime)
{
    if (m_RightPressed) {
        m_Position.x += m_Speed * elapsedTime;
        Logger::Log("PlayableCharacter", "Moving right → X = " + std::to_string(m_Position.x));
    }

    if (m_LeftPressed) {
        m_Position.x -= m_Speed * elapsedTime;
        Logger::Log("PlayableCharacter", "Moving left ← X = " + std::to_string(m_Position.x));
    }

    if (m_IsJumping) {
        m_TimeThisJump += elapsedTime;

        if (m_TimeThisJump < m_JumpDuration) {
            m_Position.y -= m_Gravity * 2 * elapsedTime;
            Logger::Log("PlayableCharacter", "Jumping ↑ Y = " +
                std::to_string(m_Position.y) +
                ", Time = " + std::to_string(m_TimeThisJump));
        } else {
            m_IsJumping = false;
            m_IsFalling = true;
            Logger::Log("PlayableCharacter", "Jump ended → falling begins");
        }
    }

    if (m_IsFalling) {
        m_Position.y += m_Gravity * elapsedTime;
        Logger::Log("PlayableCharacter", "Falling ↓ Y = " + std::to_string(m_Position.y));
    }

    sf::FloatRect r = m_Sprite.getGlobalBounds();

    m_Feet.position.x = r.position.x + 3;
    m_Feet.position.y = r.position.y + r.size.y - 1;
    m_Feet.size.x = r.size.x - 6;
    m_Feet.size.y = 1;

    m_Head.position.x = r.position.x;
    m_Head.position.y = r.position.y + (r.size.y * 0.3f);
    m_Head.size.x = r.size.x;
    m_Head.size.y = 1;

    m_Right.position.x = r.position.x + r.size.x - 2;
    m_Right.position.y = r.position.y + r.size.y * 0.35f;
    m_Right.size.x = 1;
    m_Right.size.y = r.size.y * 0.3f;

    m_Left.position.x = r.position.x;
    m_Left.position.y = r.position.y + r.size.y * 0.5f;
    m_Left.size.x = 1;
    m_Left.size.y = r.size.y * 0.3f;

    m_Sprite.setPosition(m_Position);

    Logger::Log("PlayableCharacter", "Updated body rects & sprite position → X = " +
        std::to_string(m_Position.x) + ", Y = " +
        std::to_string(m_Position.y));
}

sf::FloatRect PlayableCharacter::getPosition()
{
    Logger::Log("PlayableCharacter", "Fetching sprite global bounds");
    return m_Sprite.getGlobalBounds();
}

sf::Vector2f PlayableCharacter::getCenter()
{
    sf::FloatRect bounds = m_Sprite.getGlobalBounds();
    sf::Vector2f center(
        m_Position.x + bounds.size.x / 2,
        m_Position.y + bounds.size.y / 2
    );
    Logger::Log("PlayableCharacter", "Center point → (" +
        std::to_string(center.x) + ", " +
        std::to_string(center.y) + ")");
    return center;
}

sf::FloatRect PlayableCharacter::getFeet()  { return m_Feet; }
sf::FloatRect PlayableCharacter::getHead()  { return m_Head; }
sf::FloatRect PlayableCharacter::getLeft()  { return m_Left; }
sf::FloatRect PlayableCharacter::getRight() { return m_Right; }
sf::Sprite PlayableCharacter::getSprite()   { return m_Sprite; }

void PlayableCharacter::stopFalling(float position)
{
    sf::FloatRect bounds = getPosition();
    m_Position.y = position - bounds.size.y;
    m_Sprite.setPosition(m_Position);
    m_IsFalling = false;

    Logger::Log("PlayableCharacter", "Stopped falling → Y = " + std::to_string(m_Position.y));
}

void PlayableCharacter::stopRight(float position)
{
    sf::FloatRect bounds = m_Sprite.getGlobalBounds();
    m_Position.x = position - bounds.size.x;
    m_Sprite.setPosition(m_Position);

    Logger::Log("PlayableCharacter", "Stopped moving right → X = " + std::to_string(m_Position.x));
}

void PlayableCharacter::stopLeft(float position)
{
    sf::FloatRect bounds = m_Sprite.getGlobalBounds();
    m_Position.x = position + bounds.size.x;
    m_Sprite.setPosition(m_Position);

    Logger::Log("PlayableCharacter", "Stopped moving left ← X = " + std::to_string(m_Position.x));
}

void PlayableCharacter::stopJump()
{
    m_IsJumping = false;
    m_IsFalling = true;

    Logger::Log("PlayableCharacter", "Jump interrupted → falling resumes");
}
