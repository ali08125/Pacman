#pragma once

#include <SFML/Graphics.hpp>
#include <info.hpp>

class Ghost
{
private:

    std::array<sf::Clock, 4> clock;
    std::array<sf::Sprite, 4> ghost;
    std::array<std::array<std::array<sf::Texture, 2>, 4>, 4> ghostTexture;
    std::array<std::array<sf::Texture, 2>, 2> scaredGhostTexture;
    sf::Clock scaredTime;
    std::array<sf::Clock, 4> scaredTimeWink;
    std::array<int, 4> wink;

    std::array<int, 4> ghostDir;
    std::array<int, 4> frame;

    bool scared;
    
    //Initialilization
    void initGhosts();
    //Chase Pacman
    int chaseMode(sf::Vector2f pacmanPos, std::array<bool, 4> wall);
    //Move randomly
    int scatterMode(std::array<bool, 4> wall, int dir);
    //Animate the Ghost
    void animation(int dir, int i, bool scare);
    
public:
    Ghost();
    void update(std::array<std::array<sf::RectangleShape, Width>, Height> map
    ,sf::Vector2f pacmanPos, std::array<bool, 4> accident, bool start, bool eatPowerFood);
    void draw(sf::RenderWindow &window);

    std::array<sf::Sprite, 4> getGhost() { return ghost; };
};