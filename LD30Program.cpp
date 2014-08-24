//
//														WUMBO FRAMEWORK
//			http://www.github.com/wademcgillis/WumboFramework & http://www.wademcgillis.com/ludumdare/Wumbo-LD29Example.zip
//
#include "LD30Program.h"
#include "Wumbo-Shader.h"
#include "Wumbo-ShaderBuilder.h"
#include "GM.h"
#include "Wumbo-Quicky.h"
#include "Wumbo-Renderer.h"

#include "Level.h"

GLuint program;

#define I_AM_THE_PROGRUS
#include "Resources.h"

Wumbo::Sprite *allocStaticSprite(Wumbo::Renderer *r, Wumbo::Texture *texture, int w, int h, int u, int v, int uW, int vH)
{
	Wumbo::Sprite *spr = new Wumbo::Sprite(r);
	spr->setTexture(texture);
	spr->setOffset(0,0);
	spr->setSize(w,h);
	spr->setAlpha(1);
	spr->setScale(1,1);
	spr->setSubimageCount(1);
	spr->setSubrectPixels(0,u,v,uW,vH);
	return spr;
}

Wumbo::Sprite *allocStaticSprite(Wumbo::Renderer *r, Wumbo::Texture *texture, int u, int v, int uW, int vH)
{
	Wumbo::Sprite *spr = new Wumbo::Sprite(r);
	spr->setTexture(texture);
	spr->setOffset(0,0);
	spr->setSize(uW,vH);
	spr->setAlpha(1);
	spr->setScale(1,1);
	spr->setSubimageCount(1);
	spr->setSubrectPixels(0,u,v,uW,vH);
	return spr;
}

Wumbo::Sprite *allocAnimatedSprite(Wumbo::Renderer *r, Wumbo::Texture *texture, int frameCount, int w, int h)
{
	Wumbo::Sprite *spr = new Wumbo::Sprite(r);
	spr->setTexture(texture);
	spr->setOffset(0,0);
	spr->setSize(w,h);
	spr->setAlpha(1);
	spr->setScale(1,1);
	spr->setSubimageCount(frameCount);
	return spr;
}

Wumbo::Program *WUMBOFRAMEWORK_GETPROGRAM()
{
	static Wumbo::Program *ld30 = new LD30Program();
	return ld30;
}

