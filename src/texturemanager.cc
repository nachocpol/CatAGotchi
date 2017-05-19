#include "texturemanager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	
}

TextureManager * TextureManager::GetInstance()
{
	static TextureManager sTextureManager;
	return &sTextureManager;
}

sf::Texture * TextureManager::GetTexture(const char * path)
{
	for each(auto ele in mTextures)
	{
		if (ele.Path == path)
		{
			return &ele.SfTexture;
		}
	}
	// Could not find the texture
	return nullptr;
}

sf::Texture * TextureManager::AddTexture(const char * path)
{
	TextureStorage texSt;
	if (!texSt.SfTexture.loadFromFile(path))
	{
		// Could not load the texture
		return nullptr;
	}
	mTextures.push_back(texSt);
	return &mTextures[mTextures.size() - 1].SfTexture;
}
