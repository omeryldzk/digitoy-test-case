#include "player.h"
#include <functional>
#include <bits/algorithmfwd.h>

// Add a tile to the player's hand
void Player::addTile(const Tile& tile) {
    hand.push_back(tile);
}
// Get the player's hand
std::vector<Tile>& Player::getHand() {
    return hand;
}

// Get the player's Pers
std::vector<std::vector<Tile*>> Player::getPers() const {
    return pers;
}

// Get the player's how many tiles to win
int Player::getNumberOfTilesToWin() const {
    return numberOfTilesToWin;
}

// Get the player's how many tiles to win
void Player::setNumberOfTilesToWin(int number)  {
    numberOfTilesToWin = number;
}

// Print the player's hand
void Player::printHand() const {
    for (const auto& tile : hand) {
        tile.print();
    }
}

// Insertion sort reasonable complexity O(n^2) for max n=13 
void Player::InsertionSort(std::vector<std::reference_wrapper<Tile>>& tiles) {
    for (size_t i = 1; i < tiles.size(); ++i) {
        std::reference_wrapper<Tile> key = tiles[i]; // Keep reference
        int j = i - 1;

        while (j >= 0 && tiles[j].get().getNumber() > key.get().getNumber()) {
            tiles[j + 1] = tiles[j]; // Shift
            --j;
        }
        tiles[j + 1] = key; // Insert at the correct position
    }
}

