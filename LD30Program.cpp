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

	texMain = new Wumbo::Texture("GFX/texture.png");

	sprGlow = new Wumbo::Sprite(renderer);
	sprGlow->setTexture(texMain);
	sprGlow->setOffset(0,0);
	sprGlow->setSize(192,192);
	sprGlow->setAlpha(1);
	sprGlow->setScale(1,1);
	sprGlow->setSubimageCount(1);
	sprGlow->setSubrectPixels(0,0,0,192,192);

	for(int i=0;i<9;i++)
	{
		sprTerrain[i] = new Wumbo::Sprite(renderer);
		sprTerrain[i]->setTexture(texMain);
		sprTerrain[i]->setOffset(0,0);
		sprTerrain[i]->setSize(192,192);
		sprTerrain[i]->setAlpha(1);
		sprTerrain[i]->setScale(1,1);
		sprTerrain[i]->setSubimageCount(1);
		sprTerrain[i]->setSubrectPixels(0,448+192*(i%3),448+192*(i/3),192,192);
	}

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