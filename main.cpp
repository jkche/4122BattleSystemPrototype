#include <SFML/Graphics.hpp>
#include <cmath>
#include "character.h"
#include "MoveMenu.h"
//#include <iostream>
#include "Player.h"

//function prototypes
float distanceFormula(float, float, float, float);
bool isHoveringEnemy(sf::RenderWindow &, sf::Vector2i, sf::Vector2f, float);
bool isClickPlayer(sf::RenderWindow &, sf::Vector2i, sf::Vector2f, float);
void drawPiMenu(sf::CircleShape &, sf::Vector2f);

int main()
{
//    Move move("hello", 1, 1);
    sf::RenderWindow window(sf::VideoMode(1920,1080), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);

    //Disable key repeat for mouse clicks
    window.setKeyRepeatEnabled(false);



//    Player texture options
    sf::Texture playerTexture;
    playerTexture.loadFromFile("player.png");
    Player player(&playerTexture, sf::Vector2u(3,4), 0.3f, 100.0f);

    //sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
    sf::RectangleShape moveButton(sf::Vector2f(200,20));
    sf::CircleShape piMenu(30.0f);
    sf::CircleShape piMenuAttackButton(10.0f);
    sf::CircleShape enemyHighlight(30.0f);
    MoveButton testButton(400,400,sf::Color::Cyan,sf::Color::Yellow,2.0f,30.0f);
    MoveMenu enemyPiMenu(player.getPosition().x, player.getPosition().y, 80.0f);
    sf::RectangleShape enemyBox(sf::Vector2f(100.0f, 100.0f));
    sf::CircleShape enemyHighlight2(30.0f);


    //Color objects
    //player.setFillColor(sf::Color::White);
    moveButton.setFillColor(sf::Color::Green);
    piMenu.setFillColor(sf::Color::Transparent);
    piMenu.setOutlineColor(sf::Color::Red);
    piMenuAttackButton.setFillColor(sf::Color::Green);
    piMenu.setOutlineThickness(2.0f);
    enemyHighlight.setFillColor(sf::Color::Transparent);
    enemyHighlight.setOutlineColor(sf::Color::Yellow);
    enemyHighlight.setOutlineThickness(2.0f);
    enemyBox.setFillColor(sf::Color::Transparent);
    enemyBox.setOutlineColor(sf::Color::Red);
    enemyBox.setOutlineThickness(2.0f);
    enemyHighlight2.setFillColor(sf::Color::Transparent);
    enemyHighlight2.setOutlineColor(sf::Color::Yellow);
    enemyHighlight2.setOutlineThickness(2.0f);

    //Position Objects
    //player.setOrigin(50.0f, 50.0f);
//    player.setPosition(200.0f, 200.0f);
    piMenu.setPosition(-100.0f, -100.0f);
    piMenu.setOrigin(50.0f, 50.0f);
    piMenuAttackButton.setPosition(piMenu.getPosition().x,piMenu.getPosition().y);
    enemyHighlight.setPosition(-100.0f, -100.0f);
    enemyHighlight2.setPosition(-100.0f, -100.0f);

    moveButton.setPosition(312.0f,492.0f);
    enemyBox.setPosition(1500.0f, 500.0f);
    enemyBox.setOrigin(enemyBox.getSize().x/2,enemyBox.getSize().y/2);



//    sf::Vector2u textureSize = playerTexture.getSize();
//    textureSize.x /= 3;
//    textureSize.y /= 4;
//
//    player.setTextureRect(sf::IntRect(textureSize.x*2, textureSize.y*3, textureSize.x, textureSize.y));

    float deltaTime = 0.0f;
    sf::Clock clock;
    float attackTimer = 6;//*deltaTime;
    float frameCounter = 0.0f;
//    float frameSpeed = 20.0f;

    //bools
    bool piMenuOpen = false;
    bool playerSelect = false;
    bool enemySelect = false;
    bool playerAttack = false;


    while(window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        //deltaTime = 0.006f;
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
            if(isHoveringEnemy(window, sf::Mouse::getPosition(window), enemyBox.getPosition(), 50)) {
//                enemyHighlight.setPosition(player.getPosition().x - enemyHighlight.getRadius(), player.getPosition().y - enemyHighlight.getRadius());
                drawPiMenu(enemyHighlight2, enemyBox.getPosition());
            }
            else {
                enemyHighlight2.setPosition(-100.0f, -100.0f);
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
                    if(isHoveringEnemy(window, sf::Mouse::getPosition(window), player.getPosition(), 50)) {
                        playerSelect = true;
                        player.setOrigPos(player.getPosition());
                    }
                    if(isHoveringEnemy(window, sf::Mouse::getPosition(window), enemyBox.getPosition(), 50) && playerSelect == true) {
                        enemySelect = true;
                        player.initAttack(); //fill attack animations
                    }

                    //Mouse input
                    //Player move across screen by mouse button
//                    if(sf::Mouse::getPosition(window).x > 312 && sf::Mouse::getPosition(window).y > 492){
//                        printf("\nMouse position on action click -> x: %i, y: %i\n",
//                               sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
//                        for(int i = 0; i < 150; ++i){
//                            window.clear();
//                            //player.move(2.0f,0.0f);
//                            if(i < 75)
//                                player.move(2.0f,-50.0f/75);
//                            else
//                                player.move(2.0f,50.0f/75);
//                            window.draw(player);
//                            window.display();
//                        }
//                        for(int i = 0; i < 50; ++i){
//                            window.clear();
//                            player.move(-6.0f,0.0f);
//                            window.draw(player);
//                            window.display();
//                        }
//                    }

            }
        }

//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x >= 0){
//            player.move(-1.0f, 0.0f);
//        }
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y >= 0){
//            player.move(0.0f, -1.0f);
//        }
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y <= window.getSize().y){
//            player.move(0.0f, 1.0f);
//        }
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x <= window.getSize().x){
//            player.move(1.0f, 0.0f);
//        }

//        animation.update(0, deltaTime, false, false, false);
//        player.setTextureRect(animation.uvRect);
        if(playerSelect && enemySelect) { //attack initiated
            playerSelect = false;
            enemySelect = false;
            printf("\nAttack initiated\n");
//            clock.restart();    //set clock to 0 to use elapsed time for animation calculations
            playerAttack = true;
        }
        if(frameCounter < attackTimer && playerAttack){
//            printf("\nAttack Clock Counting\n");
            frameCounter += deltaTime;
            if(frameCounter < attackTimer/2)
                player.updateAttack(deltaTime,enemyBox.getPosition(),true, attackTimer, 1);
            else
                player.updateAttack(deltaTime,enemyBox.getPosition(),false, attackTimer, 1);
        }else if(playerAttack){
            frameCounter -= attackTimer;
            playerAttack = false;
        }else {
//            playerAttack = false;
            player.update(deltaTime, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), false);
        }
        window.clear(sf::Color(160,150,150));
        player.draw(window);
        window.draw(moveButton);
        window.draw(piMenu);
        window.draw(piMenuAttackButton);
        window.draw(enemyHighlight);
        window.draw(testButton.getAppearance());
        for(int i = 0; i < enemyPiMenu.piMenu.size(); ++i)
        {
            window.draw(enemyPiMenu.piMenu[i].getAppearance());
        }
        window.draw(enemyBox);
        window.draw(enemyHighlight2);
        window.display();
    }

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

bool isClickPlayer(sf::RenderWindow & win, sf::Vector2i mousePos, sf::Vector2f playerPos, float radius){
    if(distanceFormula(mousePos.x, playerPos.x, mousePos.y, playerPos.y) < radius)
        return true;
    else
        return false;
}

void drawPiMenu(sf::CircleShape & enemyCircle, sf::Vector2f enemyPos){
    enemyCircle.setPosition(enemyPos.x - enemyCircle.getRadius(), enemyPos.y - enemyCircle.getRadius());

}