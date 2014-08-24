#include "obj_portal.h"
#include "Level.h"
#include "Resources.h"
#include "Wumbo-Quicky.h"
#include "obj_player.h"
#include <cmath>
bool obj_portal::alreadyWarped = false;
obj_portal::obj_portal(Level *lvl, std::string myname, std::string destport, std::string destroom) : obj_talker(lvl,OBJ_PORTAL)
{
	thisPortal = myname;
	destinationPortal = destport;
	destinationRoom = destroom;
}
void obj_portal::begin()
{
	hitbox = Wumbo::Hitbox(0,0,256,256);
	type = OBJ_PORTAL;
	sprite = sprPortal;
	drawX = x;
	drawY = y;
	printf("PORTAL DESTINATION: %s\n",destinationPortal.c_str());
	printf("PORTAL ROOMINATION: %s\n",destinationRoom.c_str());
	phrases.push_back("");
}
void obj_portal::update()
{
	obj_talker::update();
	if (collisionAt(x,y,OBJ_PLAYER))
	{
		if (Wumbo::__quickyKeyboard->isKeyPressed(Wumbo::Key::Space) && !alreadyWarped)
		{
			if (destinationRoom != "")
				level->getProgram()->setScene(new Level(level->getProgram(),destinationRoom,destinationPortal));
			else
			{
				printf("WARPING\n");
				for(int i=0;i<level->entities.size();i++)
				{
					Entity *e = level->entities.at(i);
					if (e->type == OBJ_PORTAL)
					{
						if (((obj_portal*)e)->thisPortal == destinationPortal)
						{
							level->player->x = e->x+64;
							level->player->y = e->y+128;
							alreadyWarped = true;
							printf("SAY WE'VE WAPRED\n");
						}
					}
				}
			}
		}
	}
}
void obj_portal::render()
{
	obj_talker::render();
}
void obj_portal::destroy()
{
}