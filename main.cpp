#include <SFML/Graphics.hpp>
#include <cmath>
#include "character.h"
#include "FillBar.h"
//#include "MoveButton.h"
#include "MoveMenu.h"
//#include <vector>
//#include <iostream>

//function prototypes
float distanceFormula(float, float, float, float);
bool isHoveringEnemy(sf::RenderWindow &, sf::Vector2i, sf::Vector2f, float);
void drawPiMenu(sf::CircleShape &, sf::Vector2f);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);

    //Disable key repeat for mouse clicks
    window.setKeyRepeatEnabled(false);

    sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
    sf::RectangleShape moveButton(sf::Vector2f(200,20));
    sf::CircleShape piMenu(30.0f);
    sf::CircleShape piMenuAttackButton(10.0f);
    sf::CircleShape enemyHighlight(30.0f);
    MoveButton testButton(400,400,sf::Color::Cyan,sf::Color::Yellow,2.0f,30.0f);
    MoveMenu enemyPiMenu(player.getPosition().x, player.getPosition().y, 80.0f);


    //Color objects
    player.setFillColor(sf::Color::Cyan);
    moveButton.setFillColor(sf::Color::Green);
    piMenu.setFillColor(sf::Color::Transparent);
    piMenu.setOutlineColor(sf::Color::Red);
    piMenuAttackButton.setFillColor(sf::Color::Green);
    piMenu.setOutlineThickness(2.0f);
    enemyHighlight.setFillColor(sf::Color::Transparent);
    enemyHighlight.setOutlineColor(sf::Color::Yellow);
    enemyHighlight.setOutlineThickness(2.0f);

    //Position Objects
    player.setOrigin(50.0f, 50.0f);
    player.setPosition(200.0f, 200.0f);
    piMenu.setPosition(-100.0f, -100.0f);
    piMenu.setOrigin(50.0f, 50.0f);
    piMenuAttackButton.setPosition(piMenu.getPosition().x,piMenu.getPosition().y);
    enemyHighlight.setPosition(-100.0f, -100.0f);

    moveButton.setPosition(312.0f,492.0f);

//    sf::Texture playerTexture;

    FillBar *hpbar = new FillBar(100, 100, 400, 100, sf::Color::Red, sf::Color::Magenta, 0);
    hpbar->amount = 0.75f;

    //bools
    bool piMenuOpen = false;


    while(window.isOpen())
    {
    	
        sf::Event evnt;
        while(window.pollEvent(evnt)){
            ////TEST
            if(isHoveringEnemy(window, sf::Mouse::getPosition(window), player.getPosition(), 100)) {
//                enemyHighlight.setPosition(player.getPosition().x - enemyHighlight.getRadius(), player.getPosition().y - enemyHighlight.getRadius());
                drawPiMenu(enemyHighlight, player.getPosition());
                enemyPiMenu.setMenuPosition(sf::Vector2f(player.getPosition().x+player.getSize().x/2,player.getPosition().y+player.getSize().y/2));
            }
            else {
                enemyHighlight.setPosition(-100.0f, -100.0f);
                enemyPiMenu.resetMenuPosition();
            }

            ////TEST END
            switch(evnt.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    //std::cout << "New window width: " << evnt.size.width << " New window height: "<< evnt.size.height << std::endl;
                    printf("New window width: %i New window height: %i\n", evnt.size.width, evnt.size.height);
                    break;
                case sf::Event::TextEntered:
                    if(evnt.text.unicode < 128){
                        printf("%c", evnt.text.unicode);
                    }
                case sf::Event::MouseButtonPressed:

                    //Mouse input
                    //Player move across screen by mouse button
                    if(sf::Mouse::getPosition(window).x > 312 && sf::Mouse::getPosition(window).y > 492){
                        printf("\nMouse position on action click -> x: %i, y: %i\n",
                               sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
                        for(int i = 0; i < 150; ++i){
                            window.clear();
                            //player.move(2.0f,0.0f);
                            if(i < 75)
                                player.move(2.0f,-50.0f/75);
                            else
                                player.move(2.0f,50.0f/75);
                            window.draw(player);
                            window.display();
                        }
                        for(int i = 0; i < 50; ++i){
                            window.clear();
                            player.move(-6.0f,0.0f);
                            window.draw(player);
                            window.display();
                        }
                    }

            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x >= 0){
            player.move(-0.1f, 0.0f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y >= 0){
            player.move(0.0f, -0.1f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y <= window.getSize().y){
            player.move(0.0f, 0.1f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x <= window.getSize().x){
            player.move(0.1f, 0.0f);
        }
        
        hpbar->update();

        window.clear();
        
        window.draw(player);
        window.draw(moveButton);
        window.draw(piMenu);
        window.draw(piMenuAttackButton);
        window.draw(enemyHighlight);
        window.draw(testButton.getAppearance());
        
        window.draw(hpbar->background);
        window.draw(hpbar->foreground);
        
        for(int i = 0; i < enemyPiMenu.piMenu.size(); ++i)
        {
            window.draw(enemyPiMenu.piMenu[i].getAppearance());
        }
        
        window.display();
    }
    //delete hpbar;
    return 0;
}


//calculate distance for circle and hovering calculations
float distanceFormula(float x1, float x2, float y1, float y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool isHoveringEnemy(sf::RenderWindow & win, sf::Vector2i mousePos, sf::Vector2f enemyPos, float radius){
    if(distanceFormula(mousePos.x, enemyPos.x, mousePos.y, enemyPos.y) < radius)
        return true;
    else
        return false;
}

void drawPiMenu(sf::CircleShape & enemyCircle, sf::Vector2f enemyPos){
    enemyCircle.setPosition(enemyPos.x - enemyCircle.getRadius(), enemyPos.y - enemyCircle.getRadius());

}