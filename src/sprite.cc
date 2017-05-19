#include <iostream>
#include "sprite.h"
#include "texturemanager.h"

Sprite::Sprite(const char* path)
{
	mTexture = TextureManager::GetInstance()->AddTexture(path);
	if (!mTexture)
	{
		printf("ERROR: Could not load the texture:%s\n", path);
		return;
	}
	mSfSprite.setTexture(*mTexture);
}

Sprite::~Sprite()
{
}