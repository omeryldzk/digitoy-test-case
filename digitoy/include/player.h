#ifndef PLAYER_H
#define PLAYER_H

#include "tile.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <functional>


class Player {
private:
    std::vector<Tile> hand; // Oyuncunun elindeki taşlar
    std::vector<std::vector<Tile*>> pers; // Stores all possible sets and runs // muhtemel tüm perler
    std::vector<std::vector<Tile*>> final_pers; // Stores the final sets and runs // Düz perler
    std::vector<std::vector<Tile*>> duplicate_pers; // Stores the duplicate sets // Çift perler
    int numberOfTilesToWin; // Oyuncunun bitmeye kaç taşı kaldı

    // Sorting and grouping helpers
    // Düz perleri bulmadan önce sorting
    void InsertionSort(std::vector<std::reference_wrapper<Tile>>& tiles);
    // Düz perleri bulur 1 2 3
    void FindRuns(std::vector<std::reference_wrapper<Tile>>& tiles, Tile* joker_1, Tile* joker_2);
    // Düz set perleri bulur 4 4 4
    void FindSets(std::vector<std::reference_wrapper<Tile>>& tiles, Tile* joker_1, Tile* joker_2);
    // Çiftleri bulur
    void FindDuplicatePers();

    

public:
    // Add a tile to the player's hand
    void addTile(const Tile& tile);

    // Get the player's hand and Pers
    std::vector<Tile>& getHand() ;
    std::vector<std::vector<Tile*>> getPers() const;
    void setNumberOfTilesToWin(int number);
    int getNumberOfTilesToWin() const;

    // Print the player's hand and Pers
    void printHand() const;
    void PrintPlayersPers() const;
    void PrintPlayersduplicatePers() const;


    // Find possible sets and runs
    void FindPers();

    // Evaluate the player's hand returns the best score
        // Çift veya düz hangisinde oyunuc bitmeye daha yakınsa onun skorunu döndürür
        // Ayrıca perleri print eder
    int evaluateHand();

};

#endif // PLAYER_H
