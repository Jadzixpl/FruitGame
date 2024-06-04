#pragma once
#include <SFML/Graphics.hpp> 

#include <string>
#include <random>
#include <ctime>

using namespace std;


class Fruit : public sf::Sprite
{
protected:
	sf::Texture texture;
	sf::Vector2f location;
	sf::Sprite sprite;
	int points; // jab³ko-30 gruszka-35 banan-40 winogrona-50
public:
	Fruit();
	void drawFruit(sf::RenderWindow& window);
	int getPoints();
	Fruit& operator=(const Fruit& other);
	void setLocation(sf::Vector2f newLocation);
	sf::Sprite& getSprite();
	Fruit& operator[](int zwrot);
};



