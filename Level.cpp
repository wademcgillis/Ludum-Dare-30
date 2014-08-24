#include "Level.h"
#include "Wumbo-Quicky.h"
#include "Wumbo-Types.h"
#include "Wumbo-Functions.h"
#include "Wumbo-Shader.h"
#include "Resources.h"

float randomf(float f)
{
	return f * (float) rand() / (float)RAND_MAX;
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
	//
	//
	//					END DRAW WORLD MENU
	//
	//





	// draw game 










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