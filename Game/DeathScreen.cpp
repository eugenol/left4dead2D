#include "DeathScreen.h"
#include "Common.h"
#include "InputManager.h"


DeathScreen::DeathScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72) : font18(font_18), font24(font_24), font72(font_72)
{
	image = al_load_bitmap("gameover.png");

	CTwoDVector buttonLocation(DISPLAY_WIDTH - 100, DISPLAY_HEIGHT - 28);
	ALLEGRO_COLOR buttonColor = al_map_rgb(255, 0, 0);
	auto callback = [this]() {this->returnToMenu = true; };
	m_button = std::make_unique<CButton>(buttonLocation, 200, 38, "Main Menu", font_18, buttonColor, callback);
}


DeathScreen::~DeathScreen()
{
	al_destroy_bitmap(image);
}

void DeathScreen::Update()
{
	CTwoDVector mouse = InputManager::getInstance().GetMousePosition();

	returnToMenu = false;

	if (InputManager::getInstance().isMouseButtonPressed(LEFTM))
	{
		m_button->OnClicked(mouse);
	}
}

void DeathScreen::Draw()
{
	al_draw_text(font24, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 20, ALLEGRO_ALIGN_CENTRE, "You did not survive the zombie horde!");
	al_draw_bitmap(image, 128, 92, 0);
	m_button->Draw();
}



