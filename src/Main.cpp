/**
 * @file Main.cpp
 * @brief Entry point for the Thomas Was Alone game engine.
 * @version 1.0
 * @date 2024-08-15
 * @author Oussama Amara
 */
#include "Engine.hpp"

int main()
{
	// Declare an instance of Engine
	Engine engine;

	// Start the engine
	engine.run();

	// Quit in the usual way when the engine is stopped
	return 0;
}