void Player::FindRuns(std::vector<std::reference_wrapper<Tile>>& tiles, Tile* joker_1, Tile* joker_2) {
    if (tiles.size() < 3) return;
    int joker_flag = 0;
    std::vector<std::reference_wrapper<Tile>> currentRun;

    // Cover edge case when duplicate tiles 8 8 9 9 10 10 
            // creates 2 seperate pers 8 9 10 and 8 9 10
    // Saving duplicate tiles to check if they can be used in another run
    std::vector<std::reference_wrapper<Tile>> duplicateTiles;

    // Check if the current tile is joker
    if(tiles[0].get().getIsJoker() == false)
        currentRun.push_back(tiles[0]);

    for (size_t i = 1; i < tiles.size(); ++i) {
        
        // En son eklenen elaman joker ise perin devamı için jokerden bi önceki elamanın 2 fazlası olması gerekir
        // Örneğin => 2 3 joker 5 durumu 
        if(currentRun.size() > 2){
            if(currentRun.back().get().getIsJoker() == true){
                if ((tiles[i-1].get().getNumber() == currentRun[currentRun.size() - 2].get().getNumber() + 2 )
                    && tiles[i-1].get().getIsJoker() == false) {
                    currentRun.push_back(tiles[i-1]);
                }
                // 2 3 jokerden sonra 5 gelmeme durumu peri kaydet ve current runi clear et
                // Convert reference wrappers to pointers before adding to pers
                std::vector<Tile*> persRun;
                for (auto& tileRef : currentRun) {
                    tileRef.get().incrementPerCount(); 
                    persRun.push_back(&tileRef.get()); // Store as pointer
                }
                pers.push_back(persRun);
                currentRun.clear();
                currentRun.push_back(tiles[i]);
            }
        }
        // Check if the current tile is part of the run
        // Also dont use joker as normal tile
        else if ((tiles[i].get().getNumber() == tiles[i - 1].get().getNumber() + 1 )
         && tiles[i].get().getIsJoker() == false) {
            currentRun.push_back(tiles[i]);
        }

        // 13 -> 1 condition on runs
        // Also dont use joker as normal tile
        else if(((tiles[i].get().getNumber() == 1 ) && (tiles[i - 1].get().getNumber()) == 13)
        && tiles[i].get().getIsJoker() == false){
            currentRun.push_back(tiles[i]);
        }

        // Saving duplicate tiles to check if they can be used in another run
        else if ((tiles[i].get().getNumber() == tiles[i - 1].get().getNumber())
        && tiles[i].get().getIsJoker() == false) {
            duplicateTiles.push_back(tiles[i]);
        }
        else {
            if (currentRun.size() >= 3) {
                
                // Convert reference wrappers to pointers before adding to pers
                std::vector<Tile*> persRun;
                for (auto& tileRef : currentRun) {
                    tileRef.get().incrementPerCount(); 
                    persRun.push_back(&tileRef.get()); // Store as pointer
                }
                pers.push_back(persRun);
                currentRun.clear();
                currentRun.push_back(tiles[i]);
            }

            // Check if player has joker and can be used in the run
            else if (currentRun.size() == 2) {
                // Check if player has joker
                if(joker_1 != nullptr && joker_flag == 0){ 
                    currentRun.push_back(*joker_1);
                    if(joker_2 != nullptr)
                        joker_flag = 1; 

                }
                else if(joker_2 != nullptr && joker_flag == 1){
                    currentRun.push_back(*joker_2);
                    if(joker_1 != nullptr)
                        joker_flag = 0;
                }
                else{
                    currentRun.clear();
                    currentRun.push_back(tiles[i]);
                }

            }
            // Clear the current run
            else {
                currentRun.clear();
                currentRun.push_back(tiles[i]);
        }
    }
    }

    // Check the last run seperatly because 
    // After the loop ends, there may still be a valid run that has not been processed
    if (currentRun.size() >= 3) {
        std::vector<Tile*> persRun;
        for (auto& tileRef : currentRun) {
            tileRef.get().incrementPerCount();
            persRun.push_back(&tileRef.get());
        }
        pers.push_back(persRun);
    }
    
    currentRun.clear();

    // Check for duplicate tiles that can be used in another run
    if (duplicateTiles.size() >= 3) {

        // First duplicate tile is not used in the previous pers
        currentRun.push_back(duplicateTiles[0]);

        for (size_t i = 1; i < duplicateTiles.size(); ++i) {
            if ((duplicateTiles[i].get().getNumber() == duplicateTiles[i - 1].get().getNumber() + 1) && 
            duplicateTiles[i].get().getIsJoker() == false) {
                currentRun.push_back(duplicateTiles[i]);
            }
            // 13 -> 1 condition on runs
            else if(((duplicateTiles[i].get().getNumber() == 1 ) && (duplicateTiles[i - 1].get().getNumber()) == 13)
            && duplicateTiles[i].get().getIsJoker() == false){
                currentRun.push_back(duplicateTiles[i]);
            }
            // En son eklenen elaman joker ise perin devamı için jokerden bi önceki elamanın 2 fazlası olması gerekir
            else if(currentRun.back().get().getIsJoker() == true){
                if ((duplicateTiles[i-1].get().getNumber() == currentRun[currentRun.size() - 2].get().getNumber() + 2 )
                    && duplicateTiles[i-1].get().getIsJoker() == false) {
                    currentRun.push_back(duplicateTiles[i-1]);
            }
            }
            else {
                if (currentRun.size() >= 3) {
                
                    // Convert reference wrappers to pointers before adding to pers
                    std::vector<Tile*> persRun;
                    for (auto& tileRef : currentRun) {
                        tileRef.get().incrementPerCount(); 
                        persRun.push_back(&tileRef.get()); // Store as pointer
                    }
                    pers.push_back(persRun);

                    // Clear the current run
                    currentRun.clear();
                    currentRun.push_back(tiles[i]);
                }

                // Check if player has joker and can be used in the run
                // Check if player has joker and can be used in the run
                else if (currentRun.size() == 2) {
                    // Check if player has joker
                    if(joker_1 != nullptr && joker_flag == 0){ 
                        currentRun.push_back(*joker_1);
                        // eğer tek jokeri varsa flagi değiştirmemize gerek yok
                        if(joker_2 != nullptr)
                            joker_flag = 1; 

                    }
                    else if(joker_2 != nullptr && joker_flag == 1){
                        currentRun.push_back(*joker_2);
                        if(joker_1 != nullptr)
                            joker_flag = 0;
                    }
                    else{
                        currentRun.clear();
                        currentRun.push_back(tiles[i]);
                    }

                }
                else {

                    // Clear the current run
                    currentRun.clear();
                    currentRun.push_back(tiles[i]);
                
            }
            }
    }

    // Check the last run seperatly because 
    // After the loop ends, there may still be a valid run that has not been processed

    if (currentRun.size() >= 3) {
        std::vector<Tile*> persRun;
        for (auto& tileRef : currentRun) {
            tileRef.get().incrementPerCount();
            persRun.push_back(&tileRef.get());
        }
        pers.push_back(persRun);
        }

}
}

