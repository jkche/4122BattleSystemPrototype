//
// Created by justi_000 on 4/28/2018.
//

#ifndef SFMLDEMO_MOVEBUTTON_H
#define SFMLDEMO_MOVEBUTTON_H
#include <SFML/Graphics.hpp>
#define PI 3.14159265

class MoveButton {
private:
    sf::CircleShape appearance;
    float centerX;
    float centerY;
    float posX;
    float posY;
public:
    //Constructors
    MoveButton();
    MoveButton(float,float,sf::Color,sf::Color,float,float);    //init x, y, fill color, outline color, outline thickness, radius

    //Get functions
    sf::CircleShape getAppearance();
    void setCenter(float, float);
    void setPosition(float, float);
};


#endif //SFMLDEMO_MOVEBUTTON_H
