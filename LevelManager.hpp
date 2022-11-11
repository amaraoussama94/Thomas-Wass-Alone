#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <sstream>
#include <fstream>

#include "TextureHolder.hpp"

using namespace sf;
using namespace std;

class LevelManager
{
private:
    Vector2i m_LevelSize; //horizontal and vertical number of tiles that the current map contains
    Vector2f m_StartPosition;
    float m_TimeModifier = 1;
    float m_BaseTimeLimit = 0;
    int m_CurrentLevel = 0;
    const int NUM_LEVELS = 4;
// public declarations go here
public:
    const int TILE_SIZE = 50;
    const int VERTS_IN_QUAD = 4;
    float getTimeLimit();
    Vector2f getStartPosition();
    int** nextLevel(VertexArray& rVaLevel);
    Vector2i getLevelSize();
    int getCurrentLevel();
};