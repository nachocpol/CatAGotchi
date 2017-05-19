#include "cat.h"

Cat::Cat()
{
}

Cat::~Cat()
{
}

void Cat::Update(float dt)
{
	mStats.Age += dt;
	mStats.Hunger += dt;
}
