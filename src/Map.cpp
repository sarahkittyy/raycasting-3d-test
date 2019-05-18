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

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draw the vertex array
	target.draw(mVertices, states);
}