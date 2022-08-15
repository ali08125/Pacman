#pragma once
#include <array>
#include <info.hpp>
#include <SFML/Graphics.hpp>

bool collision(float i_x, float i_y, std::array<std::array<sf::RectangleShape, Width>, Height> map, int door = 0);