#include "game.h"
#include <algorithm>
#include <random>
#include <iostream>

// Constructor
Game::Game() {
    createTiles();
    players.resize(4); // 4 players
}

// Create all 106 tiles
void Game::createTiles() {
    std::vector<std::string> colors = {"red", "black", "blue", "yellow"};
    for (const auto& color : colors) {
        for (int num = 1; num <= 13; ++num) {
            tiles.push_back(Tile(num, color)); // Normal tile
            tiles.push_back(Tile(num, color)); // Second set
        }
    }
    // Add fake jokers
    tiles.push_back(Tile(-1, "none", false, true, 0)); // Fake joker 1
    tiles.push_back(Tile(-1, "none", false, true, 0)); // Fake joker 2
}

// Shuffle and distribute tiles
void Game::shuffleAndDistribute() {
    std::random_device rd;
    std::shuffle(tiles.begin(), tiles.end(), rd);

     
    // Player 1 gets 15 tiles
    players[0].addTile(tiles.back());
    tiles.pop_back();

    // Taşlar karıştırıldıktan sonra oyunculara dağıtılır sırasıyla 15 14 14 14 şeklinde değıtılır
        // Oyunuclara taşların referansı dağıtılır copy object oluşturulmaz
    for(int j = 0; j < 4; ++j){
        for(int i = 0; i < 14; ++i){
            players[j].addTile(tiles.back());
            tiles.pop_back();
        }
    }
   
}

// Determine the joker
void Game::determineJoker() {
    // Taşlar 21li gruplar halinde 5erli gruplar halinde tutulduğu için
        // random bir stack ve random bir taş seçilir
    int stackIndex = rand() % 21; // Random stack
    int tileIndex = rand() % 5;   // Random tile in the stack

    Tile& jokerTile = tiles[stackIndex * 5 + tileIndex]; // Reference instead of copy
    if (jokerTile.getNumber() == 13) {
        jokerTile.setNumber(1); // Wrap around
    } else {
        jokerTile.setNumber(jokerTile.getNumber() + 1); // Next number
    }
    jokerTile.setIsJoker(true);
    joker = jokerTile;


    // Change fake_jokers numeric value to jokers numeric value
    // Sayısını random olarak belirlediğimiz jokerin orijinal tile objesini
        // joker olarak değiştir
    for (auto& player : players) {
        for (auto& tile : player.getHand()) {
            if (tile.getIsFakeJoker() == true) {
                tile.setNumber(joker.getNumber());
                tile.setColor(joker.getColor());
            }
            if (tile.getNumber() == joker.getNumber() && tile.getColor() == joker.getColor() && tile.getIsFakeJoker() == false) {
                tile.setIsJoker(true);
            }
            
        }
    }

}

// Get the joker
Tile& Game::getJoker() {
    return joker;
}

// Get the joker
std::vector<Player>& Game::getPlayers(){
    return players;
}


// Print all tiles (for debugging)
void Game::printTiles() const {
    for (const auto& tile : tiles) {
        tile.print();
    }
}