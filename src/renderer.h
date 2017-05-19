/*
	renderer.h nachocpol@gmail.com
*/

#pragma once

#include <SFML/Graphics.hpp>

class Sprite;
class Button;
class Renderer
{
public:
	Renderer();
	~Renderer();
	bool Init(unsigned int w,unsigned int h);
	sf::RenderWindow* GetWindow();
	void Render(Sprite* sprite);
	void Render(Button* button);
private:
	sf::RenderWindow mWindow;
	sf::VideoMode mVidMode;
	sf::Uint32 mWindowStile;
};