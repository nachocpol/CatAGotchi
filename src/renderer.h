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
	~Renderer();
	static Renderer* GetInstance();
	bool Init(unsigned int w,unsigned int h);
	sf::RenderWindow* GetWindow();
	void Render(Sprite* sprite);
	void Render(Button* button);
	sf::VideoMode GetVideoMode() { return mVidMode; }
private:
	Renderer();
	sf::RenderWindow mWindow;
	sf::VideoMode mVidMode;
	sf::Uint32 mWindowStile;
};