#pragma once
#include <SFML/Graphics.hpp>
#include <optional> // Required for std::optional

using namespace sf;

// HUD class manages pause message, timer, and level display
class Hud
{
private:
    Font m_Font;                        // Font resource used for all text
    std::optional<Text> m_StartText;   // Optional: initialized after font is loaded
    std::optional<Text> m_TimeText;
    std::optional<Text> m_LevelText;

public:
    Hud();                             // Constructor sets up HUD after font loading

    // Getters return default-constructed text if not set
    Text getMessage();
    Text getLevel();
    Text getTime();

    // Setters to update displayed HUD content
    void setLevel(String text);
    void setTime(String text);
};
