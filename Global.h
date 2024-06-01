#pragma once
#include <SFML/Graphics.hpp>

extern sf::Vector2f space1, space2, space3, space4, space5, space6;
extern bool taken1, taken2, taken3, taken4, taken5, taken6;

extern sf::Texture jablko;

extern sf::Texture gruszka;

extern sf::Texture banan;

extern sf::Texture winogrona;

extern int kindOfFruit; //owoce
extern int placeForFruit; //miejsca

extern bool gameOver;
extern long int totalScore;
extern Fruit* tab;
extern int currentFruit;