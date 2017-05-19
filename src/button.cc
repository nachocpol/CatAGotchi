#include "SFML/Window.hpp"
#include "button.h"
#include "sprite.h"

Button::Button(const char* Btn)
{
	mBtnSprite = std::shared_ptr<Sprite>(new Sprite(Btn));
}

Button::~Button()
{
}

bool Button::IsPressed()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition();
		auto bounds = mBtnSprite->mSfSprite.getGlobalBounds();
		if (mousePos.x >= bounds.left &&
			mousePos.x <= (bounds.left + bounds.width) &&
			mousePos.y >= bounds.top &&
			mousePos.y <= (bounds.top + bounds.height))
		{
			return true;
		}
	}
	return false;
}
