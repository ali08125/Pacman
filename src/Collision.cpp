#include <Collision.hpp>
#include <cmath>

using namespace std;
using namespace sf;

bool collision(float px, float py, array<array<RectangleShape, Width>, Height> map, int door)
{
    float cell_x = px / static_cast<float>(CellSize);
	float cell_y = py / static_cast<float>(CellSize);

    for (int a = 0; a < 4; a++)
	{
	    float x = 0;
		float y = 0;

		switch (a)
		{
			case 0: //Top left cell
			{
				x = static_cast<float>(floor(cell_x));
				y = static_cast<float>(floor(cell_y));

				break;
			}
			case 1: //Top right cell
			{
				x = static_cast<float>(ceil(cell_x));
				y = static_cast<float>(floor(cell_y));

				break;
			}
			case 2: //Bottom left cell
			{
				x = static_cast<float>(floor(cell_x));
				y = static_cast<float>(ceil(cell_y));

				break;
			}
			case 3: //Bottom right cell
			{
				x = static_cast<float>(ceil(cell_x));
				y = static_cast<float>(ceil(cell_y));
			}
		}

		Vector2f block(10 * CellSize, 8 * CellSize);
		if (0 <= x && 0 <= y && Height > y && Width > x)
		{
            if (map[y][x].getFillColor() == Color::Blue)
            {
                return 1;
            } else if (map[y][x].getPosition() == block && door == 0)
			{
				return 1;
			}
        }
    }
    return 0;
}
