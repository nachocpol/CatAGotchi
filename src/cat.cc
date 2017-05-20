#include <string>
#include "SFML/Graphics.hpp"
#include "cat.h"
#include "sprite.h"
#include "button.h"
#include "renderer.h"

Cat::Cat()
{
	// Set initial state
	mState = kIdle;

	// Set initial stats
	mStats.Age = 0.0f;
	mStats.Weight = 0.0f;
	mStats.Hunger = 0.0f;
	mStats.Misses = 0.0f;
	mStats.Happiness = 0.5f;

	// Main font
	if (!mMainFont.loadFromFile(mFontPath))
	{
		printf("ERROR:Could not load the main font.\n");
	}

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
	for (int i = 0; i < mHearts; i++)
	{
		mEmptHeartsSprites.push_back(Sprite(mEmptHeartPath));
		mEmptHeartsSprites[mEmptHeartsSprites.size() - 1].mSfSprite.setPosition
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
	for (int i = 0; i < mFoods; i++)
	{
		mEmpFoodSprites.push_back(Sprite(mEmpFoodPath));
		mEmpFoodSprites[mEmpFoodSprites.size() - 1].mSfSprite.setPosition
		(
			i * 64.0f,
			64.0f + 5.0f
		);
	}

	// Init buttons
	mFeedBtn = std::shared_ptr<Button>(new Button(mStdButton,mStdButtonPressed));
	mFeedBtn->SetPosition(0.0f, 512.0f);
	mGoToStatsBtn = std::shared_ptr<Button>(new Button(mStdButton, mStdButtonPressed));
	mGoToStatsBtn->SetPosition(0.0f, 620.0f);
	mBackToIdleStatsBtn = std::shared_ptr<Button>(new Button(mStdButton, mStdButtonPressed));
	mBackToIdleStatsBtn->SetPosition(128.0f, 620.0f);

	// Init cat
	mCat = std::shared_ptr<Sprite>(new Sprite(mCatPath));
}

Cat::~Cat()
{
}

void Cat::Update(float dt)
{
	switch (mState)
	{
	case kIdle:
		UpdateIdle(dt);
		break;
	case kPlaying:
		UpdatePlaying(dt);
		break;
	case kSleeping:
		UpdateSleeping(dt);
		break;
	case kStats:
		UpdateStats(dt);
		break;
	default:
		break;
	}
}

void Cat::Render(sf::RenderWindow* renderWindow)
{
	switch (mState)
	{
	case kIdle:
		RenderIdle(renderWindow);
		break;
	case kPlaying:
		RenderPlaying(renderWindow);
		break;
	case kSleeping:
		RenderSleeping(renderWindow);
		break;
	case kStats:
		RenderStats(renderWindow);
		break;
	default:
		break;
	}
}

void Cat::UpdateIdle(float dt)
{
	// Events
	if (mGoToStatsBtn->IsPressed())
	{
		mState = kStats;
		return;
	}
	if (mFeedBtn->IsPressed())
	{
		mFedCurTimer += dt;
		if (mFedCurTimer >= mFeedBtnCd)
		{
			mFedCurTimer = 0.0f;
			// Reduce hunger
			mStats.Hunger -= mSnackHunger;
			// Increase weight
			mStats.Weight += mSnackWeight;
		}
	}

	mStats.Age += dt;
	if (mStats.Hunger < 1.0f)
	{
		mStats.Hunger += mHungerRatio * dt;
	}

	// Calc cur food
	mCurFoods = (mFoods * (1.0f - mStats.Hunger));
	if (mCurFoods > mFoods)mCurFoods = mFoods;
}

void Cat::UpdatePlaying(float dt)
{
}

void Cat::UpdateSleeping(float dt)
{
}

void Cat::UpdateStats(float dt)
{
	// Back to idle
	if (mBackToIdleStatsBtn->IsPressed())
	{
		mState = kIdle;
		return;
	}
}

void Cat::RenderIdle(sf::RenderWindow * renderWindow)
{
	auto r = Renderer::GetInstance();

	r->Render(mCat.get());
	r->Render(mFeedBtn.get());
	r->Render(mGoToStatsBtn.get());

	// Bg hearts
	for (int i = 0; i<mHearts; i++)
	{
		renderWindow->draw(mEmptHeartsSprites[i].mSfSprite);
	}
	// Current hearts
	for (int i = 0; i<mCurHears; i++)
	{
		renderWindow->draw(mHeartsSprites[i].mSfSprite);
	}

	// Bg foods
	for (int i = 0; i<mFoods; i++)
	{
		renderWindow->draw(mEmpFoodSprites[i].mSfSprite);
	}
	// Current foods
	for (int i = 0; i<mCurFoods; i++)
	{
		renderWindow->draw(mFoodSprites[i].mSfSprite);
	}
}

void Cat::RenderPlaying(sf::RenderWindow * renderWindow)
{
	auto r = Renderer::GetInstance();
}

void Cat::RenderSleeping(sf::RenderWindow * renderWindow)
{
	auto r = Renderer::GetInstance();
}

void Cat::RenderStats(sf::RenderWindow * renderWindow)
{
	auto r = Renderer::GetInstance();
	
	// Age
	mStatsAge.setFont(mMainFont);
	mStatsAge.setPosition(5.0f, 0.0f);
	mStatsAge.setColor(sf::Color::Black);
	std::string age = "Age:" + std::to_string(mStats.Age);
	mStatsAge.setString(age);
	renderWindow->draw(mStatsAge);

	// Weight
	mStatsWeight.setFont(mMainFont);
	mStatsWeight.setPosition(5.0f, 64.0f);
	mStatsWeight.setColor(sf::Color::Black);
	std::string wei = "Weight:" + std::to_string(mStats.Weight);
	mStatsWeight.setString(wei);
	renderWindow->draw(mStatsWeight);

	// Hunger
	mHungerText.setFont(mMainFont);
	mHungerText.setPosition(5.0f, 128.0f);
	mHungerText.setColor(sf::Color::Black);
	int hungerPer = (int)(mStats.Hunger * 100.0f);
	std::string hun = "Hunger:" + std::to_string(hungerPer) + "%";
	mHungerText.setString(hun);
	renderWindow->draw(mHungerText);

	// Happiness
	mHappinessText.setFont(mMainFont);
	mHappinessText.setPosition(5.0f, 192.0f);
	mHappinessText.setColor(sf::Color::Black);
	int hapPer = (int)(mStats.Happiness * 100.0f);
	std::string hap = "Happiness:" + std::to_string(hapPer) + "%";
	mHappinessText.setString(hap);
	renderWindow->draw(mHappinessText);

	r->Render(mBackToIdleStatsBtn.get());

}