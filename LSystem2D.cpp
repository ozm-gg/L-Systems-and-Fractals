#include "LSystem2D.h"

void move(sf::RectangleShape &line, std::pair<double, double> &cursor, double ang, double d_ang, double len) {
    line.rotate(ang);
    line.setPosition(cursor.first, cursor.second);
    double coss =cos((ang + d_ang) * M_PI / 180);
    double sinn = sin((ang + d_ang) * M_PI / 180);
    cursor = std::pair<double, double>(cursor.first + (len*coss),//(fabs(coss) < 0.5? 0 : 1)*(coss < 0? -1: 1),
                                 cursor.second - (len*sinn));//(fabs(sinn) < 0.5? 0 : 1)*(sinn < 0? -1: 1));

    //std::cout<<cursor.first<<"  "<<cursor.second<<std::endl;
}

LSystem2D::LSystem2D(const char *axiom, double &width, double &length, double &angle, sf::RenderWindow *window) {
    this->cursor = std::pair<double, double>(0, 0);
    this->state = axiom;
    this->axiom = axiom;
    this->width = width;
    this->length = length;
    this->angle = angle;
    this->window = window;
    this->dir = 0;
}

void LSystem2D::addRule(std::string &&key, std::string &&value) {
    rules[key] = value;
}

void LSystem2D::draw(int startPosX, int startPosY) {
    cursor = std::pair<double, double>(startPosX, startPosY);
    dir = 0;
    //std::cout<<"draw"<<std::endl;
    for (auto movement: state) {
        sf::RectangleShape line(sf::Vector2f(length,width));
        line.setOrigin(sf::Vector2f(0, width/2));
        line.setFillColor(sf::Color::White);
        //sf::RectangleShape ch(sf::Vector2f(2,2));
        //ch.setFillColor(sf::Color::Red);
        switch (movement) {
            case 'F':
                line.rotate(-dir);
                move(line, cursor, 0, dir, length);
                window->draw(line);
                //ch.setPosition(cursor.first, cursor.second);
                //window->draw(ch);
                //window->display();
                break;
            case '+':
                dir += angle;
                break;
            case '-':
                dir -= angle;
                break;
            default:
                break;
        }
    }
}

void LSystem2D::genPath(int n_iter) {
    for (int i = 0; i < n_iter; ++i) {
        for (auto &[key, value]: rules) {
            std::string value_ = value;
            for (auto &c: value_)
                c = (char) tolower(c);
            state = std::regex_replace(state, std::regex(key), value_);
        }
        for (auto &c: state)
            c = (char) toupper(c);
    }
    std::cout << state << std::endl;
}
