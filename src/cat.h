/*
	cat.h nachocpol@gmail.com
*/

#include <vector>
#include <memory>

struct CatStats
{
	float Health;
	float Hunger;
	float Happiness;
	float Weight;
	float Misses;
	float Age;	
};

enum CatStates
{
	kMainMenu,
	kIdle,
	kPlaying,
	kSleeping,
	kStats,
	kFade,
	kDead
};

enum CurDayTime
{
	kSunRise,
	kMidday,
	kSunset,
	kNight
};

class RenderWindow;
class Sprite;
class Button;
class Cat
{
public:
	Cat();
	~Cat();
	void Update(float dt);
	void Render(sf::RenderWindow* renderWindow);

private:
	void UpdateMainMenu(float dt);
	void UpdateIdle(float dt);
	void UpdatePlaying(float dt);
	void UpdateSleeping(float dt);
	void UpdateStats(float dt);
	void UpdateFade(float dt);
	void UpdateDead(float dt);

	void RenderMainMenu(sf::RenderWindow* renderWindow);
	void RenderIdle(sf::RenderWindow* renderWindow);
	void RenderPlaying(sf::RenderWindow* renderWindow);
	void RenderSleeping(sf::RenderWindow* renderWindow);
	void RenderStats(sf::RenderWindow* renderWindow);
	void RenderFade(sf::RenderWindow* renderWindow);
	void RenderDead(sf::RenderWindow* renderWindow);
	
	void Reset();

	CatStats mStats;
	CatStates mState;

	// Fade
	const char* mFadeTPath = "../data/textures/fadet.png";
	float mFadeTime = 0.20f;
	float mFadeCurTime = 0.0f;
	bool mHasFadedOut = false;
	CatStates mFadeCurState;
	CatStates mFadeFrom;
	CatStates mFadeTo;
	std::shared_ptr<Sprite> mFader;

	// Bg tracks
	const char* mTrack1 = "../data/sounds/catsong_1.wav";
	const char* mTrack2 = "../data/sounds/catsong_3.wav";

	// Font
	const char* mFontPath = "../data/fonts/HoboStd.otf";
	sf::Font mMainFont;

	// Ratios and caps
	float mMaxAge = 1800.0f;	// 30minutes
	float mHungerRatio = 0.01f;	// +0.01 each second
	float mSnackWeight = 10.0f;	// + 10grames
	float mSnackHunger = 0.25f;	// -0.25f hunger
	float mMealWeight = 50.0f;	// + 100grames
	float mMealHunger = 0.5f;	// - 0.5f hunger
	float mPoopRatio = 0.025f;	// -0.05f each second
	float mPoopCd = 15.0f;		// how often poop
	float mPoopStartSick = 10.0f; // after poopCd + sick reduce health
	
	// Main menu
	const char* mTitlePath = "../data/textures/title.png";
	const char* mStartBtnPath = "../data/textures/start.png";
	const char* mStartBtnPresPath = "../data/textures/startpres.png";
	const char* mContBtnPath = "";
	const char* mMainBgPath = "../data/textures/catagotchi_background.png";
	std::shared_ptr<Button> mStartBtn;
	std::shared_ptr<Sprite> mTitle;
	std::shared_ptr<Sprite> mMainBg;
	bool mHasStarted = false;
	sf::Text mCredits;

	// Audio
	const char* mAudioPath = "../data/textures/audio.png";
	const char* mAudioMutePath = "../data/textures/audiomute.png";
	bool mIsMuted = false;
	std::shared_ptr<Sprite> mAudio;
	std::shared_ptr<Sprite> mAudioMute;
	float mAudioCd = 0.2f;
	float mAudioCurCd = 0.2f;

	// Time of day
	float mCurTime = 0.0f;
	float mTimeDay = 0.0f;
	int mTotalDays = 0;
	// 1.0f / mTimeMod = DayDuration seconds
	float mTimeMod = 0.02f;
	CurDayTime mCurDayTime;
	std::vector<const char*> mSunrisePath;
	std::vector<const char*> mMiddayPath;
	std::vector<const char*> mSunsetPath;
	std::vector<const char*> mNightPath;
	std::vector<std::shared_ptr<Sprite>> mSunrise;
	std::vector<std::shared_ptr<Sprite>> mMidday;
	std::vector<std::shared_ptr<Sprite>> mSunset;
	std::vector<std::shared_ptr<Sprite>> mNight;
	bool mBgTransition = false;
	Sprite* mTransitionFrom;
	Sprite* mTransitionTo;
	float mTransitionCur = 0.0f;
	float mTransitionCd = 0.35f;

	// Poop
	const char* mPoopPath = "../data/textures/poop.png";
	float mCurPoopTimer = 0.0f;
	bool mHasPoop = true;
	std::shared_ptr<Sprite> mPoopSprite;

	// Hearts
	const char* mHeartPath = "../data/textures/heart.png";
	const char* mEmptHeartPath = "../data/textures/heartempt.png";
	int mHearts = 4;
	int mCurHears = 4;
	std::vector<Sprite> mHeartsSprites;
	std::vector<Sprite> mEmptHeartsSprites;

	// Food
	const char* mFodPath = "../data/textures/bread.png";
	const char* mEmpFoodPath = "../data/textures/breadempt.png";
	int mFoods = 4;
	int mCurFoods = 0;
	std::vector<Sprite> mFoodSprites;
	std::vector<Sprite> mEmpFoodSprites;

	// Buttons
	// Feed
	const char* mStdButton = "../data/textures/btntest.png";
	const char* mStdButtonPressed = "../data/textures/btntestpres.png";
	const char* mCookiePath = "../data/textures/cookie.png";
	const char* mCookiePresPath = "../data/textures/cookiepres.png";
	std::shared_ptr<Button> mFeedBtn;
	std::shared_ptr<Button> mSnackBtn;
	std::shared_ptr<Button> mMealBtn;
	float mFeedBtnCd = 0.15f;
	float mFedCurTimer = 0.15f;
	float mSnackCd = 0.25f;
	float mSnackCurTimer = 0.25f;
	float mMealCd = 0.25f;
	float mMealCurTimer = 0.25f;
	bool mShowFeedBtns = false;
	// Stats
	// Go to stats
	const char* mGoToStatsPaht = "../data/textures/settings.png";
	const char* mGoToStatsPresPaht = "../data/textures/settingspres.png";
	std::shared_ptr<Button> mGoToStatsBtn;
	// Back to idle
	const char* mBackPath = "../data/textures/back.png";
	const char* mBackPathPressPath = "../data/textures/back.png";
	std::shared_ptr<Button> mBackToIdleStatsBtn;
	// Pet
	std::shared_ptr<Button> mPetBtn;
	// Clean
	const char* mCleanPath = "../data/textures/clean.png";
	const char* mCleanPresPath = "../data/textures/cleanpres.png";
	std::shared_ptr<Button> mCleanBtn;

	// Stats text
	const char* mStatsBgPath = "../data/textures/catagotchi_background.png";
	std::shared_ptr<Sprite> mStatsBg;
	sf::Text mStatsTitle;
	sf::Text mStatsAge;
	sf::Text mStatsWeight;
	sf::Text mHungerText;
	sf::Text mHappinessText;
	sf::Text mHealthText;
	sf::Text mTotalDaysText;

	// Dead
	const char* mDeadBtnPath = "../data/textures/continue_small.png";
	const char* mDeadBtnPressedPath = "../data/textures/continue.png";
	std::shared_ptr<Button> mDeadBtn;

	// Debug
	bool mShowDebug = false;
};