void Player::FindSets(std::vector<std::reference_wrapper<Tile>>& tiles, Tile* joker_1, Tile* joker_2) {
    if (tiles.size() < 3) return;
    int joker_flag = 0;

    std::map<int, std::vector<std::reference_wrapper<Tile>>> numberGroups;

    // Group tiles by number
    for (auto& tile : tiles) {

        // Tries to find the number group if not exists then creates a new group
        // I did this to explicitly create vectors before adding reference wrappers
        int number = tile.get().getNumber();
        auto it = numberGroups.find(number);
        if (it == numberGroups.end()) {

            // Create an empty vector and then add the reference
                // So if number group doesnt exist in tiles we dont need to create new group

            // reference_wrapper kullandığım için sayı grubunu sadece varlığından emin olduktan sonra
                // yeni bir reference_wrapper objesi oluştuyorum
                // örneğin 3 sayısı hiç yoksa ve ben boş yere bir reference_wrapper objesi oluşturmuyorum
            std::vector<std::reference_wrapper<Tile>> newGroup;
            newGroup.push_back(tile);
            numberGroups.insert({number, newGroup});
        } else {

            // Add to existing group
            it->second.push_back(tile);
        }
    }

    for (auto& [number, group] : numberGroups) {
        if (group.size() >= 2) {

            std::map<std::string, size_t> bestTileIndices;
            std::map<std::string, size_t> dupTileIndices;

            // if there are duplicate colors, store the best and the duplicate
            // best is the one with the lowest perCount 
            // which is the number of times it has been used in anather pers

            // Bu kısımda eğer aynı renkten 2 tane varsa ve
            for (size_t i = 0; i < group.size(); ++i) {
                const std::string& color = group[i].get().getColor();
                auto it = bestTileIndices.find(color);

                // no duplicate color found
                if (it == bestTileIndices.end()) {
                    bestTileIndices[color] = i;
                } 
                else {
                        // if the current tile has a lower perCount, it is the new best
                        // Bu kısmın amacı eğer aynı renkten 2 tane varsa ve 
                            // biri önceden perde kullanılmış ise önce kullanılmamış olanı kullanmak
                    if (group[i].get().getPerCount() < group[it->second].get().getPerCount()) {
                        dupTileIndices[color] = it->second;
                        bestTileIndices[color] = i;
                    } else {
                        dupTileIndices[color] = i;
                        bestTileIndices[color] = it->second;

                    }
                }
            }

            // Store valid sets if there are at least 3 unique colors
            if (bestTileIndices.size() >= 3) {
                std::vector<Tile*> validSet;
                for (auto& [color, index] : bestTileIndices) {
                    validSet.push_back(&group[index].get());
                    group[index].get().incrementPerCount();
                }
                pers.push_back(validSet);
            }

            // Check if player has joker and can be used in the set
            // Tek Okey durumu
            else if(bestTileIndices.size() == 2 && (joker_1 != nullptr) && (joker_flag == 0)){
                std::vector<Tile*> validSet;
                for (auto& [color, index] : bestTileIndices) {
                    validSet.push_back(&group[index].get());
                    group[index].get().incrementPerCount();
                    if(joker_2 != nullptr)
                        joker_flag = 1;
                }
                validSet.push_back(joker_1);
                joker_1->incrementPerCount();
                pers.push_back(validSet);
            }

            // Çift Okey durumu
            else if(bestTileIndices.size() == 2 && (joker_2 != nullptr) && (joker_flag == 1)){
                std::vector<Tile*> validSet;
                for (auto& [color, index] : bestTileIndices) {
                    validSet.push_back(&group[index].get());
                    group[index].get().incrementPerCount();
                    if (joker_1 != nullptr)
                        joker_flag = 0;
                }
                validSet.push_back(joker_1);
                joker_2->incrementPerCount();
                pers.push_back(validSet);
            }



            // Store valid sets if there are at least 3 colors with duplicates
            if (dupTileIndices.size() >= 3) {
                std::vector<Tile*> validSet;
                for (auto& [color, index] : dupTileIndices) {
                    validSet.push_back(&group[index].get());
                    group[index].get().incrementPerCount();
                }
                pers.push_back(validSet);
            }
            // Tek okey durumu 
            else if(dupTileIndices.size() == 2 && (joker_1 != nullptr) && (joker_flag == 0)){
                std::vector<Tile*> validSet;
                for (auto& [color, index] : dupTileIndices) {
                    validSet.push_back(&group[index].get());
                    group[index].get().incrementPerCount();
                    if(joker_2 != nullptr)
                        joker_flag = 1;
                }
                validSet.push_back(joker_1);
                joker_1->incrementPerCount();
                pers.push_back(validSet);
            }
            // Çift okey durumu 
            else if(dupTileIndices.size() == 2 && (joker_2 != nullptr) && (joker_flag == 1)){
                std::vector<Tile*> validSet;
                for (auto& [color, index] : dupTileIndices) {
                    validSet.push_back(&group[index].get());
                    group[index].get().incrementPerCount();
                    if (joker_1 != nullptr)
                        joker_flag = 0;
                }
                validSet.push_back(joker_1);
                joker_2->incrementPerCount();
                pers.push_back(validSet);
            }

        }
        }
}

