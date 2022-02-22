#include <iostream>
#include "Tile.h"
#include "TextureManager.h"

Tile::Tile() {
	SetTileHidden();
}

void Tile::SetTileHidden() {
	tile_hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
	tile_revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
	flag.setTexture(TextureManager::GetTexture("flag"));
	mine.setTexture(TextureManager::GetTexture("mine"));
	isHidden = true;
	isFlag = false;
	isMine = false;
	numMines = 0;
}

void Tile::SetPosition(float xpos, float ypos) {
	tile_hidden.setPosition(xpos, ypos);
	tile_revealed.setPosition(xpos, ypos);
	flag.setPosition(xpos, ypos);
	mine.setPosition(xpos, ypos);
	number.setPosition(xpos, ypos);
}

void Tile::Draw(sf::RenderWindow& window) {
	if (isFlag) {
		window.draw(tile_hidden);
		window.draw(flag);
	}
	else if (numMines > 0) {
		window.draw(tile_revealed);
		LoadNum();
		window.draw(number);
	}
	else if (isHidden)
		window.draw(tile_hidden);
	else
		window.draw(tile_revealed);
}

void Tile::DrawEnd(sf::RenderWindow& window) {
	if (isMine) {
		window.draw(tile_revealed);
		window.draw(mine);
	}
	else
		window.draw(tile_hidden);
}

void Tile::DrawMines(sf::RenderWindow& window) {
	Draw(window);
	if (isMine) {
		window.draw(tile_revealed);
		window.draw(mine);
	}
}

int Tile::RevealTile() {
	int tileCount = 0;
	if (isHidden && !isFlag) {
		isHidden = false;
		tileCount++;
		if (GetNumMines() > 0) {
			LoadNum();
		}
		else if (!isMine) {
			for (int i = 0; i < adjTiles.size(); i++)
				tileCount += adjTiles[i]->RevealTile();
		}
	}
	return tileCount;
}

void Tile::Flag() {
	isFlag = !isFlag;
}

void Tile::LoadNum() {
	number.setTexture(TextureManager::GetTexture("number_" + std::to_string(numMines)));
}

sf::Vector2f Tile::GetPosition() {
	return tile_hidden.getPosition();
}

vector<Tile*> Tile::GetAdjTiles() {
	return adjTiles;
}

sf::FloatRect Tile::GetBounds() {
	return tile_hidden.getGlobalBounds();
}

int Tile::GetNumMines() {
	for (Tile* t : adjTiles)
		if (t->GetMine())
			numMines++;
	return numMines;
}

bool Tile::GetHidden() {
	return isHidden;
}

bool Tile::GetMine() {
	return isMine;
}

bool Tile::GetFlag() {
	return isFlag;
}

void Tile::SetMine() {
	isMine = true;
}

void Tile::SetAdjTiles(vector<Tile*>& tiles) {
	for (int i = 0; i < tiles.size(); i++)
		adjTiles.push_back(tiles.at(i));
}