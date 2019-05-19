#include "Player.hpp"

Player::Player(sf::Vector2f start_pos, Map* m)
	: mMap(m)
{
	//Init the circle
	mPlayer.setRadius(2);
	mPlayer.setFillColor(sf::Color::Black);
	mPlayer.setOrigin(mPlayer.getLocalBounds().width / 2.0f,
					  mPlayer.getLocalBounds().height / 2.0f);
	mPlayer.setPosition(start_pos);

	//init vars
	mVel   = 0;
	mAngle = 0;

	mVA.setPrimitiveType(sf::Quads);
	mLineArray.setPrimitiveType(sf::Lines);

	//Update the raycasting lines.
	updateCastLines();
}

void Player::update(const double seconds)
{
	//Convenient aliases
	using Key = sf::Keyboard::Key;
	auto Hit  = &sf::Keyboard::isKeyPressed;

	//The player's acceleration
	const double accel   = 300 * seconds;
	const double a_accel = 200 * seconds;

	if (Hit(Key::A))   //turn left
	{
		mAngle -= a_accel;
	}
	else if (Hit(Key::D))   //turn right
	{
		mAngle += a_accel;
	}

	//Wrap the angle around.
	if (mAngle > 360)
	{
		mAngle = mAngle - 360;
	}
	else if (mAngle < 0)
	{
		mAngle = 360 - mAngle;
	}

	if (Hit(Key::W))   //forwards
	{
		mVel += accel;
	}
	else if (Hit(Key::S))   //backwards
	{
		mVel -= accel;
	}
	else
	{
		//Deaccelerate
		if (mVel > accel / 2.0)
		{
			mVel -= accel;
		}
		else if (mVel < -accel / 2.0)
		{
			mVel += accel;
		}
		else
		{
			mVel = 0;
		}
	}

	//Velocity cap
	const double vCap = 120.;
	mVel			  = std::min(std::max(mVel, -vCap), vCap);

	//Move the player
	move(seconds, 0.5 * accel * seconds * seconds);
	//Update the cast lines
	updateCastLines();
}

void Player::move(const double factor, const double plus)
{
	//Get the X & Y velocity          //angle is backwards, so we flip it
	double xv = mVel * std::sin(toRad(180 - mAngle));
	double yv = mVel * std::cos(toRad(180 - mAngle));

	//Move the player.
	mPlayer.move(xv * factor + plus, yv * factor + plus);
}

void Player::updateCastLines()
{
	//player pos.
	sf::Vector2f pos = mPlayer.getPosition();
	//clear raytracing lines.
	mLines.clear();
	mLineArray.clear();
	//For every line..
	for (size_t i = 0; i < (size_t)LINES; ++i)
	{
		//Get the angle range..
		float angle_min = mAngle - FOV / 2.f;
		float angle_max = mAngle + FOV / 2.f;
		//Get the angle to use
		float angle = angle_min + (angle_max - angle_min) * (float(i) / LINES);

		//Push the line.
		mLines.push_back(Line(pos, mMap->castRay(pos,
												 size_t(180 - angle) % 360,
												 VIEW_DIST)));

		//Bind the line.
		mLines.back().bind(&mLineArray, sf::Color::Red);
	}

	updateVertexArray();
}

void Player::updateVertexArray()
{
	mVA.clear();
	//Player's position.
	sf::Vector2f pos = mPlayer.getPosition();

	size_t index = 0;

	//For every cast line...
	for (auto& line : mLines)
	{
		//The point it's collided with...
		sf::Vector2f pt = line.get(1);
		//The distance from that point to the player's position.
		double dist = std::hypot(pos.x - pt.x, pos.y - pt.y);
		//That distance converted to greyscale.
		double grey = std::exp(5.5 - (dist / 80.));
		//The color to use.
		sf::Color color(grey, grey, grey);
		//Get the height of the rectangle.
		double height = 1000. / (dist * std::cos(toRad(FOV)));
		//Get the dist off the floor of the rectangle.
		double floor_dist = (500 - height) / 2.0;
		//Get the width of the rectangle.
		double width = 500. / double(mLines.size());

		//Get the top left coord of the rectangle.
		sf::Vector2f tl(width * index,
						floor_dist);

		//Create the four points
		mVA.append(sf::Vertex(
			sf::Vector2f(tl.x, tl.y),
			color));
		mVA.append(sf::Vertex(
			sf::Vector2f(tl.x + width, tl.y),
			color));
		mVA.append(sf::Vertex(
			sf::Vector2f(tl.x + width, tl.y + height),
			color));
		mVA.append(sf::Vertex(
			sf::Vector2f(tl.x, tl.y + height),
			color));


		index++;
	}
}

void Player::draw2D(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mLineArray, states);
	target.draw(mPlayer, states);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mVA, states);
}