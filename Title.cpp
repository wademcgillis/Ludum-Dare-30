#include "Title.h"
#include "Resources.h"
#include "Wumbo-Quicky.h"
#include "Level.h"
Title::Title(Wumbo::Program *prog) : Scene(prog)
{
}
void Title::begin()
{
}
void Title::update()
{
	if (Wumbo::OpenGL2())
		glUseProgram(megaShader->getProgramID());
	glBindTexture(GL_TEXTURE_2D, texTitle->getTexture());
	Wumbo::__quickyRenderer->setVirtualRenderTarget(Wumbo::VirtualRenderTarget(0,0,576,576,576,576));
	glClearColor(.33,.33,.33,1);
	glClear(GL_COLOR_BUFFER_BIT);
	if (Wumbo::__quickyKeyboard->isKeyPressed(Wumbo::Key::Space))
		program->setScene(new Level(program,"test"));
	sprTitle->draw();
}
void Title::render()
{
}
void Title::end()
{
}
void Title::onClose()
{
}