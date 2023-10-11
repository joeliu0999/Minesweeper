//
// Created by User on 12/4/2022.
//
#include "Button.h"

Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick){
    position=_position;
    click=_onClick;
}
sf::Vector2f Button::getPosition(){
    return position;
}
sf::Sprite* Button::getSprite(){
    return sprite;
}
void Button::setSprite(sf::Sprite* _sprite){
    sprite=_sprite;
}
void Button::onClick(){
    click();
}

