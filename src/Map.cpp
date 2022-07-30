#include <Map.hpp>
#include <iostream>

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
    /*
    
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
    
*/
    //Load fruits photo
    if(!apple.loadFromFile("../Photo/fruits/apple.png"))
        std::cerr << "can not open apple.png\n";

    if(!strawberry.loadFromFile("../Photo/fruits/strawberry.png"))
        std::cerr << "can not open strawberry.png\n";

    if(!cherry.loadFromFile("../Photo/fruits/cherry.png"))
        std::cerr << "can not open cherry.png\n";

    if(!peach.loadFromFile("../Photo/fruits/peach.png"))
        std::cerr << "can not open peach.png\n";

    if(!grape.loadFromFile("../Photo/fruits/grape.png"))
        std::cerr << "can not open grape.png\n";

    if(!banana.loadFromFile("../Photo/fruits/banana.png"))
        std::cerr << "can not open banana.png\n";

    //Wall
    RectangleShape Wall(Vector2f(CellSize, CellSize));

    // Common food
    CircleShape food(CellSize / 5);
    food.setFillColor(Color::White);

    // Power food
    CircleShape power(CellSize / 3);
    power.setFillColor(Color::White);

    // Fruit
    Fruit.scale(Vector2f(0.5, 0.5));

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
    
    Fruit.setTexture(apple);
    Fruit.setPosition(Vector2f(2 * CellSize + 5, 2 * CellSize + 5));
    window.draw(Fruit);
    
    Fruit.setTexture(strawberry);
    Fruit.setPosition(Vector2f(2 * CellSize + 5, 3 * CellSize + 5));
    window.draw(Fruit);

    Fruit.setTexture(cherry);
    Fruit.setPosition(Vector2f(2 * CellSize + 5, 4 * CellSize + 5));
    window.draw(Fruit);

    Fruit.setTexture(peach);
    Fruit.setPosition(Vector2f(2 * CellSize + 5, 1 * CellSize + 5));
    window.draw(Fruit);

    Fruit.setTexture(grape);
    Fruit.setPosition(Vector2f(2 * CellSize + 5, 5 * CellSize + 5));
    window.draw(Fruit);

    Fruit.setTexture(banana);
    Fruit.setPosition(Vector2f(2 * CellSize + 5, 6 * CellSize + 5));
    window.draw(Fruit);
    
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
void Map::setFruit(std::vector<sf::Sprite> fruit)
{
    this->fruit = fruit;
}

void Map::createFruit(CircleShape pacman)
{
    bool notCreated = true;
    srand(time(0));
    int x;
    int y;

    if (level == 0)//level <= 64)
    {
        Fruit.setTexture(apple);
    } else if (level > 64 && level <= 128)
    {
        Fruit.setTexture(strawberry);
    } else if (level > 128 && level <= 192)
    {
        Fruit.setTexture(cherry);
    } else if (level == 1)//level > 192 && level <= 224)
    {
        Fruit.setTexture(peach);
    } else if (level > 224 && level <= 240)
    {
        Fruit.setTexture(grape);
    } else if (level > 240 && level <= 255)
    {
        Fruit.setTexture(banana);
    }    
    
    while (notCreated)
    {
        x = rand() % 20;
        y = rand() % 21;
        Fruit.setPosition(Vector2f(x * CellSize + 5, y * CellSize + 5));
        

        int tmp = 0;

        //Check that it does not interfere with anything
        if (sketch[y][x] == '.')
        {    
            if (Fruit.getGlobalBounds().intersects(pacman.getGlobalBounds()))
            {
                continue;
            }
            
            for (auto & a : foods)
            {
                if (a.getGlobalBounds().intersects(Fruit.getGlobalBounds()))
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

    fruit.push_back(Fruit);
}