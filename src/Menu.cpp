#include <Menu.hpp>
#include <iostream>
#include <info.hpp>

using namespace std;
using namespace sf;

Menu::Menu()
{
    this->initMenu();
}

void Menu::initMenu()
{
    if (!backgroundTexture.loadFromFile("../Photo/menu/pacmanMenu.jpg"))
        cerr << "can not open the background!!!" << endl;
    background.setTexture(backgroundTexture);
    
    if(!font.loadFromFile("../Fonts/MaldiniBold-EaqGW.otf"))
        cerr << "can not open the font!!!" << endl;

    score.setFont(font);
    this->score.setCharacterSize(24);
    this->score.setPosition(30, 1);

    level.setFont(font);
    level.setCharacterSize(24);
    level.setPosition(500, 660);

    levelUp.setFont(font);
    levelUp.setCharacterSize(48);
    levelUp.setPosition((Width / 2 * CellSize) - 70, (Height / 2 * CellSize) - 60);

    death.setFont(font);
    death.setCharacterSize(48);
    death.setString("YOU DIED");
    death.setOrigin(death.getLocalBounds().width / 2, death.getLocalBounds().height / 2);
    death.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f - 70);

    deathScore.setFont(font);
    deathScore.setCharacterSize(32);
    

    if (!pacmanTexture.loadFromFile("../Photo/pacman/2.png"))
        cout << "can not open 2.png" << endl;
    for (size_t i = 0; i < 3; i++)
    {
        pacman[i].setTexture(pacmanTexture);
        pacman[i].setScale(Vector2f(0.2, 0.2)); 
    }
    pacman[0].setPosition(30, 665);
    pacman[1].setPosition(60, 665);
    pacman[2].setPosition(90, 665);
    
}

void Menu::draw(sf::RenderWindow &window, int score, int level, int health)
{
    this->score.setString("SCORE " + to_string(score));
    this->level.setString("LEVEL " + to_string(level));

    window.draw(this->score);
    window.draw(this->level);

    for (size_t i = 0; i < health; i++)
    {
        window.draw(this->pacman[i]);
    }    
}

void Menu::levelUpScreen(RenderWindow &window, int level)
{
    Clock loadingScreen;
    this->levelUp.setString("LEVEL " + to_string(level));

    Event event;
    while (loadingScreen.getElapsedTime().asSeconds() <= 2)
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }
        window.clear(Color::Black);

        window.draw(levelUp);

        window.display();
    }
}

void Menu::deathScreen(RenderWindow &window, int score)
{
    deathScore.setString("SCORE " + to_string(score));
    deathScore.setOrigin(deathScore.getLocalBounds().width / 2, deathScore.getLocalBounds().height / 2);
    deathScore.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f - 20);
    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        window.clear(Color::Black);

        window.draw(death);
        window.draw(deathScore);

        window.display();
    }
}

void Menu::gameMenu(sf::RenderWindow &window)
{
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        window.clear();

        window.draw(background);

        window.display();
    }
}