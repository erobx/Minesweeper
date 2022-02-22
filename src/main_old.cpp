#include <SFML/Graphics.hpp>
#include "Board.h"
#include <vector>

int main()
{
    Board board;

    int width = board.GetCols() * 32;
    int height = (board.GetRows() * 32) + 88;
    vector<vector<Tile>> tiles = board.GetTiles();

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}