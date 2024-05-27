#include "Fruit.h"
#include <iostream>
using namespace std;

Fruit::Fruit() {

	switch (kindOfFruit)
	{
	case 1:
		this->name = "apple";
		this->texture = jablko;
		this->points = 30;
		break;
	case 2:
		this->name = "pear";
		this->texture = gruszka;
		this->points = 35;
		break;
	case 3:
		this->name = "banana";
		this->texture = banan;
		this->points = 40;
		break;
	case 4:
		this->name = "grapes";
		this->texture = winogrona;
		this->points = 50;
		break;
	}

	sprite.setTexture(this->texture);
}


void Fruit::drawFruit(sf::RenderWindow& window) {
	window.draw(sprite);
}

int Fruit::getPoints()
{
	return this->points;
}


Fruit& Fruit::operator=(const Fruit& other)
{
	name = other.name;
	texture = other.texture;
	location = other.location;
	sprite = other.sprite;
	points = other.points;

	return *this;
}

void Fruit::setLocation(sf::Vector2f newLocation)
{
	this->location = newLocation;
	sprite.setPosition(this->location);
}
