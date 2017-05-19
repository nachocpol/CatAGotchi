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

sf::Texture* TextureManager::GetTexture(const char * path)
{
	for each(auto ele in mTextures)
	{
		if (ele->Path == path)
		{
			return &ele->SfTexture;
		}
	}
	// Could not find the texture
	return nullptr;
}

sf::Texture * TextureManager::AddTexture(const char * path)
{
	// Check if the texture already exist
	auto curTex = GetTexture(path);
	if (curTex)
	{
		return curTex;
	}

	// Load the texture, we make first the push back
	// so the reference to the texture isnt lost
	mTextures.push_back(TextureStorage());
	if (!mTextures[mTextures.size() - 1].SfTexture.loadFromFile(path))
	{
		// Could not load the texture
		mTextures.pop_back();
		return nullptr;
	}
	mTextures[mTextures.size() - 1].Path = path;
	return &mTextures[mTextures.size() - 1].SfTexture;
}
