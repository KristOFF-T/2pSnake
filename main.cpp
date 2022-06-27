#include "iostream"
#include "SFML/Graphics.hpp"
#include "second.hpp"
#include "snake.hpp"
#include "cmath"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(W, W), "2P Snake", sf::Style::Close);
    window.setFramerateLimit(fps);

    Snake p1(sf::Vector2f(2,2), sf::Color(255,0,0), 1);
    Snake p2(sf::Vector2f(TC-3, TC-3), sf::Color(0,0,255), 2);
    sf::Vector2f applePos(newPos(p1.parts, p2.parts));
    sf::CircleShape appleShape(CTS, 3);
    appleShape.setFillColor(sf::Color::Green);
    appleShape.setOrigin(CTS,CTS);

    sf::Font font;
    font.loadFromFile("FFFFORWA.TTF");

    //vector<Snake> snakes = {Snake(sf::Vector2f(2,2), sf::Color::Red, 1),
    //                        Snake(sf::Vector2f(TC-3,TC-3), sf::Color::Blue, 2)};

    unsigned short restartCd = 36;

    while(run) {
        rot+=20;
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == event.Closed) run = false;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) run = false;

            //for(Snake s : snakes) s.handleControl();
        }
        if(!restartCd) {
            p1.handleControl();
            p2.handleControl();
        }
        
        //for(Snake s : snakes) s.move();
        p1.move();
        p2.move();

        if(p1.checkAlive(p2.parts) || p2.checkAlive(p1.parts)) {
            //cout << "dead\n";
            p1.reset();
            p2.reset();
            applePos = newPos(p1.parts, p2.parts);
            restartCd = fps*3;
        }

        if(p1.eatApple(applePos) || p2.eatApple(applePos)) {
            applePos = newPos(p1.parts, p2.parts);
        }

        appleShape.rotate(3);
        appleShape.setPosition(sf::Vector2f(applePos.x*TS+CTS,applePos.y*TS+CTS));

        //draw
        window.clear(bgc);
        //for(Snake s : snakes) s.draw(window);
        p1.draw(window);
        p2.draw(window);

        if(restartCd) {
            restartCd--;
            drawText(window, to_string(restartCd/fps+1), sf::Vector2f(CW-30, CW-30), font, sf::Color::White, 60);
        }

        drawText(window, to_string(p1.length-defLen), sf::Vector2f(CTS,CTS), font, p1.color, TS);
        drawText(window, to_string(p2.length-defLen), sf::Vector2f(W-TS,CTS), font, p2.color, TS);

        appleShape.rotate(3);
        window.draw(appleShape);

        window.display();
    }

    return 0;
}