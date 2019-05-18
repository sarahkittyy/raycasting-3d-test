#include "Map.hpp"

Map::Map()
{
	mVertices.setPrimitiveType(sf::Lines);
}

Line* Map::pushLine(sf::Vector2f a, sf::Vector2f b, sf::Color color)
{
	//Create the line
	mLines.push_back(Line(a, b));
	//Get the newly created line
	Line* created = &mLines.back();
	//Bind it
	created->bind(&mVertices, color);
	//Return it
	return created;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draw the vertex array
	target.draw(mVertices, states);
}