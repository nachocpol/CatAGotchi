/*
	button.h nachocpol@gmail.com
*/

#pragma once

#include <memory>

class Sprite;
class Button
{
public:
	Button(const char* Btn,const char* BtnPres);
	~Button();
	bool IsPressed();
	Sprite* GetSprite();
	void SetPosition(float x, float y);

private:
	bool mIsPressed = false;
	std::shared_ptr<Sprite> mBtnSprite;
	std::shared_ptr<Sprite> mBtnSpritePres;
};
