#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.hpp"
#include "Thomas.hpp"
#include "Bob.hpp"
#include "LevelManager.hpp"
#include "SoundManager.hpp"
#include "HUD.hpp"
#include "ParticleSystem.hpp"

using namespace sf;

class Engine {
private:
    //-------------------------
    // Core Game Management
    //-------------------------
    RenderWindow m_Window;              // Main game window
    TextureHolder th;                   // Texture manager (singleton pattern)

    //-------------------------
    // Characters & Gameplay
    //-------------------------
    Thomas m_Thomas;                    // First playable character
    Bob m_Bob;                          // Second playable character
    bool m_Character1 = true;           // Active character (Thomas/Bob)
    bool m_Playing = false;             // Game state flag
    bool m_SplitScreen = false;         // Split-screen mode toggle

    //-------------------------
    // Environment & Level Data
    //-------------------------
    LevelManager m_LM;                  // Level layout loader
    bool m_NewLevelRequired = true;     // Flag to trigger level refresh
    VertexArray m_VALevel;              // Tile vertex array for rendering
    int** m_ArrayLevel = nullptr;       // Raw level data array
    Texture m_TextureTiles;             // Tilesheet texture

    //-------------------------
    // Views & Camera System
    //-------------------------
    View m_MainView;                    // Full-screen view
    View m_LeftView, m_RightView;       // Split-screen character views
    View m_BGMainView, m_BGLeftView, m_BGRightView; // Background decor views
    View m_HudView;                     // HUD overlay view

    //-------------------------
    // Background & Visual Effects
    //-------------------------
    Texture m_BackgroundTexture;        // Background texture (parallax decor)
    std::unique_ptr<sf::Sprite> m_BackgroundSprite; // Sprite initialized in constructor
    Shader m_RippleShader;              // Shader for ripple/water/fire effect
    ParticleSystem m_PS;                // Particle system manager

    //-------------------------
    // HUD & Feedback Systems
    //-------------------------
    Hud m_Hud;                          // HUD UI manager
    int m_FramesSinceLastHUDUpdate = 0;    // Frame counter for HUD refresh
    int m_TargetFramesPerHUDUpdate = 500;  // Target frames between HUD updates

    //-------------------------
    // Audio Management
    //-------------------------
    SoundManager m_SM;                  // Sound effect manager
    std::vector<Vector2f> m_FireEmitters;  // Positions for fire sound emitters

    //-------------------------
    // Timing & Game Rules
    //-------------------------
    float m_TimeRemaining = 10;         // Countdown timer per level
    Time m_GameTimeTotal;               // Accumulated game time
    const int TILE_SIZE = 50;           // Tile dimension in pixels
    const int VERTS_IN_QUAD = 4;        // Vertices per quad (SFML rendering)
    const int GRAVITY = 300;            // Gravity constant for characters

    //-------------------------
    // Internal Logic Functions
    //-------------------------
    void input();                       // Handle all input events
    void update(float dtAsSeconds);     // Game state update
    void draw();                        // Render all visual elements
    void loadLevel();                   // Setup and initialize level
    bool detectCollisions(PlayableCharacter& character); // Collision check
    void populateEmitters(std::vector<Vector2f>& vSoundEmitters, int** arrayLevel); // Setup sound emitters

public:
    // Constructor handles sprite initialization and component setup
    Engine();

    // Main game loop runs update/render logic
    void run();
};
