/*
* Input manager class, this object can only be created once (it is a singleton)
* it is a global object, not good practice, but they key array was global anyway,
* so it doesnt make much of a difference. Could be a bit clunky to use, but removes
* all the code from main. Also, was good practice.
* use as follows:
* 		InputManager::getInstance().getInput(ev); // gets input from event 
*
*		if (InputManager::getInstance().isKeyPressed(ESCAPE)) // check if key is pressed.
*			game_done = true;
*
*/

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
