/*
* The function main() contains the initialisation of the allegro libraries, as well as loading of the game assets (bitmaps, audio)
* and the game loop. Loading of the assets has been moved to a parallel thread, so that a loading animation can be displayed
* The InitData class is used for the parallel process. it is easy to add on to it if more assets are needed.
*
* Also, if you are loading an asset here, please remember to destroy it at the end of main.
* -E
*/
#pragma warning (disable : 4996)
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "InputManager.h"
#include <cstdlib>    
#include <ctime>

#include "ScreenManager.h"
#include "Common.h"
#include "mappy_A5.h"

//Display width & height, can move to a header file later.
//Moved here, lots of things might use this. dont need to pass as arguments.

int gameTime = 0;
int gameTimeUpdateCounter = 0;

int main(int argc, char **argv)
{
	// Game loop & rendering variables
	bool game_done = false;				// used for game loop
	bool redraw = false;				// used for rendering

	int escapeDelay = 0;
	srand(time(nullptr));
	
	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;			//Pointer to display.
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;	//Pointer to event queue
	ALLEGRO_TIMER *timer = NULL;				//Pointer to timer
	//Audio
	ALLEGRO_SAMPLE *bg_music = NULL;
	ALLEGRO_SAMPLE_INSTANCE *bgInstance = NULL;
	//Bitmaps
	ALLEGRO_BITMAP *meleeZombieSpriteSheet = NULL;
	ALLEGRO_BITMAP *zombieDeathAnimationSpriteSheet = NULL;
	ALLEGRO_BITMAP *healthBarSpriteSheet = NULL;
	ALLEGRO_BITMAP *skullImage = NULL;
	ALLEGRO_BITMAP *gameoverImage = NULL;
	ALLEGRO_BITMAP *potionImage = NULL;
	ALLEGRO_BITMAP *bulletSpriteSheet = NULL;
	ALLEGRO_BITMAP *bulletExplosionSpriteSheet = NULL;
	ALLEGRO_THREAD *loading = NULL;
	//Fonts
	ALLEGRO_FONT *font_18 = NULL;
	ALLEGRO_FONT *font_24 = NULL;
	ALLEGRO_FONT *font_72 = NULL;
	//Mouse
	ALLEGRO_BITMAP *cursorImage = NULL;
	ALLEGRO_MOUSE_CURSOR *cursor = NULL;
	
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

	//Intitialize addons
	al_install_keyboard();		//Keyboard
	al_install_mouse();			//Mouse
	al_init_primitives_addon(); //Primitives (shapes)
	al_init_image_addon();		//Images
	al_install_audio();			//Audio
	al_init_acodec_addon();		//Audio


	// create display & check if succesful.
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!display) {
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Could not initatialize the display",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1; // exit program
	}
	al_set_window_title(display, "Zombie Rush"); //Sets title on window

	//create font for loading screen
	font_72 = al_load_ttf_font("pirulen.ttf", 72, 0); //can use different font

																										//Set up cursor Image
	cursorImage = al_load_bitmap("target.png");
	al_convert_mask_to_alpha(cursorImage, al_map_rgb(255, 255, 255));

	//Load images
	healthBarSpriteSheet = al_load_bitmap("healthbar.png");
	skullImage = al_load_bitmap("skull.png");
	potionImage = al_load_bitmap("potion.png");
	gameoverImage = al_load_bitmap("gameover.png");
	meleeZombieSpriteSheet = al_load_bitmap("zombie_0.png");				//Enemy Image
	zombieDeathAnimationSpriteSheet = al_load_bitmap("Zombie_death_spritesheet.png");
	bulletSpriteSheet = al_load_bitmap("spike_ball_projectile.png");//Bullet Image
	bulletExplosionSpriteSheet = al_load_bitmap("explosion.png"); //Bullet Explosion Animation

																																			//Data->background = al_load_bitmap("city_background.png");	//Load Background
																																			//Sounds & Musics
	al_reserve_samples(1);
	bg_music = al_load_sample("A Night of Dizzy Spells.ogg");
	bgInstance = al_create_sample_instance(bg_music);
	al_set_sample_instance_playmode(bgInstance, ALLEGRO_PLAYMODE_LOOP);
	//can set other properties here such as speed, gain, etc..
	al_attach_sample_instance_to_mixer(bgInstance, al_get_default_mixer());

	//Create additional Fonts
	font_18 = al_load_ttf_font("pirulen.ttf", 18, 0); //can use different font
	font_24 = al_load_ttf_font("pirulen.ttf", 24, 0); //can use different font

																													//Create Timer
	timer = al_create_timer(1.0 / FPS);
	//Create Event Queue
	event_queue = al_create_event_queue();

	//Register Event Sources
	al_register_event_source(event_queue, al_get_display_event_source(display)); //display events
	al_register_event_source(event_queue, al_get_timer_event_source(timer)); // timer events
	al_register_event_source(event_queue, al_get_keyboard_event_source()); // keyboard events
	al_register_event_source(event_queue, al_get_mouse_event_source()); // mouse events


	//Mouse cursor
	cursor = al_create_mouse_cursor(cursorImage, 16, 16);
	al_set_mouse_cursor(display, cursor);