void Player::FindPers() {
    pers.clear(); // Clear previous Pers

    std::map<std::string, std::vector<std::reference_wrapper<Tile>>> colorGroups;
    std::vector<std::reference_wrapper<Tile>> tile_refs;

    Tile* joker_1 = nullptr;
    Tile* joker_2 = nullptr;
    int jokerFlag = 0;

    for (auto& tile : hand) {
        const std::string& color = tile.getColor();

        // Tries to find the color group if not exists then creates a new group
        // I did this to explicitly create vectors before adding reference wrappers

        auto it = colorGroups.find(color);
        if (it == colorGroups.end()) {
            std::vector<std::reference_wrapper<Tile>> newGroup;
            newGroup.push_back(std::ref(tile));
            colorGroups.insert({color, newGroup});
        } else {
            it->second.push_back(std::ref(tile));
        }
        // Check if user has joker
        if (tile.getIsJoker() && jokerFlag == 0) {
            jokerFlag++;
            joker_1 = &tile;
            continue;
        }
        // Check if user has 2 joker
        if (tile.getIsJoker() && jokerFlag == 1) {
            jokerFlag++;
            joker_2 = &tile;
        }
        tile_refs.push_back(std::ref(tile));
    }

    // Find runs for each color group
    for (auto& [color, tiles] : colorGroups) {
        // Sort the tiles by number 
        // Cover edge case where 13 -> 1
        // Cover edge case when duplicate tiles 8 8 9 10 only uses 8 9 10 
        // Cover edge case when duplicate tiles 8 8 9 9 10 10 
            // creates 2 seperate pers 8 9 10 and 8 9 10
        // Cover edge cases with joker
        // Okeyin geldiği durumları da içerir. Önce küçükten büyüğe sıralar
            //  Ardından FindRuns methodu ile perleri bulur
        InsertionSort(tiles);
        FindRuns(tiles, joker_1, joker_2);

    }
    // Find sets for the entire hand with 3 or 4 tiles of the same number
    // Cover edge case when duplicate tiles for same color
        // First creates 1 per without using duplicate one 
            // duplicate one is with the same color and number but higher perCount
            // which means can be used in another per
        // Then tries to create another per using the duplicate one 
    // Okeyin geldiği durumları da içerir. tile_refs taşların referanslarını içeren
        // reference wrapper vektörüdür

    FindSets(tile_refs, joker_1, joker_2);
}

void Player::PrintPlayersPers() const {
    int number = 0;
    for (const auto& per : final_pers) {
        std::cout << "Düz Pers " << number << ":\n";
        for (const auto& tile : per) {
            tile->print();
        }
        std::cout << "\n";
        number++;
    }
}

