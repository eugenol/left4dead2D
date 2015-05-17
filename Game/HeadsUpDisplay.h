#pragma once
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class HeadsUpDisplay
{
public:
	HeadsUpDisplay();
	~HeadsUpDisplay();
	void Update(int health, int lives, int score, int megashotCount);
	void draw();
private:
	//Variables from Player to Display on the HUD
	int health, lives, score, megaShotCount;
	
	//Font For The HUD
	ALLEGRO_FONT *Scorefont20;

	//HUD Images and animation
	ALLEGRO_BITMAP *megaShotCountStar;
	int animationFrameWidth;//this is the width of the bitmap region
	int animationFrameHeight;//this is the height of bitmap region
	int currentAnimationFrame;//this is the frame we are on
	int frameCount; //frame Count
	int maxFrameCount = 0; //the last frames of animation sequence
	int minFrameCount;//the first frame of animation sequence
	int frameDelay; //delay associated to animation
	int rotationAngle;

	void animationUpdate();
};

