#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <Map.hpp>

class Pacman
{
private:
    sf::CircleShape player;
    sf::Vector2f Pos;
    int dir;

    void initPacman();
    bool collision(float i_x, float i_y, std::array< std::array<sf::RectangleShape, Width>, Height> map);

public:
    Pacman();
    void draw(sf::RenderWindow & window);
    void update(std::array< std::array<sf::RectangleShape, Width>, Height> map);
};