#include <Collision.hpp>
#include <cmath>

using namespace std;
using namespace sf;

bool collision(float px, float py, array<array<RectangleShape, Width>, Height> map, int door)
{
	RectangleShape wall(Vector2f(CellSize, CellSize));
	wall.setPosition(px, py);

	for (size_t i = 0; i < Width; i++)
	{
		for (size_t j = 0; j < Height; j++)
		{
			if (wall.getGlobalBounds().intersects(map[j][i].getGlobalBounds())
			&& map[j][i].getFillColor() == Color::Blue)
			{
				return 1;
			}

			if (door == 0 && wall.getGlobalBounds().intersects(map[j][i].getGlobalBounds())
			&& map[j][i].getFillColor() == Color::White)
			{
				return 1;
			}
		}
	}
	return 0;
}
