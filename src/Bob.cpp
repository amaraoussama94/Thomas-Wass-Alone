#include "Bob.hpp"
#include "TextureHolder.hpp"

Bob::Bob()
    : PlayableCharacter(TextureHolder::GetTexture("graphics/bob.png"))
{
    m_JumpDuration = .25;
}


bool Bob::handleInput()
{
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::Key::Up))
	{

		// Start a jump if not already jumping
		// but only if standing on a block (not falling)
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}

	}
	else
	{
		m_IsJumping = false;
		m_IsFalling = true;

	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		m_LeftPressed = true;

	}
	else
	{
		m_LeftPressed = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::Key::Right))
	{

		m_RightPressed = true;;

	}
	else
	{
		m_RightPressed = false;
	}

	return m_JustJumped;
}