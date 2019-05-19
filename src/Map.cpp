#include "Map.hpp"

Map::Map()
{
	mVertices.setPrimitiveType(sf::Lines);
}

void Map::loadFromJson(std::string fname)
{
	using nlohmann::json;

	//open the file
	std::ifstream file(fname);

	if (!file)
	{
		throw std::runtime_error("Invalid json file " + fname);
	}

	//Create the json object
	json data;
	file >> data;   //extract the data
	//close the file.
	file.close();

	//Get the color
	sf::Color color(data["color"][0], data["color"][1], data["color"][2]);

	//Get the lines array.
	json::array_t lines = data["lines"];
	//For every two lines...
	for (int i = 0; i < lines.size(); i += 2)
	{
		//Get the two points.
		sf::Vector2f a, b;
		a.x = lines[i][0];
		a.y = lines[i][1];
		b.x = lines[i + 1][0];
		b.y = lines[i + 1][1];
		//Push the two lines
		pushLine(a, b, color);
	}
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

sf::Vector2f Map::castRay(sf::Vector2f pt1, double theta, float max)
{
	theta = toRad(theta);
	theta = float(int(theta * 100)) / 100.f;

	//Turn infinity to just a really big number, for compatibility.
	if (max == INFINITY)
	{
		max = 9999999.f;
	}

	//Second point to the input line.
	sf::Vector2f pt2(pt1.x + max * std::sin(theta), pt1.y + max * std::cos(theta));

	//Intersection with minimum distance to pt1
	sf::Vector2f min_res{INFINITY, INFINITY};
	//Iterate over all lines..
	for (auto& line : mLines)
	{
		//Get the two line points
		sf::Vector2f l1 = line.get(0);
		sf::Vector2f l2 = line.get(1);

		float m1, m2;
		float b1, b2;

		//The intersection of the two lines.
		sf::Vector2f intersection;

		//If both lines are vertical...
		if (pt2.x - pt1.x == 0 && l2.x - l1.x == 0)
		{
			//They're parallel & don't touch.
			continue;
		}
		//If the given line is vertical...
		else if (pt2.x - pt1.x == 0)
		{
			//Get the slope of the other line
			m2 = (l2.y - l1.y) / (l2.x - l1.x);
			b2 = l1.y - m2 * l1.x;   //y intercept

			//Plug in the equation x = pt1.x
			float yi = m2 * pt1.x + b2;   //place where the given vertical line meets the current line

			//Intersection of two lines now @ (pt1.x, yi)
			intersection = sf::Vector2f(pt1.x, yi);
		}
		else if (l2.x - l1.x == 0)   //If the current line is vertical...
		{
			//Get the slope of the other line
			m1 = (pt2.y - pt1.y) / (pt2.x - pt1.x);
			b1 = pt1.y - m1 * pt1.x;   // y intercept

			//Plug in the equation x = l1.x
			float yi = m1 * l1.x + b1;   //place where the given vertical line meets the given line

			//Intersection of two lines now @ (l1.x, yi)
			intersection = sf::Vector2f(l1.x, yi);
		}
		else
		{
			//Get the slope of the two lines
			m1 = (pt2.y - pt1.y) / (pt2.x - pt1.x);
			m2 = (l2.y - l1.y) / (l2.x - l1.x);
			//Y intercepts
			b1 = pt1.y - m1 * pt1.x;
			b2 = l1.y - m2 * l1.x;

			//If the slopes are equal, they're parallel
			if (m1 == m2)
			{
				continue;
			}

			//Get the intersection
			float xi	 = (b2 - b1) / (m1 - m2);
			float yi	 = m1 * xi + b1;
			intersection = sf::Vector2f(xi, yi);
		}

		//Check if the colliding point is contained in both rectangles created by both lines.
		sf::FloatRect r1(std::min(l1.x, l2.x) - 1.f,
						 std::min(l1.y, l2.y) - 1.f,
						 std::max(std::abs(l2.x - l1.x) + 1.f, 2.f),
						 std::max(std::abs(l2.y - l1.y) + 1.f, 2.f));
		sf::FloatRect r2(std::min(pt1.x, pt2.x) - 1.f,
						 std::min(pt1.y, pt2.y) - 1.f,
						 std::max(std::abs(pt2.x - pt1.x) + 1.f, 2.f),
						 std::max(std::abs(pt2.y - pt1.y) + 1.f, 2.f));
		//If they both contain the point...
		if (r1.contains(intersection) && r2.contains(intersection))
		{
			//Check the distance from intersection to min_res
			if (std::hypot(pt1.x - intersection.x,
						   pt1.y - intersection.y) <
				std::hypot(pt1.x - min_res.x,
						   pt1.y - min_res.y))
			{
				//If it's closer, set it.
				min_res = intersection;
			}
		}
	}

	//Return the minimum intersection
	return (min_res != sf::Vector2f(INFINITY, INFINITY)) ? (min_res) : (pt1);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draw the vertex array
	target.draw(mVertices, states);
}