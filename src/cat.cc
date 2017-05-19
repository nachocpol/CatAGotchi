#include "SFML/Graphics.hpp"
#include "cat.h"
#include "sprite.h"
#include "button.h"
#include "renderer.h"

Cat::Cat()
{
	// Set initial stats
	mStats.Age = 0.0f;
	mStats.Weight = 0.0f;
	mStats.Hunger = 0.0f;
	mStats.Misses = 0.0f;

	// Hearts
	for (int i = 0; i < mHearts; i++)
	{
		mHeartsSprites.push_back(Sprite(mHeartPath));
		mHeartsSprites[mHeartsSprites.size() - 1].mSfSprite.setPosition
		(
			i * 64.0f,
			5.0f
		);
	}
	// Foods
	for (int i = 0; i < mFoods; i++)
	{
		mFoodSprites.push_back(Sprite(mFodPath));
		mFoodSprites[mFoodSprites.size() - 1].mSfSprite.setPosition
		(
			i * 64.0f,
			64.0f + 5.0f
		);
	}

	// Init buttons
	mFeedBtn = std::shared_ptr<Button>(new Button(mStdButton,mStdButtonPressed));
	mFeedBtn->SetPosition(0.0f, 512.0f);
}

Cat::~Cat()
{
}

void Cat::Update(float dt)
{
	// Events
	if (mFeedBtn->IsPressed())
	{
		mStats.Hunger -= 0.01f;
	}

	mStats.Age += dt;
	if (mStats.Hunger < 1.0f)
	{
		mStats.Hunger += dt;
	}

	// Calc cur food
	mCurFoods = (mFoods * (1.0f - mStats.Hunger)) + 1.0f;
	if (mCurFoods > mFoods)mCurFoods = mFoods;
	printf("%i\n", mCurFoods);
}

void Cat::Render(sf::RenderWindow* renderWindow)
{
	RenderUi(renderWindow);
}

void Cat::RenderUi(sf::RenderWindow* renderWindow)
{
	RenderButtons(renderWindow);
	RenderHealthBar(renderWindow);
	RenderFoodBar(renderWindow);
}

void Cat::RenderButtons(sf::RenderWindow* renderWindow)
{
	Renderer::GetInstance()->Render(mFeedBtn.get());
}

void Cat::RenderHealthBar(sf::RenderWindow* renderWindow)
{
	for each(auto ele in mHeartsSprites)
	{
		renderWindow->draw(ele.mSfSprite);
	}
}

void Cat::RenderFoodBar(sf::RenderWindow * renderWindow)
{
	for(int i = 0;i<mCurFoods;i++)
	{
		renderWindow->draw(mFoodSprites[i].mSfSprite);
	}
}
