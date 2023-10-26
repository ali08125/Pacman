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
    std::vector<sf::CircleShape> foods;//Save foods
    std::vector<sf::CircleShape> powerFood;//Save power foods
    std::vector<sf::Sprite> fruit;//Save fruits

    sf::Sprite Fruit;
    sf::Texture apple;
    sf::Texture strawberry;
    sf::Texture cherry;
    sf::Texture peach;
    sf::Texture grape;
    sf::Texture banana;

    int level;
    bool initFruit;//Change the size of the fruit only once

    //Intial the game map
    void initMap();

public:
    Map();
    void update(sf::Time time);
    void draw(sf::RenderWindow & window);
    
    int getLevel() { return level; };
    std::array< std::array<sf::RectangleShape, Width>, Height> getMap() { return map; }; 
    std::vector<sf::CircleShape> getFood() { return foods; };
    std::vector<sf::CircleShape> getPowerFood() { return powerFood; };
    std::vector<sf::Sprite> getFruit() { return fruit; };
    //Spawn a fruit on the map
    void createFruit(sf::Sprite pacman);
    

    //Common food information update
    void setFood(std::vector<sf::CircleShape> foods);
    //Power food information update
    void setPowerFood(std::vector<sf::CircleShape> powerFood);
    //Fruit information update
    void setFruit(std::vector<sf::Sprite> fruit); 

    //Checks whether all the food has been eaten 
    bool checkEndLevel();
    //Reset the map
    void resetMap();
};