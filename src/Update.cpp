#include "Engine.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

// Utility function to replace old intersects() method
bool intersects(const FloatRect& a, const FloatRect& b)
{
    return a.position.x < b.position.x + b.size.x &&
           a.position.x + a.size.x > b.position.x &&
           a.position.y < b.position.y + b.size.y &&
           a.position.y + a.size.y > b.position.y;
}


void Engine::update(float dtAsSeconds)
{
    if (m_NewLevelRequired)
    {
        // These calls to spawn will be moved to a new
        // LoadLevel function soon
        // Spawn Thomas and Bob
        //m_Thomas.spawn(Vector2f(0,0), GRAVITY);
        //m_Bob.spawn(Vector2f(100, 0), GRAVITY);

        // Make sure spawn is called only once
        //m_TimeRemaining = 10;
        //m_NewLevelRequired = false;

        // Load a level
        loadLevel();
    }

    if (m_Playing)
    {
        // Update Thomas
        m_Thomas.update(dtAsSeconds);

        // Update Bob
        m_Bob.update(dtAsSeconds);

        // Detect collisions and see if characters have reached the goal tile
        // The second part of the if condition is only executed
        // when thomas is touching the home tile
        if (detectCollisions(m_Thomas) && detectCollisions(m_Bob))
        {
            // New level required
            m_NewLevelRequired = true;

            // Play the reach goal sound
            m_SM.playReachGoal();
        }
        else
        {
            // Run bobs collision detection
            detectCollisions(m_Bob);
        }

        // Let bob and thomas jump on each others heads
        if (intersects(m_Bob.getFeet(), m_Thomas.getHead()))
        {
            m_Bob.stopFalling(m_Thomas.getHead().position.y);
        }
        else if (intersects(m_Thomas.getFeet(), m_Bob.getHead()))
        {
            m_Thomas.stopFalling(m_Bob.getHead().position.y);
        }

        // Count down the time the player has left
        m_TimeRemaining -= dtAsSeconds;

        // Have Thomas and Bob run out of time?
        if (m_TimeRemaining <= 0)
        {
            m_NewLevelRequired = true;
        }
    } // End if playing

    // Check if a fire sound needs to be played
    for (Vector2f emitter : m_FireEmitters)
    {
        // Where is this emitter?
        float posX = emitter.x;
        float posY = emitter.y;

        // Make a 500 pixel rectangle around the emitter
        FloatRect localRect({posX - 250.f, posY - 250.f}, {500.f, 500.f});

        // Is the player inside localRect?
        if (intersects(m_Thomas.getPosition(), localRect))
        {
            // Play the sound and pass in the location as well
            m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
        }
    }

    // Set the appropriate view around the appropriate character
    if (m_SplitScreen)
    {
        m_LeftView.setCenter(m_Thomas.getCenter());
        m_RightView.setCenter(m_Bob.getCenter());
    }
    else
    {
        // Centre full screen around appropriate character
        if (m_Character1)
        {
            m_MainView.setCenter(m_Thomas.getCenter());
        }
        else
        {
            m_MainView.setCenter(m_Bob.getCenter());
        }
    }

    // Time to update the HUD?
    m_FramesSinceLastHUDUpdate++;

    // Update the HUD every m_TargetFramesPerHUDUpdate frames
    if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
    {
        stringstream ssTime;
        stringstream ssLevel;

        // Update the time text
        ssTime << static_cast<int>(m_TimeRemaining);
        m_Hud.setTime(ssTime.str());

        // Update the level text
        ssLevel << "Level:" << m_LM.getCurrentLevel();
        m_Hud.setLevel(ssLevel.str());

        m_FramesSinceLastHUDUpdate = 0;
    }

    // Update the particles
    if (m_PS.running())
    {
        m_PS.update(dtAsSeconds);
    }
} // End of update function
