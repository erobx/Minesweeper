#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include "Board.h"
#include "TextureManager.h"
#include "Random.h"
using namespace std;

vector<int> Board::LoadConfig(string config) {
    vector<int> settings;

    ifstream myfile(config);
    while (!myfile.eof()) {
        int temp;
        myfile >> temp;
        settings.push_back(temp);
    }
    myfile.close();
    return settings;
}

Board::Board() {
    faceHappy.setTexture(TextureManager::GetTexture("face_happy"));
    faceLose.setTexture(TextureManager::GetTexture("face_lose"));
    faceWin.setTexture(TextureManager::GetTexture("face_win"));
    debug.setTexture(TextureManager::GetTexture("debug"));
    test_1.setTexture(TextureManager::GetTexture("test_1"));
    test_2.setTexture(TextureManager::GetTexture("test_2"));
    test_3.setTexture(TextureManager::GetTexture("test_3"));
    digit.setTexture(TextureManager::GetTexture("digits"));

    Reset();
}

void Board::Draw(sf::RenderWindow& window) {
    // If game won...
    if (win) {
        DrawBtns(window);
        DrawRemaining(window);
    }
    // If game ended...
    if (!gameState) {
        for (vector<Tile> t : tiles) {
            for (Tile tile : t)
                tile.DrawEnd(window);
        }
        DrawBtns(window);
        DrawRemaining(window);
    }
    // Game still going but cheating...
    else if (toggle) {
        for (vector<Tile> t : tiles) {
            for (Tile tile : t)
                tile.DrawMines(window);
        }
        DrawBtns(window);
        DrawRemaining(window);
    }
    // If game didn't end...
    else {
        for (vector<Tile> t : tiles) {
            for (Tile tile : t)
                tile.Draw(window);
        }
        DrawBtns(window);
        DrawRemaining(window);
    }
}

void Board::DrawBtns(sf::RenderWindow& window) {
    faceHappy.setPosition(window.getSize().x / 2.f - 32.f, window.getSize().y - 88.f);
    faceLose.setPosition(window.getSize().x / 2.f - 32.f, window.getSize().y - 88.f);
    faceWin.setPosition(window.getSize().x / 2.f - 32.f, window.getSize().y - 88.f);
    sf::Vector2f smilePos = faceHappy.getPosition();
    debug.setPosition((float)smilePos.x + (32.f * 4), (float)smilePos.y);

    sf::Vector2f debugPos = debug.getPosition();
    test_1.setPosition((float)debugPos.x + (32.f * 2), (float)debugPos.y);

    sf::Vector2f test1Pos = test_1.getPosition();
    test_2.setPosition((float)test1Pos.x + (32.f * 2), (float)test1Pos.y);

    sf::Vector2f test2Pos = test_2.getPosition();
    test_3.setPosition((float)test2Pos.x + (32.f * 2), (float)test2Pos.y);

    if (gameState)
        window.draw(faceHappy);
    else if (win)
        window.draw(faceWin);
    else
        window.draw(faceLose);

    window.draw(debug);
    window.draw(test_1);
    window.draw(test_2);
    window.draw(test_3);
}

void Board::DrawRemaining(sf::RenderWindow& window) {
    if (numMines > 9) {
        char a = to_string(numMines)[0];
        int first_num = a - '0';
        char b = to_string(numMines)[1];
        int second_num = b - '0';
        digit.setTextureRect(sf::IntRect(first_num * 21, 0, 21, 32));
        digit.setPosition(32.f, window.getSize().y - 88.f);
        window.draw(digit);
        digit.setTextureRect(sf::IntRect(second_num * 21, 0, 21, 32));
        digit.setPosition(32.f + 21.5, window.getSize().y - 88.f);
        window.draw(digit);
    }
    else if (numMines > -1) {
        char a = to_string(numMines)[0];
        int first_num = a - '0';
        digit.setTextureRect(sf::IntRect(first_num * 21, 0, 21, 32));
        digit.setPosition(32.f, window.getSize().y - 88.f);
        window.draw(digit);
    }
    else if (numMines > -9) {
        // Draw dash for negative
        digit.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
        digit.setPosition(32.f, window.getSize().y - 88.f);
        window.draw(digit);
        char a = to_string(numMines)[1];
        int first_num = a - '0';
        digit.setTextureRect(sf::IntRect(first_num * 21, 0, 21, 32));
        digit.setPosition(32.f + 21.5, window.getSize().y - 88.f);
        window.draw(digit);
    }
    else {
        // Draw dash for negative
        digit.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
        digit.setPosition(32.f, window.getSize().y - 88.f);
        window.draw(digit);
        char a = to_string(numMines)[1];
        int first_num = a - '0';
        char b = to_string(numMines)[2];
        int second_num = b - '0';
        digit.setTextureRect(sf::IntRect(first_num * 21, 0, 21, 32));
        digit.setPosition(32.f + 21.5, window.getSize().y - 88.f);
        window.draw(digit);
        digit.setTextureRect(sf::IntRect(second_num * 21, 0, 21, 32));
        digit.setPosition(32.f + 43.f, window.getSize().y - 88.f);
        window.draw(digit);
    }
}

