#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Line.hpp"

/**
 * @brief Drawable map class, consisting of lines strewn around the screen.
 * 
 */
class Map : public sf::Drawable
{
public:
	/**
	 * @brief Construct the map
	 * 
	 */
	Map();

	/**
	 * @brief Push a new line to the map.
	 * 
	 * @param a Pt A
	 * @param b Pt B
	 * @param color The line color
	 * 
	 * @returns A constant pointer to the created line
	 */
	Line* pushLine(sf::Vector2f a,
				   sf::Vector2f b,
				   sf::Color color = sf::Color::White);

private:
	/**
	 * @brief SFML's draw() override.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief The map vertex array.
	 * 
	 * @remarks NEVER DIRECTLY MODIFY THIS
	 * USE Line::bind()!!
	 * 
	 */
	sf::VertexArray mVertices;

	/**
	 * @brief The main vector of lines.
	 * 
	 */
	std::vector<Line> mLines;
};