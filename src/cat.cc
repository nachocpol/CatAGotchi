#include <string>
#include "SFML/Graphics.hpp"
#include "cat.h"
#include "sprite.h"
#include "button.h"
#include "renderer.h"
#include "audiomanager.h"

Cat::Cat()
{
	// Initialize sounds and bg music
	auto audioMan = AudioManager::GetInstance();
	audioMan->AddTrack(mTrack1);
	audioMan->AddTrack(mTrack2);
	audioMan->SetVolume(0.0f);
	audioMan->PlayMusic();

	// Set initial state
	mState = kMainMenu;

	// Set initial stats
	mStats.Health = 1.0f;
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

	// Window size
	auto r = Renderer::GetInstance();
	auto wSize = r->GetWindow()->getSize();

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
			i * 64.0f + 256.0f,
			5.0f
		);
	}
	for (int i = 0; i < mFoods; i++)
	{
		mEmpFoodSprites.push_back(Sprite(mEmpFoodPath));
		mEmpFoodSprites[mEmpFoodSprites.size() - 1].mSfSprite.setPosition
		(
			i * 64.0f + 256.0f,
			5.0f
		);
	}

	// Init buttons
	// start menu
	mStartBtn = std::shared_ptr<Button>(new Button(mStartBtnPath, mStartBtnPath));
	mStartBtn->SetPosition(192.0f, 360.0f);
	// menu
	mGoToStatsBtn = std::shared_ptr<Button>(new Button(mStdButton, mStdButtonPressed));
	mGoToStatsBtn->SetPosition(384.0f, 656.0f);
	mBackToIdleStatsBtn = std::shared_ptr<Button>(new Button(mStdButton, mStdButtonPressed));
	mBackToIdleStatsBtn->SetPosition(128.0f, 550.0f);
	// actions
	mFeedBtn = std::shared_ptr<Button>(new Button(mStdButton,mStdButtonPressed));
	mFeedBtn->SetPosition(0.0f, 656.0f);
	mPetBtn = std::shared_ptr<Button>(new Button(mStdButton, mStdButtonPressed));
	mPetBtn->SetPosition(128.0f, 656.0f);
	mCleanBtn = std::shared_ptr<Button>(new Button(mStdButton, mStdButtonPressed));
	mCleanBtn->SetPosition(256.0f, 656.0f);

	// Init cat
	mCat = std::shared_ptr<Sprite>(new Sprite(mCatPath));

	// Poop
	mPoopSprite = std::shared_ptr<Sprite>(new Sprite(mPoopPath));
	mPoopSprite.get()->mSfSprite.setPosition(256.0f, 400.0f);

	// Main background
	mBackground = std::shared_ptr<Sprite>(new Sprite(mBgPath));

	// Title
	mTitle = std::shared_ptr<Sprite>(new Sprite(mTitlePath));
	mTitle->mSfSprite.setPosition(0.0f, 100.0f);

	// Fader
	mFader = std::shared_ptr<Sprite>(new Sprite(mFadeTPath));
	mFader->mSfSprite.setColor(sf::Color(255, 255, 255, 0));
}

Cat::~Cat()
{
}

void Cat::Update(float dt)
{
	AudioManager::GetInstance()->Update(dt);

	switch (mState)
	{
	case kMainMenu:
		UpdateMainMenu(dt);
		break;
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
	case kFade:
		UpdateFade(dt);
	default:
		break;
	}
}

void Cat::Render(sf::RenderWindow* renderWindow)
{
	switch (mState)
	{
	case kMainMenu:
		RenderMainMenu(renderWindow);
		break;
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
	case kFade:
		RenderFade(renderWindow);
		break;
	default:
		break;
	}
}

void Cat::UpdateMainMenu(float dt)
{
	if (mStartBtn->IsPressed())
	{
		mHasStarted = true;
		mState = kFade;
		mFadeFrom = kMainMenu;
		mFadeTo = kIdle;

		return;
	}
}

