/*
	renderer.h nachocpol@gmail.com
*/

#pragma once

#include <SFML/Graphics.hpp>

class Sprite;
class Renderer
{
public:
	Renderer();
	~Renderer();
	bool Init(unsigned int w,unsigned int h);
	sf::RenderWindow* GetWindow();
	void Render(Sprite* sprite);

private:
	sf::RenderWindow mWindow;
	sf::VideoMode mVidMode;
	sf::Uint32 mWindowStile;
};