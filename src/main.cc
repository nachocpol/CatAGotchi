#include "renderer.h"
#include "cat.h"

int main()
{
	Renderer* r = Renderer::GetInstance();
	r->Init(512,720);

	Cat cat;

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
		cat.Update(0.00001f);

		r->GetWindow()->clear(sf::Color::White);

		cat.Render(r->GetWindow());

		r->GetWindow()->display();
	}
}