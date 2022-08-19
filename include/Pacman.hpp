#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <info.hpp>

class Pacman
{
private:
    sf::Clock clock;
    sf::Clock powerFoodTime;
    sf::Sprite player;//Pacman
    sf::Texture pacman1;//The first mode of Pacman
    sf::Texture pacman2;//The second mode of Pacman
    sf::Texture pacman3;//The third mode of Pacman
  
    int dir;//Direction
    int nextDir;//Next direction
    int previousDir;//Previous direction
    int score;//Score
    int foodNum;//Foods eaten by Pacman in a level
    int lastLevel;//Understand when level up
    int frame;//Control pacman animation
    std::array<bool, 4> ghsotCollision;//Pacman encounter with the ghost
    bool start;//Is the game started?!
    bool spawnFruit1;//Spawn the first fruit in a level
    bool spawnFruit2;////Spawn the second fruit in a level
    bool eatPowerFood;//Eating power food
    int ghostEncounter;//Wich ghost has met Pacman?
    std::array<bool, 4> scaredGhost;//Is the Ghost scared?!
    float pacmanSpeed = Speed + 0.5;//The speed at wich Pacman moves
    bool levelUp;
    int health;//Player health
    bool death;//Is Pacman out of health?!
    
    //Initialize variables
    void initVariables();
    //Return Pacman to the first position
    void reset();
    //Move the Pacman
    void move(std::array<std::array<sf::RectangleShape, Width>, Height> map);
    //When Pacman encouter foods, eat them
    void eat(std::vector<sf::CircleShape> &food, std::vector<sf::CircleShape> &powerFood
    ,std::vector<sf::Sprite> &fruit);
    //Has Pacman encountered a ghost?!
    bool accident(sf::Sprite ghost);
    //Reset pacman rotation
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
    , std::array<sf::Sprite, 4> ghost, bool end, int level, std::vector<sf::Sprite> &fruit);
    
    //Get Pacman position
    sf::Vector2f getPos() { return player.getPosition(); };
    std::array<bool, 4> getGhostCollision() { return ghsotCollision; };
    sf::Sprite getPacman() { return player; };
    int getScore() { return score; };
    bool getStart() { return start; };
    bool getPowerFoodInfo();
    int getGhostEncounter();
    bool getLevelUp();
    int getHealth() { return health; };
    bool getDeath() { return death; };

    //Reset pacman after his death
    void resetPacman();
    //Check when Pacman has eaten 70 or 170 foods
    bool createFruit(); 
};