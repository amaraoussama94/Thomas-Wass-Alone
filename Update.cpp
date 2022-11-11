#include "Engine.hpp"

#include <sstream>
//#include <SFML/Graphics.hpp>
//using namespace sf;

void Engine::update(float dtAsSeconds)
{
    if (m_Playing)
    {
        // Count down the time the player has left
        m_TimeRemaining -= dtAsSeconds;
        // Have Thomas and Bob run out of time?
        if (m_TimeRemaining <= 0)
        {
            m_NewLevelRequired = true;
        }
    }// End if playing
}