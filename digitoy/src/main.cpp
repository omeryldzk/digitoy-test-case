#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(0)); // Seed for random number generation

    Game game;
    game.shuffleAndDistribute(); // Shuffle and distribute tiles
    game.determineJoker(); // Determine the joker tile

    // Display the Joker tile
    std::cout << "Joker:\n";
    game.getJoker().print();
    std::cout << "\n";

    // Determine the winner
    int lowestScore = 16; // Max possible score + 1
    Player* winner = nullptr; // Pointer to track the winner
    int winner_count;
    for (size_t i = 0; i < game.getPlayers().size(); ++i) {
        Player& player = game.getPlayers()[i];

        std::cout << "Player " << i + 1 << "'s Hand:\n";
        player.printHand();
        std::cout << "\n";

        // Evaluate player's hand and set the number of tiles needed to win
        std::cout << "Player " << i + 1 << "'s Pers:\n";
        int playerScore = player.evaluateHand();
        player.setNumberOfTilesToWin(playerScore);
        std::cout << "Remaining tile score: " << playerScore << "\n\n";

        // Update the winner if the score is the lowest
        if (lowestScore > playerScore) {
            lowestScore = playerScore;
            winner = &player;
            winner_count = i;
        }
    }

    if (winner) {
        std::cout << "Winner is Player " << winner_count + 1 << " with the least remaining tiles: " << lowestScore << "\n";
    } else {
        std::cout << "No winner found.\n";
    }

    return 0;
}

/// You can use the following main function to test the implementation

// int main() {
//     srand(time(0)); // Seed for random number generation

//     Game game;

//     // Step 1: Determine the Joker BEFORE assigning hands
//     game.determineJoker();
//     Tile joker = game.getJoker(); // Store the Joker tile

//     // Display the determined Joker
//     std::cout << "Joker Tile: ";
//     joker.print();
//     std::cout << "\n";

//     // Get the players
//     std::vector<Player>& players = game.getPlayers();

//     // Step 2: Assign tiles to players AFTER Joker is set

//     // Player 1 (15 tiles, including the Joker)
//     players[0].addTile(Tile(8, "red"));
//     players[0].addTile(Tile(8, "red"));
//     players[0].addTile(Tile(9, "red"));
//     players[0].addTile(Tile(9, "red"));
//     players[0].addTile(Tile(10, "red"));
//     players[0].addTile(Tile(10, "red"));
//     players[0].addTile(Tile(1, "blue"));
//     players[0].addTile(Tile(2, "blue"));
//     players[0].addTile(Tile(3, "black"));
//     players[0].addTile(Tile(4, "blue"));
//     players[0].addTile(Tile(5, "blue"));
//     players[0].addTile(Tile(6, "black"));
//     players[0].addTile(Tile(7, "black"));
//     players[0].addTile(Tile(11, "red"));
//     players[0].addTile(joker); // Adding the determined Joker

//     // Case if there are duplicate tiles 8 8 9 9 10 10 which needs to make two pers
//         // Also okey tile choose to make per with largest number of tiles 
//     // Expected : 8 9 10 , 8 9 10 , 1 2 okey 4 5 (6, 7, joker not per)

//     // Player 2 (14 tiles)
//     players[1].addTile(Tile(1, "red"));
//     players[1].addTile(Tile(2, "red"));
//     players[1].addTile(Tile(3, "red"));
//     players[1].addTile(Tile(4, "red"));
//     players[1].addTile(Tile(4, "black"));
//     players[1].addTile(Tile(4, "yellow"));
//     players[1].addTile(Tile(10, "red"));
//     players[1].addTile(Tile(8, "yellow"));
//     players[1].addTile(Tile(9, "yellow"));
//     players[1].addTile(Tile(10, "yellow"));
//     players[1].addTile(Tile(11, "yellow"));
//     players[1].addTile(Tile(12, "yellow"));
//     players[1].addTile(Tile(13, "yellow"));
//     players[1].addTile(Tile(10, "blue"));

//     // Case if two pers tries to use same tile 4 4 4 and 10 10 10
//     // Expected : 1 2 3 4  , 8 9 10 11 12 13 (4, 4, 4 and 10, 10, 10 not per)

//     // Player 3 (14 tiles)
//     players[2].addTile(Tile(3, "red"));
//     players[2].addTile(Tile(3, "black"));
//     players[2].addTile(Tile(3, "blue"));
//     players[2].addTile(Tile(1, "blue"));
//     players[2].addTile(Tile(2, "blue"));
//     players[2].addTile(Tile(4, "blue"));
//     players[2].addTile(Tile(5, "blue"));
//     players[2].addTile(Tile(4, "blue"));
//     players[2].addTile(Tile(5, "blue"));
//     players[2].addTile(Tile(9, "black"));
//     players[2].addTile(Tile(10, "black"));
//     players[2].addTile(Tile(11, "black"));
//     players[2].addTile(Tile(12, "black"));
//     players[2].addTile(Tile(13, "black"));

//     // Case if three pers tries to use same tile 3, 3, 3 and 3, 4, 5 and 3, 4, 5
//     // Expected : 9 10 11 12 13 , 1 2 3 4 5 (3, 3, 3 and 3, 4, 5 and 3, 4, 5 not per)

//     // Player 4 (14 tiles)
//     players[3].addTile(Tile(1, "red"));
//     players[3].addTile(Tile(1, "yellow"));
//     players[3].addTile(joker); // Adding the determined Joker
//     players[3].addTile(Tile(2, "blue"));
//     players[3].addTile(Tile(3, "blue"));
//     players[3].addTile(Tile(9, "blue"));
//     players[3].addTile(Tile(10, "blue"));
//     players[3].addTile(Tile(8, "yellow"));
//     players[3].addTile(Tile(9, "yellow"));
//     players[3].addTile(Tile(10, "yellow"));
//     players[3].addTile(Tile(11, "red"));
//     players[3].addTile(Tile(11, "red"));
//     players[3].addTile(Tile(13, "red"));
//     players[3].addTile(Tile(13, "yellow"));

//     // Case if there are duplicate more tiles 1 1 5 5 7 7 11 11 13 13 
//         // Çift el gelme durumu
//     // Expected : 1 1 5 5 7 7 11 11 13 13 

//     // Step 3: Display each player's hand and evaluate it
//     for (size_t i = 0; i < players.size(); ++i) {
//         Player& player = players[i];

//         std::cout << "Player " << i + 1 << "'s Hand:\n";
//         player.printHand();
//         std::cout << "\n";

//         // Evaluate and display the player's Pers
//         std::cout << "Player " << i + 1 << "'s Pers:\n";
//         int score = player.evaluateHand();
//         std::cout << "Remaining tile score: " << score << "\n\n";
//     }

//     return 0;
// }
