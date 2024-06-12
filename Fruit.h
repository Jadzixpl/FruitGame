#pragma once
#include <SFML/Graphics.hpp> 
#include <string>
#include <random>
#include <ctime>
#include "Global.h"

using namespace std;


class Fruit : public sf::Sprite
{
protected:
    sf::Texture texture;
    sf::Vector2f location;
    sf::Sprite sprite;
    int points; // jab³ko-30 gruszka-35 banan-40 winogrona-50
    int assignedTree;
    vector<sf::Vector2f> locations;

public:
    Fruit() {

        location = sf::Vector2f(-50.f,-50.f);
        texture.loadFromFile("apyl.png");
        points = 30;
        assignedTree = 0;

        sprite.setTexture(texture);

        /*locations.push_back(sf::Vector2f(100, 100));
        locations.push_back(sf::Vector2f(200, 100));
        locations.push_back(sf::Vector2f(300, 100));
        locations.push_back(sf::Vector2f(100, 200));
        locations.push_back(sf::Vector2f(200, 200));
        locations.push_back(sf::Vector2f(300, 200));*/


        /*srand(static_cast<unsigned int>(time(0)));


        setLocation(locations[rand() % 6]);*/
    }

    void drawFruit(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }


    Fruit& operator=(const Fruit& other)
    {
        texture = other.texture;
        location = other.location;
        sprite = other.sprite;
        points = other.points;
        locations = other.locations;

        return *this;
    }

    void setLocation(sf::Vector2f newLocation)
    {
        this->location = newLocation;
        sprite.setPosition(newLocation);
    }

    sf::Sprite& getSprite()
    {
        return sprite;
    }

    Fruit& operator[](int zwrot)
    {
        return this[zwrot];
    }

    void randomizeLocation()
    {
        setLocation(locations[rand() % 6]);
    }

    void assignTree(int tree)
    {
        assignedTree = tree;
    }

    int getTree() 
    {
        return assignedTree;
    }

    void setPoints(int punkty) 
    {
        points = punkty;
    }

    int getPoints()
    {
        return points;
    }

    void setTexture(sf::Texture teksturka)
    {
        texture = teksturka;
    }
};