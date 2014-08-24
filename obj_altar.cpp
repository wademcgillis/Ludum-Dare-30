#include "obj_altar.h"
#include "Level.h"
#include "Resources.h"
#include "Wumbo-Quicky.h"
obj_altar::obj_altar(Level *lvl) : Entity(lvl)
{
	x = 0;
	y = 0;
	type = OBJ_ALTAR;
	hitbox = Wumbo::Hitbox(16,52,101,76);
}
void obj_altar::begin()
{
}
void obj_altar::update()
{	
}
void obj_altar::render()
{
	sprAltar->setPosition(x,y);
	sprAltar->draw();

	if (gems & 0x1)
	{
		sprStones->setActiveSubimage(0);
		sprStones->setPosition(x+56,y+69);
		sprStones->draw();
	}
	if (gems & 0x2)
	{
		sprStones->setActiveSubimage(1);
		sprStones->setPosition(x+66,y+69);
		sprStones->draw();
	}
	if (gems & 0x4)
	{
		sprStones->setActiveSubimage(2);
		sprStones->setPosition(x+61,y+60);
		sprStones->draw();
	}
	if (gems & 0x8)
	{
		sprStones->setActiveSubimage(3);
		sprStones->setPosition(x+61,y+78);
		sprStones->draw();
	}
}
void obj_altar::destroy()
{
}