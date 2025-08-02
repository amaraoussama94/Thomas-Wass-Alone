#include "Background.h"

Background::Background()
{
    // Load texture directly through your TextureHolder singleton
    m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");

    // Immediately initialize the sprite with the texture
    m_BackgroundSprite = sf::Sprite(m_BackgroundTexture);
}

void Background::draw(sf::RenderWindow& window)
{
    window.draw(m_BackgroundSprite);
}
