#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <info.hpp>

class Pacman
{
private:
    sf::CircleShape player;
    sf::Vector2f Pos;
    int dir;


    void initPacman();
    //bool collision(float i_x, float i_y, std::array<std::string, Height> sketch);

public:
    Pacman();
    void draw(sf::RenderWindow & window);
    void update(std::vector<sf::RectangleShape> Walls, float dt, std::array<std::string, Height> sketch);
};