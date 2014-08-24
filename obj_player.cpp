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
	hitbox = Wumbo::Hitbox(20,9,90,121);
}
void obj_player::update()
{
	if (Wumbo::__quickyKeyboard->isKeyDown(Wumbo::Key::Left))
	{
		frameTick++;
		x -= 16;
		facingLeft = true;
	}
	if (Wumbo::__quickyKeyboard->isKeyDown(Wumbo::Key::Right))
	{
		frameTick++;
		x += 16;
		facingLeft = false;
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
	if (y < 576-128-128)
	{
		vspeed += 1;
		y += vspeed;
	}
	if (y > 576-128-128)
	{
		vspeed = 0;
		y = 576-128-128;
	}
}
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