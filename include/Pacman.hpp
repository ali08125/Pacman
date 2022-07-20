#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Pacman
{
private:
    sf::CircleShape player;
    //sf::RectangleShape player;
    sf::Vector2f Pos;
    int dir;
    int nextDir;


    void initPacman();

public:
    Pacman();
    void draw(sf::RenderWindow & window);
    void move(std::vector<sf::RectangleShape> Walls, float dt);
};