/**
 * @file background.cpp
 * @brief Implementation of the Background class for rendering the game background.
 * @version 1.0
 * @date 2024-08-15
 * @author Oussama Amara
 */
#include "background.hpp"

Background::Background()
    : m_BackgroundTexture(TextureHolder::GetTexture("graphics/background.png")),
      m_BackgroundSprite(m_BackgroundTexture) // Initializes with texture directly
{
}

void Background::draw(sf::RenderWindow& window)
{
    window.draw(m_BackgroundSprite);
}
