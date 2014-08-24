#ifndef __Level_h__
#define __Level_h__
#include "Wumbo-Scene.h"
#include "Wumbo-Types.h"
#include "Wumbo-Sprite.h"
extern int worldStyle;


typedef struct
{
	unsigned char ID;
	unsigned char WORLD;
	unsigned char rand3;
} LD30Tile;

#include "Entity.h"
class obj_player;
#include <vector>

class Level : public Wumbo::Scene
{
public:
	std::string destinationRoom;
	std::string destinationPortal;
	bool altaredbefore;
	int room_width;
	std::vector<Entity*> entities;
	obj_player *player;
	int dSize;
	int menuOffset;
	bool showingWorldMenu;
	LD30Tile tiles[128*9];
private:
	void draw_thing(bool horz, Wumbo::Sprite *bg, int x, int y, unsigned int key, int setWorldStyleTo);
public:
	Level(Wumbo::Program *prog, std::string filename, std::string warpto);
	Level(Wumbo::Program *prog, std::string filename);
	void begin();
	void update();
	void render();
	void end();
	void onClose();

	Entity *addEntity(Entity *ent, int x, int y);
};
#endif