/*
	button.h nachocpol@gmail.com
*/

#pragma once

#include <memory>

class Sprite;
class Button
{
public:
	Button(const char* Btn);
	~Button();
	bool IsPressed();
	Sprite* GetSprite() { return mBtnSprite.get(); }

private:
	std::shared_ptr<Sprite> mBtnSprite;
};
