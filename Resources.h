#ifndef __Resource_h__
#define __Resource_h__
#include "Wumbo-Shader.h"
#include "Wumbo-Sprite.h"
#include "Wumbo-Texture.h"
#ifdef I_AM_THE_PROGRUS
#define RES
#else
#define RES extern
#endif

RES Wumbo::Shader *megaShader;

RES Wumbo::Texture *texMain;

RES Wumbo::Sprite *sprGlow;

RES Wumbo::Sprite *sprTerrain[9];
#endif