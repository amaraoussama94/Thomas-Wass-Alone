#include "Engine.hpp"

void Engine::input()
{
    while (auto eventOpt = m_Window.pollEvent())
    {
        std::visit([&](auto&& event) {
            using T = std::decay_t<decltype(event)>;

            // Handle window close event
            if constexpr (std::is_same_v<T, sf::Event::WindowClosed>)
            {
                m_Window.close();
            }

            // Handle key pressed
            if constexpr (std::is_same_v<T, sf::Event::KeyPressed>)
            {
                // Handle the player quitting
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                {
                    m_Window.close();
                }

                // Handle the player starting the game
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                {
                    m_Playing = true;
                }

                // Switch between Thomas and Bob
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab))
                {
                    m_Character1 = !m_Character1;
                }

                // Switch between full and split-screen
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
                {
                    m_SplitScreen = !m_SplitScreen;
                }
            }
        }, *eventOpt);
    }

    // Handle input specific to Thomas
    if (m_Thomas.handleInput())
    {
        // Play a jump sound
        m_SM.playJump();
    }

    // Handle input specific to Bob
    if (m_Bob.handleInput())
    {
        // Play a jump sound
        m_SM.playJump();
    }
}

