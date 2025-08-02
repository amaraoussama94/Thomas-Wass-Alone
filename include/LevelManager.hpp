#pragma once

#include <SFML/Graphics.hpp>

class LevelManager
{
private:
    sf::Vector2i m_LevelSize;         // Number of tiles in x and y direction
    sf::Vector2f m_StartPosition;     // Where the player should start
    float m_TimeModifier = 1.0f;
    float m_BaseTimeLimit = 0.0f;
    int m_CurrentLevel = 0;
    static constexpr int m_NumLevels = 4;

public:
    static constexpr int TILE_SIZE = 50;
    static constexpr int VERTS_IN_QUAD = 4;

    // Get the time limit of the level
    float getTimeLimit();

    // Get the player's starting position
    sf::Vector2f getStartPosition();

    // Load the next level and fill vertex array
    int** nextLevel(sf::VertexArray& rVaLevel);

    // Get current level's tile dimensions
    sf::Vector2i getLevelSize();

    // Get current level number
    int getCurrentLevel();
};
