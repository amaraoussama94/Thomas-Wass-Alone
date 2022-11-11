#pragma once
#include "PlayableCharacter.hpp"

class Bob : public PlayableCharacter
{
public:
    // A constructor specific to Bob
    Bob();
    // The overriden input handler for Bob
    bool virtual handleInput();
};