void Board::Reset() {
    vector<int> config = LoadConfig("boards/config.cfg");
    numCols = config.at(0);
    numRows = config.at(1);
    numMines = config.at(2);
    gameState = true;
    tiles.clear();
    for (int i = 0; i < numCols; i++) {
        vector<Tile> row;
        for (int j = 0; j < numRows; j++) {
            Tile tempTile;
            tempTile.SetPosition(32.f * i, 32.f * j);
            row.push_back(tempTile);
        }
        tiles.push_back(row);
    }

    int minesToAdd = numMines;
    while (minesToAdd > 0) {
        int i = Random::Int(0, numCols - 1);
        int j = Random::Int(0, numRows - 1);
        if (!tiles[i][j].GetMine()) {
            tiles[i][j].SetMine();
            minesToAdd--;
        }
    }
    // Set adjTiles
    SetAdjTiles();
}

void Board::Update(int c, int r) {
    int tileCount;
    if (tiles[c][r].GetHidden() && !tiles[c][r].GetFlag() && !tiles[c][r].GetMine()) {
        tileCount = tiles[c][r].RevealTile();
        if (numCols * numRows - numMines == tileCount)
            win = true;
    }
    else if (tiles[c][r].GetMine()) {
        gameState = false;
    }
}

void Board::Flag(int c, int r) {
    if (tiles[c][r].GetHidden() == false);
    else if (!tiles[c][r].GetFlag()) {
        tiles[c][r].Flag();
        numMines--;
    }
    else {
        tiles[c][r].Flag();
        numMines++;
    }
}

void Board::Toggle() {
    toggle = !toggle;
}

void Board::LoadTest(string num) {
    Reset();
    string filename = "boards/testboard" + num + ".brd";
    ifstream myfile(filename);
    if (!myfile.is_open()) {
        cout << "Could not open file " << filename << endl;
        return;
    }
    vector<vector<char>> board;
    string line;
    while (getline(myfile, line)) {
        vector<char> row;

        for (char c : line) {
            row.push_back(c);
        }
        board.push_back(row);
    }
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] == '1')
                tiles[j][i].SetMine();
            else
                tiles[j][i].SetTileHidden();
        }
    }
    myfile.close();
}

// Accessors
vector<vector<Tile>> Board::GetTiles() {
    return tiles;
}

void Board::SetAdjTiles() {
    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            vector<Tile*> temp;

            bool aboveRow = i - 1 >= 0;
            bool belowRow = i + 1 < numCols;
            bool leftCol = j - 1 >= 0;
            bool rightCol = j + 1 < numRows;

            // Sides
            if (aboveRow)
                temp.push_back(&tiles[i - 1][j]);
            if (belowRow)
                temp.push_back(&tiles[i + 1][j]);
            if (leftCol)
                temp.push_back(&tiles[i][j - 1]);
            if (rightCol)
                temp.push_back(&tiles[i][j + 1]);

            // Corners
            if (aboveRow && leftCol)
                temp.push_back(&tiles[i - 1][j - 1]);
            if (aboveRow && rightCol)
                temp.push_back(&tiles[i - 1][j + 1]);
            if (belowRow && leftCol)
                temp.push_back(&tiles[i + 1][j - 1]);
            if (belowRow && rightCol)
                temp.push_back(&tiles[i + 1][j + 1]);
            
            tiles[i][j].SetAdjTiles(temp);
        }
    }
}

int Board::GetRows() {
    return numRows;
}

int Board::GetCols() {
    return numCols;
}

sf::Sprite Board::GetHappy() {
    return faceHappy;
}

sf::Sprite Board::GetSad() {
    return faceLose;
}

sf::Sprite Board::GetWin() {
    return faceWin;
}

sf::Sprite Board::GetDebug() {
    return debug;
}

sf::Sprite Board::GetTest1() {
    return test_1;
}

sf::Sprite Board::GetTest2() {
    return test_2;
}

sf::Sprite Board::GetTest3() {
    return test_3;
}
