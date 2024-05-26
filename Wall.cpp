#include "Wall.h"

Wall::Wall(sf::Vector2f x)
{
	this->size = sf::Vector2f(96.f, 48.f);
	this->wallColor = sf::Color::Transparent;
	this->wallLocation = x;
}

sf::RectangleShape Wall::setShape() const
{
	sf::RectangleShape shape(size);
	shape.setPosition(wallLocation);
	shape.setFillColor(wallColor);
	return shape;
}