void LD30Program::begin()
{
	srand(time(NULL));

	Wumbo::Program::begin();
	// build the shader
	Wumbo::ShaderBuilder builder;
	builder.loadVertexShader(std::string("GFX/Shader.vsh"));
	builder.loadFragmentShader(std::string("GFX/Shader.fsh"));
	builder.addAttrib(Wumbo::WumboVertexAttribPosition, "position");
	builder.addAttrib(Wumbo::WumboVertexAttribColor, "color");
	builder.addAttrib(Wumbo::WumboVertexAttribTexCoord0, "texcoord0");
	builder.addUniform("supermatrix");
	megaShader = builder.generate();
	if (megaShader == NULL)
	{
		megaShader = new Wumbo::Shader();
		printf("megashader is null");
	}
	program = megaShader->getProgramID();
	printf("program is %i\n",program);
	// initialize input
	inputManager = new Wumbo::InputManager(this);
	inputManager->initialize();
	inputManager->setReceiveKeyboardUpdates(true);
	inputManager->setReceiveXbox360Updates(true);
	inputManager->setReceiveTouchUpdates(true);
	inputManager->setReceiveAccelerometerUpdates(true);
	inputManager->setReceiveMouseUpdates(true);
	if (!Wumbo::OpenGL2())
		renderer = new Wumbo::Renderer(this,1);
	else
		renderer = new Wumbo::Renderer(this,2);
	renderer->setRotation(Wumbo::ScreenRotation_DOWN);
	renderer->resetVirtualRenderTarget();
	setAssignedFrameRate(30);
	
	renderer->setTitle("Example Program");

	GM::gm_wumbo_init(this);
	Wumbo::Quicky_SetProgram(this);
	renderer->setDisplaySize(576,600);
	renderer->centerDisplayOnScreen();









/*









																		DINNER TIME



S







*/

	gems = 0xF;

	worldStyle = 1;

	texMain = new Wumbo::Texture("GFX/texture.png");
	texWorld_Pastel = new Wumbo::Texture("GFX/pastel.png");
	texWorld_Dark = new Wumbo::Texture("GFX/dark.png");
	texWorld_Real = new Wumbo::Texture("GFX/real.png");
	texWorld_ZONGU = new Wumbo::Texture("GFX/dark.png");

	sprGlow_Horz = allocStaticSprite(renderer,texMain,448,64,192,0,448,64);
	sprGlow_Vert = allocStaticSprite(renderer,texMain,64,448,0,192,64,448);
	sprGlow_Big = allocStaticSprite(renderer,texMain,576,576,192,192,448,448);

	sprWorldSelector_Pastel = allocStaticSprite(renderer,texWorld_Pastel,64,448,640,0,64,448);
	sprWorldSelector_Dark = allocStaticSprite(renderer,texWorld_Dark,64,448,704,0,64,448);
	sprWorldSelector_Real = allocStaticSprite(renderer,texWorld_Real,448,64,576,640,448,64);
	sprWorldSelector_ZONGU = allocStaticSprite(renderer,texWorld_ZONGU,448,64,576,704,448,64);


	sprPlayer = allocAnimatedSprite(renderer,texWorld_Pastel,2,128,128);
		sprPlayer->setSubrectPixels(0,2,2,128,128);
		sprPlayer->setSubrectPixels(1,132,2,128,128);

	sprDirt = allocAnimatedSprite(renderer,texWorld_Pastel,3,64,64);
		sprDirt->setSubrectPixels(0,262,134,64,64);
		sprDirt->setSubrectPixels(1,262,200,64,64);
		sprDirt->setSubrectPixels(2,262,267,64,64);

	sprGrass = allocAnimatedSprite(renderer,texWorld_Pastel,3,64,64);
		sprGrass->setSubrectPixels(0,262,333,64,64);
		sprGrass->setSubrectPixels(1,328,333,64,64);
		sprGrass->setSubrectPixels(2,328,267,64,64);

	sprPortal = allocStaticSprite(renderer,texWorld_Pastel,		256,256,	2,132,		256,256);
	sprSign = allocStaticSprite(renderer,texWorld_Pastel,		64,64,		262,2,		64,64);
	sprMushroom = allocStaticSprite(renderer,texWorld_Pastel,	64,64,		262,68,		64,64);
	sprBuilding = allocStaticSprite(renderer,texWorld_Pastel,	256,256,	328,2,		256,256);
	sprTree = allocStaticSprite(renderer,texWorld_Pastel,		128,256,	586,2,		128,256);
	sprCow = allocStaticSprite(renderer,texWorld_Pastel,		128,128,	716,2,		128,128);
	sprAltar = allocStaticSprite(renderer,texWorld_Pastel,		128,128,	394,267,	128,128);
	
	sprStones = allocAnimatedSprite(renderer,texWorld_Pastel,4,	9,17);
		sprStones->setSubrectPixels(0,	524,267,	9,17);//left
		sprStones->setSubrectPixels(1,	524,286,	9,17);//right
		sprStones->setSubrectPixels(2,	535,267,	9,17);//up
		sprStones->setSubrectPixels(3,	535,286,	9,17);//down

	sprSpeech[0] = allocStaticSprite(renderer,texMain,	0,832,	 16,16);
	sprSpeech[1] = allocStaticSprite(renderer,texMain,	16,832,	 16,16);
	sprSpeech[2] = allocStaticSprite(renderer,texMain,	48,832,	 16,16);

	sprSpeech[3] = allocStaticSprite(renderer,texMain,	0,848,	 16,16);
	sprSpeech[4] = allocStaticSprite(renderer,texMain,	16,848,	 16,16);
	sprSpeech[5] = allocStaticSprite(renderer,texMain,	48,848,	 16,16);

	sprSpeech[6] = allocStaticSprite(renderer,texMain,	0,864,	 16,32);
	sprSpeech[7] = allocStaticSprite(renderer,texMain,	16,864,	 16,32);
	sprSpeech[8] = allocStaticSprite(renderer,texMain,	48,864,	 16,32);



	sprSpeech[ 9] = allocStaticSprite(renderer,texMain,	0,896,	 24,24);
	sprSpeech[10] = allocStaticSprite(renderer,texMain,	24,896,	 8,24);
	sprSpeech[11] = allocStaticSprite(renderer,texMain,	40,896,	 24,24);

	sprSpeech[12] = allocStaticSprite(renderer,texMain,	0,916,	 16,8);
	sprSpeech[13] = allocStaticSprite(renderer,texMain,	19,909,	 8,8);
	sprSpeech[14] = allocStaticSprite(renderer,texMain,	48,916,	 16,8);

	sprSpeech[15] = allocStaticSprite(renderer,texMain,	0,928,	 32,32);
	sprSpeech[16] = allocStaticSprite(renderer,texMain,	28,928,	 8,32);
	sprSpeech[17] = allocStaticSprite(renderer,texMain,	32,928,	 32,32);

	sprSpeechMore = allocStaticSprite(renderer,texMain,	0,800,	 64,32);


	sprFont = allocAnimatedSprite(renderer,texMain,64,32,32);
	for(int i=0;i<64;i++)
		sprFont->setSubrectPixels(i,32*(i%32),960+32*(i/32),32,32);

	setScene(new Level(this,"test"));
}
void LD30Program::update()
{
	Wumbo::Program::update();
}
void LD30Program::render()
{
	Wumbo::Program::render();
}
void LD30Program::end()
{
	Wumbo::Program::end();
}