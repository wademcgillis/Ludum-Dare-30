#include "Entity.h"
#include "Level.h"
#include "Resources.h"
Entity::Entity(Level *lvl)
{
	level = lvl;
	WORLD = 0xF;// DEFAULT TO ALL WORLDS
}
bool Entity::collideTerrain(int xx, int yy)
{
	hitbox.x = xx;
	hitbox.y = yy;
	int L = hitbox.x + hitbox.left;
	int T = hitbox.y + hitbox.top;
	for(int i=L/64;i<=(L+hitbox.width)/64;i++)
			for(int j=T/64;j<=(T+hitbox.height)/64;j++)
			{
				if (level->tiles[128*j + i].ID == TILE_DIRT)
					if (level->tiles[128*j + i].WORLD & worldStyle)
					{
						Wumbo::Hitbox h(0,0,64,64);
						h.x = 64*i;
						h.y = 64*j;
						if (hitbox.hits(h))
							return true;
					}
			}
	return false;
}
bool Entity::collisionAt(int xx, int yy, unsigned int otype)
{
	return entityAt(xx,yy,otype) != NULL;
}
Entity *Entity::entityAt(int xx, int yy, unsigned int otype)
{
	for(unsigned int i=0;i<level->entities.size();i++)
	{
		Entity *e = level->entities.at(i);
		if (e != this)
			if (e->type == otype)
			{
				if (e->WORLD & worldStyle)
				{
					hitbox.x = xx;
					hitbox.y = yy;
					e->hitbox.x = e->x;
					e->hitbox.y = e->y;
					if (hitbox.hits(e->hitbox))
						return e;
				}
			}
	}
	return NULL;
}