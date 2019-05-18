#include "Player.hpp"

Player::Player(sf::Vector2f start_pos)
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
		mAngle += a_accel;
	}
	else if (Hit(Key::D))   //turn right
	{
		mAngle -= a_accel;
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
}

void Player::move(const double factor, const double plus)
{
	//Get the X & Y velocity
	double xv = mVel * std::sin(toRad(mAngle));
	double yv = mVel * std::cos(toRad(mAngle));

	//Move the player.
	mPlayer.move(xv * factor + plus, yv * factor + plus);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draw the player
	target.draw(mPlayer, states);
}