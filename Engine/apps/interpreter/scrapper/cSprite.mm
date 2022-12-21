//
//  Sprite.m
//  Prototype
//
//  Created by Michael Johnson on 23/09/2008.
//  Copyright 2008 The Game Creators. All rights reserved.
//

#include "cSprite.h"

extern Texture2D*      g_pTexture;

const GLubyte squareColors [ ] =
{
    255, 255, 255, 255,
    255, 255, 255, 255,
    255, 255, 255, 255,
    255, 255, 255, 255,
};

cSpriteEx::cSpriteEx ( )
{
    glEnable            ( GL_TEXTURE_2D );
    //glTexEnvi           ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
    glEnableClientState ( GL_VERTEX_ARRAY );
    glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
    glTexParameteri     ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri     ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );	
}

cSpriteEx::~cSpriteEx ( )
{

}

void cSpriteEx::Draw ( int width, int height )
{
	float a = [ g_pTexture GetMaxS ];
	float b = [ g_pTexture GetMaxT ];

    GLfloat	coordinates [ ] =
	{
        0, b,
        0, 0,
        a, b, 
        a, 0,
    };

	const GLfloat vertices [ ] =
	{
		0.0f,   0.0f,
		0.0f,	height,
		width,  0.0f,
		width,	height,
	};
	
    glBindTexture       ( GL_TEXTURE_2D, [ g_pTexture name ] );
    glVertexPointer     ( 2, GL_FLOAT, 0, vertices );
    glTexCoordPointer   ( 2, GL_FLOAT, 0, coordinates );
    glColorPointer      ( 4, GL_UNSIGNED_BYTE, 0, squareColors );
	glDrawArrays        ( GL_TRIANGLE_STRIP, 0, 4 );
}