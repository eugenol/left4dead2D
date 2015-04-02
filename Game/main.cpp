#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

int main(int argc, char **argv)

{
	ALLEGRO_DISPLAY *display = NULL;

	if (!al_init())
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Could not initatialize allegro",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	display = al_create_display(640, 480);
	if (!display) {
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Could not initatialize the display",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_rest(5.0);

	al_show_native_message_box(al_get_current_display(), "Good", "Good", "If you can read this, then everything is set up correctly",
		NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);

	al_destroy_display(display);

	return 0;
}