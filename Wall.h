#pragma once
#include <SFML/Graphics.hpp>

class Wall: public sf::Sprite
{
private:
	sf::Vector2f wallLocation;
	sf::Color wallColor;
	sf::Vector2f size;

public:
	Wall(sf::Vector2f x);
	sf::RectangleShape setShape() const;
};

