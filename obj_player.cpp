#include "obj_player.h"
#include "Level.h"
#include "Resources.h"
obj_player::obj_player(Level *lvl) : Entity(lvl)
{
}
void obj_player::begin()
{
	x = 0;
	y = 0;
}
void obj_player::update()
{
}
void obj_player::render()
{
	sprPlayer->setPosition(x,y);
	sprPlayer->draw();
}
void obj_player::destroy()
{
}