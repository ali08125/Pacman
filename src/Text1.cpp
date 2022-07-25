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
    if(font.loadFromFile("../Fonts/Plaguard-ZVnjx.otf"))
        cerr << "can not open the font!!!" << endl;

    text.setFont(font);
    text.setColor(Color::White);
    text.setCharacterSize(24);
    text.setPosition(50, CellSize * Height - CellSize);
    text.setString("helloooooooo");
}

void Text1::draw(sf::RenderWindow &window)
{
    window.draw(text);
}