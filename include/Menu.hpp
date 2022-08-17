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
    sf::Text play;
    sf::Text setting;
    sf::Text quit;
    sf::Texture backgroundTexture;
    std::array<sf::Sprite, 3> pacman;
    sf::Texture pacmanTexture;
    sf::Sprite background;

    void initMenu();
public:
    Menu();
    void levelUpScreen(sf::RenderWindow &window, int level);
    void deathScreen(sf::RenderWindow &window, int score);
    void gameMenu(sf::RenderWindow &window);
    void mouseHower(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window, int score, int level, int health);

};