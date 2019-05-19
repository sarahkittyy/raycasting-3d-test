#include <SFML/Graphics.hpp>
#include <iostream>

#include "Map.hpp"
#include "Player.hpp"

int main()
{
	//app window
	sf::RenderWindow window(sf::VideoMode(500, 500), "Raycasting 2");
	sf::Clock appClock;   //app clock

	////App vars
	Map m;   //main map
	m.loadFromJson("resource/map.json");

	Player p({200, 500}, &m);   //map player
	////

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

		//Draw the player's POV.
		window.draw(p);

		//display
		window.display();
	}

	return 0;
}