#include "obj_player.h"
#include "Level.h"
#include "Resources.h"
#include "Wumbo-Quicky.h"
obj_player::obj_player(Level *lvl) : Entity(lvl)
{
}
void obj_player::begin()
{
	vspeed = 0;
	frameTick = 0;
	facingLeft = false;
	type = OBJ_PLAYER;
	hitbox = Wumbo::Hitbox(16,16,96,112);
}
void obj_player::update()
{
	if (Wumbo::__quickyKeyboard->isKeyDown(Wumbo::Key::Left))
	{
		frameTick++;
		facingLeft = true;
		for(int i=16;i>0;i--)
			if (!collideTerrain(x-i,y))
			{
				printf("WE MOVED LEFT BY %i\n",i);
				x -= i;
				i = 0;
			}
	}
	if (Wumbo::__quickyKeyboard->isKeyDown(Wumbo::Key::Right))
	{
		frameTick++;
		facingLeft = false;
		for(int i=16;i>0;i--)
			if (!collideTerrain(x+i,y))
			{
				printf("WE MOVED RIGHT BY %i\n",i);
				x += i;
				i = 0;
			}
	}
	if (Wumbo::__quickyKeyboard->isKeyPressed(Wumbo::Key::Up) && collideTerrain(x,y+1))
	{
		vspeed = -16;
	}
	if (x < 0)
		x = 0;
	if (x > level->room_width-128)
		x = level->room_width-128;
	if (Wumbo::__quickyKeyboard->isKeyPressed(Wumbo::Key::Space))
	{
		if (collisionAt(x,y,OBJ_ALTAR))
			ALTARED = true;
	}
	while (frameTick >= 8)
		frameTick -= 8;
	if (!collideTerrain(x,y+1))
	{
		vspeed += 1;
	}
	y += vspeed;
	bool did = false;
	while(collideTerrain(x,y))
	{
		did = true;
		if (vspeed < 0)
			y++;
		if (vspeed > 0)
			y--;
	}
	if (did)
		vspeed = 0;
}
extern void draw_fancy_rectangle(int x, int y, int w, int h, int style);
void obj_player::render()
{
	sprPlayer->setFlipX(facingLeft);
	sprPlayer->setActiveSubimage(frameTick/4);
	sprPlayer->setPosition(x,y);
	sprPlayer->draw();
}
void obj_player::destroy()
{
}