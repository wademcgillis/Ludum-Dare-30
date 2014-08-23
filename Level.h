#ifndef __Level_h__
#define __Level_h__
#include "Wumbo-Scene.h"
#include "Wumbo-Types.h"

typedef struct
{
	float x;
	float y;
	float targetX;
	float targetY;
	float dx;
	float dy;
	unsigned int bgcolor;
} Screen;

class Level : public Wumbo::Scene
{
public:
	bool animatingScreens;
	std::vector<char> renderIDs;
	Screen screens[9];
	Wumbo::vec2di dragOffset;
	char selectedScreenID;
public:
	Level(Wumbo::Program *prog);
	void begin();
	void update();
	void render();
	void end();
	void onClose();
};
#endif