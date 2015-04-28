#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "GameEntity.h"

enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = { false, false, false, false, false };

int main(int argc, char **argv)
{
	//Display width & height, can move to a header file later.
	const int DISPLAY_HEIGHT = 600;
	const int DISPLAY_WIDTH = 800;
	const int FPS = 60; //Framerate

	bool game_done = false; // used for game loop
	bool redraw = false; // used for rendering

	ALLEGRO_DISPLAY *display = NULL; //Pointer to display.
	ALLEGRO_EVENT_QUEUE *event_queue = NULL; //Pointer to event queue
	ALLEGRO_TIMER *timer = NULL; //Pointer to timer

	//Initialise allegro, if unsuccesful, show error.
	if (!al_init())
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Could not initatialize allegro",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1; //exit program
	}

	//Initialsise addons
	al_init_primitives_addon(); //Initialise primitives
	al_init_image_addon(); //Initialise images


	//Install keyboard & mouse
	al_install_keyboard();
	al_install_mouse();

	// create display & check if succesful.
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!display) {
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Could not initatialize the display",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1; // exit program
	}
	al_set_window_title(display, "Zombie Rush"); //Sets title on window

	//Create Timer
	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the timer",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Create Event Queue
	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the event queue",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Register Event Sources
	al_register_event_source(event_queue, al_get_timer_event_source(timer)); // timer events
	al_register_event_source(event_queue, al_get_display_event_source(display)); //display events
	al_register_event_source(event_queue, al_get_keyboard_event_source()); // keyboard events
	al_register_event_source(event_queue, al_get_mouse_event_source()); // mouse events


	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	al_start_timer(timer); //Start the timer

	while (!game_done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev); // wait for event

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{

			redraw = true;
			//Update code goes here
		}

		// Capture close windows event
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_done = true;


		//Capture key input, try to find more elegand approach. using singleton??
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
				game_done = true; // exit game loop
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
			}
		}

		//Rendering
		if (redraw && al_is_event_queue_empty(event_queue)) //have to wait until event queue is empty befor redrawing.
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			//Rendering code goes here

			al_flip_display();
		}
	}


	// Cleanup
	// Destroy everything that you create that doesnt do its own cleanup
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}