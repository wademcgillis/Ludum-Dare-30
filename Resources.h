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

RES int worldStyle;
RES bool PAUSED;


RES Wumbo::Shader *megaShader;

RES Wumbo::Texture *texMain;
RES Wumbo::Texture *texWorld_Pastel;
RES Wumbo::Texture *texWorld_Dark;
RES Wumbo::Texture *texWorld_Real;
RES Wumbo::Texture *texWorld_ZONGU;

RES Wumbo::Sprite *sprGlow_Horz;
RES Wumbo::Sprite *sprGlow_Vert;

RES Wumbo::Sprite *sprGlow_Big; // Or Glow_Home

RES Wumbo::Sprite *sprWorldSelector_Pastel;
RES Wumbo::Sprite *sprWorldSelector_Dark;
RES Wumbo::Sprite *sprWorldSelector_Real;
RES Wumbo::Sprite *sprWorldSelector_ZONGU;
#endif