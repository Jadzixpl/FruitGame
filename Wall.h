#pragma once
#include <SFML/Graphics.hpp>
class Wall
{
private:
	sf::Vector2f walllocation;
	sf::Color wallcolor;
	sf::Vector2f size;

public:
	Wall(sf::Vector2f x, sf::Vector2f y);
};

