#pragma once
#include <SFML/Graphics.hpp> 
#include <string>
#include <random>
#include <ctime>
#include <thread>
#include "Global.h"

using namespace std;

class Lawnmower: public sf::Sprite
{
protected:
	sf::Sprite kosiara;
	const float speed = 1.f;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(kosiara, states);
	}
public:
	Lawnmower(sf::Texture *teksturaKosiarki) 
	{
		kosiara.setTexture(*teksturaKosiarki);
		setStartingPlace();
	}

	void setStartingPlace() 
	{
		switch (rand() % 2 + 1)
		{
		case 1:
			kosiara.setPosition(0.f, 200.f);
			break;
		case 2:
			kosiara.setPosition(0.f, 400.f);
			break;
		}
	}

	void moveLawnmower() 
	{
		kosiara.move(speed, 0.f);
		if (kosiara.getPosition().x > 1000.f)
		{
			kosiara.move(0.f, 0.f);
			std::this_thread::sleep_for(std::chrono::seconds(rand() % 8 + 3));//poprawiæ-----------------------
			setStartingPlace();
		}
	}

	sf::Vector2f getPosition()
	{
		return kosiara.getPosition();
	}

	~Lawnmower() {};
};

