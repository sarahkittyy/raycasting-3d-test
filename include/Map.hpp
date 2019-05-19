#pragma once

#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

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
	 * @brief Load the map from given json filename
	 * 
	 * @param fname The path to the map json file
	 */
	void loadFromJson(std::string fname);

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

	/**
	 * @brief Casts a ray from the given point, with the given angle.
	 * 
	 * @param pt1 The point of origin for the ray. 
	 * @param theta The angle at which the ray is sent at.
	 * @param max The maximum ray distance.
	 * 
	 * @return sf::Vector2f The point of intersection of the ray on the map's lines, or the initial point if no intersection was found.
	 */
	sf::Vector2f castRay(sf::Vector2f pt1, float theta, float max);

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

	//RAYCASTING METHODS

	/**
	 * @brief Convert degrees to radians
	 * 
	 */
	constexpr float toRad(float deg)
	{
		return deg * 3.14159265358979 / 180;
	}
};