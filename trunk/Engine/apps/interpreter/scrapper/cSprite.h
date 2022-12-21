//
//  Sprite.h
//  Prototype
//
//  Created by Michael Johnson on 23/09/2008.
//  Copyright 2008 The Game Creators. All rights reserved.
//

#import "Texture2D.h"

class cSpriteEx
{
	public:
		float		m_iX;
		float		m_iY;
		
		int			m_iOriginalX;
		int			m_iOriginalY;
	
		int			m_iWidth;
		int			m_iHeight;
		
		Texture2D*	m_pTexture;

		 cSpriteEx ( );
		~cSpriteEx ( );
		
		void Draw ( int width, int height );
};


