#pragma once

class Snake {
    public:
        unsigned short num, length, rot, deaths;
        sf::Vector2f head, vel, defPos;
        sf::Color color;
        std::vector<sf::Vector2f> parts = {};

        void handleControl();
        void move();
        bool checkAlive(std::vector<sf::Vector2f> &oParts);
        void reset();
        bool eatApple(sf::Vector2f &applePos);
        void draw(sf::RenderWindow &i_window);

        Snake(sf::Vector2f headPos, sf::Color color, int num);
};