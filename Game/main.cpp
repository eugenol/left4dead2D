#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "GameEntity.h"
#include "InputManager.h"
#include "Player.h"

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
	//Background music
	ALLEGRO_SAMPLE *bg_music = NULL;
	ALLEGRO_SAMPLE_INSTANCE *bgInstance = NULL;

	//Initialise allegro, if unsuccesful, show error.
	if (!al_init())
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Could not initatialize allegro",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1; //exit program
	}
	//Allegro Installations and Initialisations
	//Initialsise addons
	al_init_primitives_addon(); //Initialise primitives
	al_init_image_addon(); //Initialise images
	
	//Install keyboard & mouse
	al_install_keyboard();
	al_install_mouse();

	//Audio
	al_install_audio();
	al_init_acodec_addon();

	//Game variable initialisation
	ALLEGRO_BITMAP *playerSpriteSheet;
	playerSpriteSheet = al_load_bitmap("player_sprite.png");
	Player player(100, DISPLAY_HEIGHT, DISPLAY_HEIGHT, 100, 100, 4, 4, 0, 1, 32, PLAYER,  playerSpriteSheet);

	//Sounds & Musics
	al_reserve_samples(1);
	bg_music = al_load_sample("A Night of Dizzy Spells.ogg");
	bgInstance = al_create_sample_instance(bg_music);
	al_set_sample_instance_playmode(bgInstance, ALLEGRO_PLAYMODE_LOOP);
	//can set other properties here such as speed, gain, etc..
	al_attach_sample_instance_to_mixer(bgInstance, al_get_default_mixer());
	if (!bg_music)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Could not load music",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		//return -1; //exit program
	}

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

	//Start playing the music
	al_play_sample_instance(bgInstance);//turned off for now.. it can get irritating!!

	al_start_timer(timer); //Start the timer

	while (!game_done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev); // wait for event

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			player.update();
			redraw = true;
			//Update code goes here
		}

		// Capture close windows event
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_done = true;

		//Capture key input
		InputManager::getInstance().getInput(ev);

		//Escape key pressed? exit game
		if (InputManager::getInstance().isKeyPressed(ESCAPE))
			game_done = true;


		//Rendering
		if (redraw && al_is_event_queue_empty(event_queue)) //have to wait until event queue is empty befor redrawing.
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			player.draw();
			//Rendering code goes here

			al_flip_display();
		}
	}


	// Cleanup
	// Destroy everything that you create that doesnt do its own cleanup
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_sample_instance(bgInstance);
	al_destroy_sample(bg_music);

	return 0;
}