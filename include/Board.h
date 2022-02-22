#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Tile.h"
using std::string;

class Board {
    int numRows;
    int numCols;
    int numMines;
    vector<int> LoadConfig(string config);
    vector<vector<Tile>> tiles;
    bool gameState = true;
    bool toggle = false;
    bool win = false;
    // Btns
    sf::Sprite faceHappy;
    sf::Sprite faceLose;
    sf::Sprite faceWin;
    sf::Sprite debug;
    sf::Sprite test_1;
    sf::Sprite test_2;
    sf::Sprite test_3;
    sf::Sprite digit;
public:
    Board();
    void Draw(sf::RenderWindow& window);
    void DrawBtns(sf::RenderWindow& window);
    void DrawRemaining(sf::RenderWindow& window);
    void Reset();
    void Update(int c, int r);
    void Flag(int c, int r);
    void Toggle();
    void LoadTest(string num);

    vector<vector<Tile>> GetTiles();
    void SetAdjTiles();
    int GetRows();
    int GetCols();
    sf::Sprite GetHappy();
    sf::Sprite GetSad();
    sf::Sprite GetWin();
    sf::Sprite GetDebug();
    sf::Sprite GetTest1();
    sf::Sprite GetTest2();
    sf::Sprite GetTest3();
};