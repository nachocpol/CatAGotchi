#include "SFML/System.hpp"
#include "renderer.h"
#include "cat.h"

int main()
{
	Renderer* r = Renderer::GetInstance();
	r->Init(512,720);

	Cat cat;

	sf::Clock clock;
	while (r->GetWindow()->isOpen())
	{
		// Delta time
		sf::Time elapsed = clock.restart();

		sf::Event event;
		while (r->GetWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				r->GetWindow()->close();
			}
		}
		cat.Update(elapsed.asSeconds());

		r->GetWindow()->clear(sf::Color::White);

		cat.Render(r->GetWindow());

		r->GetWindow()->display();
	}
}