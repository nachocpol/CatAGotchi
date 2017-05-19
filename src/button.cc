#include "SFML/Window.hpp"
#include "button.h"
#include "sprite.h"
#include "renderer.h"

Button::Button(const char* Btn, const char* BtnPres)
{
	mBtnSprite = std::shared_ptr<Sprite>(new Sprite(Btn));
	mBtnSpritePres = std::shared_ptr<Sprite>(new Sprite(BtnPres));
}

Button::~Button()
{
}

bool Button::IsPressed()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		auto r = Renderer::GetInstance();
		sf::Vector2i mousePos = sf::Mouse::getPosition(*r->GetWindow());
		auto bounds = mBtnSprite->mSfSprite.getGlobalBounds();
		if (mousePos.x >= bounds.left &&
			mousePos.x <= (bounds.left + bounds.width) &&
			mousePos.y >= bounds.top &&
			mousePos.y <= (bounds.top + bounds.height))
		{
			mIsPressed = true;
			return true;
		}
	}
	mIsPressed = false;
	return false;
}

Sprite * Button::GetSprite()
{
	if (mIsPressed)
	{
		return mBtnSpritePres.get();
	}
	return mBtnSprite.get();
}

void Button::SetPosition(float x, float y)
{
	mBtnSprite->mSfSprite.setPosition(x, y);
	mBtnSpritePres->mSfSprite.setPosition(x, y);
}
