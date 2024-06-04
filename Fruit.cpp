#include "Fruit.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Global.h"

using namespace std;


Fruit::Fruit() {

	switch (kindOfFruit)
	{
	case 1:
		this->texture = jablko;
		this->points = 30;
		break;
	case 2:
		this->texture = gruszka;
		this->points = 35;
		break;
	case 3:
		this->texture = banan;
		this->points = 40;
		break;
	case 4:
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
	texture = other.texture;
	location = other.location;
	sprite = other.sprite;
	points = other.points;

	return *this;
}

void Fruit::setLocation(sf::Vector2f newLocation)
{
	this->location = newLocation;
	sprite.setPosition(newLocation);//tutaj by³o location
}

sf::Sprite& Fruit::getSprite()
{
	return sprite;
}

Fruit& Fruit::operator[](int zwrot)
{
	return this[zwrot];
}

