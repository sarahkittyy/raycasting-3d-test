#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <cmath>
#include <vector>

#include "Map.hpp"

/**
 * @brief A movable single point, representing the player / camera position.
 * 
 */
class Player : public sf::Drawable
{
public:
	/**
	 * @brief Construct a new Player object
	 * 
	 * @param start_pos The starting player position
	 * @param m The main app map.
	 */
	Player(sf::Vector2f start_pos, Map* m);

	/**
	 * @brief Update the player
	 * 
	 * @param seconds The seconds elapsed since last frame.
	 */
	void update(const double seconds);

	/**
	 * @brief Draw the 2d representation of the player & the raytraced map.
	 * 
	 */
	void draw2D(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	/**
	 * @brief SFML's draw() override.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief Pointer to the main map.
	 * 
	 */
	Map* mMap;

	/**
	 * @brief How far the raycaster will travel.
	 * 
	 */
	const float VIEW_DIST = INFINITY;

	/**
	 * @brief The range (in degrees) of FOV for the player.
	 * 
	 */
	const float FOV = 80;

	/**
	 * @brief How many lines make up the FOV.
	 * 
	 */
	const float LINES = 800;

	/**
	 * @brief The raytracing line vertex array.
	 * 
	 */
	sf::VertexArray mVA;

	/**
	 * @brief The 2D vertex array for the top-down view of the raytracing lines.
	 * 
	 */
	sf::VertexArray mLineArray;

	/**
	 * @brief The raytracing lines.
	 * 
	 */
	std::vector<Line> mLines;

	/**
	 * @brief The circle representing the player.
	 * 
	 */
	sf::CircleShape mPlayer;

	/**
	 * @brief The angle of the player's movement.
	 * 
	 */
	double mAngle;

	/**
	 * @brief The player's velocity along mAngle
	 * 
	 */
	double mVel;

	/**
	 * @brief Move the player according to mAngle and mVel
	 * 
	 * @param factor What to scale the velocity by when moving the player.
	 * @param plus The additional term added to {xv, yv} * factor.
	 */
	void move(const double factor, const double plus);

	/**
	 * @brief Update the raycast lines.
	 * 
	 */
	void updateCastLines();

	/**
	 * @brief Update the vertex array for the quads rendered by the cast lines.
	 * 
	 */
	void updateVertexArray();

	//UTIL//
	constexpr double toRad(double deg)
	{
		return deg * 3.141592653589783238 / 180;
	}
};