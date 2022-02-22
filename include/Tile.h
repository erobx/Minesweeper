#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using std::vector;

class Tile {
    sf::Sprite tile_hidden;
    sf::Sprite tile_revealed;
    sf::Sprite flag;
    sf::Sprite mine;
    sf::Sprite number;
    bool isHidden;
    bool isFlag;
    bool isMine;
    int numMines;
    vector<Tile*> adjTiles;
public:
    // Constructor
    Tile();
    void SetTileHidden();
    void SetPosition(float xpos, float ypos);
    void Draw(sf::RenderWindow& window);
    void DrawEnd(sf::RenderWindow& window);
    void DrawMines(sf::RenderWindow& window);
    int RevealTile();
    void Flag();
    void LoadNum();

    sf::Vector2f GetPosition();
    vector<Tile*> GetAdjTiles();
    sf::FloatRect GetBounds();
    int GetNumMines();
    bool GetHidden();
    bool GetMine();
    bool GetFlag();
    void SetMine();
    void SetAdjTiles(vector<Tile*>& tiles);
};