/*
	texturemanager.h nachocpol@gmail.com
*/

#pragma once

#include <vector>
#include "SFML/Graphics.hpp"

struct TextureStorage
{
	const char* Path;
	sf::Texture SfTexture;
};

class TextureManager
{
public:
	~TextureManager();
	static TextureManager* GetInstance();
	sf::Texture* GetTexture(const char* path);
	sf::Texture* AddTexture(const char* path);

private:
	TextureManager();
	std::vector<TextureStorage> mTextures;
};

