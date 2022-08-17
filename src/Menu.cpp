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
    death.setCharacterSize(72);
    death.setString("YOU DIED");
    death.setOrigin(death.getLocalBounds().width / 2, death.getLocalBounds().height / 2);
    death.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f - 70);

    deathScore.setFont(font);
    deathScore.setCharacterSize(50);

    play.setFont(font);
    play.setCharacterSize(72);
    play.setString("PLAY");
    play.setOrigin(play.getLocalBounds().width / 2, play.getLocalBounds().height / 2);
    play.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f - 70);

    setting.setFont(font);
    setting.setCharacterSize(72);
    setting.setString("SETTINGS");
    setting.setOrigin(setting.getLocalBounds().width / 2, setting.getLocalBounds().height / 2);
    setting.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f + 20);

    quit.setFont(font);
    quit.setCharacterSize(72);
    quit.setString("QUIT");
    quit.setOrigin(quit.getLocalBounds().width / 2, quit.getLocalBounds().height / 2);
    quit.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f + 110);
    

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
    deathScore.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f + 20);
    
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

        window.draw(background);
        window.draw(death);
        window.draw(deathScore);

        window.display();
    }
}

int Menu::gameMenu(sf::RenderWindow &window)
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

        int click = mouseHandle(window);
        if(click != 0)
        {
            switch (click)
            {
            case 1://Play
                return 1;
                break;
            case 2://Settings
                
                break;
            case 3://Quit
                window.close();
                return 3;
                break;
            }
        }

        window.clear();

        window.draw(background);
        window.draw(play);
        window.draw(setting);
        window.draw(quit);

        window.display();
    }
    exit(EXIT_SUCCESS);
    return 0;
}

int Menu::mouseHandle(sf::RenderWindow &window)
{
    Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));

    //play
    if (play.getGlobalBounds().contains(mouse))
    {
        play.setFillColor(Color::Yellow);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            return 1;
        }
    } else
    {
        play.setFillColor(Color::White);
    }
    //seetings
    if (setting.getGlobalBounds().contains(mouse))
    {
        setting.setFillColor(Color::Yellow);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            return 2;
        }
    } else
    {
        setting.setFillColor(Color::White);
    }
    //quit
    if (quit.getGlobalBounds().contains(mouse))
    {
        quit.setFillColor(Color::Yellow);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            return 3;
        }
    } else
    {
        quit.setFillColor(Color::White);
    }

    return 0;
}

void Menu::settingScreen(sf::RenderWindow &window)
{

}