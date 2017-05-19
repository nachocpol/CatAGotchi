/*
	cat.h nachocpol@gmail.com
*/

struct CatStats
{
	float Hunger;
	float Happiness;
	float Weight;
	float Misses;
	float Age;	
};

class Cat
{
public:
	Cat();
	~Cat();
	void Update(float dt);

private:
	CatStats mStats;
};
