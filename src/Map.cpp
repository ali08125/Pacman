#include <Map.hpp>

using namespace sf;

Map::Map()
{
    this->initMap();
}

void Map::initMap()
{
    /*
    sketch = {
        " ################### ",
        " #........#........# ",
        " #0##.###.#.###.##0# ",
        " #.................# ",
        " #.##.# #####.#.##.# ",
        " #....#...#...#....# ",
        " ####.### # ###.#### ",
        "    #.#       #.#    ",
        "#####.# ##### #.#####",
        "     .  #   #  .     ",
        "#####.# ##### #.#####",
        "    #.#       #.#    ",
        " ####.# ##### #.#### ",
        " #........#........# ",
        " #.##.###.#.###.##.# ",
        " #0.#..... .....#.0# ",
        " ##.#.#.#####.#.#.## ",
        " #....#...#...#....# ",
        " #.######.#.######.# ",
        " #.................# ",
        " ################### ",
        "                     ",
        "                     "
    };
*/
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
        "    # #       # #    ",
        " #### # ##### # #### ",
        " #        #        # ",
        " # ## ### # ### ## # ",
        " #  #      ..   #  # ",
        " ## # # ##### # # ## ",
        " #    #   #   #    # ",
        " # ###### # ###### # ",
        " #                 # ",
        " ################### ",
        "                     ",
        "                     "
    };

    RectangleShape Wall(Vector2f(CellSize, CellSize));

    // Common food
    CircleShape food(CellSize / 5);
    food.setFillColor(Color::White);

    // Power food
    CircleShape power(CellSize / 3);
    power.setFillColor(Color::White);

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
                food.setPosition(Vector2f((j * CellSize) + 10, (i * CellSize) + 10));
                foods.push_back(food);
                break;
            case '0':
                power.setPosition(Vector2f((j * CellSize) + 5, (i * CellSize) + 5));
                powerFood.push_back(power);
                break;
            }
        }
    }
}

bool Map::checkEndLevel()
{
    if (foods.empty() && powerFood.empty())
    {
        level++;
        initMap();
        return true;
    }
    return false;
}

void Map::draw(RenderWindow & window)
{
    if (checkEndLevel())
    {
        initMap();
    }
    
    for (size_t i = 0; i < Height; i++)
    {
        for (size_t j = 0; j < Width; j++)
        {
            window.draw(map[i][j]);
        }
    }

    for(auto & a : foods)
    {
        window.draw(a);
    }

    for(auto & a : powerFood)
    {
        window.draw(a);
    }
}

void Map::setFood(std::vector<sf::CircleShape> foods)
{
    this->foods = foods;
}

void Map::setPowerFood(std::vector<sf::CircleShape> powerFood)
{
    this->powerFood = powerFood;
}