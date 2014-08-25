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
class obj_talker;
#include <vector>

class Level : public Wumbo::Scene
{
public:
	int phrasePosition;
	int speechWidth;
	int speechHeight;
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
	obj_talker *talking;
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

	void draw_text(int x, int y, std::string str);
	Entity *addEntity(Entity *ent, int x, int y);

	void calculate_sound();
};
#endif