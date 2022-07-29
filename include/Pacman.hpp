#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <info.hpp>

class Pacman
{
private:
    sf::CircleShape player; //Pacman
    int dir; //Direction
    int score = 0; //Score
    int foodNum = 0; //Foods eaten by Pacman in a level
    int lastLevel = 1; //Understand when level up
    bool ghsotCollision; //Pacman encounter with the ghost

    void reset();
    void eat(std::vector<sf::CircleShape> &food, std::vector<sf::CircleShape> &powerFood);
    bool accident(sf::RectangleShape ghost);

public:
    Pacman();
    void draw(sf::RenderWindow & window);
    
    void update(std::array< std::array<sf::RectangleShape, Width>, Height> map
    , std::vector<sf::CircleShape> &food, std::vector<sf::CircleShape> &powerFood
    , sf::RectangleShape ghost, bool end, int level);

    int getScore() { return score; };
    sf::Vector2f getPos() { return player.getPosition(); };
    bool getGhostCollision() { return ghsotCollision; };
    bool createFruit();
    
};