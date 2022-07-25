#include <Map.hpp>

using namespace sf;

Map::Map()
{
    this->initMap();
}

void Map::initMap()
{
    sketch = {
        " ################### ",
        " #........#........# ",
        " #.##.###.#.###.##.# ",
        " #.................# ",
        " #.##.# #####.#.## # ",
        " #....#...#...#....# ",
        " #### ### # ### #### ",
        "    # #       # #    ",
        "##### # ##### # #####",
        "        #   #        ",
        "##### # ##### # #####",
        "    # #       # #   ",
        " #### ### # ### #### ",
        " #....#...#...#....# ",
        " #.##.#.#####.#.##.# ",
        " #.................# ",
        " #.##.###.#.###.##.# ",
        " #........#........# ",
        " ################### ",
        "                     ",
        "                     "
    };

    RectangleShape Wall(Vector2f(CellSize, CellSize));
    CircleShape point(CellSize / 5);
    
    point.setFillColor(Color::Cyan);

    for (size_t i = 0; i < Height; i++)
    {
        for (size_t j = 0; j < Width; j++)
        {
            switch (sketch[i][j])
            {
            case '#':
                Wall.setFillColor(Color::Blue);
                Wall.setPosition(Vector2f(j * CellSize, i * CellSize));
                map[i][j] = Wall;
                break;
            case ' ':
                Wall.setFillColor(Color::Black);
                Wall.setPosition(Vector2f(j * CellSize, i * CellSize));
                map[i][j] = Wall;
                break;
            case '.':
                point.setPosition(Vector2f((j * CellSize) + 10, (i * CellSize) + 10));
                points.push_back(point);
                break;
            }
            
        }
    }
}

void Map::draw(RenderWindow & window)
{
    for (size_t i = 0; i < Height; i++)
    {
        for (size_t j = 0; j < Width; j++)
        {
            window.draw(map[i][j]);
        }
    }

    for(auto & a : points)
    {
        window.draw(a);
    }
}