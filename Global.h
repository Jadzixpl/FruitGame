#pragma once
#include <SFML/Graphics.hpp>

class Fruit;

extern sf::Texture jablko;
extern sf::Texture gruszka;
extern sf::Texture banan;
extern sf::Texture winogrona;

extern int pointsInHand;

extern bool gameOver;
extern long int totalScore;
extern std::vector<Fruit> tab;
extern int currentFruit;