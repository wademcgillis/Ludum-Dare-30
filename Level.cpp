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

Level::Level(Wumbo::Program *prog) : Wumbo::Scene(prog)
{
	
}
void Level::begin()
{
	for(unsigned int i=0;i<9;i++)
	{
		renderIDs.push_back(i);
		screens[i].x = screens[i].targetX = 192*(i%3);
		screens[i].y = screens[i].targetY = 192*(i/3);
		screens[i].dx = screens[i].dy = 0;
		screens[i].bgcolor = 0xFF000000 | (85*(i%3) << 16) | (85*(i/3) << 8) | 255;
	}
	selectedScreenID = -1;
	animatingScreens = false;
}
void Level::update()
{
}
void Level::render()
{
	if (animatingScreens)
	{
		//printf("animating\n");
		bool yes = true;
		for(unsigned int i = 0; i < 9; i++)
		{
			if (abs(screens[i].x-screens[i].targetX) <= abs(screens[i].dx))
				screens[i].x = screens[i].targetX;
			else
				screens[i].x += screens[i].dx;

			if (abs(screens[i].y-screens[i].targetY) <= abs(screens[i].dy))
				screens[i].y = screens[i].targetY;
			else
				screens[i].y += screens[i].dy;

			if (screens[i].x != screens[i].targetX || screens[i].y != screens[i].targetY)
			{
				/*printf("\tscreen[%i].x = %i\n",i,screens[i].x);
				printf("\tscreen[%i].y = %i\n",i,screens[i].y);
				printf("\tscreen[%i].targetX = %i\n",i,screens[i].targetX);
				printf("\tscreen[%i].targetY = %i\n",i,screens[i].targetY);
				printf("\tscreen[%i].dx = %i\n",i,screens[i].dx);
				printf("\tscreen[%i].dy = %i\n",i,screens[i].dy);*/
				yes = false;
			}
		}
		if (yes)
		{
			for(unsigned int i = 0; i < 9; i++)
				screens[i].dx = screens[i].dy = 0;
			animatingScreens = false;
		}
	}
	if (Wumbo::__quickyMouse->isButtonPressed(1) && !animatingScreens)
	{
		if (Wumbo::__quickyMouse->getPosition().x > 0 && Wumbo::__quickyMouse->getPosition().y > 24 && Wumbo::__quickyMouse->getPosition().x < 576 && Wumbo::__quickyMouse->getPosition().y < 576+24)
		{
			int xx = Wumbo::__quickyMouse->getPosition().x/192;
			int yy = (Wumbo::__quickyMouse->getPosition().y-24)/192;
			selectedScreenID = -1;
			for(unsigned int i=0;(i < 9 && selectedScreenID == -1);i++)
				if (xx*192 == screens[i].targetX && yy*192 == screens[i].targetY)
					selectedScreenID = i;
			dragOffset.x = screens[selectedScreenID].targetX - Wumbo::__quickyMouse->getPosition().x;
			dragOffset.y = screens[selectedScreenID].targetY - (Wumbo::__quickyMouse->getPosition().y);
			bool yes = false;
			for(unsigned int i=0;(i<renderIDs.size() && !yes);i++)
			{
				if (renderIDs.at(i) == selectedScreenID)
				{
					renderIDs.erase(renderIDs.begin()+i);
					renderIDs.push_back(selectedScreenID);
					yes = true;
				}
			}
		}
	}
	if (Wumbo::__quickyMouse->isButtonReleased(1) && !animatingScreens)
	{
		if (Wumbo::__quickyMouse->getPosition().x > 0 && Wumbo::__quickyMouse->getPosition().y > 24 && Wumbo::__quickyMouse->getPosition().x < 576 && Wumbo::__quickyMouse->getPosition().y < 576+24)
		{
			int destXX = (screens[selectedScreenID].x + 96)/192;
			int destYY = (screens[selectedScreenID].y + 96 - 24)/192;
			if (destXX >= 0 && destXX < 3 && destYY >= 0 && destYY < 3)
			{
				int targetID = -1;
				for(unsigned int i=0;(i < 9 && targetID == -1);i++)
					if (destXX*192 == screens[i].targetX && destYY*192 == screens[i].targetY)
						targetID = i;

				screens[targetID].targetX = screens[selectedScreenID].targetX;
				screens[targetID].targetY = screens[selectedScreenID].targetY;

				screens[targetID].dx = (screens[targetID].targetX-screens[targetID].x)/10;
				screens[targetID].dy = (screens[targetID].targetY-screens[targetID].y)/10;

				screens[selectedScreenID].targetX = destXX*192;
				screens[selectedScreenID].targetY = destYY*192;

				screens[selectedScreenID].dx = (screens[selectedScreenID].targetX-screens[selectedScreenID].x)/10.f;
				screens[selectedScreenID].dy = (screens[selectedScreenID].targetY-screens[selectedScreenID].y)/10.f;

				bool yes = false;
				for(unsigned int i=0;(i<renderIDs.size() && !yes);i++)
				{
					if (renderIDs.at(i) == targetID)
					{
						renderIDs.erase(renderIDs.begin()+i);
						renderIDs.push_back(targetID);
						yes = true;
					}
				}
				yes = false;
				for(unsigned int i=0;(i<renderIDs.size() && !yes);i++)
				{
					if (renderIDs.at(i) == selectedScreenID)
					{
						renderIDs.erase(renderIDs.begin()+i);
						renderIDs.push_back(selectedScreenID);
						yes = true;
					}
				}
				animatingScreens = true;

				selectedScreenID = -1;
			}
			else if (selectedScreenID > -1)
			{
				screens[selectedScreenID].x = screens[selectedScreenID].targetX;
				screens[selectedScreenID].y = screens[selectedScreenID].targetY;
				selectedScreenID = -1;
			}
		}
		else if (selectedScreenID > -1)
		{
			screens[selectedScreenID].x = screens[selectedScreenID].targetX;
			screens[selectedScreenID].y = screens[selectedScreenID].targetY;
			selectedScreenID = -1;
		}
	}
	if (selectedScreenID >= 0)
	{
		screens[selectedScreenID].x = Wumbo::__quickyMouse->getPosition().x + dragOffset.x;
		screens[selectedScreenID].y = Wumbo::__quickyMouse->getPosition().y + dragOffset.y;
	}
	
	if (Wumbo::OpenGL2())
		glUseProgram(megaShader->getProgramID());
	glBindTexture(GL_TEXTURE_2D, texMain->getTexture());

	// clear entire window
	Wumbo::__quickyRenderer->setVirtualRenderTarget(Wumbo::VirtualRenderTarget(0,0,576,600,576,600));
	glClearColor(1,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	// clear top bar
	Wumbo::__quickyRenderer->setVirtualRenderTarget(Wumbo::VirtualRenderTarget(0,0,576,24,576,24));
	glClearColor(randomf(1),randomf(1),randomf(1),1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	// render screens
	for(unsigned int i = 0; i < 9; i++)
	{
		Wumbo::__quickyRenderer->setVirtualRenderTarget(Wumbo::VirtualRenderTarget(screens[renderIDs.at(i)].x,24+screens[renderIDs.at(i)].y,192,192,192,192));
		glClearColor(((screens[renderIDs.at(i)].bgcolor >> 16) & 0xFF)/255.f,((screens[renderIDs.at(i)].bgcolor >> 8) & 0xFF)/255.f,1.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		sprTerrain[renderIDs.at(i)]->setPosition(0,0);
		sprTerrain[renderIDs.at(i)]->draw();


		sprGlow->setPosition(0,0);
		sprGlow->setColor(0x000000);//255,0,255,255);
		sprGlow->setActiveSubimage(0);
		sprGlow->setAlpha(1.f);
		sprGlow->setScale(1,1);
		//sprGlow->draw();
	}
}
void Level::end()
{
}
void Level::onClose()
{
}