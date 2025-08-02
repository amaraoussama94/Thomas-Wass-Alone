#include "Engine.hpp"

Engine::Engine()
{
    // Retrieve desktop resolution using SFML 3.0's updated API
    Vector2u desktopSize = VideoMode::getDesktopMode().size;
    Vector2f resolution{static_cast<float>(desktopSize.x), static_cast<float>(desktopSize.y)};

    // Create the main render window
    m_Window.create(VideoMode{desktopSize}, "Thomas was late");
    // Optional: Use sf::Style::Fullscreen for immersive gameplay

    // Configure primary game view (centered, full-resolution)
    m_MainView.setSize(resolution);
    m_MainView.setCenter(resolution / 2.f);

    // Configure HUD overlay view with same resolution
    m_HudView.setSize(resolution);
    m_HudView.setCenter(resolution / 2.f);

    // Split-screen setup: each view covers half of the screen
    m_LeftView.setViewport(FloatRect({0.001f, 0.001f}, {0.498f, 0.998f}));
    m_RightView.setViewport(FloatRect({0.5f, 0.001f}, {0.499f, 0.998f}));

    // Corresponding background views for each gameplay view
    m_BGLeftView.setViewport(FloatRect({0.001f, 0.001f}, {0.498f, 0.998f}));
    m_BGRightView.setViewport(FloatRect({0.5f, 0.001f}, {0.499f, 0.998f}));

    // Ensure shader functionality exists before applying effects
    if (!Shader::isAvailable())
    {
        m_Window.close(); // Exit gracefully if shaders unsupported
    }
    else
    {
        // Load vertex and fragment shaders for ripple effects
        if (!m_RippleShader.loadFromFile("shaders/vertShader.vert", "shaders/rippleShader.frag"))
        {
            // You may want to log or throw shader loading errors here
        }
    }

    // Load and bind background texture to sprite (SFML 3.0 compliance)
	m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");
	m_BackgroundSprite = std::make_unique<sf::Sprite>(m_BackgroundTexture);

    // Load tile sheet texture for map rendering
    m_TextureTiles = TextureHolder::GetTexture("graphics/tiles_sheet.png");

    // Initialize particle system with a fixed maximum count
    m_PS.init(1000); // Particle limit for effects like fire or dust
}

void Engine::run()
{
    Clock clock; // SFML clock to measure frame durations

    while (m_Window.isOpen())
    {
        // Time since last frame
        Time dt = clock.restart();
        m_GameTimeTotal += dt;

        // Convert time delta to seconds for uniform updates
        float dtAsSeconds = dt.asSeconds();

        // Game loop: input → update → draw
        input();
        update(dtAsSeconds);
        draw();
    }
}
