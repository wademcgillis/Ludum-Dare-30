//
//  Shader.fsh
//  Wumbo
//
//  Created by Wade McGillis on 10/26/13.
//  Copyright (c) 2013 Wade McGillis. All rights reserved.1:26 PM 8/23/2014
//
//#version 120
varying vec4 vertexColor;
varying vec2 texcoord0frag;
varying float alpha;
//varying lowp float y;
uniform sampler2D texture;

void main()
{
	//gl_FragColor = vec4(0.0,1.0,0.0,1.0);
	vec4 col = vertexColor * texture2D(texture, texcoord0frag);
	col.a *= alpha;
	gl_FragColor = col;
}