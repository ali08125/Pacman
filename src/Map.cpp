#include <Map.hpp>
#include <iostream>

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

    //Fruits
    apple.setRadius(CellSize / 3);
    apple.setFillColor(Color::Red);

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

void Map::update(sf::Time time)
{
    checkEndLevel();
    
    if (!fruit.empty() && time.asSeconds() > 10)
    {
        fruit.erase(fruit.begin());
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

    if (!fruit.empty())
    {
        window.draw(fruit[0]);
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
void Map::setFruit(std::vector<sf::CircleShape> fruit)
{
    this->fruit = fruit;
}

void Map::createFruit()
{
    bool notCreated = true;
    srand(time(0));
    int x;
    int y;

    if (level < 64)
    {
        while (notCreated)
        {
            x = rand() % 20;
            y = rand() % 21;
            apple.setPosition(Vector2f(x * CellSize + 5, y * CellSize + 5));

            int tmp = 0;

            //Check that it does not interfere with anything
            if (sketch[y][x] == '.')
            {    
                for (auto & a : foods)
                {
                    if (a.getGlobalBounds().intersects(apple.getGlobalBounds()))
                    {
                        tmp = 1;
                    }
                }
            } else
                continue;

            if(tmp == 1)
                continue;

            notCreated = false;
        }
    }

    fruit.push_back(apple);
}