#ifndef __Title_h__
#define __Title_h__
#include "Wumbo-Scene.h"

class Title : public Wumbo::Scene
{
public:
	Title(Wumbo::Program *prog);
	void begin();
	void update();
	void render();
	void end();
	void onClose();
};
#endif