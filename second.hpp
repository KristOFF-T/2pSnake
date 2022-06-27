#include "cmath"
#include "SFML/Graphics.hpp"

#ifndef k
    #define k
    namespace k {
        unsigned const int W=800, CW=W/2;
        unsigned const short fps=12, TC=20, TS=W/TC, CTS=TS/2;
        bool run=true;
        const sf::Color bgc(0,0,40);

        unsigned const short defLen = TC/3;

        unsigned int rot = 0;
        unsigned const short HS = CTS+10;
        sf::RectangleShape getRect(sf::Vector2f &pos) {
            sf::RectangleShape rect(sf::Vector2f(TS-2,TS-2));
            rect.setPosition(pos.x*TS+1, pos.y*TS+1);
            return rect;
        }

        void drawRect(sf::RectangleShape rect, sf::Color &color, sf::RenderWindow &i_window) {
            rect.setFillColor(color);
            i_window.draw(rect);
        }

        int randRange(int maxInt) {
            return rand()%maxInt;
        }

        sf::Vector2f newPos(std::vector<sf::Vector2f> &parts1, std::vector<sf::Vector2f> &parts2) {
            bool good = false;
            sf::Vector2f pos(randRange(TC),randRange(TC));
            while(!good) {
                good = true;
                sf::Vector2f pos(randRange(TC), randRange(TC));
                for(sf::Vector2f p : parts1) {
                    if(p.x == pos.x && p.y == pos.y) good = false;
                }
                for(sf::Vector2f p : parts2) {
                    if(p == pos) good = false;
                }
            }
            return pos;
        }
        void drawText(sf::RenderWindow &window, std::string dstring, sf::Vector2f pos, sf::Font &font, sf::Color color, int fs=16) {
            sf::Text oText;
            oText.setFont(font);
            oText.setCharacterSize(fs);
            oText.setPosition(pos);
            oText.setString(dstring);
            oText.setFillColor(color);
            window.draw(oText);
        }
    }

#endif