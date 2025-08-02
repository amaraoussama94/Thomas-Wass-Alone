#include "Engine.hpp"
using namespace sf;
using namespace std;

// Where an emitter will be placed
void Engine::populateEmitters(vector<Vector2f>& vSoundEmitters, int** arrayLevel)
{
    // Make sure the vector is empty
    if (!vSoundEmitters.empty())
    {
        vSoundEmitters.clear();
    }

    // Keep track of the previous emitter
    // so we don't make too many
    FloatRect previousEmitter;

    // Search for fire in the level
    for (int x = 0; x < static_cast<int>(m_LM.getLevelSize().x); x++)
    {
        for (int y = 0; y < static_cast<int>(m_LM.getLevelSize().y); y++)
        {
            if (arrayLevel[y][x] == 2) // fire is present
            {
                // Create a rectangle for the current fire tile
                Vector2f firePosition(x * TILE_SIZE, y * TILE_SIZE);
                Vector2f fireSize(TILE_SIZE, TILE_SIZE);
                FloatRect currentRect(firePosition, fireSize);

                // Skip over any fire tiles too near a previous emitter
                if (!previousEmitter.findIntersection(currentRect).has_value())
                {
                    // Add the coordinates of this fire block
                    vSoundEmitters.push_back(firePosition);

                    // Make a rectangle 6 blocks x 6 blocks,
                    // so we don't make any more emitters too close to this one
                    previousEmitter.position = firePosition;
                    previousEmitter.size = Vector2f(TILE_SIZE * 6, TILE_SIZE * 6);
                }
            }
        }
    }
}
