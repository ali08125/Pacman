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
        " #        #        # ",
        " # ## ### # ### ## # ",
        " #                 # ",
        " # ## # ##### # ## # ",
        " #    #   #   #    # ",
        " #### ### # ### #### ",
        "    # #       # #    ",
        "##### # ##### # #####",
        "        #   #        ",
        "##### # ##### # #####",
        "    # #       # #   ",
        " #### ### # ### #### ",
        " #    #   #   #    # ",
        " # ## # ##### # ## # ",
        " #                 # ",
        " # ## ### # ### ## # ",
        " #        #        # ",
        " ################### ",
        "                     ",
        "                     "
    };

    RectangleShape Wall(Vector2f(CellSize, CellSize));

    for (size_t i = 0; i < Height; i++)
    {
        for (size_t j = 0; j < Width; j++)
        {
            switch (sketch[i][j])
            {
            case '#':
                Wall.setFillColor(Color::Blue);
                Wall.setPosition(Vector2f(j * CellSize, i * CellSize));
                map.push_back(Wall);
                break;
            case ' ':
                Wall.setFillColor(Color::Black);
                Wall.setPosition(Vector2f(j * CellSize, i * CellSize));
                map.push_back(Wall);
                break;
            }
            
        }
    }
}

void Map::draw(RenderWindow & window, float dt)
{
    for(auto & a : map)
    {
       window.draw(a);
    }   
}