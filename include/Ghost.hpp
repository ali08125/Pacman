#pragma once

#include <SFML/Graphics.hpp>
#include <info.hpp>

class Ghost
{
private:
    //sf::RectangleShape ghost;
    sf::Sprite ghost;
    std::array<sf::Texture, 8> ghostTexture;
    int dir;
    
    //Initialilization
    void initGhosts();
    //Chase Pacman
    int chaseMode(sf::Vector2f pacmanPos, std::array<bool, 4> wall);
    //Move randomly
    int scatterMode(std::array<bool, 4> wall);
public:
    Ghost();
    void update(std::array<std::array<sf::RectangleShape, Width>, Height> map
    ,sf::Vector2f pacmanPos, bool accident, bool start);
    void draw(sf::RenderWindow &window);

    sf::Sprite getGhost() { return ghost; };
};