#include "HeadsUpDisplay.h"
#include <allegro5\allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "CEvent.h"
#include "Player.h"

HeadsUpDisplay::HeadsUpDisplay()
	:
	m_healthBar( ),
	m_lives(3),
	m_playerLives( ),
	m_gameTimer( )
{
	Scorefont20 = al_load_ttf_font("pirulen.ttf", 20, 0);
	health = 100;
	lives = 3;
	score = 0;
	megaShotCount = 0;
}


HeadsUpDisplay::~HeadsUpDisplay()
{
	al_destroy_font(Scorefont20);
}

void HeadsUpDisplay::Update( double deltaTime )
{
	m_healthBar.DoLogic( health );

	if (m_lives.HasChanged())
	{
		m_playerLives.SetLivesLeft(m_lives);
	}

	m_gameTimer.Update( 1/60.0 );

}

void HeadsUpDisplay::Draw()
{
	al_draw_textf(Scorefont20, al_map_rgb(255, 0, 0), 0, 560, 0, "Zombies Killed: %i", score);
	al_draw_textf(Scorefont20, al_map_rgb(255, 0, 0), 0, 580, 0, "MegaShots Stored: %i", megaShotCount);
	al_draw_textf(Scorefont20, al_map_rgb(255, 0, 0), 0, 540, 0, "Health: %i", health);

	m_healthBar.Draw();
	m_playerLives.Draw();
	m_gameTimer.Draw();
}

void HeadsUpDisplay::OnNotify( const GameEntity& entity, CEvent* event )
{
	switch(event->GetEventType())
	{
	case EVENT_PLAYER_STATS:
		GetPlayerStats( event );
		break;
	}
}

void HeadsUpDisplay::GetPlayerStats( CEvent* event )
{
	CPlayerStatEvent*  playerStats = dynamic_cast<CPlayerStatEvent*>(event);
	if (playerStats == nullptr)
	{
		return;
	}

	health = playerStats->GetPlayerHealth();
	m_lives = playerStats->GetPlayerLives();
	score = playerStats->GetPlayerScore();
	megaShotCount = playerStats->GetPlayerMegaShotCount();
}