//load the map
	if (MapLoad("map1.FMP.", 1))
		return -5;

	//create screens and add to screenmanager
	GameScreen game(bulletSpriteSheet, meleeZombieSpriteSheet, healthBarSpriteSheet, skullImage, gameoverImage, potionImage, zombieDeathAnimationSpriteSheet);
	ScreenManager::getInstance().addGameScreen(&game);
	MenuScreen menu(font_18, font_24, font_72, &game);
	ScreenManager::getInstance().addMenuScreen(&menu);
	CreditScreen credits(font_18, font_24, font_72);
	ScreenManager::getInstance().addCreditScreen(&credits);
	ScoreScreen scores(font_18, font_24, font_72);
	ScreenManager::getInstance().addScoreScreen(&scores);
	DeathScreen death(font_18, font_24, font_72);
	ScreenManager::getInstance().addDeathScreen(&death);

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
			// Handles different screens
			if (ScreenManager::getInstance().getScreenState() == ScreenManager::MENU)
			{
				switch (menu.getCurrentMenuOption())
				{
					case MenuScreen::NEWGAME:
					{
						ScreenManager::getInstance().setNewGame();
						ScreenManager::getInstance().changeGameState(ScreenManager::PLAYING);
						InputManager::getInstance().clearInput();
						break;
					}
					case MenuScreen::HIGHSCORES:
					{
						ScreenManager::getInstance().changeGameState(ScreenManager::HIGHSCORES);
						break;
					}
					case MenuScreen::CREDITS:
					{
						ScreenManager::getInstance().changeGameState(ScreenManager::CREDITS);
						break;
					}
					case MenuScreen::EXITGAME:
					{
						ScreenManager::getInstance().setExitState(true);
						break;
					}
					case MenuScreen::RESUMEGAME:
					{
						ScreenManager::getInstance().changeGameState(ScreenManager::PLAYING);
						InputManager::getInstance().clearInput();
						break;
					}

				}
				menu.clearCurrentMenuOption();
			}
			else if (ScreenManager::getInstance().getScreenState() == ScreenManager::CREDITS)
			{
				if (credits.GetReturnToMenu())
				{
					ScreenManager::getInstance().changeGameState(ScreenManager::MENU);
					credits.SetReturnToMenu();
				}
			}
			else if (ScreenManager::getInstance().getScreenState() == ScreenManager::HIGHSCORES)
			{
				if (scores.GetReturnToMenu())
				{
					ScreenManager::getInstance().changeGameState(ScreenManager::MENU);
					scores.SetReturnToMenu();
				}
			}
			else if (ScreenManager::getInstance().getScreenState() == ScreenManager::DIED)
			{
				if (death.GetReturnToMenu())
				{
					ScreenManager::getInstance().changeGameState(ScreenManager::MENU);
					death.SetReturnToMenu();
				}
			}

			ScreenManager::getInstance().Update();
		}


		//Escape key pressed? exit game
		if (InputManager::getInstance().isKeyPressed(ESCAPE))
		{
			if (escapeDelay++ == 0)
			{
				if (ScreenManager::getInstance().getScreenState() == ScreenManager::PLAYING)
					ScreenManager::getInstance().changeGameState(ScreenManager::MENU);
				else if (ScreenManager::getInstance().getScreenState() == ScreenManager::MENU)
				{
					if (ScreenManager::getInstance().isGameActive())
						ScreenManager::getInstance().changeGameState(ScreenManager::PLAYING);
				}
				else if (ScreenManager::getInstance().getScreenState() == ScreenManager::CREDITS)
					ScreenManager::getInstance().changeGameState(ScreenManager::MENU);
				else if (ScreenManager::getInstance().getScreenState() == ScreenManager::HIGHSCORES)
					ScreenManager::getInstance().changeGameState(ScreenManager::MENU);
				else if (ScreenManager::getInstance().getScreenState() == ScreenManager::DIED)
					ScreenManager::getInstance().changeGameState(ScreenManager::MENU);

			}
			else if (escapeDelay == 14)
				escapeDelay = 0;
		}
	
		game_done = ScreenManager::getInstance().getExitState();

		// Capture close windows event
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_done = true;

		//Rendering
		if (redraw && al_is_event_queue_empty(event_queue)) //have to wait until event queue is empty before redrawing.
		{
			redraw = false;
			
			al_clear_to_color(al_map_rgb(0, 0, 0));

			ScreenManager::getInstance().Draw();
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
	al_destroy_bitmap(healthBarSpriteSheet);
	al_destroy_bitmap(gameoverImage);
	al_destroy_bitmap(skullImage);
	al_destroy_bitmap(potionImage);
	al_destroy_bitmap(bulletSpriteSheet);
	al_destroy_bitmap(bulletExplosionSpriteSheet);
	al_destroy_bitmap(meleeZombieSpriteSheet);
	al_destroy_bitmap(zombieDeathAnimationSpriteSheet);
	//Destroy font
	al_destroy_font(font_72);
	MapFreeMem();
	return 0;
}