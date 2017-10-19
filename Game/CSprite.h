#pragma once
#include <allegro5/allegro_primitives.h>
#include "CTwoDVector.h"
#include <string>

struct SpriteSheetProperties
{
	int m_animationFrameWidth;//this is the width of the bitmap region
	int m_animationFrameHeight;//this is the height of bitmap region
	int m_currentAnimationFrame;//this is the frame we are on
	int m_frameCount; //frame Count
	int m_maxFrameCount; //the last frames of animation sequence
	int m_minFrameCount;//the first frame of animation sequence
	int m_frameDelay; //delay associated to animation
};

class CSprite
{
public:
	CSprite( std::string imageName, SpriteSheetProperties& properties);
	CSprite( ALLEGRO_BITMAP* imageToUse, SpriteSheetProperties& properties); //Sprite does not own this image and will not destroy it.
	~CSprite();

	void Draw( CTwoDVector&& position, int direction = 0);
	void Draw(ALLEGRO_COLOR tintColor, CTwoDVector&& position, int direction =0);
	void DoLogic();
	void UpdateAnimation();

	int GetFrameCount() { return m_properties.m_frameCount; }
	int GetCurrentAnimationFrame() { return m_properties.m_currentAnimationFrame; }
	int GetFrameWidth() { return m_properties.m_animationFrameWidth; }
	int GetFrameHeight() { return m_properties.m_animationFrameHeight; }
	int GetMaxFrameCount() { return m_properties.m_maxFrameCount; }
private:

	bool m_ownsImage;
	ALLEGRO_BITMAP* m_image;
  SpriteSheetProperties m_properties;

};