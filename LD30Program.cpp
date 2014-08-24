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


	//glColorMask(1.f,0.f,1.f,1.f);

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
	//renderer->centerDisplayOnScreen();












	worldStyle = 0;

	texMain = new Wumbo::Texture("GFX/texture.png");
	texWorld_Pastel = new Wumbo::Texture("GFX/pastel.png");
	texWorld_Dark = new Wumbo::Texture("GFX/dark.png");
	texWorld_Real = new Wumbo::Texture("GFX/pastel.png");
	texWorld_ZONGU = new Wumbo::Texture("GFX/dark.png");

	sprGlow_Horz = allocStaticSprite(renderer,texMain,448,64,192,0,448,64);
	sprGlow_Vert = allocStaticSprite(renderer,texMain,64,448,0,192,64,448);
	sprGlow_Big = allocStaticSprite(renderer,texMain,576,576,192,192,448,448);

	sprWorldSelector_Pastel = allocStaticSprite(renderer,texWorld_Pastel,64,448,640,0,64,448);
	sprWorldSelector_Dark = allocStaticSprite(renderer,texWorld_Dark,64,448,704,0,64,448);
	sprWorldSelector_Real = allocStaticSprite(renderer,texWorld_Real,448,64,576,640,448,64);
	sprWorldSelector_ZONGU = allocStaticSprite(renderer,texWorld_ZONGU,448,64,576,704,448,64);

	setScene(new Level(this));
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