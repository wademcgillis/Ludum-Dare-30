#ifndef __obj_entity_h__
#define __obj_entity_h__
#include "Wumbo-Hitbox.h"
class Level;

const unsigned int OBJ_PLAYER	 = 1;
const unsigned int OBJ_ALTAR	 = 2;
const unsigned int OBJ_PORTAL	 = 3;
const unsigned int OBJ_SIGN		 = 4;
const unsigned int OBJ_MUSHROOM	 = 5;
const unsigned int OBJ_BUILDING	 = 6;
const unsigned int OBJ_TREE		 = 7;
const unsigned int OBJ_COW		 = 8;

class Entity
{
public:
	int x, y;
	Level *level;
	Wumbo::Hitbox hitbox;
	unsigned int type;
public:
	Entity(Level *lvl);
	bool collisionAt(int x, int y, unsigned int otype);
	Entity *entityAt(int x, int y, unsigned int otype);
	virtual void begin() {}
	virtual void update() {}
	virtual void render() {}
	virtual void destroy() {}
};
#endif