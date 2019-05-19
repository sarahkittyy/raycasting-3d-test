#include "Line.hpp"

Line::Line(sf::Vector2f a, sf::Vector2f b)
	: a(a),
	  b(b)
{
}

void Line::bind(sf::VertexArray* v, sf::Color c)
{
	//The (new) size of the vertex array
	size_t s = v->getVertexCount() + 2;
	while (v->getVertexCount() < s)
	{
		v->append(sf::Vertex());
	}
	//Bind the two new vertices
	mBound[0] = &((*v)[s - 1]);
	mBound[1] = &((*v)[s - 2]);

	//Set their color.
	mBound[0]->color = c;
	mBound[1]->color = c;

	//Update them
	updateVertices();
}

void Line::updateVertices()
{
	//Set the two vertices's new position.
	mBound[0]->position = a;
	mBound[1]->position = b;
}

void Line::set(int pt, sf::Vector2f n)
{
	switch (pt)
	{
	default:
		throw std::out_of_range("Not a valid point in the line!");
	case 0:
		a = n;
		break;
	case 1:
		b = n;
		break;
	}

	//Update the bound vertices
	updateVertices();
}

sf::Vector2f Line::get(int pt)
{
	switch (pt)
	{
	default:
		throw std::out_of_range("Not a valid point in the line!");
	case 0:
		return a;
	case 1:
		return b;
	}
}