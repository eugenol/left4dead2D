#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

int main(int argc, char **argv)
{
	//Display width & height, can move to a header file later.
	const int DISPLAY_HEIGHT = 600;
	const int DISPLAY_WIDTH = 800;

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

	// create display & check if succesful.
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!display) {
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Could not initatialize the display",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1; // exit program
	}

	al_set_window_title(display, "Zombie Rush");

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_rest(5.0);

	al_show_native_message_box(al_get_current_display(), "Good", "Good", "If you can read this, then everything is set up correctly",
		NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);

	al_destroy_display(display);

	return 0;
}