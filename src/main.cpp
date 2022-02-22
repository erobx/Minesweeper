#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include "TextureManager.h"
#include "Board.h"
#include "Tile.h"
using namespace std;
using namespace sf;

int main() {
    Board board;

    int width = board.GetCols() * 32;
    int height = (board.GetRows() * 32) + 88;
    vector<vector<Tile>> tiles = board.GetTiles();

    RenderWindow window(VideoMode(width, height), "Minesweeper");

    window.setFramerateLimit(60);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            // If user left clicked
            if (event.type == Event::MouseButtonPressed) {
                Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
                if (event.mouseButton.button == Mouse::Left) {
                    // Click on tile
                    for (int i = 0; i < board.GetCols(); i++) {
                        for (int j = 0; j < board.GetRows(); j++)
                            if (tiles[i][j].GetBounds().contains(mouse))
                                board.Update(i, j);
                    }
                    FloatRect btnSmile = board.GetHappy().getGlobalBounds();
                    FloatRect btnSad = board.GetSad().getGlobalBounds();
                    FloatRect btnWin = board.GetWin().getGlobalBounds();
                    if (btnSmile.contains(mouse) || btnSad.contains(mouse) || btnWin.contains(mouse))
                        board.Reset();

                    FloatRect btnDebug = board.GetDebug().getGlobalBounds();
                    if (btnDebug.contains(mouse))
                        board.Toggle();

                    // Test Boards
                    FloatRect btnTest1 = board.GetTest1().getGlobalBounds();
                    FloatRect btnTest2 = board.GetTest2().getGlobalBounds();
                    FloatRect btnTest3 = board.GetTest3().getGlobalBounds();

                    if (btnTest1.contains(mouse))
                        board.LoadTest("1");
                    if (btnTest2.contains(mouse))
                        board.LoadTest("2");
                    if (btnTest3.contains(mouse))
                        board.LoadTest("3");
                }
                if (event.mouseButton.button == Mouse::Right) {
                    for (int i = 0; i < board.GetCols(); i++) {
                        for (int j = 0; j < board.GetRows(); j++)
                            if (tiles[i][j].GetBounds().contains(mouse))
                                board.Flag(i, j);
                    }
                }
            }
        }

        window.clear(Color::White);

        // Draw board
        board.Draw(window);

        window.display();
    }

    // Clear out any textures before the program ends
    TextureManager::Clear();
    return 0;
}
