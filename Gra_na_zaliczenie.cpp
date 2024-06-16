#include <SFML/Graphics.hpp> 
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib> 
#include <ctime>

#include "Fruit.h"
#include "Wall.h"
#include "Global.h"
#include "Lawnmower.h"
//to do-------------:(
//pająk
//naprawić ściany

using namespace std;

bool gameOver = false;
bool tutorial = true;
bool startGame = false;

long int totalScore = 0;

sf::Texture jablko, gruszka, banan, winogrona, kosiarka; 

std::vector<Fruit> tab; //wektor do przechowywania owoców 

std::vector<int> availableTrees;

int currentFruit = 0;

int pointsInHand = 0;

const float FRUIT_RANGE_X = 30.f;
const float FRUIT_RANGE_Y = 30.f;

sf::Vector2f treePositions[] = {
    sf::Vector2f(58.f, 100.f),
    sf::Vector2f(58.f, 250.f),
    sf::Vector2f(58.f, 400.f),
    sf::Vector2f(846.f, 100.f),
    sf::Vector2f(846.f, 250.f),
    sf::Vector2f(846.f, 400.f)
};

bool takenTrees[] = { false, false, false, false, false, false };

int tabKos[10];

int main(void) {
    sf::RenderWindow window(sf::VideoMode(1000, 650), "Fruit Game", sf::Style::Titlebar | sf::Style::Close);

    window.setMouseCursorVisible(false);

    //wczytywanie tekstur----------------------------------------------------------------------
    sf::Texture postac_p;
    postac_p.loadFromFile("farmer_przod.png");
    sf::Texture postac_t;
    postac_t.loadFromFile("farmer_tyl.png");
    sf::Texture postac_prawo;
    postac_prawo.loadFromFile("farmer_pbok.png");
    sf::Texture postac_lewo;
    postac_lewo.loadFromFile("farmer_lbok.png");

    sf::Texture postac_p_owoc;
    postac_p_owoc.loadFromFile("farmer_przod_owoc.png");
    sf::Texture postac_t_owoc;
    postac_t_owoc.loadFromFile("farmer_tyl_owoc.png");
    sf::Texture postac_prawo_owoc;
    postac_prawo_owoc.loadFromFile("farmer_pbok_owoc.png");
    sf::Texture postac_lewo_owoc;
    postac_lewo_owoc.loadFromFile("farmer_lbok_owoc.png");


    sf::Texture drzewo;
    drzewo.loadFromFile("drzewo.png");
    sf::Texture trawa;
    trawa.loadFromFile("trawakurwa.png"); 
    sf::Texture pudelko;
    pudelko.loadFromFile("pudlo.png");

    kosiarka.loadFromFile("kosiarka.png");
    jablko.loadFromFile("apyl.png");
    gruszka.loadFromFile("gruszka.png");
    banan.loadFromFile("banan.png");
    winogrona.loadFromFile("winogrona.png");


    //postać
    sf::Sprite character;
    character.setTexture(postac_p);
    character.setPosition(500, 500);
    bool appleInHand = false;

    //drzewa
    sf::Sprite tree1, tree2, tree3, tree4, tree5, tree6;
    tree1.setTexture(drzewo); tree1.setPosition(58.f, 100.f);
    tree2.setTexture(drzewo); tree2.setPosition(58.f, 250.f);
    tree3.setTexture(drzewo); tree3.setPosition(58.f, 400.f);
    tree4.setTexture(drzewo); tree4.setPosition(846.f, 100.f);
    tree5.setTexture(drzewo); tree5.setPosition(846.f, 250.f);
    tree6.setTexture(drzewo); tree6.setPosition(846.f, 400.f);

    //pudełko
    sf::Sprite box;
    box.setTexture(pudelko);
    box.setPosition(500.f, 576.f);
    
    //trawa
    sf::Sprite grass;
    grass.setTexture(trawa);
    grass.setPosition(0.f, 0.f);

    //wczytanie scoru------------------------------------------------------------------------------------------
    sf::Font font;
    if (!font.loadFromFile("Jaro-Regular-VariableFont_opsz.ttf")) 
    {
        std::cout << "Błąd ładowania czcionki!" << endl;
        return 1;
    }
    sf::Text score;
    score.setFont(font);
    score.setFillColor(sf::Color::White);
    score.setCharacterSize(40);
    score.setPosition(10.f ,10.f);

    //timer -----------------------------------------------------------------------------------------------
    sf::Text timer;
    timer.setFont(font);
    timer.setFillColor(sf::Color::White);
    timer.setCharacterSize(40);
    timer.setPosition(800.f, 10.f);

    sf::Texture Gametutorial;
    Gametutorial.loadFromFile("tutorial.png");
    sf::Sprite tuto;
    tuto.setTexture(Gametutorial);
    tuto.setPosition(0.f, 0.f);

    sf::Texture koniecGry;
    koniecGry.loadFromFile("gameover.png");
    sf::Sprite over;
    over.setTexture(koniecGry);
    over.setPosition(0.f, 0.f);


    //niewidzialne ściany----------------------------------------------------------------------------------------
    /*Wall wall0(sf::Vector2f(58.f, 100.f));
    Wall wall1(sf::Vector2f(58.f, 250.f));
    Wall wall2(sf::Vector2f(58.f, 400.f));
    Wall wall3(sf::Vector2f(846.f, 100.f));
    Wall wall4(sf::Vector2f(846.f, 250.f));
    Wall wall5(sf::Vector2f(846.f, 400.f));*/


    tab.reserve(50);//zarezerwowane żeby nie alokować pamięci :D
    for (int i = 0; i < 50; i++) {
        
        switch (rand() % 4 + 1)
        {
        case 1:
            tab.push_back(Fruit(&jablko, 30));
            break;
        case 2:
            tab.push_back(Fruit(&gruszka,35));
            break;
        case 3:
            tab.push_back(Fruit(&banan, 40));
            break;
        case 4:
            tab.push_back(Fruit(&winogrona,45));
            break;
        default:
            break;
        }
       
    }

    float characterSpeed = 0.15;

    sf::Clock fruitClock; //zegary
    sf::Clock gameTime;
   
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        // poruszanie po ekranie postaci-------------------------------------------------------------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (appleInHand)
                character.setTexture(postac_prawo_owoc);
            else
                character.setTexture(postac_prawo);

            character.move(characterSpeed, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (appleInHand)
                character.setTexture(postac_lewo_owoc);
            else
                character.setTexture(postac_lewo);

            character.move(-characterSpeed, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (appleInHand)
                character.setTexture(postac_t_owoc);
            else
                character.setTexture(postac_t);
            
            character.move(0, -characterSpeed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (appleInHand)
                character.setTexture(postac_p_owoc);
            else
                character.setTexture(postac_p);

            character.move(0, characterSpeed);
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
        //for (auto& wall : { wall0, wall1, wall2, wall3, wall4, wall5 }) {
        //    if (character.getGlobalBounds().intersects(wall.getGlobalBounds()))//ściana 0
        //    {
        //        cout << "Kolizja" << endl;

        //        if (character.getGlobalBounds().left < wall.getPosition().x)
        //            character.setPosition(character.getPosition().x - 0.1f, character.getPosition().y);
        //        else if (character.getGlobalBounds().left > wall.getPosition().x)
        //            character.setPosition(character.getPosition().x + 0.1f, character.getPosition().y);

        //        if (character.getGlobalBounds().top < wall.getPosition().y)
        //            character.setPosition(character.getPosition().x, character.getPosition().y - 0.1f);
        //        else if (character.getGlobalBounds().top > wall.getPosition().y)
        //            character.setPosition(character.getPosition().x, character.getPosition().y + 0.1f);
        //    }
        //}
         
        srand(static_cast<unsigned>(time(0)));

        // Losowanie nowego owocu co 5 sekund-----------------------------------------------------------------------
        if (fruitClock.getElapsedTime().asSeconds() > 5.0f && !gameOver && gameTime.getElapsedTime().asSeconds() <= 61) {
            for (int i = 0; i < 6; ++i) {
                if (!takenTrees[i]) {
                    availableTrees.push_back(i);
                }
            }

            if (!availableTrees.empty() && currentFruit < tab.size()) {
                int randomTreeIndex = rand() % availableTrees.size();
                int treeIndex = availableTrees[randomTreeIndex];

                float treeX = treePositions[treeIndex].x;
                float treeY = treePositions[treeIndex].y;

                float fruitX = treeX + (rand() % (int)(2 * FRUIT_RANGE_X)) - FRUIT_RANGE_X;//Generowanie wokół drzewa
                float fruitY = treeY + (rand() % (int)(2 * FRUIT_RANGE_Y)) - FRUIT_RANGE_Y;


                tab[currentFruit].setLocation(sf::Vector2f(fruitX, fruitY));
                takenTrees[treeIndex] = true;

                tab[currentFruit].assignTree(treeIndex);

                std::cout << "Owoc wygenerowany na pozycji: " << fruitX << " , " << fruitY << endl;

                ++currentFruit;
            }

            fruitClock.restart();
        }

        //przejazd kosiarki ------------------------------------------------------------------------------
        Lawnmower brumbrum(&kosiarka);
        brumbrum.moveLawnmower();
        
        // Podnoszenie owocu-------------------------------------------------------------------------------
        bool keyPressedE = sf::Keyboard::isKeyPressed(sf::Keyboard::E);

        for (int j = 0; j < currentFruit; j++) {
            if (character.getGlobalBounds().intersects(tab[j].getSprite().getGlobalBounds())) {
                if (keyPressedE && !appleInHand) {
                    appleInHand = true;
                    pointsInHand = tab[j].getPoints();
                    tab[j].setLocation(sf::Vector2f(1000.f, 1000.f));
                    std::cout << "Podniesiono owoc" << endl;
                    takenTrees[tab[j].getTree()] = false;
                }
            }
        }

        //kosz----------------------------------------------------------------------------------------------
        if (keyPressedE && character.getGlobalBounds().intersects(box.getGlobalBounds()))
        {
            appleInHand = false;
            totalScore +=pointsInHand;
            pointsInHand = 0;
        }

        //koniec gry -----------------------------------------------------------------------------------
        if (startGame && gameTime.getElapsedTime().asSeconds() > 60)
        {
            gameOver = true;
            startGame = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return 1;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            tutorial = false;
            startGame = true;
            gameTime.restart();
        }

        //wyświetlanie-------------------------------------------------------------------------------
        if (startGame)
        {
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

            for (auto& fruit : tab) {
                fruit.drawFruit(window);
            }

            window.draw(brumbrum);

            score.setString("SCORE: " + std::to_string(totalScore));
            window.draw(score);
            timer.setString("TIME: " + std::to_string(static_cast<int>(60 - gameTime.getElapsedTime().asSeconds())));
            window.draw(timer);
            window.display();
        }

        if (gameOver)
        {
            window.clear();
            window.draw(over);
            window.display();
        }

        if (tutorial)
        {
            window.clear();
            window.draw(tuto);
            window.display();
        }
    }


    std::cout << "Dzienkuje za zagranie :)" << endl;

    return 0;
}

