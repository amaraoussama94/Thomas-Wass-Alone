#include "LevelManager.hpp"
#include <fstream>

int** LevelManager::nextLevel(sf::VertexArray& rVaLevel)
{
    // Increment the current level
    m_CurrentLevel++;

    // Reset to level 1 if we reached beyond the last
    if (m_CurrentLevel > m_NumLevels)
        m_CurrentLevel = 1;

    std::string levelPath = "levels/level" + std::to_string(m_CurrentLevel) + ".txt";

    std::ifstream inputFile(levelPath);
    std::string line;
    std::vector<std::string> levelLines;

    // Read level data from file
    while (std::getline(inputFile, line))
    {
        levelLines.push_back(line);
    }

    // Set level size based on file
    m_LevelSize.y = levelLines.size();
    m_LevelSize.x = levelLines[0].length();

    // Allocate memory for the level array
    int** levelArray = new int*[m_LevelSize.y];
    for (int i = 0; i < m_LevelSize.y; ++i)
    {
        levelArray[i] = new int[m_LevelSize.x];
    }

    // Parse the level map
    for (size_t y = 0; y < levelLines.size(); ++y)
    {
        std::string row = levelLines[y];

        for (size_t x = 0; x < row.length(); ++x)
        {
            char cell = row[x];

            switch (cell)
            {
                case '1':
                    levelArray[y][x] = 1;
                    break;
                case '2':
                    levelArray[y][x] = 2;
                    m_StartPosition.x = static_cast<float>(x * TILE_SIZE);
                    m_StartPosition.y = static_cast<float>(y * TILE_SIZE);
                    break;
                default:
                    levelArray[y][x] = 0;
                    break;
            }
        }
    }

    // Clear the vertex array
    rVaLevel.clear();

    // SFML 3.0 uses triangles now
    rVaLevel.setPrimitiveType(sf::PrimitiveType::Triangles);

    // Populate the vertex array based on level data
    for (int y = 0; y < m_LevelSize.y; ++y)
    {
        for (int x = 0; x < m_LevelSize.x; ++x)
        {
            if (levelArray[y][x] == 1)
            {
                sf::Vector2f position(x * TILE_SIZE, y * TILE_SIZE);

                sf::Vector2f topLeft     = position;
                sf::Vector2f topRight    = position + sf::Vector2f(TILE_SIZE, 0);
                sf::Vector2f bottomLeft  = position + sf::Vector2f(0, TILE_SIZE);
                sf::Vector2f bottomRight = position + sf::Vector2f(TILE_SIZE, TILE_SIZE);

                sf::Vector2f texTopLeft     = {0.f, 0.f};
                sf::Vector2f texTopRight    = {TILE_SIZE, 0.f};
                sf::Vector2f texBottomLeft  = {0.f, TILE_SIZE};
                sf::Vector2f texBottomRight = {TILE_SIZE, TILE_SIZE};

                // First triangle
                rVaLevel.append(sf::Vertex(topLeft, texTopLeft));
                rVaLevel.append(sf::Vertex(topRight, texTopRight));
                rVaLevel.append(sf::Vertex(bottomRight, texBottomRight));

                // Second triangle
                rVaLevel.append(sf::Vertex(topLeft, texTopLeft));
                rVaLevel.append(sf::Vertex(bottomRight, texBottomRight));
                rVaLevel.append(sf::Vertex(bottomLeft, texBottomLeft));
            }
        }
    }

    // Scale time limit based on level size
    m_BaseTimeLimit = m_LevelSize.y * 10.0f;
    return levelArray;
}
