/**
 * @file Thomas.hpp
 * @brief Declaration of the Thomas class, a playable character in the game
 * @date 2025-06-15
 * @version 1.0
 * @author Oussama amara
 */
#pragma once
#include "PlayableCharacter.hpp"

class Thomas : public PlayableCharacter
{
public:
	// A constructor specific to Thomas
	 Thomas();

	// The overriden input handler for Thomas
	bool virtual handleInput();

};
