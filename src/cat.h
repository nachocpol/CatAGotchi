/*
	cat.h nachocpol@gmail.com
*/

#include <vector>
#include <memory>

struct CatStats
{
	float Hunger;
	float Happiness;
	float Weight;
	float Misses;
	float Age;	
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
	void RenderUi(sf::RenderWindow* renderWindow);
	void RenderButtons(sf::RenderWindow* renderWindow);
	void RenderHealthBar(sf::RenderWindow* renderWindow);
	void RenderFoodBar(sf::RenderWindow* renderWindow);

	CatStats mStats;

	// Hearts
	const char* mHeartPath = "../data/textures/heart.png";
	int mHearts = 4;
	int mCurHears = 0;
	std::vector<Sprite> mHeartsSprites;

	// Food
	const char* mFodPath = "../data/textures/bread.png";
	int mFoods = 4;
	int mCurFoods = 0;
	std::vector<Sprite> mFoodSprites;

	// Buttons
	const char* mStdButton = "../data/textures/btntest.png";
	const char* mStdButtonPressed = "../data/textures/btntestpres.png";
	std::shared_ptr<Button> mFeedBtn;

	// Cat
	const char* mCatPath = "../data/textures/cat.png";
	std::shared_ptr<Sprite> mCat;
};
