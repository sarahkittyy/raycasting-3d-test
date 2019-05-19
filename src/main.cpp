#include <SFML/Graphics.hpp>
#include <iostream>

#include "Map.hpp"
#include "Player.hpp"

int main()
{
	//app window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Raycasting 2");
	sf::Clock appClock;   //app clock

	////App vars
	Map m;   //main map
	m.loadFromJson("resource/map.json");

	Player p({200, 500}, &m);   //map player
	////

	//Background colors.
	sf::RectangleShape ceil, floor;
	ceil.setFillColor(sf::Color(90, 90, 90));
	ceil.setSize({500, 250});
	floor.setFillColor(sf::Color(50, 50, 50));
	floor.setSize({500, 250});
	floor.setPosition({0, 250});

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
		//seconds elapsed since last frame.
		double elapsed = double(appClock.restart().asSeconds());

		//Update the player.
		p.update(elapsed);

		//clear
		window.clear(sf::Color(127, 127, 127));

		//Draw the floor and ceil
		window.draw(floor);
		window.draw(ceil);

		//Draw the player's POV.
		window.draw(p);

		sf::RenderStates s;
		s.transform.translate({500, 0});
		window.draw(m, s);
		p.draw2D(window, s);

		//display
		window.display();
	}

	return 0;
}