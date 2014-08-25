#ifndef __Resource_h__
#define __Resource_h__
#include "Wumbo-Shader.h"
#include "Wumbo-Sprite.h"
#include "Wumbo-Texture.h"
#include "FjordsSound.h"
#ifdef I_AM_THE_PROGRUS
#define RES
#else
#define RES extern
#endif

RES int worldStyle;
RES bool ALTARED;
RES unsigned char gems;


RES Wumbo::Shader *megaShader;

RES Wumbo::Texture *texMain;
RES Wumbo::Texture *texWorld_Pastel;
RES Wumbo::Texture *texWorld_Dark;
RES Wumbo::Texture *texWorld_Real;
RES Wumbo::Texture *texWorld_ZONGU;

RES Wumbo::Texture *texTitle;

RES Wumbo::Sprite *sprGlow_Horz;
RES Wumbo::Sprite *sprGlow_Vert;

RES Wumbo::Sprite *sprGlow_Big; // Or Glow_Home

RES Wumbo::Sprite *sprWorldSelector_Pastel;
RES Wumbo::Sprite *sprWorldSelector_Dark;
RES Wumbo::Sprite *sprWorldSelector_Real;
RES Wumbo::Sprite *sprWorldSelector_ZONGU;


RES Wumbo::Sprite *sprTitle;


RES Wumbo::Sprite *sprPlayer;

RES Wumbo::Sprite *sprDirt;
RES Wumbo::Sprite *sprGrass;
RES Wumbo::Sprite *sprPortal;
RES Wumbo::Sprite *sprSign;
RES Wumbo::Sprite *sprMushroom;
RES Wumbo::Sprite *sprBuilding;
RES Wumbo::Sprite *sprTree;
RES Wumbo::Sprite *sprCow;
RES Wumbo::Sprite *sprAltar;
RES Wumbo::Sprite *sprStones;

RES Wumbo::Sprite *sprFont;
RES Wumbo::Sprite *sprSpeech[18];
RES Wumbo::Sprite *sprSpeechMore;

RES double snd_pastel;
RES double snd_dark;
RES double snd_real;
RES double snd_ZONGU;

RES double snd_talk;
RES double snd_wip;

const unsigned int TILE_DIRT = 1;
const unsigned int TILE_GRASS = 2;
#endif