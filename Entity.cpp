#include "Entity.h"
#include "Level.h"
Entity::Entity(Level *lvl)
{
	level = lvl;
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
				hitbox.x = xx;
				hitbox.y = yy;
				e->hitbox.x = e->x;
				e->hitbox.y = e->y;
				if (hitbox.hits(e->hitbox))
					return e;
			}
	}
	return NULL;
}