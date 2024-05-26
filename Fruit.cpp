#include "Fruit.h"
#include <iostream>
using namespace std;


sf::Texture jablko;
auto teksturaJablka = jablko.loadFromFile("apyl.png");

sf::Texture gruszka;
auto teksturaGruszki = gruszka.loadFromFile("gruszka.png");

sf::Texture banan;
auto teksturaBanana = banan.loadFromFile("banan.png");

sf::Texture winogrona;
auto teksturaWinogrona = winogrona.loadFromFile("winogrona.png");

int kindOfFruit = rand() % 4 + 1; //owoce 1-jab³ko 2-gruszka 3- banan 4-winogrono
int placeForFruit = rand() % 6 + 1; //miejsca

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

	/*switch (placeForFruit)
	{
	case 1:
		if (taken1 == false)
		{
			this->location = space1;
			taken1 = true;
		}
		else
			placeForFruit++;
		break;
	case 2:
		if (taken2 == false)
		{
			this->location = space2;
			taken2 = true;
		}
		else
			placeForFruit++;
		break;
	case 3:
		if (taken3 == false)
		{
			this->location = space3;
			taken3 = true;
		}
		else
			placeForFruit++;
		break;
	case 4:
		if (taken4 == false)
		{
			this->location = space4;
			taken4 = true;
		}
		else
			placeForFruit++;
		break;
	case 5:
		if (taken5 == false)
		{
			this->location = space5;
			taken5 = true;
		}
		else
			placeForFruit++;
		break;
	case 6:
		if (taken6 == false)
		{
			this->location = space6;
			taken6 = true;
		}
		break;
	}

	sprite.setPosition(this->location);*/
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
