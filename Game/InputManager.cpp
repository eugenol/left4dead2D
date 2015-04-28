#include "InputManager.h"


InputManager::InputManager()
{
	for (int i = 0; i < 6; i++)
		keys[i] = false; //initialise all keys to unpressed.
}


InputManager::~InputManager()
{
}

InputManager & InputManager::getInstance()
{
	static InputManager instance;
	return instance;
}

void InputManager::getInput(ALLEGRO_EVENT &ev)
{
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
			keys[UP] = true;
			break;
		case ALLEGRO_KEY_DOWN:
			keys[DOWN] = true;
			break;
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = true;
			break;
		case ALLEGRO_KEY_SPACE:
			keys[SPACE] = true;
			break;
		case ALLEGRO_KEY_ESCAPE:
			keys[ESCAPE] = true;
			break;
		}
	}

	if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
			keys[UP] = false;
			break;
		case ALLEGRO_KEY_DOWN:
			keys[DOWN] = false;
			break;
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = false;
			break;
		case ALLEGRO_KEY_SPACE:
			keys[SPACE] = false;
			break;
		case ALLEGRO_KEY_ESCAPE:
			keys[ESCAPE] = false;
			break;
		}
	}
}

bool InputManager::isKeyPressed(int key)
{
	return keys[key];
}