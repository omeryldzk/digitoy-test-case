#include "tile.h"

Tile::Tile(int num, std::string col, bool joker, bool fakeJoker, int PerCount)
    : number(num), color(col), isJoker(joker), isFakeJoker(fakeJoker), PerCount(PerCount) {}


// Getters
int Tile::getNumber() const {
    return number;
}

std::string Tile::getColor() const {
    return color;
}

void Tile::setCommitted(bool value){
    committed = value;
}

bool Tile::isCommitted() const {
    return committed;
}

bool Tile::getIsJoker() const {
    return isJoker;
}

bool Tile::getIsFakeJoker() const {
    return isFakeJoker;
}


int Tile::getPerCount() const {
    return PerCount;
}

// Setters
void Tile::setNumber(int num) {
    number = num;
}

void Tile::setColor(std::string col) {
    color = col;
}

void Tile::setIsJoker(bool joker) {
    isJoker = joker;
}

void Tile::setIsFakeJoker(bool fakeJoker) {
    isFakeJoker = fakeJoker;
}

void Tile::setPerCount(int PerCount) {
    this->PerCount = PerCount; 
}


// Print tile details
void Tile::print() const {
    std::cout << "Tile: " << color << " " << number;
    if (isJoker) std::cout << " (Joker)";
    if (isFakeJoker) std::cout << " (Fake Joker)";
    std::cout << "\n";
}

 // Increment PerCount
void Tile::incrementPerCount() {
    PerCount++;
}