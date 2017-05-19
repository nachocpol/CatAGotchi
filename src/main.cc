#include "renderer.h"
#include "sprite.h"

int main()
{
	Sprite nCat("../data/textures/nyanc.jpeg");

	Renderer r;
	r.Init(512,512);
	while (r.GetWindow()->isOpen())
	{
		sf::Event event;
		while (r.GetWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				r.GetWindow()->close();
			}
		}

		r.GetWindow()->clear();
		r.Render(&nCat);
		r.GetWindow()->display();
	}
}