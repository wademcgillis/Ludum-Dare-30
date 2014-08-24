#ifndef __Level_h__
#define __Level_h__
#include "Wumbo-Scene.h"
#include "Wumbo-Types.h"
#include "Wumbo-Sprite.h"
extern int worldStyle;


#include "Entity.h"
#include "obj_player.h"
#include <vector>

class Level : public Wumbo::Scene
{
public:
	std::vector<Entity*> entities;
	obj_player *player;
	int dSize;
	int menuOffset;
	bool showingWorldMenu;
	unsigned int tiles[128*9];
private:
	void draw_thing(bool horz, Wumbo::Sprite *bg, int x, int y, unsigned int key, int setWorldStyleTo);
public:
	Level(Wumbo::Program *prog);
	void begin();
	void update();
	void render();
	void end();
	void onClose();

	Entity *addEntity(Entity *ent, int x, int y);
};
#endif