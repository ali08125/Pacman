#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <info.hpp>
#include <vector>

class Map
{
private:
    std::array<std::string, Height> sketch;
    std::array<std::array<sf::RectangleShape, Width>, Height> map;
    std::vector<sf::CircleShape> foods;
    std::vector<sf::CircleShape> powerFood;

    sf::Sprite Fruit;
    std::vector<sf::Sprite> fruit;
    sf::Texture apple;
    sf::Texture strawberry;
    sf::Texture cherry;
    sf::Texture peach;
    sf::Texture grape;
    sf::Texture banana;
    
    

    int level = 1;

    void initMap();

public:
    Map();
    void update(sf::Time time);
    void draw(sf::RenderWindow & window);
    
    std::array< std::array<sf::RectangleShape, Width>, Height> getMap() { return map; };

    //Common food
    std::vector<sf::CircleShape> getFood() { return foods; };
    void setFood(std::vector<sf::CircleShape> foods);
    //Power food
    std::vector<sf::CircleShape> getPowerFood() { return powerFood; };
    void setPowerFood(std::vector<sf::CircleShape> powerFood);
    //Fruit
    void createFruit(sf::Sprite pacman);
    std::vector<sf::Sprite> getFruit() { return fruit; };
    void setFruit(std::vector<sf::Sprite> fruit); 

    int getLevel() { return level; };

    bool checkEndLevel();
 
};