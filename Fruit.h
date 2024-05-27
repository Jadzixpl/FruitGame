#pragma once
#include <SFML/Graphics.hpp> 

#include <string>
#include <random>
#include <ctime>

using namespace std;

sf::Vector2f space1(155.f, 164.f), space2(155.f, 314.f), space3(155.f, 464.f), space4(814.f, 164.f), space5(814.f, 314.f), space6(814.f, 464.f);
bool taken1 = false, taken2 = false, taken3 = false, taken4 = false, taken5 = false, taken6 = false;

sf::Texture jablko;
auto teksturaJablka = jablko.loadFromFile("apyl.png");

sf::Texture gruszka;
auto teksturaGruszki = gruszka.loadFromFile("gruszka.png");

sf::Texture banan;
auto teksturaBanana = banan.loadFromFile("banan.png");

sf::Texture winogrona;
auto teksturaWinogrona = winogrona.loadFromFile("winogrona.png");

int kindOfFruit = rand() % 4 + 1; //owoce
int placeForFruit = rand() % 6 + 1; //miejsca

class Fruit : public sf::Sprite
{
protected:
	string name;
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
};



