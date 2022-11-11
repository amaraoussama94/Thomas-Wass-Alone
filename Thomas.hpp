#pragma once
#include "PlayableCharacter.hpp"

class Thomas : public PlayableCharacter
{
public:
    // A constructor specific to Thomas
    Thomas();
    // The overridden input handler for Thomas
    bool virtual handleInput();
    };