void Cat::UpdateIdle(float dt)
{
	// Check debug
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		mShowDebug = !mShowDebug;
	}

	// Feed btn
	if (mFeedBtn->IsPressed())
	{
		mFedCurTimer += dt;
		if (mFedCurTimer >= mFeedBtnCd)
		{
			mFedCurTimer = 0.0f;
			// Reduce hunger
			mStats.Hunger -= mSnackHunger;
			mStats.Hunger = std::fmax(0.0f, mStats.Hunger);
			// Increase weight
			mStats.Weight += mSnackWeight;
		}
	}
	// Pet btn
	// Clean btn
	if (mCleanBtn->IsPressed())
	{
		if (mHasPoop)
		{
			mHasPoop = false;
			mCurPoopTimer = 0.0f;
		}
	}
	// Stats btn
	if (mGoToStatsBtn->IsPressed())
	{
		mState = kFade;
		mFadeFrom = kIdle;
		mFadeTo = kStats;
		return;
	}

	mStats.Age += dt;
	if (mStats.Hunger < 1.0f)
	{
		mStats.Hunger += mHungerRatio * dt;
	}

	// Calc cur food
	mCurFoods = 1.0f + (mFoods * (1.0f - mStats.Hunger));
	if (mCurFoods > mFoods)mCurFoods = mFoods;

	// Update poop status
	mCurPoopTimer += dt;
	if (mCurPoopTimer >= mPoopCd)
	{
		mHasPoop = true;
	}
	// Get sick if poop is there for a long time
	if (mCurPoopTimer > (mPoopStartSick + mPoopCd) && mHasPoop)
	{
		mStats.Health -= mPoopRatio * dt;
		mStats.Health = std::max(0.0f, mStats.Health);
	}

	// Update health and hearts
	mCurHears = 1.0f + (mHearts * (mStats.Health));
	if (mCurHears > mHearts)mCurHears = mHearts;

	// Check dead
	if (mStats.Health == 0.0f)
	{
		Reset();
		mState = kMainMenu;
		return;
	}
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
		mState = kFade;
		mFadeFrom = kStats;
		mFadeTo = kIdle;
		return;
	}
}

void Cat::UpdateFade(float dt)
{
	// Is fadding out
	if (!mHasFadedOut)
	{
		mFadeCurState = mFadeFrom;

		mFadeCurTime += dt;
		int curAlpha = (int)((255.0f * mFadeCurTime) / mFadeTime);
		mFader->mSfSprite.setColor(sf::Color(255, 255, 255, curAlpha));
		if (mFadeCurTime >= mFadeTime)
		{
			mHasFadedOut = true;
			mFader->mSfSprite.setColor(sf::Color(255, 255, 255, 255));
			mFadeCurTime = mFadeTime;
		}
	}
	// Is fadding in
	else
	{
		mFadeCurState = mFadeTo;

		mFadeCurTime -= dt;
		float curAlpha = (255.0f * mFadeCurTime) / mFadeTime;
		mFader->mSfSprite.setColor(sf::Color(255, 255, 255, (float)curAlpha));
		if (mFadeCurTime <= 0.0f)
		{
			mHasFadedOut = false;
			mFader->mSfSprite.setColor(sf::Color(255, 255, 255, 0));
			mState = mFadeTo;
			return;
		}
	}
}

void Cat::RenderMainMenu(sf::RenderWindow * renderWindow)
{
	auto r = Renderer::GetInstance();
	r->Render(mStartBtn.get());
	r->Render(mTitle.get());
}

void Cat::RenderIdle(sf::RenderWindow * renderWindow)
{
	auto r = Renderer::GetInstance();

	r->Render(mBackground.get());
	r->Render(mFeedBtn.get());
	r->Render(mPetBtn.get());
	r->Render(mCleanBtn.get());
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

	// Poop!
	if (mHasPoop)
	{
		r->Render(mPoopSprite.get());
	}

	// Debug
	if (mShowDebug)
	{
		RenderStats(renderWindow);
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

	// Health
	mHealthText.setFont(mMainFont);
	mHealthText.setPosition(5.0f, 256.0f);
	mHealthText.setColor(sf::Color::Black);
	int heaPer = (int)(mStats.Health * 100.0f);
	std::string hea = "Health:" + std::to_string(heaPer) + "%";
	mHealthText.setString(hea);
	renderWindow->draw(mHealthText);

	r->Render(mBackToIdleStatsBtn.get());
}

void Cat::RenderFade(sf::RenderWindow * renderWindow)
{
	switch (mFadeCurState)
	{
	case kMainMenu:
		RenderMainMenu(renderWindow);
		break;
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

	renderWindow->draw(mFader->mSfSprite);
}

void Cat::Reset()
{
	// Set initial stats
	mStats.Health = 1.0f;
	mStats.Age = 0.0f;
	mStats.Weight = 0.0f;
	mStats.Hunger = 0.0f;
	mStats.Misses = 0.0f;
	mStats.Happiness = 0.5f;

	mCurPoopTimer = 0.0f;
}
