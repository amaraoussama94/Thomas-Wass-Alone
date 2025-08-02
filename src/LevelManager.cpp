
#include <fstream>
#include "LevelManager.hpp"

int** LevelManager::nextLevel(sf::VertexArray& rVaLevel)
{
    // Increment the current level
    m_CurrentLevel++;
    if (m_CurrentLevel > m_NumLevels)
        m_CurrentLevel = 1;

    std::string levelPath = "levels/level" + std::to_string(m_CurrentLevel) + ".txt";
    std::ifstream inputFile(levelPath);
    std::string line;
    std::vector<std::string> levelLines;

    // Read the level file line by line
    while (std::getline(inputFile, line))
    {
        levelLines.push_back(line);
    }

    m_LevelSize.y = levelLines.size();
    m_LevelSize.x = levelLines[0].length();

    // Allocate the level array
    int** levelArray = new int*[m_LevelSize.y];
    for (int i = 0; i < m_LevelSize.y; ++i)
    {
        levelArray[i] = new int[m_LevelSize.x];
    }

    // Fill the array with values from file
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

    // Clear and set primitive type
    rVaLevel.clear();
    rVaLevel.setPrimitiveType(sf::PrimitiveType::Triangles);

    // Build geometry using triangles
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

                // First triangle (topLeft, topRight, bottomRight)
                sf::Vertex v1, v2, v3;
                v1.position = topLeft;     v1.texCoords = texTopLeft;
                v2.position = topRight;    v2.texCoords = texTopRight;
                v3.position = bottomRight; v3.texCoords = texBottomRight;
                rVaLevel.append(v1);
                rVaLevel.append(v2);
                rVaLevel.append(v3);

                // Second triangle (topLeft, bottomRight, bottomLeft)
                sf::Vertex v4, v5, v6;
                v4.position = topLeft;     v4.texCoords = texTopLeft;
                v5.position = bottomRight; v5.texCoords = texBottomRight;
                v6.position = bottomLeft;  v6.texCoords = texBottomLeft;
                rVaLevel.append(v4);
                rVaLevel.append(v5);
                rVaLevel.append(v6);
            }
        }
    }

    // Set the time limit for the level
    m_BaseTimeLimit = m_LevelSize.y * 10.0f;
    return levelArray;
}

float LevelManager::getTimeLimit()
{
    return m_BaseTimeLimit * m_TimeModifier;
}

sf::Vector2f LevelManager::getStartPosition()
{
    return m_StartPosition;
}

sf::Vector2i LevelManager::getLevelSize()
{
    return m_LevelSize;
}

int LevelManager::getCurrentLevel()
{
    return m_CurrentLevel;
}
