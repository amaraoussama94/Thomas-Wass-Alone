#include "Background.hpp"

Background::Background()
    : m_BackgroundTexture(TextureHolder::GetTexture("graphics/background.png")),
      m_BackgroundSprite(m_BackgroundTexture) // Initializes with texture directly
{
}

void Background::draw(sf::RenderWindow& window)
{
    window.draw(m_BackgroundSprite);
}
