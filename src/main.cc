#include "renderer.h"
#include "sprite.h"
#include "button.h"
int main()
{
	Sprite nCat("../data/textures/nyanc.jpeg");
	Button btn("../data/textures/btntest.png");

	Renderer r;
	r.Init(512,720);
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
		r.Render(&btn);

		r.GetWindow()->display();
	}
}