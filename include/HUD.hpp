/**
 * @file HUD.hpp
 * @brief Declaration of the Hud class to manage the Heads-Up Display in the game
 * @date 2025-06-15
 * @version 1.0
 * @author Oussama amara
 */
#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Hud
{
private:
    Font m_Font;
    Text m_StartText;
    Text m_TimeText;
    Text m_LevelText;

public:
    Hud();
    Text getMessage();
    Text getLevel();
    Text getTime();
    void setLevel(String text);
    void setTime(String text);
};