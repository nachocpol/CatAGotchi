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

	std::shared_ptr<TextureStorage> texSt =  std::shared_ptr<TextureStorage>( new TextureStorage);
	if (!texSt->SfTexture.loadFromFile(path))
	{
		// Could not load the texture
		return nullptr;
	}
	mTextures.push_back(std::move(texSt));
	mTextures[mTextures.size() - 1]->Path = path;
	return &mTextures[mTextures.size() - 1]->SfTexture;
}
