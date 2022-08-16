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
    
}

void Menu::draw(sf::RenderWindow &window, int score, int level)
{
    this->score.setString("SCORE : " + to_string(score));
    this->level.setString("LEVEL : " + to_string(level));

    window.draw(this->score);
    window.draw(this->level);
}