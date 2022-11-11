 #pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.hpp"

using namespace sf;

class Engine
{
private:
    // The texture holder
    TextureHolder th;
    const int TILE_SIZE = 50;//each tile in the sprite-sheet is 50 pixels wide and 50 pixels high
    const int VERTS_IN_QUAD = 4;
    // The force pushing the characters down
    const int GRAVITY = 300;//number of pixels by which the game characters will be pushed downward each secon
    // A regular RenderWindow
    RenderWindow m_Window;
    // The main Views
    View m_MainView;
    View m_LeftView;
    View m_RightView;
    // Three views for the background
    View m_BGMainView;
    View m_BGLeftView;
    View m_BGRightView;
    View m_HudView;
    // Declare a sprite and a Texture
    // for the background
    Sprite m_BackgroundSprite;
    Texture m_BackgroundTexture;
    // Is the game currently playing?
    bool m_Playing = false;
    // Is character 1 or 2 the current focus?
    bool m_Character1 = true;//Initially, it is initialized to true, to center on Thomas
    // Start in full screen (not split) mode
    bool m_SplitScreen = false;
    // Time left in the current level (seconds)
    float m_TimeRemaining = 10;
    Time m_GameTimeTotal;
    // Is it time for a new/first level?
    bool m_NewLevelRequired = true;
    // Private functions for internal use only
    void input();
    void update(float dtAsSeconds);
    void draw();
public:
    // The Engine constructor
    Engine();
    // Run will call all the private functions
    void run();
};