#include <fstream>
#include "LevelManager.hpp"
#include "Logger.hpp"  

int** LevelManager::nextLevel(sf::VertexArray& rVaLevel)
{
    m_CurrentLevel++;
    if (m_CurrentLevel > m_NumLevels)
        m_CurrentLevel = 1;

    std::string levelPath = "levels/level" + std::to_string(m_CurrentLevel) + ".txt";
    Logger::Log("LevelManager", "Loading level file: " + levelPath);

    std::ifstream inputFile(levelPath);
    if (!inputFile.is_open())
    {
        Logger::Log("LevelManager", "ERROR: Failed to open file " + levelPath);
        return nullptr;
    }

    std::string line;
    std::vector<std::string> levelLines;

    while (std::getline(inputFile, line))
    {
        levelLines.push_back(line);
    }
    inputFile.close();

    m_LevelSize.y = levelLines.size();
    m_LevelSize.x = levelLines.empty() ? 0 : levelLines[0].length();
    Logger::Log("LevelManager", "Parsed level size: " + std::to_string(m_LevelSize.x) + "x" + std::to_string(m_LevelSize.y));

    int** levelArray = new int*[m_LevelSize.y];
    for (int i = 0; i < m_LevelSize.y; ++i)
    {
        levelArray[i] = new int[m_LevelSize.x];
    }

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
                    Logger::Log("LevelManager", "Solid block at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
                    break;
                case '2':
                    levelArray[y][x] = 2;
                    m_StartPosition.x = static_cast<float>(x * TILE_SIZE);
                    m_StartPosition.y = static_cast<float>(y * TILE_SIZE);
                    Logger::Log("LevelManager", "Spawn point at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
                    break;
                default:
                    levelArray[y][x] = 0;
                    break;
            }
        }
    }

    rVaLevel.clear();
    rVaLevel.setPrimitiveType(sf::PrimitiveType::Triangles);
    Logger::Log("LevelManager", "Building geometry...");

    int solidTileCount = 0;
    for (int y = 0; y < m_LevelSize.y; ++y)
    {
        for (int x = 0; x < m_LevelSize.x; ++x)
        {
            if (levelArray[y][x] == 1)
            {
                solidTileCount++;

                sf::Vector2f position(x * TILE_SIZE, y * TILE_SIZE);

                sf::Vector2f topLeft     = position;
                sf::Vector2f topRight    = position + sf::Vector2f(TILE_SIZE, 0);
                sf::Vector2f bottomLeft  = position + sf::Vector2f(0, TILE_SIZE);
                sf::Vector2f bottomRight = position + sf::Vector2f(TILE_SIZE, TILE_SIZE);

                sf::Vector2f texTopLeft     = {0.f, 0.f};
                sf::Vector2f texTopRight    = {TILE_SIZE, 0.f};
                sf::Vector2f texBottomLeft  = {0.f, TILE_SIZE};
                sf::Vector2f texBottomRight = {TILE_SIZE, TILE_SIZE};

                sf::Vertex v1, v2, v3, v4, v5, v6;
                v1.position = topLeft;     v1.texCoords = texTopLeft;
                v2.position = topRight;    v2.texCoords = texTopRight;
                v3.position = bottomRight; v3.texCoords = texBottomRight;

                v4.position = topLeft;     v4.texCoords = texTopLeft;
                v5.position = bottomRight; v5.texCoords = texBottomRight;
                v6.position = bottomLeft;  v6.texCoords = texBottomLeft;

                rVaLevel.append(v1);
                rVaLevel.append(v2);
                rVaLevel.append(v3);
                rVaLevel.append(v4);
                rVaLevel.append(v5);
                rVaLevel.append(v6);
            }
        }
    }

    Logger::Log("LevelManager", "Geometry built for " + std::to_string(solidTileCount) + " solid tiles");

    m_BaseTimeLimit = m_LevelSize.y * 10.0f;
    Logger::Log("LevelManager", "Base time limit set: " + std::to_string(m_BaseTimeLimit));

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
