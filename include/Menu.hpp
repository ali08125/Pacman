#pragma once

#include <SFML/Graphics.hpp>

class Menu
{
private:
    sf::Font font;
    sf::Text score;
    sf::Text level;
    sf::Text levelUp;
    sf::Text death;
    sf::Text deathScore;
    sf::Text highscore1;
    sf::Text play;
    sf::Text setting;
    sf::Text quit;
    sf::Text backToMenu;
    sf::Text resetHighScore;
    sf::Text menu;
    sf::Text highScore;
    sf::Text Reseted;
    sf::Text deathScreenMenu;//Back to menu from death screen
    sf::Texture backgroundTexture;
    sf::Texture background1Texture;
    std::array<sf::Sprite, 3> pacman;
    sf::Texture pacmanTexture;
    sf::Sprite background;
    sf::Sprite background1;
    sf::Clock clock;
    bool reset = false;

    void initMenu();
public:
    Menu();
    void levelUpScreen(sf::RenderWindow &window, int level);
    bool deathScreen(sf::RenderWindow &window, int score);
    int gameMenu(sf::RenderWindow &window);
    int mouseHandle(sf::RenderWindow &window, std::string tmp);
    void settingScreen(sf::RenderWindow &window);
    void resetData();
    void draw(sf::RenderWindow &window, int score, int level, int health);

};