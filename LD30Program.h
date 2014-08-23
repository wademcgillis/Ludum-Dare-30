#ifndef __LD30Program_h__
#define __LD30Program_h__
#include "Wumbo-Program.h"
class LD30Program : public Wumbo::Program
{
public:
	void begin();
	void update();
	void render();
	void end();
};
#endif