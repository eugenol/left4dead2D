#include "InitData.h"


InitData::InitData() : display(NULL), event_queue(NULL), timer(NULL), playerSpriteSheet(NULL), healthBarSpriteSheet(NULL), skullImage(NULL), gameoverImage(NULL), enemy_image(NULL), bulletSpriteSheet(NULL), bulletExplosionSpriteSheet(NULL),
background(NULL), bg_music(NULL), bgInstance(NULL), cursorImage(NULL), font_18(NULL), font_24(NULL), done_loading(false)
{

}


InitData::~InitData()
{

}
