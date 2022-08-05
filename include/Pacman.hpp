#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <info.hpp>

class Pacman
{
private:
    sf::Clock clock;//Time
    sf::Sprite player;//Pacman
    sf::Texture pacman1;//The first mode of Pacman
    sf::Texture pacman2;//The second mode of Pacman
    sf::Texture pacman3;//The third mode of Pacman
  
    int dir;//Direction
    int nextDir;
    int lastDir;
    int score = 0;//Score
    int foodNum = 0;//Foods eaten by Pacman in a level
    int lastLevel = 1;//Understand when level up
    int frame = 1;//Control pacman animation
    bool ghsotCollision;//Pacman encounter with the ghost
    bool start = false;//Is the game started?!
    bool spawnFruit1 = false;
    bool spawnFruit2 = false;
    

    void initVariables();
    //Return Pacman to the first position
    void reset();
    //When Pacman encouter foods, eat them
    void eat(std::vector<sf::CircleShape> &food, std::vector<sf::CircleShape> &powerFood
    ,std::vector<sf::Sprite> &fruit);
    //
    bool accident(sf::RectangleShape ghost);
    //Reset pacman rotate
    void Rotate();
    //Animate pacman
    void animation();

public:
    Pacman();
    //Draw Pacman in the window
    void draw(sf::RenderWindow & window);
    
    //Pacman changes in every frame
    void update(std::array< std::array<sf::RectangleShape, Width>, Height> map
    , std::vector<sf::CircleShape> &food, std::vector<sf::CircleShape> &powerFood
    , sf::RectangleShape ghost, bool end, int level, std::vector<sf::Sprite> &fruit);

    //Get score
    int getScore() { return score; };
    //Get Pacman position
    sf::Vector2f getPos() { return player.getPosition(); };
    //Get Ghost collision
    bool getGhostCollision() { return ghsotCollision; };
    //Check when Pacman has eaten 70 or 170 foods
    bool createFruit(); 
    //Get Pacman
    sf::Sprite getPacman() { return player; };
    
};