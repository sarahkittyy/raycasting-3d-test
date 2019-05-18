#include <SFML/Graphics.hpp>
#include <iostream>

#include "Map.hpp"

int main()
{
	//app window
	sf::RenderWindow window(sf::VideoMode(500, 500), "Raycasting 2");
	sf::Clock appClock;   //app clock

	////App vars
	Map m;   //main map

	////

	//Configuration
	m.loadFromJson("resource/map.json");
	//

	while (window.isOpen())
	{
		//poll events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}
		//ms elapsed since last frame
		double msElapsed = appClock.restart().asSeconds() * 1000.0;

		//clear
		window.clear(sf::Color(127, 127, 127));

		//draw the map
		window.draw(m);

		//display
		window.display();
	}

	return 0;
}