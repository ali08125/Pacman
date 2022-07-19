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
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        window.clear();

        //Draw
        

        window.display();
    }
    

}