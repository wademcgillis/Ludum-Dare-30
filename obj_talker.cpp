#include "obj_talker.h"
#include "Level.h"
#include "Resources.h"
#include "Wumbo-Quicky.h"
#include "obj_player.h"
#include <cmath>
obj_talker::obj_talker(Level *lvl, unsigned type_) : Entity(lvl)
{
	scaletick = 0;
	type = type_;
}
void obj_talker::begin()
{
	sprite = NULL;
	switch(type)
	{
	case OBJ_SIGN:
		sprite = sprSign;
		hitbox = Wumbo::Hitbox(0,0,64,64);
		break;
	case OBJ_MUSHROOM:
		sprite = sprMushroom;
		hitbox = Wumbo::Hitbox(0,0,64,64);
		break;
	case OBJ_BUILDING:
		sprite = sprBuilding;
		hitbox = Wumbo::Hitbox(15,15,222,241);
		break;
	case OBJ_TREE:
		sprite = sprTree;
		hitbox = Wumbo::Hitbox(27,0,70,256);
		break;
	case OBJ_COW:
		sprite = sprCow;
		hitbox = Wumbo::Hitbox(4,20,120,108);
		break;
	}
	scaleX = 1;
	scaleY = 1;
	drawX = x;
	drawY = y;
}
void obj_talker::print()
{
	printf("[TALKER %i PHRASES]\n",(unsigned int)this);
	for(int i=0;i<phrases.size();i++)
		printf("\tPHRASE %i: \"%s\"\n",i,phrases.at(i).c_str());
}
void obj_talker::update()
{
	if (sprite != NULL && phrases.size() > 0)
	{
		if (collisionAt(x,y,OBJ_PLAYER))
		{
			scaletick += .2f;
			scaleX = 1.f+.1f*cos(scaletick);
			scaleY = 1.f+.1f*sin(scaletick);
			drawX = x - .05f*sprite->getWidth()*cos(scaletick);
			drawY = y - .1f*sprite->getHeight()*sin(scaletick);
		}
		else
		{
			scaleX = 1;
			scaleY = 1;
			drawX = x;
			drawY = y;
		}
	}
}
void obj_talker::render()
{
	if (sprite != NULL)
	{
		sprite->setScale(scaleX,scaleY);
		sprite->setFlipX(level->player->x+64 > x+sprite->getWidth()/2);
		sprite->setPosition(drawX,drawY);
		sprite->draw();
	}
}
void obj_talker::destroy()
{
}