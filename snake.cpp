#include "SFML/Graphics.hpp"
#include "iostream"
#include "snake.hpp"
#include "second.hpp"

using std::vector;

void Snake::handleControl() {
    int tdir = -1;
    //this->vel = sf::Vector2f(0,0);
    switch(this->num) {
        case 1:
            if      (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) tdir = 3;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) tdir = 1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) tdir = 2;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) tdir = 0;
            break;

        case 2:
            if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    tdir = 3;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  tdir = 1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  tdir = 2;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) tdir = 0;

            break;
    }

    switch(tdir) {
        case 0:
            if(this->vel.x == 0) this->vel = sf::Vector2f(1,0);
            break;
        case 1:
            if(this->vel.y == 0) this->vel = sf::Vector2f(0,1);
            break;
        case 2:
            if(this->vel.x == 0) this->vel = sf::Vector2f(-1,0);
            break;
        case 3:
            if(this->vel.y == 0) this->vel = sf::Vector2f(0,-1);
            break;
    }
}

void Snake::move() {
    this->parts.push_back(this->head);
    if(this->parts.size() > this->length) {
        this->parts.erase(this->parts.begin());
    }
    this->head.x += this->vel.x;
    this->head.y += this->vel.y;
    
    if(this->head.x < 0) this->head.x = TC-1;
    if(this->head.y < 0) this->head.y = TC-1;
    if(this->head.x > TC-1) this->head.x = 0;
    if(this->head.y > TC-1) this->head.y = 0;
}

bool Snake::eatApple(sf::Vector2f &ap) {
    if(this->head == ap) {
        this->length++;
        return true;
    }

    return false;
}

bool Snake::checkAlive(vector<sf::Vector2f> &oParts) {
    if(this->length > defLen) {
        for(sf::Vector2f spp : this->parts) {
            if(spp == this->head) {
                return true;
            }
        }
    }
    
    for(sf::Vector2f spp : oParts) {
        if(spp == this->head) {
            return true;
        }
    }
    
    return false;
}

void Snake::reset() {
    this->head = this->defPos;
    this->parts.clear();
    this->length = k::defLen;
    this->vel = sf::Vector2f(0,0);
}

void Snake::draw(sf::RenderWindow &i_window) {
    this->rot += (this->vel.x - this->vel.y)*12;
    //k::drawRect(k::getRect(this->head), this->color, i_window);

    int headrot = 0;
    if(this->vel.x == 0 && this->vel.y == 1) headrot = 180;
    if(this->vel.x == 1 && this->vel.y == 0) headrot = 90;
    if(this->vel.x == -1&& this->vel.y == 0) headrot = 270;

    sf::CircleShape rect(CTS, 3);
    rect.setPosition(sf::Vector2f(head.x*TS, head.y*TS));
    //k::drawRect(k::getRect(spp), this->color, i_window);
    //rect.setFillColor(sf::Color::White);
    rect.move(CTS,CTS);
    rect.setOrigin(CTS, CTS);
    rect.setRotation(headrot);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(TS/11);
    i_window.draw(rect);

    for(sf::Vector2f spp : this->parts) {
        sf::CircleShape rect(CTS, 5);
        rect.setPosition(sf::Vector2f(spp.x*TS, spp.y*TS));
        //k::drawRect(k::getRect(spp), this->color, i_window);

        rect.setFillColor(this->color);
        rect.move(CTS,CTS);
        rect.setOrigin(CTS, CTS);
        rect.setRotation(this->rot);
        //rect.setOutlineColor(sf::Color::Black);
        //rect.setOutlineThickness(3);
        i_window.draw(rect);

    }
}

Snake::Snake(sf::Vector2f headPos, sf::Color color, int num) {
    this->head = headPos;
    this->defPos = headPos;
    this->length = defLen;
    this->color = color;
    this->parts = parts;
    this->num = num;
    this->rot = 0;
}