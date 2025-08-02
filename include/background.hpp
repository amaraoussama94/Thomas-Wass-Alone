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
