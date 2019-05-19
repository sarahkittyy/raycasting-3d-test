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

	mLines.setPrimitiveType(sf::Lines);


	fline.bind(&mLines);
	//Create the forward-facing line
	fline.set(0, start_pos);
	fline.set(1, mMap->castRay(start_pos, mAngle, VIEW_DIST));
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
	sf::Vector2f pos = mPlayer.getPosition();
	fline.set(0, pos);
	fline.set(1, mMap->castRay(pos, 180 - mAngle, VIEW_DIST));
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draw the player
	target.draw(mPlayer, states);
	//Draw the raycast lines
	target.draw(mLines, states);
}