#include <SFML/Graphics.hpp> 
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib> 
#include <ctime>

#include "Fruit.h"
#include "Wall.h"

//to do-------------:(
//pudełko
//kosiarka
//pająk
//może dzwięki jak zdąrze
//timer
//wyświetlanie punktów
//tablice sprawdzać po wskaźnikach????

using namespace std;

//podstawowe zmienne
bool gameOver = true;
long int totalScore = 0;

Fruit* tab = new Fruit[50]; //tablica do przechowywania owoców

int currentFruit = 0;


int main(void) {
    sf::RenderWindow window(sf::VideoMode(1000, 650), "Fruit Game", sf::Style::Titlebar | sf::Style::Close);

    window.setMouseCursorVisible(false);

    //wczytywanie tekstur
    sf::Texture postac;
    postac.loadFromFile("bitmapa.png");
    sf::Texture drzewo;
    drzewo.loadFromFile("drzewo.png");
    sf::Texture trawa;
    trawa.loadFromFile("trawakurwa.png"); 
    sf::Texture pudelko;

    sf::Texture kosz;

    sf::Texture kosiarka;

    sf::Texture pajak;

    //postać
    sf::Sprite character;
    character.setTexture(postac);
    character.setPosition(500, 500);
    bool appleInHand = false;

    //drzewa
    sf::Sprite tree1;
    tree1.setTexture(drzewo);
    tree1.setPosition(58.f,100.f);

    sf::Sprite tree2;
    tree2.setTexture(drzewo);
    tree2.setPosition(58.f, 250.f);

    sf::Sprite tree3;
    tree3.setTexture(drzewo);
    tree3.setPosition(58.f, 400.f);
    
    sf::Sprite tree4;
    tree4.setTexture(drzewo);
    tree4.setPosition(846.f, 100.f);

    sf::Sprite tree5;
    tree5.setTexture(drzewo);
    tree5.setPosition(846.f, 250.f);

    sf::Sprite tree6;
    tree6.setTexture(drzewo);
    tree6.setPosition(846.f, 400.f);

    //pudełko
    sf::RectangleShape box(sf::Vector2f(32.f, 32.f));
    box.setFillColor(sf::Color::Magenta);
    box.setPosition(500.f, 586.f);
    
    //trawa
    sf::Sprite grass;
    grass.setTexture(trawa);
    grass.setPosition(0.f, 0.f);

    //wczytanie scoru
    sf::Font font;
    if (!font.loadFromFile("Jaro-Regular-VariableFont_opsz.ttf")) 
    {
        cout << "Błąd ładowania czcionki!" << endl;
        return 1;
    }
    sf::Text score;
    score.setFont(font);
    score.setString("SCORE : ");
    score.setFillColor(sf::Color::White);
    score.setCharacterSize(40);
    score.setPosition(10.f ,10.f);

    //niewidzialne ściany----------------------------------------------------------------------------------------
    Wall wall0(sf::Vector2f(58.f, 100.f));

    Wall wall1(sf::Vector2f(58.f, 250.f));

    Wall wall2(sf::Vector2f(58.f, 400.f));
    
    Wall wall3(sf::Vector2f(846.f, 100.f));
    
    Wall wall4(sf::Vector2f(846.f, 250.f));

    Wall wall5(sf::Vector2f(846.f, 400.f));


    for (int i = 0; i < 50; i++) //losowanie owoców do tablicy --------------------------------------------------
    {
        tab[i] = Fruit();
    }
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // poruszanie po ekranie postaci-------------------------------------------------------------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            character.move(0.1f, 0.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            character.move(-0.1f, 0.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            character.move(0.f, -0.1f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            character.move(0.f, 0.1f);
        }

        //kolizja ścian postaci ---------------------------------------------------------------------------------------
       if (character.getPosition().x < 0)
            character.setPosition(0, character.getPosition().y);

        if (character.getPosition().x + character.getGlobalBounds().width > window.getSize().x)
            character.setPosition(window.getSize().x - character.getGlobalBounds().width, character.getPosition().y);

        if (character.getPosition().y < 0)
            character.setPosition(character.getPosition().x, 0);

        if (character.getPosition().y + character.getGlobalBounds().height > window.getSize().y)
            character.setPosition(character.getPosition().x, window.getSize().y - character.getGlobalBounds().height);
        

        //kolizje (osobne niewidzialne bloki)
        if (character.getGlobalBounds().intersects(wall0.getGlobalBounds()) )//ściana 0
        {
            if (character.getGlobalBounds().left < wall0.getPosition().x)
                character.setPosition(character.getPosition().x - 0.1f, character.getPosition().y);
            else if (character.getGlobalBounds().left > wall0.getPosition().x)
                character.setPosition(character.getPosition().x + 0.1f, character.getPosition().y);

            if(character.getGlobalBounds().top < wall0.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y - 0.1f);
            else if (character.getGlobalBounds().top > wall0.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y + 0.1f);
        }
        if (character.getGlobalBounds().intersects(wall1.getGlobalBounds()))//ściana 1
        {
            if (character.getGlobalBounds().left < wall1.getPosition().x)
                character.setPosition(character.getPosition().x - 0.1f, character.getPosition().y);
            else if (character.getGlobalBounds().left > wall1.getPosition().x)
                character.setPosition(character.getPosition().x + 0.1f, character.getPosition().y);

            if (character.getGlobalBounds().top < wall1.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y - 0.1f);
            else if (character.getGlobalBounds().top > wall1.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y + 0.1f);
        }
        if (character.getGlobalBounds().intersects(wall2.getGlobalBounds()))//śćiana 2
        {
            if (character.getGlobalBounds().left < wall2.getPosition().x)
                character.setPosition(character.getPosition().x - 0.1f, character.getPosition().y);
            else if (character.getGlobalBounds().left > wall2.getPosition().x)
                character.setPosition(character.getPosition().x + 0.1f, character.getPosition().y);

            if (character.getGlobalBounds().top < wall2.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y - 0.1f);
            else if (character.getGlobalBounds().top > wall2.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y + 0.1f);
        }
        if (character.getGlobalBounds().intersects(wall3.getGlobalBounds()))//ściana 3
        {
            if (character.getGlobalBounds().left < wall3.getPosition().x)
                character.setPosition(character.getPosition().x - 0.1f, character.getPosition().y);
            else if (character.getGlobalBounds().left > wall3.getPosition().x)
                character.setPosition(character.getPosition().x + 0.1f, character.getPosition().y);

            if (character.getGlobalBounds().top < wall3.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y - 0.1f);
            else if (character.getGlobalBounds().top > wall3.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y + 0.1f);
        }
        if (character.getGlobalBounds().intersects(wall4.getGlobalBounds()))//ściana 4
        {
            if (character.getGlobalBounds().left < wall4.getPosition().x)
                character.setPosition(character.getPosition().x - 0.1f, character.getPosition().y);
            else if (character.getGlobalBounds().left > wall4.getPosition().x)
                character.setPosition(character.getPosition().x + 0.1f, character.getPosition().y);

            if (character.getGlobalBounds().top < wall4.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y - 0.1f);
            else if (character.getGlobalBounds().top > wall4.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y + 0.1f);
        }
        if (character.getGlobalBounds().intersects(wall5.getGlobalBounds()))//ściana 5
        {
            if (character.getGlobalBounds().left < wall5.getPosition().x)
                character.setPosition(character.getPosition().x - 0.1f, character.getPosition().y);
            else if (character.getGlobalBounds().left > wall5.getPosition().x)
                character.setPosition(character.getPosition().x + 0.1f, character.getPosition().y);

            if (character.getGlobalBounds().top < wall5.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y - 0.1f);
            else if (character.getGlobalBounds().top > wall5.getPosition().y)
                character.setPosition(character.getPosition().x, character.getPosition().y + 0.1f);
        }
        
        
        //render owoców-------------------------------------------------------------------------------
        srand(static_cast<unsigned>(time(0)));
        
        int placeForFruit = rand() % 6 + 1; //miejsca//1-jabłko 2-gruszka 3- banan 4-winogrono

        sf::Clock clock;
        
           while (!gameOver)
            {
               sf::Time elapsed = clock.getElapsedTime();
               

               if (elapsed.asSeconds() > 5.0f)
               {

                   switch (placeForFruit)
                   {
                   case 1:
                       if (taken1 == false)
                       {
                           tab[currentFruit].location = space1;
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

                   clock.restart();
               }
            }


        //podnoszenie jabłka----------------------------------------------------------------------------
            bool keyPressedE = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
            
            for (int j = 0; j < i; j++)
            {
                if (character.getGlobalBounds().intersects(tab[j].getGlobalBounds()))
                {
                    if (keyPressedE && !appleInHand)
                    {
                        appleInHand = true;
                        tab[j].setPosition(1000.f, 1000.f);
                    }
                }
            }

        //kosz

            for(int k = 0; k < i; k++)
            if (keyPressedE && character.getGlobalBounds().intersects(box.getGlobalBounds()) && appleInHand)
            {
                appleInHand = false;
                totalScore += tab[k].getPoints(); //chyba git?
            }
        

        window.clear();

        window.draw(grass);

        window.draw(tree1);
        window.draw(tree2);
        window.draw(tree3);
        window.draw(tree4);
        window.draw(tree5);
        window.draw(tree6);


        window.draw(box);

        window.draw(character);


        window.draw(score);

        window.draw(wall0.setShape());
        window.draw(wall1.setShape());
        window.draw(wall2.setShape());
        window.draw(wall3.setShape());
        window.draw(wall4.setShape());
        window.draw(wall5.setShape());

        window.display();
    }

    delete[] tab;

    std::cout << "Dzienkuje za zagranie :)" << endl;

    return 0;
}

