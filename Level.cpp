#include "Level.h"
#include "Wumbo-Quicky.h"
#include "Wumbo-Types.h"
#include "Wumbo-Functions.h"
#include "Wumbo-Shader.h"
#include "Resources.h"
#include "rapidxml.hpp"

float randomf(float f)
{
	return f * (float) rand() / (float)RAND_MAX;
}

char *file_contents(const char* path)
{
	FILE *f = fopen(path,"rb");
	if (!f)
		return NULL;
	fseek(f,0,SEEK_END);
	int size = ftell(f);
	char *contents = new char[size+1];
	memset(contents,0,size+1);
	fpos_t zero = 0;
	fsetpos(f,&zero);
	fread(contents,size,1,f);
	fclose(f);
	return contents;
}

bool mouse_in_rect(int x, int y, int w, int h)
{
	Wumbo::vec2di bob = Wumbo::__quickyMouse->getPosition();
	return (bob.x >= x && bob.x < x+w && bob.y >= y && bob.y < y+h);
}

Level::Level(Wumbo::Program *prog) : Wumbo::Scene(prog)
{
	
}
void Level::begin()
{
	menuOffset = 0;
	dSize = 0;
	//printf();
	rapidxml::xml_document<char> bob;
	bob.parse<0>(file_contents("C:\\LD30\\SOURCE\\OGMO\\test.oel"));
	printf("ZOOT\n");
	for(rapidxml::xml_node<char> *first = bob.first_node()->first_node()->first_node();first;first = first->next_sibling())
	{
		printf("%s\n",first->name());
		if (strcmp("Ground",first->name()))
		{
			int xx = atoi((char*)first->first_attribute("x"))/16;
			int yy = atoi((char*)first->first_attribute("y"))/16;
			for(int i = 0; i < atoi(first->first_attribute(width))/16; i++)
				for(int j = 0; j < atoi(first->first_attribute(height))/16; j++)
					tiles[64*yy + xx] = rand()%3;
		}
			
	}
	printf("PICKLE\n");
	//first->next_sibling();
}
void Level::update()
{
}
void Level::draw_thing(bool horz, Wumbo::Sprite *bg, int x, int y, unsigned int key, int setWorldStyleTo)
{
	Wumbo::Sprite *glow = NULL;
	if (horz)
		glow = sprGlow_Horz;
	else
		glow = sprGlow_Vert;
	glow->setAlpha(.5f);
	Wumbo::__quickyRenderer->setVirtualRenderTarget(Wumbo::VirtualRenderTarget(x,y,horz?448:64,horz?64:448,horz?448:64,horz?64:448));
	bool hov_mouse = mouse_in_rect(x,y,horz?448:64,horz?64:448);
	bool hov_key = Wumbo::__quickyKeyboard->isKeyDown(key);
	bg->setPosition(0 + 2*(hov_mouse && Wumbo::__quickyMouse->isButtonDown(0)),0 + 2*(hov_mouse && Wumbo::__quickyMouse->isButtonDown(0)));
	bg->draw();
	if (hov_mouse || hov_key)
		glow->setColor(0xFF00FF);
	else
		glow->setColor(0xFFFFFF);
	glow->setPosition(0,0);
	glow->draw();
	if ((hov_mouse && Wumbo::__quickyMouse->isButtonReleased(0)) || (Wumbo::__quickyKeyboard->isKeyReleased(key)))
	{
		worldStyle = setWorldStyleTo;
		dSize = -8;
	}
}
Entity *Level::addEntity(Entity *ent, int x, int y)
{

	ent->x = x;
	ent->y = y;
	ent->begin();
	entities.push_back(ent);
	return ent;
}
void Level::render()
{
	if (Wumbo::OpenGL2())
		glUseProgram(megaShader->getProgramID());
	glBindTexture(GL_TEXTURE_2D, texMain->getTexture());
	//
	//
	//					BEGIN DRAW WORLD MENU
	//
	//
	if (Wumbo::__quickyKeyboard->isKeyPressed(Wumbo::Key::Return))
	{
		if (menuOffset == 0)
		{
			PAUSED = true;
			dSize = 8;
		}
		else if (menuOffset == 64)
			dSize = -8;
	}

	menuOffset += dSize;
	if (menuOffset < 0)
	{
		PAUSED = false;
		menuOffset = 0;
		dSize = 0;
	}
	if (menuOffset > 64)
	{
		menuOffset = 64;
		dSize = 0;
	}
	// clear entire window
	Wumbo::__quickyRenderer->setVirtualRenderTarget(Wumbo::VirtualRenderTarget(0,0,576,600,576,600));
	glClearColor(.33,.33,.33,1);
	glClear(GL_COLOR_BUFFER_BIT);

	Wumbo::__quickyRenderer->setVirtualRenderTarget(Wumbo::VirtualRenderTarget(0,0,576,24,576,24));
	glClearColor(randomf(1),randomf(1),randomf(1),1);
	glClear(GL_COLOR_BUFFER_BIT);

	if (PAUSED)
	{
		sprGlow_Vert->setAlpha(.5f);
		bool hov_mouse = false;
		bool hov_key = false;

		// LEFT BAR
		draw_thing(false, sprWorldSelector_Pastel, 0, 24+64, Wumbo::Key::Left, 0);
		// RIGHT BAR
		draw_thing(false, sprWorldSelector_Dark, 512, 24+64, Wumbo::Key::Right, 1);
		// TOP BAR
		draw_thing(true, sprWorldSelector_Real, 64, 24, Wumbo::Key::Up, 0);
		// BOTTOM BAR
		draw_thing(true, sprWorldSelector_ZONGU, 64, 24+512, Wumbo::Key::Down, 1);
	}

	//
	//
	//					DRAW LEVEL
	//
	//
	Wumbo::__quickyRenderer->setVirtualRenderTarget(Wumbo::VirtualRenderTarget(menuOffset,24+menuOffset,576-2*menuOffset,576-2*menuOffset,576,576));
	glClearColor(.5f,.5f,.5f,1);
	glClear(GL_COLOR_BUFFER_BIT);

	if (worldStyle == 0)
		glBindTexture(GL_TEXTURE_2D, texWorld_Pastel->getTexture());
	if (worldStyle == 1)
		glBindTexture(GL_TEXTURE_2D, texWorld_Dark->getTexture());
	if (worldStyle == 2)
		glBindTexture(GL_TEXTURE_2D, texWorld_Real->getTexture());
	if (worldStyle == 3)
		glBindTexture(GL_TEXTURE_2D, texWorld_ZONGU->getTexture());






	for(unsigned int i=0;i<entities.size();i++)
		entities.at(i)->render();


	// Draw the glowy border, only if we're pausing though.
	glBindTexture(GL_TEXTURE_2D, texMain->getTexture());
	sprGlow_Big->setPosition(0,0);
	sprGlow_Big->setColor(0,0,0,255);
	sprGlow_Big->setAlpha(menuOffset/64.f);
	sprGlow_Big->draw();
}
void Level::end()
{
}
void Level::onClose()
{
}