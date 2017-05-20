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
	kStats
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

	void RenderMainMenu(sf::RenderWindow* renderWindow);
	void RenderIdle(sf::RenderWindow* renderWindow);
	void RenderPlaying(sf::RenderWindow* renderWindow);
	void RenderSleeping(sf::RenderWindow* renderWindow);
	void RenderStats(sf::RenderWindow* renderWindow);

	CatStats mStats;
	CatStates mState;

	// Font
	const char* mFontPath = "../data/fonts/arial.ttf";
	sf::Font mMainFont;

	// Ratios and caps
	float mMaxAge = 1800.0f;	// 30minutes
	float mHungerRatio = 0.01f;	// +0.01 each second
	float mSnackWeight = 10.0f;	// + 10grames
	float mSnackHunger = 0.25f;	// -0.25f hunger
	float mMealWeight = 100.0f;	// + 100grames
	float mMealHunger = 0.5f;	// - 0.5f hunger
	float mPoopRatio = 0.05f;	// -0.05f each second
	float mPoopCd = 10.0f;		// how often poop
	float mPoopStartSick = 10.0f; // after poopCd + sick reduce health
	
	// Main menu
	const char* mStartBtnPath = "../data/textures/start.png";
	const char* mContBtnPath = "";
	std::shared_ptr<Button> mStartBtn;
	bool mHasStarted = false;

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
	std::shared_ptr<Button> mFeedBtn;
	float mFeedBtnCd = 1.5f;
	float mFedCurTimer = 1.5f;
	// Stats
	// Go to stats
	std::shared_ptr<Button> mGoToStatsBtn;
	// Back to idle
	std::shared_ptr<Button> mBackToIdleStatsBtn;
	// Pet
	std::shared_ptr<Button> mPetBtn;
	// Clean
	std::shared_ptr<Button> mCleanBtn;

	// Stats text
	sf::Text mStatsAge;
	sf::Text mStatsWeight;
	sf::Text mHungerText;
	sf::Text mHappinessText;
	sf::Text mHealthText;

	// Cat
	const char* mCatPath = "../data/textures/cat.png";
	std::shared_ptr<Sprite> mCat;

	// Game bg
	const char* mBgPath = "../data/textures/gamebg.jpg";
	std::shared_ptr<Sprite> mBackground;
};
