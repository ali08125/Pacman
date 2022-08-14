#pragma once

#include <SFML/Graphics.hpp>
#include <info.hpp>

class Ghost
{
private:

    sf::Clock clock;
    sf::Sprite ghost;
    std::array<std::array<sf::Texture, 2>, 4> ghostTexture;
    int dir;
    int frame;
    
    //Initialilization
    void initGhosts();
    //Chase Pacman
    int chaseMode(sf::Vector2f pacmanPos, std::array<bool, 4> wall);
    //Move randomly
    int scatterMode(std::array<bool, 4> wall);
    //Animate the Ghost
    void animation();
public:
    Ghost();
    void update(std::array<std::array<sf::RectangleShape, Width>, Height> map
    ,sf::Vector2f pacmanPos, bool accident, bool start);
    void draw(sf::RenderWindow &window);

    sf::Sprite getGhost() { return ghost; };
};