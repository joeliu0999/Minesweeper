//
// Created by User on 12/4/2022.
//

#ifndef PROJOECT4_BUTTON_H
#define PROJOECT4_BUTTON_H
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

class Button{
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
private:
    std::function<void(void)> click;
    sf::Vector2f position;
    sf::Sprite* sprite;
};

#endif //PROJOECT4_BUTTON_H
