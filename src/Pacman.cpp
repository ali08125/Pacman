#include <Pacman.hpp>
#include <iostream>
#include <Collision.hpp>

using namespace sf;
using namespace std;

Pacman::Pacman()
{
    this->reset();
}

void Pacman::reset()
{
    //player.setScale();
    //player.setFillColor(Color::Yellow);
    if (!pacman.loadFromFile("../Photo/pacman/3.png"))
        std::cerr << "can not open 3.png\n";
    pacman.setSmooth(true);

    player.setTexture(pacman);
    
    player.setScale(Vector2f(0.3, 0.3));
    player.setOrigin(Vector2f(50, 50));
    player.setPosition(Vector2f(10 * CellSize + 15, 15 * CellSize + 15));

    dir = -1;
}

void Pacman::draw(RenderWindow & window)
{
    window.draw(player);
}

void Pacman::update(array<array<RectangleShape, Width>, Height> map
, vector<CircleShape> &food, vector<CircleShape> &powerFood
, sf::RectangleShape ghost, bool end, int level, vector<Sprite> &fruit)
{
    lastDir = dir;
    //if level up
    if (level > lastLevel)
    {
        foodNum = 0;
        spawnFruit1 = false;
        spawnFruit2 = false;
        lastLevel = level;
        reset();
        if (!fruit.empty())
        {
            fruit.erase(fruit.begin());
        }
    }
    
    if (end)
    {
        reset();
    }
    
    ghsotCollision = false;

    std::array<bool, 4> wall;

    // Collision Right
    wall[0] = collision(player.getPosition().x + (Speed) - 15, player.getPosition().y - 15, map);
    // Collision Down
    wall[1] = collision(player.getPosition().x - 15, player.getPosition().y + (Speed) - 15, map);
    // Collision Left
    wall[2] = collision(player.getPosition().x - (Speed) - 15, player.getPosition().y - 15, map);
    // Collision Up
    wall[3] = collision(player.getPosition().x - 15, player.getPosition().y - (Speed) - 15, map);

    Vector2f position;
    position.x = 0;
    position.y = 0;

    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        if (wall[0] == 0)
        {
            dir = 0;
        }
    } else if(Keyboard::isKeyPressed(Keyboard::Down))
    {
        if (wall[1] == 0)
        {
            dir = 1;
        }
    } else if(Keyboard::isKeyPressed(Keyboard::Left))
    {   
        if (wall[2] == 0)
        {
            dir = 2;
        }
    } else if(Keyboard::isKeyPressed(Keyboard::Up))
    {
        if (wall[3] == 0)
        {
            dir = 3;
        }
    }

    if (wall[dir] == 0)
    { 
        switch (dir)
        {
        case 0:
            position.x += Speed;
            player.rotate(0);
            break;
        case 1:
            position.y += Speed;
            break;
        case 2:
            position.x -= Speed;
            break;
        case 3:
            position.y -= Speed;
            break;
        }
    }
    player.move(position.x, position.y);
    
    if (player.getPosition().x >= CellSize * Width)
    {
        position.x = Speed - CellSize;
        player.setPosition(Vector2f(position.x, player.getPosition().y));
        
    } else if (player.getPosition().x <= -CellSize)
    {
        position.x = Width * CellSize - Speed;
        player.setPosition(Vector2f(position.x, player.getPosition().y));
    }

    if (accident(ghost))
    {
        ghsotCollision = true;
        reset();
    }
    
    eat(food, powerFood, fruit);
    Rotate();
}

void Pacman::eat(vector<CircleShape> &food, vector<CircleShape> &powerFood, vector<Sprite> &fruit)
{
    auto it = food.begin();
    for (auto & a : food)
    {
        if (player.getGlobalBounds().intersects(a.getGlobalBounds()))
        {
            foodNum += 1;
            score += 10;
            food.erase(it);
            return;
        }
        it++;
    }

    auto it1 = powerFood.begin();
    for (auto & b : powerFood)
    {
        if (player.getGlobalBounds().intersects(b.getGlobalBounds()))
        {
            foodNum += 1;
            score += 50;
            powerFood.erase(it1);
            return;
        }
        it1++;
    }
    
    if (!fruit.empty() && player.getGlobalBounds().intersects(fruit[0].getGlobalBounds()))
    {
        if (lastLevel <= 64)
        {
            score += 100;
        } else if (lastLevel > 64 && lastLevel <= 128)
        {
            score += 300;
        } else if (lastLevel > 128 && lastLevel <= 192)
        {
            score += 500;
        } else if (lastLevel > 192 && lastLevel <= 224)
        {
            score += 700;
        } else if (lastLevel > 224 && lastLevel <= 240)
        {
            score += 1000;
        } else if (lastLevel > 240 && lastLevel <= 255)
        {
            score += 2000;
        }  
        fruit.erase(fruit.begin());
        return;
    }
}

bool Pacman::accident(RectangleShape ghost)
{
    if (player.getGlobalBounds().intersects(ghost.getGlobalBounds()) 
    || ghost.getGlobalBounds().intersects(player.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

bool Pacman::createFruit()
{
    if (foodNum == 70 && !spawnFruit1)
    {
        spawnFruit1 = true;
        return true;
    } else if (foodNum == 140 && !spawnFruit2)
    {
        spawnFruit2 = true;
        return true;
    }
    return false;
}

void Pacman::Rotate()
{
    switch (lastDir)
    {
    case 0:
        //Right
        break;    
    case 1:
        //Down
        player.rotate(-90);
        break;
    case 2:
        //Left
        player.rotate(-180);
        break;
    case 3: 
        //Up
        player.rotate(-270);
        break;
    }

    switch (dir)
    {
    case 0:
        //Right
        break;    
    case 1:
        //Down
        player.rotate(90);
        break;
    case 2:
        //Left
        player.rotate(180);
        break;
    case 3: 
        //Up
        player.rotate(270);
        break;
    }
}