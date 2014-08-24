#ifndef __obj_talker_h__
#define __obj_talker_h__
#include "Entity.h"
#include "Wumbo-Sprite.h"
class obj_talker : public Entity
{
public:
	char *typestr;
	float scaletick;
	float scaleX;
	float scaleY;
	int drawX;
	int drawY;
	Wumbo::Sprite *sprite;
	std::vector<std::string> phrases;
	int currentPhrase;
public:
	obj_talker(Level *lvl, unsigned type_);
	void begin();
	void update();
	void render();
	void destroy();

	void talk();
	
	void print();
};
#endif