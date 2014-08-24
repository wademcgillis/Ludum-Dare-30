#ifndef __obj_entity_h__
#define __obj_entity_h__
#include "Wumbo-Hitbox.h"
class Level;
class Entity
{
public:
	int x, y;
	Level *level;
	Wumbo::Hitbox hitbox;
public:
	Entity(Level *lvl);
	virtual void begin() {}
	virtual void update() {}
	virtual void render() {}
	virtual void destroy() {}
};
#endif