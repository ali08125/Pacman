#include <Menu.hpp>
#include <iostream>
#include <info.hpp>
#include <fstream>

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

    if (!background1Texture.loadFromFile("../Photo/menu/background1.jpg"))
        cerr << "can not open the background!!!" << endl;
    background1.setTexture(background1Texture);
    
    if(!font.loadFromFile("../Fonts/MaldiniBold-EaqGW.otf"))
        cerr << "can not open the font!!!" << endl;

    score.setFont(font);
    score.setCharacterSize(24);

    highScore.setFont(font);
    highScore.setCharacterSize(24);

    level.setFont(font);
    level.setCharacterSize(24);
    level.setPosition(520, 660);

    levelUp.setFont(font);
    levelUp.setCharacterSize(48);

    death.setFont(font);
    death.setCharacterSize(72);
    death.setString("YOU DIED");
    death.setOrigin(death.getLocalBounds().width / 2, death.getLocalBounds().height / 2);
    death.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f - 100);

    deathScore.setFont(font);
    deathScore.setCharacterSize(50);

    highscore1.setFont(font);
    highscore1.setCharacterSize(35);

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

    resetHighScore.setFont(font);
    resetHighScore.setCharacterSize(60);
    resetHighScore.setString("RESET HIGH SCORE");
    resetHighScore.setOrigin(resetHighScore.getLocalBounds().width / 2
    ,resetHighScore.getLocalBounds().height / 2);
    resetHighScore.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f - 10);

    backToMenu.setFont(font);
    backToMenu.setCharacterSize(60);
    backToMenu.setString("BACK TO MENU");
    backToMenu.setOrigin(backToMenu.getLocalBounds().width / 2, backToMenu.getLocalBounds().height / 2);
    backToMenu.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f + 80);

    menu.setFont(font);
    menu.setCharacterSize(24);
    menu.setString("BACK TO MENU");
    menu.setOrigin(menu.getLocalBounds().width / 2, menu.getLocalBounds().height / 2);
    menu.setPosition(95, 10);

    Reseted.setFont(font);
    Reseted.setCharacterSize(32);
    Reseted.setString("RESET SUCCESSFULLY");
    Reseted.setOrigin(Reseted.getLocalBounds().width / 2, Reseted.getLocalBounds().height / 2);
    Reseted.setPosition(CellSize * Width / 2.0f, 600);

    deathScreenMenu.setFont(font);
    deathScreenMenu.setCharacterSize(24);
    deathScreenMenu.setString("BACK TO MENU");
    deathScreenMenu.setOrigin(deathScreenMenu.getLocalBounds().width / 2
    ,deathScreenMenu.getLocalBounds().height / 2);
    deathScreenMenu.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f + 70);

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
    this->level.setString("LEVEL " + to_string(level));

    this->score.setString("SCORE " + to_string(score));
    this->score.setOrigin(this->score.getLocalBounds().width / 2, this->score.getLocalBounds().height / 2);
    this->score.setPosition(CellSize * Width / 2.0f, 10);


    //Reading highScore from file
    int high_score;
    fstream file;
    file.open("../data/data.txt", ios::in);
    file >> high_score;
    file.close();

    highScore.setString("HIGH SCORE " + to_string(high_score));
    highScore.setOrigin(highScore.getLocalBounds().width / 2, highScore.getLocalBounds().height / 2);
    highScore.setPosition(520, 10);

    window.draw(this->score);
    window.draw(this->level);

    for (size_t i = 0; i < health; i++)
    {
        window.draw(this->pacman[i]);
    }    
    window.draw(menu);
    if(mouseHandle(window, "backMenuFromGame") == 1)
    {
        gameMenu(window);
    }
    window.draw(highScore);
}

void Menu::levelUpScreen(RenderWindow &window, int level)
{
    Clock loadingScreen;
    this->levelUp.setString("LEVEL " + to_string(level));
    levelUp.setOrigin(levelUp.getLocalBounds().width / 2, levelUp.getLocalBounds().height / 2);
    levelUp.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f);

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

        window.draw(background1);
        window.draw(levelUp);

        window.display();
    }
}

bool Menu::deathScreen(RenderWindow &window, int score)
{
    //Reading highScore from file
    int high_score;
    fstream file;
    file.open("../data/data.txt", ios::in);
    file >> high_score;
    file.close();
    
    highscore1.setString("HIGH SCORE " + to_string(high_score));
    highscore1.setOrigin(highscore1.getLocalBounds().width / 2
    ,highscore1.getLocalBounds().height / 2);
    highscore1.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f + 25);


    deathScore.setString("SCORE " + to_string(score));
    deathScore.setOrigin(deathScore.getLocalBounds().width / 2, deathScore.getLocalBounds().height / 2);
    deathScore.setPosition(CellSize * Width / 2.0f, CellSize * Width / 2.0f - 30);
    
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

        if (mouseHandle(window, "deathScreen") == 1)
        {
            return true;
        }

        window.clear(Color::Black);

        window.draw(background1);
        window.draw(death);
        window.draw(deathScore);
        window.draw(highscore1);
        window.draw(deathScreenMenu);

        window.display();
    }
    return false;
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

        int click = mouseHandle(window, "menu");
        if(click != 0)
        {
            switch (click)
            {
            case 1://Play
                return 1;
                break;
            case 2://Settings
                settingScreen(window);
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

int Menu::mouseHandle(sf::RenderWindow &window, string tmp)
{
    Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));

    if (tmp == "menu")
    {    
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
    } else if (tmp == "setting")
    {
        //resetHighScore
        if (resetHighScore.getGlobalBounds().contains(mouse))
        {
            resetHighScore.setFillColor(Color::Yellow);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                return 1;
            }
        } else
        {
            resetHighScore.setFillColor(Color::White);
        }
        //backToMenu
        if (backToMenu.getGlobalBounds().contains(mouse))
        {
            backToMenu.setFillColor(Color::Yellow);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                return 2;
            }
        } else
        {
            backToMenu.setFillColor(Color::White);
        }
        return 0;
    } else if (tmp == "backMenuFromGame")
    {
        if (menu.getGlobalBounds().contains(mouse))
        {
            menu.setFillColor(Color::Yellow);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                return 1;
            }
        } else
        {
            menu.setFillColor(Color::White);
        }
    } else if (tmp == "deathScreen")
    {
        if (deathScreenMenu.getGlobalBounds().contains(mouse))
        {
            deathScreenMenu.setFillColor(Color::Yellow);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                return 1;
            }
        } else
        {
            deathScreenMenu.setFillColor(Color::White);
        }
    }
    return 0;
}

void Menu::settingScreen(sf::RenderWindow &window)
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

        int click = mouseHandle(window, "setting");
        if (click != 0)
        {
            switch (click)
            {
            case 1:
                resetData();
                clock.restart();
                reset = true;
                break;
            case 2:
                return;
                break;
            }
        }

        window.clear();
        
        window.draw(background);
        window.draw(resetHighScore);
        window.draw(backToMenu);
        if (reset == true && clock.getElapsedTime().asSeconds() < 1)
        {
            window.draw(Reseted);
        }
        window.display();
    }
    exit(EXIT_SUCCESS);
}

void Menu::resetData()
{
    int score = 0;
    fstream file;
    file.open("../data/data.txt", ios::out);
    file << score;
    file.close();
}