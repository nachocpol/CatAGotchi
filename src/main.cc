#include "renderer.h"
#include "sprite.h"
#include "button.h"
int main()
{
	Sprite nCat("../data/textures/nyanc.jpeg");
	Button btn
	(
		"../data/textures/btntest.png",
		"../data/textures/btntestpres.png"
	);
	btn.SetPosition(0.0f, 5.0f);
	Button btn2
	(
		"../data/textures/btntest.png",
		"../data/textures/btntestpres.png"
	);
	btn2.SetPosition(130.0f, 5.0f);

	Renderer* r = Renderer::GetInstance();
	r->Init(512,720);
	while (r->GetWindow()->isOpen())
	{
		sf::Event event;
		while (r->GetWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				r->GetWindow()->close();
			}
		}

		r->GetWindow()->clear();

		r->Render(&nCat);

		r->Render(&btn);
		if (btn.IsPressed())
		{
			
		}

		r->Render(&btn2);
		if (btn2.IsPressed())
		{

		}

		r->GetWindow()->display();
	}
}