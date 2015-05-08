/*
* The function main() contains the initialisation of the allegro libraries, as well as loading of the game assets (bitmaps, audio)
* and the game loop. Loading of the assets has been moved to a parallel thread, so that a loading animation can be displayed
* The InitData class is used for the parallel process. it is easy to add on to it if more assets are needed.
*
* Also, if you are loading an asset here, please remember to destroy it at the end of main.
* -E
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "GameEntity.h"
#include "Enemy.h"
#include "MeleeZombie.h"
#include "InputManager.h"
#include "Player.h"
#include "EntityManager.h"
#include "InitData.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

	//Display width & height, can move to a header file later.
//Moved here, lots of things might use this. dont need to pass as arguments.

	const int DISPLAY_HEIGHT = 600;
	const int DISPLAY_WIDTH = 800;
	const int FPS = 60; //Framerate

	static void*loading_thread(ALLEGRO_THREAD*load, void*data); // Prototype for loading thread

int main(int argc, char **argv)
{
	// Game loop & rendering variables
	bool game_done = false; // used for game loop
	bool redraw = false; // used for rendering
	int EnemySpawnTimerMax = FPS*(3 + rand() % 3);
	int EnemySpawnTimerCurrent=0;
	srand(time(NULL));
	//Parallel load
	InitData data;

	//Object List
	std::list<GameEntity*> objects;
	EntityManager::getInstance().getEntityList(&objects); // send to object manager.

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL; //Pointer to display.
	ALLEGRO_EVENT_QUEUE *event_queue = NULL; //Pointer to event queue
	ALLEGRO_TIMER *timer = NULL; //Pointer to timer
	//Audio
	ALLEGRO_SAMPLE *bg_music = NULL;
	ALLEGRO_SAMPLE_INSTANCE *bgInstance = NULL;
	//Bitmaps
	ALLEGRO_BITMAP *meleeZombieSpriteSheet = NULL;
	ALLEGRO_BITMAP *playerSpriteSheet = NULL;
	ALLEGRO_BITMAP *bulletSpriteSheet = NULL;
	ALLEGRO_THREAD *loading = NULL;
	//Fonts
	//ALLEGRO_FONT *font_18 = NULL;
	//ALLEGRO_FONT *font_24 = NULL;
	ALLEGRO_FONT *font_72 = NULL;
	//Mouse
	ALLEGRO_BITMAP *cursorImage = NULL;
	ALLEGRO_MOUSE_CURSOR *cursor = NULL;
	//Player
	Player *player = NULL;
	
	//Init fonts
	al_init_font_addon();
	al_init_ttf_addon();

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
	al_set_window_title(display, "Zombie Rush"); //Sets title on window
	data.display = display; //might not be needed now, but can use in case.

	//create font for loading screen
	font_72 = al_load_ttf_font("pirulen.ttf", 72, 0); //can use different font

	// Load using a parallel thread, while displaying a loading image
	loading = al_create_thread(loading_thread, &data);
	al_start_thread(loading);
	while (!data.done_loading)
	{
		static int  a = 0;

		if (a >= 1200)
			a = 0;

		if (a < 300)
			al_draw_text(font_72, al_map_rgb(255, 255, 255), 150, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_LEFT, "Loading   ");
		else if (a < 600)
			al_draw_text(font_72, al_map_rgb(255, 255, 255), 150, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_LEFT, "Loading.  ");
		else if (a <900)
			al_draw_text(font_72, al_map_rgb(255, 255, 255), 150, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_LEFT, "Loading.. ");
		else if (a < 1200)
			al_draw_text(font_72, al_map_rgb(255, 255, 255), 150, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_LEFT, "Loading...");
		a++;
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	al_destroy_thread(loading);

	//Get loaded data
	//display = data.display;
	event_queue = data.event_queue;
	timer = data.timer;
	playerSpriteSheet = al_clone_bitmap(data.playerSpriteSheet);
	bg_music = data.bg_music;
	bgInstance = data.bgInstance;
	cursorImage = al_clone_bitmap(data.cursorImage);
	player = data.player;
	playerSpriteSheet = al_clone_bitmap(data.bulletSpriteSheet);
	meleeZombieSpriteSheet = al_clone_bitmap(data.enemy_image);
	//Mouse cursor
	cursor = al_create_mouse_cursor(cursorImage, 16, 16);
	al_set_mouse_cursor(display, cursor);
	

	//Checks
	if (!timer)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the timer",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	if (!event_queue)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the event queue",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}




	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	//Start playing the music
	//al_play_sample_instance(bgInstance);//turned off for now.. it can get irritating!!

	al_start_timer(timer); //Start the timer

	while (!game_done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev); // wait for event


		//Capture key input
		InputManager::getInstance().getInput(ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			//Update movement etc...
			for (std::list<GameEntity*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
				(*iter)->update();

			//Check for collisions... Not the most efficient, but ok for now. can be changed later...
			//for now it campares every object, I can make it sector based later...
			for (std::list<GameEntity*>::iterator iter1 = objects.begin(); iter1 != objects.end(); iter1++)
			{
				for (std::list<GameEntity*>::iterator iter2 = objects.begin(); iter2 != objects.end(); iter2++)
				{
					if (iter1 != iter2) // Can't collide with yourself
					{
						if ((*iter1)->CheckCollision(*iter2)) //Did you collide?
							(*iter1)->Collided(*iter2); //Do something about it.
		}
				}
			}

			//Attempt to create new enemy
			if (++EnemySpawnTimerCurrent == EnemySpawnTimerMax)
			{
				EnemySpawnTimerMax = FPS*(3 + rand() % 3);
				GameEntity * entity = new MeleeZombie(rand()%DISPLAY_WIDTH, rand()%DISPLAY_HEIGHT, meleeZombieSpriteSheet);
				EntityManager::getInstance().AddEntity(entity);
				EnemySpawnTimerCurrent = 0;
			}
			// Update the entity manager to remove the dead.
			EntityManager::getInstance().UpdateList();
		}

		// Capture close windows event
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_done = true;

		//Escape key pressed? exit game
		if (InputManager::getInstance().isKeyPressed(ESCAPE))
			game_done = true;


		//Rendering
		if (redraw && al_is_event_queue_empty(event_queue)) //have to wait until event queue is empty before redrawing.
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			for (std::list<GameEntity*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
				(*iter)->draw();
			
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
	//Clear Bitmaps
	al_destroy_bitmap(playerSpriteSheet);
	al_destroy_bitmap(bulletSpriteSheet);
	al_destroy_bitmap(meleeZombieSpriteSheet);
	//Destroy font
	al_destroy_font(font_72);
	return 0;
}

static void*loading_thread(ALLEGRO_THREAD*load, void*data)
{
	InitData *Data = (InitData*)data;

	//Intitialize addons
	al_install_keyboard();		//Keyboard
	al_install_mouse();			//Mouse
	al_init_primitives_addon(); //Primitives (shapes)
	al_init_image_addon();		//Images
	al_install_audio();			//Audio
	al_init_acodec_addon();		//Audio

	//Set up cursor Image
	Data->cursorImage = al_load_bitmap("target.png");
	al_convert_mask_to_alpha(Data->cursorImage, al_map_rgb(255, 255, 255));
	
	//Load images
	Data->playerSpriteSheet = al_load_bitmap("player_sprite.png");
	Data->enemy_image = al_load_bitmap("zombie_0.png");				//Enemy Image
	Data->bulletSpriteSheet = al_load_bitmap("spike_ball_projectile.png");//Bullet Image

	//Data->background = al_load_bitmap("city_background.png");	//Load Background

	//Sounds & Musics
	al_reserve_samples(1);
	Data->bg_music = al_load_sample("A Night of Dizzy Spells.ogg");
	Data->bgInstance = al_create_sample_instance(Data->bg_music);
	al_set_sample_instance_playmode(Data->bgInstance, ALLEGRO_PLAYMODE_LOOP);
	//can set other properties here such as speed, gain, etc..
	al_attach_sample_instance_to_mixer(Data->bgInstance, al_get_default_mixer());


	Data->player = new Player(0, 100, 800, 600, 100, 100, 4, 4, 0, 1, 32, PLAYER, Data->playerSpriteSheet, Data->bulletSpriteSheet);
	EntityManager::getInstance().AddEntity(Data->player);
	Enemy::setPlayer(Data->player);

	//Create Timer
	Data->timer = al_create_timer(1.0 / FPS);
	//Create Event Queue
	Data->event_queue = al_create_event_queue();

	//Register Event Sources
	al_register_event_source(Data->event_queue, al_get_display_event_source(Data->display)); //display events
	al_register_event_source(Data->event_queue, al_get_timer_event_source(Data->timer)); // timer events
	al_register_event_source(Data->event_queue, al_get_keyboard_event_source()); // keyboard events
	al_register_event_source(Data->event_queue, al_get_mouse_event_source()); // mouse events

	al_rest(2.5);


	Data->done_loading = true;

	return NULL;
}