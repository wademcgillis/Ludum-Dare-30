#ifndef __obj_altar_h__
#define __obj_altar_h__
#include "Entity.h"
class obj_altar : public Entity
{
public:
public:
	obj_altar(Level *lvl);
	void begin();
	void update();
	void render();
	void destroy();
};
#endif