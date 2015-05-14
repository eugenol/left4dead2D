#include "InputManager.h"


InputManager::InputManager()
{
	for (int i = 0; i < numKeys; i++)
		keys.push_back(false);

	for (int i = 0; i < 3; i++)
		mouseButton[i] = false;

	mouse_x = 0;
	mouse_y = 0;
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
		case ALLEGRO_KEY_W:
			keys[UP] = true;
			break;
		case ALLEGRO_KEY_DOWN:
		case ALLEGRO_KEY_S:
			keys[DOWN] = true;
			break;
		case ALLEGRO_KEY_LEFT:
		case ALLEGRO_KEY_A:
			keys[LEFT] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
		case ALLEGRO_KEY_D:
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
		case ALLEGRO_KEY_W:
			keys[UP] = false;
			break;
		case ALLEGRO_KEY_DOWN:
		case ALLEGRO_KEY_S:
			keys[DOWN] = false;
			break;
		case ALLEGRO_KEY_LEFT:
		case ALLEGRO_KEY_A:
			keys[LEFT] = false;
			break;
		case ALLEGRO_KEY_RIGHT:
		case ALLEGRO_KEY_D:
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

	// In case of mouse movement or button press, update mouse state
	if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY
		|| ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		al_get_mouse_state(&mouseState);
		mouse_x = mouseState.x;
		mouse_y = mouseState.y;
		mouseButton[LEFTM] = mouseState.buttons & 1; // left mouse button pressed
		mouseButton[RIGHTM] = mouseState.buttons & 2; // right mouse button pressed
		mouseButton[MIDDLEM] = mouseState.buttons & 3; // middle mouse button pressed
	}
}

bool InputManager::isKeyPressed(int key)
{
	return keys[key];
}

bool InputManager::isMouseButtonPressed(int button)
{
	return mouseButton[button];
}

float InputManager::getMouseX()
{
	return mouse_x;
}

float InputManager::getMouseY()
{
	return mouse_y;
}

void InputManager::clearInput()
{
	for (int i = 0; i < 3; i++)
		mouseButton[i] = false;
	for (int i = 0; i < keys.size(); i++)
		keys[i] = false;
}