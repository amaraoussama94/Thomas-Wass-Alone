#include "HUD.hpp"

Hud::Hud()
{
    // Get desktop resolution (SFML 3.0)
    Vector2u desktopSize = VideoMode::getDesktopMode().size;
    Vector2f resolution(static_cast<float>(desktopSize.x), static_cast<float>(desktopSize.y));

    // Load font (ignore return value)
    (void)m_Font.openFromFile("fonts/Roboto-Light.ttf");

    // --- Start Text (Pause Message) ---
    m_StartText = Text(m_Font, "Press Enter when ready!", 100);
    m_StartText->setFillColor(Color::White);

    // Center the message text using local bounds
    FloatRect textRect = m_StartText->getLocalBounds();
    m_StartText->setOrigin(Vector2f(
        textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f
    ));
    m_StartText->setPosition(Vector2f(resolution.x / 2.0f, resolution.y / 2.0f));

    // --- Time Text ---
    m_TimeText = Text(m_Font, "------", 75);
    m_TimeText->setFillColor(Color::White);
    m_TimeText->setPosition(Vector2f(resolution.x - 150.0f, 0.0f));

    // --- Level Text ---
    m_LevelText = Text(m_Font, "1", 75);
    m_LevelText->setFillColor(Color::White);
    m_LevelText->setPosition(Vector2f(25.0f, 0.0f));
}

Text Hud::getMessage() {
    return m_StartText.value_or(Text(m_Font, "", 30));
}

Text Hud::getLevel() {
    return m_LevelText.value_or(Text(m_Font, "", 30));
}

Text Hud::getTime() {
    return m_TimeText.value_or(Text(m_Font, "", 30));
}


// Safe mutation only if initialized
void Hud::setLevel(String text)
{
    if (m_LevelText.has_value())
        m_LevelText->setString(text);
}

void Hud::setTime(String text)
{
    if (m_TimeText.has_value())
        m_TimeText->setString(text);
}
