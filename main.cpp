#include <SFML/Graphics.hpp>
#include <cmath>
//#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512,512), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);

    //Disable key repeat for mouse clicks
    window.setKeyRepeatEnabled(false);

    sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
    sf::RectangleShape moveButton(sf::Vector2f(200,20));
    sf::CircleShape piMenu(30.0f);
    sf::CircleShape piMenuAttackButton(10.0f);

    //Color objects
    player.setFillColor(sf::Color::Cyan);
    moveButton.setFillColor(sf::Color::Green);
    piMenu.setFillColor(sf::Color::Transparent);
    piMenu.setOutlineColor(sf::Color::Red);
    piMenuAttackButton.setFillColor(sf::Color::Green);
    piMenu.setOutlineThickness(2.0f);

    //Position Objects
    player.setOrigin(50.0f, 50.0f);
    piMenu.setPosition(-100.0f, -100.0f);
    piMenu.setOrigin(50.0f, 50.0f);
    piMenuAttackButton.setPosition(piMenu.getPosition().x,piMenu.getPosition().y);

    moveButton.setPosition(312.0f,492.0f);

    sf::Texture playerTexture;



    //bools
    bool piMenuOpen = false;


    while(window.isOpen())
    {
        sf::Event evnt;
        while(window.pollEvent(evnt)){
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

                    if(sf::Mouse::getPosition(window).x > player.getPosition().x-player.getOrigin().x
                       && sf::Mouse::getPosition(window).y > player.getPosition().y-player.getOrigin().y
                       && sf::Mouse::getPosition(window).x < player.getPosition().x-player.getOrigin().x + player.getSize().x
                       && sf::Mouse::getPosition(window).y < player.getPosition().y-player.getOrigin().y+ player.getSize().y) {
                        printf("\nPi menu opened @ player position x: %f, y: %f\n",
                               player.getPosition().x, player.getPosition().y);
                        piMenuOpen = !piMenuOpen;
                        if(piMenuOpen){
                            piMenu.setPosition(player.getPosition().x+player.getSize().x/2-piMenu.getRadius(),
                                               player.getPosition().y+player.getSize().y/2-piMenu.getRadius());

                        }else
                            piMenu.setPosition(-100.0f,-100.0f);
                        piMenuAttackButton.setPosition(piMenu.getPosition().x-piMenuAttackButton.getRadius(),piMenu.getPosition().y-piMenuAttackButton.getRadius());
                    }
                    //Player attack move
                    if(sqrt(pow(piMenuAttackButton.getPosition().x - sf::Mouse::getPosition(window).x,2)
                    + pow(piMenuAttackButton.getPosition().y - sf::Mouse::getPosition(window).y,2)) < piMenuAttackButton.getRadius()
                        && piMenuOpen) {
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
//
//        //Mouse input
//        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
//            //Player Move by Mouse Button
////            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
////            player.setPosition((float)mousePos.x, (float)mousePos.y);
//
//            //Player move across screen by mouse button
//            if(sf::Mouse::getPosition(window).x > 312 && sf::Mouse::getPosition(window).y > 492){
//                printf("\nMouse position on action click -> x: %i, y: %i\n", sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
//                for(int i = 0; i < 150; ++i){
//                    window.clear();
//                    //player.move(2.0f,0.0f);
//                    if(i < 75)
//                        player.move(2.0f,-50.0f/75);
//                    else
//                        player.move(2.0f,50.0f/75);
//                    window.draw(player);
//                    window.display();
//                }
//                for(int i = 0; i < 50; ++i){
//                    window.clear();
//                    player.move(-6.0f,0.0f);
//                    window.draw(player);
//                    window.display();
//                }
//            }
//        }
//
//        if(sf::Mouse::getPosition(window).x > player.getPosition().x-player.getOrigin().x && sf::Mouse::getPosition(window).y > player.getPosition().y-player.getOrigin().y && sf::Mouse::getPosition(window).x < player.getPosition().x-player.getOrigin().x + player.getSize().x && sf::Mouse::getPosition(window).y < player.getPosition().y-player.getOrigin().y + player.getSize().y && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//            printf("\nPi menu opened @ player position x: %f, y: %f\n", player.getPosition().x, player.getPosition().y);
//            //piMenu.setPosition(player.getPosition()-player.getOrigin());
//            //piMenu.setPosition(player.getPosition().x+player.getSize().x-player.getOrigin().x,player.getPosition().y+player.getSize().y-player.getOrigin().y/2);
//            piMenuOpen = !piMenuOpen;
//            if(piMenuOpen){
//                piMenu.setPosition(player.getPosition().x+player.getSize().x/2-piMenu.getRadius(),player.getPosition().y+player.getSize().y/2-piMenu.getRadius());
//            }else
//                piMenu.setPosition(-100.0f,-100.0f);
//        }



        window.clear();
        window.draw(player);
        window.draw(moveButton);
        window.draw(piMenu);
        window.draw(piMenuAttackButton);
        window.display();
    }

    return 0;
}


