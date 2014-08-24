#ifndef __obj_portal_h__
#define __obj_portal_h__
#include "obj_talker.h"
#include "Wumbo-Sprite.h"
class obj_portal : public obj_talker
{
public:
	std::string destinationPortal;
	std::string destinationRoom;
	std::string thisPortal;
	static bool alreadyWarped;
public:
	obj_portal(Level *lvl, std::string myname, std::string destport, std::string destroom);
	void begin();
	void update();
	void render();
	void destroy();
};
#endif