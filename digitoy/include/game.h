#ifndef GAME_H
#define GAME_H

#include "tile.h"
#include "player.h"
#include <vector>

class Game {
private:
    std::vector<Tile> tiles ;
    std::vector<Player> players;
    Tile joker;

public:
    // Constructor
    Game();

    // Create all 106 tiles
    void createTiles();

    // Shuffle and distribute tiles
    void shuffleAndDistribute();

    // Determine the joker
    void determineJoker();

    // Get the joker
    Tile& getJoker();

    std::vector<Player>& getPlayers();

    // Print all tiles (for debugging)
    void printTiles() const;
};

#endif // GAME_H