#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <Map.hpp>

class Pacman
{
private:
    sf::CircleShape player;
    int dir;
    int score;

    void reset();
    bool collision(float i_x, float i_y, std::array< std::array<sf::RectangleShape, Width>, Height> map);
    void eat(std::vector<sf::CircleShape> &food);
    bool accident(sf::RectangleShape ghost);

public:
    Pacman();
    void draw(sf::RenderWindow & window);
    void update(std::array< std::array<sf::RectangleShape, Width>, Height> map, std::vector<sf::CircleShape> &food);

    int getScore() { return score; };
};