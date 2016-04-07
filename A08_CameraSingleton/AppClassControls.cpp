#include "AppClass.h"

void AppClass::ProcessKeyboard(void)
{
	//Flag for the modifier
	bool bModifier = false;

	//ON PRESS/RELEASE
#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

	//W Moves Camera Forward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_pCamera->MoveForward(-0.1f);
	}

	//S Moves Camera Backwards
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_pCamera->MoveForward(0.1f);
	}

	//A Moves Camera Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_pCamera->MoveSideways(-0.1f);
	}

	//D Moves Camera Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_pCamera->MoveSideways(0.1f);
	}

	//Q Moves Camera Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_pCamera->MoveVertical(0.1f);
	}

	//E Moves Camera Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		m_pCamera->MoveVertical(-0.1f);
	}

	//Up changes pitch up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_pCamera->ChangePitch(-1.0f);
	}

	//Down changes pitch down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_pCamera->ChangePitch(1.0f);
	}

	//Left yaws left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_pCamera->ChangeYaw(-1.0f);
	}

	//Right yaws right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_pCamera->ChangeYaw(1.0f);
	}

	//R rolls 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_pCamera->ChangeRoll(-1.0f);
	}

	//And so does F
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		m_pCamera->ChangeRoll(1.0f);
	}

	//Exit the program
#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}