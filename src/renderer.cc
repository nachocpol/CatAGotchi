#include "renderer.h"
#include "sprite.h"
#include "button.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::Init(unsigned int w, unsigned int h)
{
	mVidMode.width = w;
	mVidMode.height = h;
	mWindowStile = sf::Style::Close | sf::Style::Titlebar;
	mWindow.create(mVidMode, "Default", mWindowStile);
	return true;
}

sf::RenderWindow * Renderer::GetWindow()
{
	return &mWindow;
}

void Renderer::Render(Sprite* sprite)
{
	mWindow.draw(sprite->mSfSprite);
}

void Renderer::Render(Button * button)
{
	mWindow.draw(button->GetSprite()->mSfSprite);
}
