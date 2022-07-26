#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <info.hpp>

class Pacman
{
private:
    sf::CircleShape player;
    int dir;
    int score = 0;
    bool ghsotCollision;

    void reset();
    void eat(std::vector<sf::CircleShape> &food);
    bool accident(sf::RectangleShape ghost);

public:
    Pacman();
    void draw(sf::RenderWindow & window);
    void update(std::array< std::array<sf::RectangleShape, Width>, Height> map, std::vector<sf::CircleShape> &food, sf::RectangleShape ghost);

    int getScore() { return score; };
    sf::Vector2f getPos() { return player.getPosition(); };
    bool getGhostCollision() { return ghsotCollision; };
    
};