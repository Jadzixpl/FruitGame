#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

class Fruit;

extern sf::Texture jablko;
extern sf::Texture gruszka;
extern sf::Texture banan;
extern sf::Texture winogrona;
extern sf::Texture kosiarka;

extern int pointsInHand;

extern bool gameOver;
extern long int totalScore;
extern std::vector<Fruit> tab;
extern int currentFruit;
