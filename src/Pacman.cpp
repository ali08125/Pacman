#include <Pacman.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

Pacman::Pacman()
{
    this->initPacman();
}

void Pacman::initPacman()
{
    Pos.x = 10 * CellSize;
    Pos.y = 11 * CellSize;
    player.setRadius(CellSize / 2);
    player.setFillColor(Color::Yellow);
    player.setPosition(Pos);
    dir = -1;
}

void Pacman::draw(RenderWindow & window)
{
    window.draw(player);
}

void Pacman::update(array<array<RectangleShape, Width>, Height> map)
{
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
    if (position.x == 0 && position.y == 0)
    {
    
    } else
        player.move(position.x, position.y);
}

bool Pacman::collision(float px, float py, array<array<RectangleShape, Width>, Height> map)
{
    
    float cell_x = px / static_cast<float>(CellSize);
	float cell_y = py / static_cast<float>(CellSize);

   // std::cout << cell_x << "\n";
    for (int a = 0; a < 4; a++)
	{
	    float x = 0;
		float y = 0;

		switch (a)
		{
			case 0: //Top left cell
			{
				x = static_cast<float>(floor(cell_x));
				y = static_cast<float>(floor(cell_y));

				break;
			}
			case 1: //Top right cell
			{
				x = static_cast<float>(ceil(cell_x));
				y = static_cast<float>(floor(cell_y));

				break;
			}
			case 2: //Bottom left cell
			{
				x = static_cast<float>(floor(cell_x));
				y = static_cast<float>(ceil(cell_y));

				break;
			}
			case 3: //Bottom right cell
			{
				x = static_cast<float>(ceil(cell_x));
				y = static_cast<float>(ceil(cell_y));
			}
		}

		if (0 <= x && 0 <= y && Height > y && Width > x)
		{
            if (map[y][x].getFillColor() == Color::Blue)
            {
                return 1;
            }
        }
    }
    return 0;
}
