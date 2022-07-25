#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <Map.hpp>

class Pacman
{
private:
    sf::CircleShape player;
    int dir;
    int score = 0;

    void reset();
    void eat(std::vector<sf::CircleShape> &food);
    bool accident(sf::RectangleShape ghost);

public:
    Pacman();
    void draw(sf::RenderWindow & window);
    void update(std::array< std::array<sf::RectangleShape, Width>, Height> map, std::vector<sf::CircleShape> &food, sf::RectangleShape ghost);

    int getScore() { return score; };
};