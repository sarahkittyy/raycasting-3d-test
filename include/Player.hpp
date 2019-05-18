#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

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
	 */
	Player(sf::Vector2f start_pos);

	/**
	 * @brief Update the player
	 * 
	 * @param seconds The seconds elapsed since last frame.
	 */
	void update(const double seconds);

private:
	/**
	 * @brief SFML's draw() override.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

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

	//UTIL//
	constexpr double toRad(double deg)
	{
		return deg * 3.141592653589783238 / 180;
	}
};