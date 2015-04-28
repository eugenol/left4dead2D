#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <allegro5/allegro.h>

enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, ESCAPE };

class InputManager
{
private:
	InputManager(); //Singleton
	bool keys[6];
public:
	~InputManager();
	static InputManager & getInstance();

	void getInput(ALLEGRO_EVENT &ev);
	bool isKeyPressed(int key);
	
	//Can't use these methods to accidentally copy the input manager.
	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;
};

#endif
