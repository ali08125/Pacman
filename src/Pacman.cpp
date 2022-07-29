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
    Vector2f Pos;

    Pos.x = 10 * CellSize;
    Pos.y = 15 * CellSize;
    player.setRadius(CellSize / 2);
    player.setFillColor(Color::Yellow);
    player.setPosition(Pos);
    dir = -1;
}

void Pacman::draw(RenderWindow & window)
{
    window.draw(player);
}

void Pacman::update(array<array<RectangleShape, Width>, Height> map
, vector<CircleShape> &food, vector<CircleShape> &powerFood
, sf::RectangleShape ghost, bool end, int level, vector<CircleShape> &fruit)
{
    //if level up
    if (level > lastLevel)
    {
        foodNum = 0;
        spawnFruit1 = false;
        spawnFruit2 = false;
        lastLevel = level;
        reset();
    }
    
    if (end)
    {
        reset();
    }
    
    ghsotCollision = false;

    std::array<bool, 4> wall;

    // Collision Right
    wall[0] = collision(player.getPosition().x + (Speed), player.getPosition().y, map);
    // Collision Down
    wall[1] = collision(player.getPosition().x, player.getPosition().y + (Speed), map);
    // Collision Left
    wall[2] = collision(player.getPosition().x - (Speed), player.getPosition().y, map);
    // Collision Up
    wall[3] = collision(player.getPosition().x, player.getPosition().y - (Speed), map);

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
}

void Pacman::eat(vector<CircleShape> &food, vector<CircleShape> &powerFood, vector<CircleShape> &fruit)
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
        auto it2 = fruit.begin();
        if (lastLevel < 64)
        {
            score += 100;
            fruit.erase(it2);
            return;
        }
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
    if (foodNum == 7 && !spawnFruit1)
    {
        spawnFruit1 = true;
        return true;
    } else if (foodNum == 13 && !spawnFruit2)
    {
        spawnFruit2 = true;
        return true;
    }
    return false;
}