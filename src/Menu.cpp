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
    if(!font.loadFromFile("../Fonts/Plaguard-ZVnjx.otf"))
        cerr << "can not open the font!!!" << endl;

    score.setFont(font);
    score.setCharacterSize(32);
    score.setPosition(20, CellSize * Height - CellSize * 1.6);

    level.setFont(font);
    level.setCharacterSize(32);
    level.setPosition(440, CellSize * Height - CellSize * 1.6);

    levelUp.setFont(font);
    levelUp.setCharacterSize(48);
    levelUp.setPosition((Width / 2 * CellSize) - 70, (Height / 2 * CellSize) - 60);
    
}

void Menu::draw(sf::RenderWindow &window, int score, int level)
{
    this->score.setString("SCORE : " + to_string(score));
    this->level.setString("LEVEL : " + to_string(level));

    window.draw(this->score);
    window.draw(this->level);
}

void Menu::levelUpScreen(sf::RenderWindow &window, int level)
{
    Clock loadingScreen;
    this->levelUp.setString("level " + to_string(level));

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