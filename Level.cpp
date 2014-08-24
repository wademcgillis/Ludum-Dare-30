#include "Level.h"
#include "Wumbo-Quicky.h"
#include "Wumbo-Types.h"
#include "Wumbo-Functions.h"
#include "Wumbo-Shader.h"
#include "Resources.h"
#include "rapidxml.hpp"

#include "obj_player.h"
#include "obj_altar.h"
#include "obj_talker.h"
#include "obj_portal.h"

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

Level::Level(Wumbo::Program *prog, std::string filename) : Wumbo::Scene(prog)
{
	destinationRoom = filename;
	destinationPortal = "";
}
Level::Level(Wumbo::Program *prog, std::string filename, std::string warpto) : Wumbo::Scene(prog)
{
	destinationRoom = filename;
	destinationPortal = warpto;	
}
void Level::begin()
{
	int playerX = 0;
	int playerY = 0;
	int warpX = -1;
	int warpY = -1;
	int arr[] = {0,1,1,2,2};
	memset(tiles,0,128*9*sizeof(LD30Tile));
	for(int i=0;i<128;i++)
		for(int j=0;j<9;j++)
		{
			tiles[128*j+i].rand3 = arr[rand()%5];
		}
	menuOffset = 0;
	dSize = 0;
	//printf();
	rapidxml::xml_document<char> bob;
	bob.parse<0>(file_contents((std::string("C:\\LD30\\SOURCE\\OGMO\\")+destinationRoom+std::string(".oel")).c_str()));
	printf("[ENTITIES]\n");
	room_width = 4*atoi(bob.first_node()->first_attribute("width")->value());
	for(rapidxml::xml_node<char> *node = bob.first_node()->first_node()->first_node();node;node = node->next_sibling())
	{
		printf("\t%s\n",node->name());
		unsigned char in = 0x0;
		char *tempStr = NULL;
		if ((char*)node->first_attribute("Pastel") != NULL)
			tempStr = node->first_attribute("Pastel")->value();
		if (tempStr == NULL || strcmp(tempStr,"True") == 0)
			in |= 0x1;
		
		if ((char*)node->first_attribute("Dark") != NULL)
			tempStr = node->first_attribute("Dark")->value();
		if (tempStr == NULL || strcmp(tempStr,"True") == 0)
			in |= 0x2;

		if ((char*)node->first_attribute("Real") != NULL)
			tempStr = node->first_attribute("Real")->value();
		if (tempStr == NULL || strcmp(tempStr,"True") == 0)
			in |= 0x4;

		if ((char*)node->first_attribute("ZONGU") != NULL)
			tempStr = node->first_attribute("ZONGU")->value();
		if (tempStr == NULL || strcmp(tempStr,"True") == 0)
			in |= 0x8;

		if (strcmp("Ground",node->name()) == 0)
		{
			int xx = atoi((char*)node->first_attribute("x")->value())/16;
			int yy = atoi((char*)node->first_attribute("y")->value())/16;
			int width = atoi((char*)node->first_attribute("width")->value())/16;
			int height = atoi((char*)node->first_attribute("height")->value())/16;
			for(int i = xx; i < xx+width; i++)
				for(int j = yy; j < yy+height; j++)
				{
					tiles[128*j + i].ID = TILE_DIRT;
					tiles[128*j + i].WORLD = in;
				}
		}
		if (strcmp("Altar",node->name()) == 0)
		{
			int xx = atoi((char*)node->first_attribute("x")->value())/16;
			int yy = atoi((char*)node->first_attribute("y")->value())/16;
			addEntity(new obj_altar(this),64*xx,64*yy);
		}

		if (strcmp("Portal",node->name()) == 0)
		{
			int xx = atoi((char*)node->first_attribute("x")->value())/16;
			int yy = atoi((char*)node->first_attribute("y")->value())/16;
			std::string TP = "";
			std::string TR = "";
			if ((char*)node->first_attribute("TargetPortal"))
				TP = (char*)node->first_attribute("TargetPortal")->value();
			if ((char*)node->first_attribute("TargetRoom"))
				TR = (char*)node->first_attribute("TargetRoom")->value();
			if ((char*)node->first_attribute("Name"))
			if (strcmp((char*)node->first_attribute("Name")->value(),destinationPortal.c_str()) == 0)
			{
				printf("ZOOPYGOOPS!\n");
				warpX = xx;
				warpY = yy;
			}
			addEntity(new obj_portal(this,(char*)node->first_attribute("Name")->value(),TP,TR),64*xx,64*yy);
		}

		unsigned int talkerID = 0;
		if (strcmp("Sign",node->name()) == 0)
			talkerID = OBJ_SIGN;
		if (strcmp("Mushroom",node->name()) == 0)
			talkerID = OBJ_MUSHROOM;
		if (strcmp("Building",node->name()) == 0)
			talkerID = OBJ_BUILDING;
		if (strcmp("Tree",node->name()) == 0)
			talkerID = OBJ_TREE;
		if (strcmp("Cow",node->name()) == 0)
			talkerID = OBJ_COW;
		if (talkerID > 0)
		{
			unsigned int t = 0;

			int xx = atoi((char*)node->first_attribute("x")->value())/16;
			int yy = atoi((char*)node->first_attribute("y")->value())/16;
			obj_talker *talk = (obj_talker*)addEntity(new obj_talker(this,talkerID),64*xx,64*yy);
			talk->WORLD = in;
			std::string words = (char*)node->first_attribute("Text")->value();
			if (words.length() > 0)
			{
				// while we're able to find \r, erase them
				unsigned int pos;
				while ((pos = words.find("\r")) != std::string::npos)
					words.erase(words.begin()+pos);
				// tokenize the text by the delimiter \n and then add them to what the entity says
				talk->phrases.push_back(strtok((char*)words.c_str(),"\n"));
				char *bob;
				while((bob = strtok(NULL,"\n")) != NULL)
					talk->phrases.push_back(bob);
			}
		}

		if (strcmp("Player",node->name()) == 0)
		{
			playerX = atoi((char*)node->first_attribute("x")->value())/16;
			playerY = atoi((char*)node->first_attribute("y")->value())/16;
		}
	}
	/*for(int i=0;i<128;i++)
		for(int j=1;j<9;j++)
		{
			// if tileID at position is DIRT
			if (tiles[128*j + i].ID >= TILE_DIRT && tiles[128*j + i].ID <= TILE_DIRT+2)
				// and above us there is a point where 
				if (tiles[128*(j-1) + i].ID == 0)
				{
					tiles[128*(j-1) + i].ID = TILE_GRASS;
					tiles[128*(j-1) + i].WORLD = tiles[128*j + i].WORLD;
				}
		}*/
	if (warpX >= 0 && warpY >= 0)
	{
		printf("WARPING!------------------------\n\t%i %i\n",64*warpX+64,64*warpY+128);
		player = (obj_player*)addEntity(new obj_player(this),64*warpX+64,64*warpY+128);	
	}
	else
	{
		player = (obj_player*)addEntity(new obj_player(this),64*playerX,64*playerY);	
		printf("PICKLE\n");
	}
	//first->next_sibling();
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
void Level::update()
{
	if (!ALTARED)
		for(unsigned int i=0;i<entities.size();i++)
			entities.at(i)->update();
	obj_portal::alreadyWarped = false;
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
	
	if (Wumbo::__quickyKeyboard->isKeyPressed(Wumbo::Key::Return) || ALTARED && !altaredbefore)
	{
		if (menuOffset == 0)
		{
			ALTARED = true;
			dSize = 8;
		}
		else if (menuOffset == 64)
			dSize = -8;
	}

	menuOffset += dSize;
	if (menuOffset < 0)
	{
		ALTARED = false;
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

	if (ALTARED)
	{
		sprGlow_Vert->setAlpha(.5f);
		bool hov_mouse = false;
		bool hov_key = false;

		// LEFT BAR
		draw_thing(false, sprWorldSelector_Pastel, 0, 24+64, Wumbo::Key::Left, 1);
		// RIGHT BAR
		draw_thing(false, sprWorldSelector_Dark, 512, 24+64, Wumbo::Key::Right, 2);
		// TOP BAR
		draw_thing(true, sprWorldSelector_Real, 64, 24, Wumbo::Key::Up, 4);
		// BOTTOM BAR
		draw_thing(true, sprWorldSelector_ZONGU, 64, 24+512, Wumbo::Key::Down, 8);
	}

	//
	//
	//					DRAW LEVEL
	//
	//
	Wumbo::__quickyRenderer->setVirtualRenderTarget(Wumbo::VirtualRenderTarget(menuOffset,24+menuOffset,576-2*menuOffset,576-2*menuOffset,576,576));
	
	

	if (worldStyle == 1)
	{
		glBindTexture(GL_TEXTURE_2D, texWorld_Pastel->getTexture());
		glClearColor(204.f/255.f,233.f/255.f,1,1);
	}
	if (worldStyle == 2)
	{
		glBindTexture(GL_TEXTURE_2D, texWorld_Dark->getTexture());
		glClearColor(.5f,0,0,1);
	}
	if (worldStyle == 4)
	{
		glBindTexture(GL_TEXTURE_2D, texWorld_Real->getTexture());
		glClearColor(.5f,.5f,.5f,1);
	}
	if (worldStyle == 8)
	{
		glBindTexture(GL_TEXTURE_2D, texWorld_ZONGU->getTexture());
		glClearColor(.5f,.5f,.5f,1);
	}
	glClear(GL_COLOR_BUFFER_BIT);


	Wumbo::Sprite::STATICXOFFSET = -(player->x+64)+576/2;
	if (Wumbo::Sprite::STATICXOFFSET > 0)
		Wumbo::Sprite::STATICXOFFSET = 0;
	if (Wumbo::Sprite::STATICXOFFSET < -(room_width-576))
		Wumbo::Sprite::STATICXOFFSET = -(room_width-576);
	for(unsigned int i=-Wumbo::Sprite::STATICXOFFSET/64;i<10-Wumbo::Sprite::STATICXOFFSET/64;i++)
		for(unsigned int j=0;j<9;j++)
		{
			if (!(tiles[128*j + i].WORLD & worldStyle))
				continue;
			int tileID = tiles[128*j + i].ID;
			switch(tileID)
			{
			case TILE_DIRT:
				sprDirt->setActiveSubimage(tiles[128*j + i].rand3);
				sprDirt->setFlipX(tiles[128*j + i].rand3 == 0 && 64*i+32 < player->x+64);
				sprDirt->setPosition(64*i,64*j);
				sprDirt->draw();
				break;
			}
		}
	for(unsigned int i=0;i<entities.size();i++)
		entities.at(i)->render();
	for(unsigned int i=-Wumbo::Sprite::STATICXOFFSET/64;i<10-Wumbo::Sprite::STATICXOFFSET/64;i++)
		for(unsigned int j=0;j<9;j++)
		{
			if (!(tiles[128*j + i].WORLD & worldStyle))
				continue;
			int tileID = tiles[128*j + i].ID;
			switch(tileID)
			{
			case TILE_DIRT:
				if (j > 0)
				{
					if (tiles[128*j + i].WORLD & worldStyle)
						if (!(tiles[128*(j-1) + i].WORLD & worldStyle))
						{
							sprGrass->setActiveSubimage(tiles[128*(j-1) + i].rand3);
							sprGrass->setFlipX(tiles[128*(j-1) + i].rand3 == 0 && 64*i+32 < player->x+64);
							sprGrass->setPosition(64*i,64*(j-1));
							sprGrass->draw();
						}
				}
				break;
			}
		}
	Wumbo::Sprite::STATICXOFFSET = 0;


	// Draw the glowy border, only if we're pausing though.
	glBindTexture(GL_TEXTURE_2D, texMain->getTexture());
	sprGlow_Big->setPosition(0,0);
	sprGlow_Big->setColor(0,0,0,255);
	sprGlow_Big->setAlpha(menuOffset/64.f);
	sprGlow_Big->draw();
	altaredbefore = ALTARED;
}
void Level::end()
{
}
void Level::onClose()
{
}