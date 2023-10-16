#pragma once
#include <string>
#include <map>
#include <utility>
#include <regex>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
enum direction {FORWARD = 1, BACKWARD = 2, LEFT = 3, RIGHT = 4};

class LSystem2D {
public:
    LSystem2D(const char *axiom, double &width, double &length, double &angle, sf::RenderWindow* window);
    void addRule(std::string&& key, std::string&& value);
    void genPath(int n_iter);
    void draw(int startPosX, int startPosY);

private:
    double dir;
    std::string axiom;
    std::string state;
    double width;
    double length;
    double angle;
    std::pair<double, double> cursor;
    std::map<std::string, std::string> rules;
    sf::RenderWindow* window;
};