#include <iostream>
#include <SFML/Graphics.hpp>
#include "LSystem2D.h"


int main()
{
    constexpr int WIDTH = 2000, HEIGHT = 1400;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Fract");
    window.setFramerateLimit(144);
    const char *axiom = "FX";
   /* const char *axiom = "X";*/
    /*const char *axiom = "FXF--FF--FF";*/
    double pen_size = 1;
    double len = 4;
    double angle = 90;
    LSystem2D lSystem2D(axiom, pen_size, len, angle, &window);
    lSystem2D.addRule("FX", "FX+FY+");
    lSystem2D.addRule("FY", "-FX-FY");

    /*lSystem2D.addRule("X", "-YF+XFX+FY-");
    lSystem2D.addRule("Y", "+XF-YFY-FX+");*/

    /*lSystem2D.addRule("F", "FF");
    lSystem2D.addRule("X", "--FXF++FXF++FXF--");*/

    lSystem2D.genPath(20);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        lSystem2D.draw(WIDTH/2,HEIGHT/2);

        window.display();
    }

    return 0;
}
