#include <Text1.hpp>
#include <iostream>
#include <info.hpp>

using namespace std;
using namespace sf;

Text1::Text1()
{
    this->initText();
}

void Text1::initText()
{
    if(!font.loadFromFile("../Fonts/Plaguard-ZVnjx.otf"))
        cerr << "can not open the font!!!" << endl;

    text.setFont(font);
    text.setCharacterSize(32);
    text.setPosition(20, CellSize * Height - CellSize*1.6);
    
}

void Text1::draw(sf::RenderWindow &window, int score)
{
    text.setString("SCORE : " + to_string(score));

    window.draw(text);
}