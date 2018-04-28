//
// Created by justi_000 on 4/28/2018.
//

#include "MoveButton.h"

MoveButton::MoveButton() {
    appearance = sf::CircleShape(0);
}

MoveButton::MoveButton(float x, float y, sf::Color fillColor, sf::Color outlineColor, float outlineThickness, float radius) {
    appearance = sf::CircleShape(radius);
    appearance.setPosition(x-radius, y-radius);
    appearance.setFillColor(fillColor);
    appearance.setOutlineColor(outlineColor);
    appearance.setOutlineThickness(outlineThickness);
}

sf::CircleShape MoveButton::getAppearance(){
    return appearance;
}

void MoveButton::setCenter(float x, float y){
    centerX = x;
    centerY = y;
}

void MoveButton::setPosition(float x, float y){
    posX = x;
    posY = y;
    appearance.setPosition(x,y);
}