#include "Engine.hpp"

void Engine::input()
{
    while (auto eventOpt = m_Window.pollEvent())
    {
        const sf::Event& event = *eventOpt;

        // Handle window close
        if (event.is<sf::Event::Closed>())
        {
            m_Window.close();
        }

        // Handle key press
        if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
        {
            const auto key = keyEvent->code;

            if (key == sf::Keyboard::Key::Escape)
                m_Window.close();

            if (key == sf::Keyboard::Key::Enter)
                m_Playing = true;

            if (key == sf::Keyboard::Key::Tab)
                m_Character1 = !m_Character1;

            if (key == sf::Keyboard::Key::E)
                m_SplitScreen = !m_SplitScreen;
        }
    }

    // Handle input specific to Thomas
    if (m_Thomas.handleInput())
        m_SM.playJump();

    // Handle input specific to Bob
    if (m_Bob.handleInput())
        m_SM.playJump();
}
