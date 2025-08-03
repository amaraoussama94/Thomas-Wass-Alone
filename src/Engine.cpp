#include "Engine.hpp"
#include "Logger.hpp"

Engine::Engine()
{
    Logger::Log("Engine.cpp", "Engine constructor started");

    // Retrieve desktop resolution using SFML 3.0's updated API
    Vector2u desktopSize = VideoMode::getDesktopMode().size;
    Vector2f resolution{static_cast<float>(desktopSize.x), static_cast<float>(desktopSize.y)};
    Logger::Log("Engine.cpp", "Desktop resolution retrieved");

    // Create the main render window
    m_Window.create(VideoMode{desktopSize}, "Thomas was late");
    Logger::Log("Engine.cpp", "Main window created");

    // Configure primary game view (centered, full-resolution)
    m_MainView.setSize(resolution);
    m_MainView.setCenter(resolution / 2.f);
    Logger::Log("Engine.cpp", "Main view configured");

    // Configure HUD overlay view with same resolution
    m_HudView.setSize(resolution);
    m_HudView.setCenter(resolution / 2.f);
    Logger::Log("Engine.cpp", "HUD view configured");

    // Split-screen setup: each view covers half of the screen
    m_LeftView.setViewport(FloatRect({0.001f, 0.001f}, {0.498f, 0.998f}));
    m_RightView.setViewport(FloatRect({0.5f, 0.001f}, {0.499f, 0.998f}));
    Logger::Log("Engine.cpp", "Split-screen views configured");

    // Corresponding background views for each gameplay view
    m_BGLeftView.setViewport(FloatRect({0.001f, 0.001f}, {0.498f, 0.998f}));
    m_BGRightView.setViewport(FloatRect({0.5f, 0.001f}, {0.499f, 0.998f}));
    Logger::Log("Engine.cpp", "Background views configured");

    // Ensure shader functionality exists before applying effects
    if (!Shader::isAvailable())
    {
        Logger::Log("Engine.cpp", "Shaders not available — closing window");
        m_Window.close(); // Exit gracefully if shaders unsupported
    }
    else
    {
        Logger::Log("Engine.cpp", "Shaders available — loading shaders...");
        if (!m_RippleShader.loadFromFile("shaders/vertShader.vert", "shaders/rippleShader.frag"))
        {
            Logger::Log("Engine.cpp", "Failed to load shaders");
        }
        else
        {
            Logger::Log("Engine.cpp", "Shaders loaded successfully");
        }
    }

    // Load and bind background texture to sprite (SFML 3.0 compliance)
    m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");
    m_BackgroundSprite = std::make_unique<sf::Sprite>(m_BackgroundTexture);
    Logger::Log("Engine.cpp", "Background texture loaded");

    // Load tile sheet texture for map rendering
    m_TextureTiles = TextureHolder::GetTexture("graphics/tiles_sheet.png");
    Logger::Log("Engine.cpp", "Tile sheet texture loaded");

    // Initialize particle system with a fixed maximum count
    m_PS.init(1000); // Particle limit for effects like fire or dust
    Logger::Log("Engine.cpp", "Particle system initialized");

    Logger::Log("Engine.cpp", "Engine constructor completed");
}

void Engine::run()
{
    Logger::Log("Engine.cpp", "Game run loop started");

    Clock clock;

    while (m_Window.isOpen())
    {
        Time dt = clock.restart();
        m_GameTimeTotal += dt;

        float dtAsSeconds = dt.asSeconds();
        Logger::Log("Engine.cpp", "New frame: dtAsSeconds = " + std::to_string(dtAsSeconds));

        input();
        Logger::Log("Engine.cpp", "Input processed");

        update(dtAsSeconds);
        Logger::Log("Engine.cpp", "Game state updated");

        draw();
        Logger::Log("Engine.cpp", "Frame drawn");
    }

    Logger::Log("Engine.cpp", "Game loop exited");
}
