#include <SFML/Graphics.hpp>
#include <info.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(Width * Width, Height * Height), "PacMan");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.Closed())
            {
                window.close();
            }
            
        }
    }
    

}