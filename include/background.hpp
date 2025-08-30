/**
 * @file background.hpp
 * @brief Declaration of the Background class for managing the game background
 * @date 2025-06-15
 * @version 1.0
 * @author Oussama amara
 */
#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.hpp"

class Background
{
public:
    Background();

    void draw(sf::RenderWindow& window);

private:
    sf::Texture m_BackgroundTexture;
    sf::Sprite m_BackgroundSprite;
};
