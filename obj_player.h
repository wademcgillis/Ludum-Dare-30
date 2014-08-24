#ifndef __obj_player_h__
#define __obj_player_h__
#include "Entity.h"
class obj_player : public Entity
{
public:
public:
	obj_player(Level *lvl);
	void begin();
	void update();
	void render();
	void destroy();
};
#endif