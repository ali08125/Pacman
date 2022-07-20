#include <Map.hpp>

using namespace sf;

Map::Map()
{
    this->initMap();
}

void Map::initMap()
{
    sketch = {
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "              #    ",
        "              #    ",
        "              #    ",
        "              #    ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "        #          ",
        "                   ",
        "                   ",
        "                   ",
        "                   "
    };
}

void Map::draw(RenderWindow & window, float dt)
{
    RectangleShape Wall(Vector2f(CellSize, CellSize));
    Wall.setFillColor(Color::Blue);

    for (size_t i = 0; i < Height; i++)
    {
        for (size_t j = 0; j < Width; j++)
        {
            switch (sketch[i][j])
            {
            case '#':
                Wall.setPosition(Vector2f(j * CellSize, i * CellSize));
                Walls.push_back(Wall);
                break;
            }
        }
    }

    for(auto & a : Walls)
    {
        window.draw(a);
    }
    
    pacman.move(Walls, dt);
    pacman.draw(window);
}