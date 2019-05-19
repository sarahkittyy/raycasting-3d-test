#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief Data and math for a line.
 * 
 */
class Line
{
public:
	/**
	 * @brief Construct a new Line object
	 * 
	 * @param a Point A
	 * @param b Point B
	 */
	Line(sf::Vector2f a = {0, 0}, sf::Vector2f b = {0, 0});

	/**
	 * @brief Bind the line to a vertex array.
	 * 
	 * @param v The vertex array to bind
	 * @param c The color of thel ine
	 */
	void bind(sf::VertexArray* v, sf::Color c = sf::Color::White);

	/**
	 * @brief Set point a(0) or b(1) to n
	 * 
	 * @param pt The point to set
	 * @param n The value to set it to.
	 */
	void set(int pt, sf::Vector2f n);

	/**
	 * @brief Get point a(0) or b(1)
	 * 
	 * @param pt The point to get
	 * @return sf::Vector2f The point.
	 */
	sf::Vector2f get(int pt);

private:
	/**
	 * @brief The bound vertices for the line.
	 * 
	 */
	sf::Vertex* mBound[2];

	/**
	 * @brief The line color
	 * 
	 */
	sf::Color mColor;

	/**
	 * @brief Update data at the mBound vertex pointers.
	 * 
	 */
	void updateVertices();

	/**
	 * @brief Point A
	 * 
	 */
	sf::Vector2f a;

	/**
	 * @brief Point B
	 * 
	 */
	sf::Vector2f b;
};