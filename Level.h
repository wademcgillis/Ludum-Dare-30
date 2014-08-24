#ifndef __Level_h__
#define __Level_h__
#include "Wumbo-Scene.h"
#include "Wumbo-Types.h"
#include "Wumbo-Sprite.h"
extern int worldStyle;

class Level : public Wumbo::Scene
{
public:
	int dSize;
	int menuOffset;
	bool showingWorldMenu;
private:
	void draw_thing(bool horz, Wumbo::Sprite *bg, int x, int y, unsigned int key, int setWorldStyleTo);
public:
	Level(Wumbo::Program *prog);
	void begin();
	void update();
	void render();
	void end();
	void onClose();
};
#endif