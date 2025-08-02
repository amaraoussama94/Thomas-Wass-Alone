#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected:
	// Of course we will need a sprite
	Sprite m_Sprite;

	// How long does a jump last
	float m_JumpDuration; //The greater the value, the further/higher the character will be able to jump

	// Is character currently jumping or falling
	bool m_IsJumping;
	bool m_IsFalling;

	// Which directions is the character currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;

	// How long has this jump lasted so far
	float m_TimeThisJump;

	// Has the player just initialted a jump
	bool m_JustJumped = false;

	// Private variables and functions come next
private:
	// What is the gravity
	float m_Gravity;

	// How fast is the character
	float m_Speed = 400;

	// Where is the player
	Vector2f m_Position;

	// Where are the characters various body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	// And a texture
	Texture m_Texture;

	// All our public functions will come next
public:

	// New constructor to initialize with a texture
	PlayableCharacter(const Texture& texture)
		: m_Texture(texture), m_Sprite(texture)
	{
		m_JumpDuration = 0;
		m_IsJumping = false;
		m_IsFalling = false;
		m_LeftPressed = false;
		m_RightPressed = false;
		m_TimeThisJump = 0;
		m_Gravity = 0;
		m_Position = Vector2f(0.f, 0.f);
		// You may also want to initialize body part rectangles here if needed
	}

	void spawn(Vector2f startPosition, float gravity);

	// This is a pure virtual function
	bool virtual handleInput() = 0;
	// This class is now abstract and cannot be instanciated

	// Where is the player
	FloatRect getPosition();

	// A rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Make the character stand firm
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	// Where is the center of the character
	Vector2f getCenter();

	// We will call this function once every frame
	void update(float elapsedTime);
};
