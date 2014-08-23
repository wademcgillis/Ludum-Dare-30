//
//  Shader.vsh
//  Wumbo
//
//  Created by Wade McGillis on 10/26/13.
//  Copyright (c) 2013 Wade McGillis. All rights reserved.
//
#define _X supermatrix[0][0]
#define _Y supermatrix[0][1]
#define _XOFFSET supermatrix[0][2]
#define _YOFFSET supermatrix[0][3]

#define _WIDTH supermatrix[1][2]
#define _HEIGHT supermatrix[1][3]

#define _XSCALE supermatrix[1][0]
#define _YSCALE supermatrix[1][1]

#define _RENDERWIDTH supermatrix[2][0]
#define _RENDERHEIGHT supermatrix[2][1]
//#version 120
attribute vec4 position;
attribute vec4 color;
attribute vec2 texcoord0;

uniform mat4 supermatrix;

varying vec4 vertexColor;
varying vec2 texcoord0frag;
varying float alpha;

//varying float y;
void main()
{
	vec4 finalPosition = position;
	finalPosition.x = (((position.x*(_WIDTH)-_XOFFSET)*_XSCALE + _X)/(_RENDERWIDTH/2.0)-1.0);
	finalPosition.y = -(((position.y*(_HEIGHT)-_YOFFSET)*_YSCALE + _Y)/(_RENDERHEIGHT/2.0)-1.0);
	vertexColor = color * vec4(supermatrix[3][0],supermatrix[3][1],supermatrix[3][2],1);/*supermatrix[3][3]);*/
	texcoord0frag = texcoord0;
	alpha = supermatrix[2][3];
	gl_Position = finalPosition;
}