void Player::PrintPlayersduplicatePers() const {
    int number = 0;
    for (const auto& per : duplicate_pers) {
        std::cout << "Çift Pers " << number << ":\n";
        for (const auto& tile : per) {
            tile->print();
        }
        std::cout << "\n";
        number++;
    }
}

void Player::FindDuplicatePers() {
    // Clear previous duplicate pers
    duplicate_pers.clear();
    
    // Group tiles by color and number
    std::map<std::pair<std::string, int>, std::vector<Tile*>> duplicate_groups;
    
    // First, group tiles by color and number
    for (auto& tile : hand) {
        if (!tile.getIsJoker()) {  // Skip jokers for duplicate matching
            std::pair<std::string, int> key = {tile.getColor(), tile.getNumber()};
            duplicate_groups[key].push_back(&tile);
        }
    }
    // Find duplicates (groups with size >= 2)
    for (const auto& [key, tiles] : duplicate_groups) {
        if (tiles.size() >= 2) {
            std::vector<Tile*> duplicate_per;
            for (auto* tile : tiles) {
                duplicate_per.push_back(tile);
            }
            // Add this per to our duplicate pers list
            duplicate_pers.push_back(duplicate_per);
        }
    }
}

int Player::evaluateHand() {
    // Clear previous state and find all potential pers
    // Change fake_jokers numeric value to jokers numeric value
    FindPers();
    
    // Clear the final pers container
    final_pers.clear();
    
    // First pass: Find pers where all tiles are only used once
    // These are definite candidates for the final solution
    for (const auto& per : pers) {
        bool allTilesUnique = true;
        for (const auto& tile : per) {
            if (tile->getPerCount() > 1) {
                allTilesUnique = false;
                break;
            }
        }
        if (allTilesUnique) {
            final_pers.push_back(per);
            // Mark these tiles as "committed" to a final per
            for (auto* tile : per) {
                tile->setCommitted(true);
            }
        }
    }
    
    // Second pass: For tiles used in multiple pers, i made a greedy choice
    // Sort pers by length (longer pers are potentially more valuable)
    // Need index for sorting 
    // persWithIndices keeps pair of index and pointer to pers (pers are pointers to tiles)
        
    std::vector<std::pair<int, const std::vector<Tile*>*>> persWithIndices;
    for (size_t i = 0; i < pers.size(); ++i) {
        persWithIndices.push_back({i, &pers[i]});
    }
    
    // Sort by per size (descending)
    std::sort(persWithIndices.begin(), persWithIndices.end(), 
        [](const auto& a, const auto& b) {
            return a.second->size() > b.second->size();
        });
    
    // Try to add pers that don't conflict with already committed tiles
    for (const auto& [idx, perPtr] : persWithIndices) {
        const auto& per = *perPtr;
        bool canAdd = true;
        
        // Check if any tile in this per is already committed
        for (const auto& tile : per) {
            if (tile->isCommitted()) {
                canAdd = false;
                break;
            }
        }
        
        if (canAdd) {
            final_pers.push_back(per);
            // Mark these tiles as committed
            for (auto* tile : per) {
                tile->setCommitted(true);
            }
        }
    }
    
    // Calculate finals_per score: sum of number of tiles not used in any final_pers
    int per_score = 0;
    for (const auto& tile : hand) {
        if (tile.isCommitted()) {
            per_score++; 
        }
    }

    per_score = hand.size() - per_score;


    FindDuplicatePers();
    // Calculate duplicate_pers score: sum of number of tiles not used in any duplicate_pers
    // find number of jokers of player
    int joker_count = 0;
    for (const auto& tile : hand) {
        if (tile.getIsJoker()) {
            joker_count++;
            // Eğer okey boştaysa score 2 azalt
            if(tile.isCommitted() == false){
                per_score -= 2;
            }
        }
    }
    int dup_score;
    // Eğer oyuncu elinde joker varsa 1 çift daha ekleyebilir onu duplicate_perse kaydetmiyorum
        // Ancak score hesaplamasında kullanıyorum
    dup_score = hand.size() - duplicate_pers.size() * 2 - joker_count * 2;

    if(per_score < dup_score){
        PrintPlayersPers();
        return per_score;
    }
    else{
        PrintPlayersduplicatePers();
        return dup_score;
    }

}