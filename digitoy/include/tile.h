#ifndef TILE_H
#define TILE_H

#include <string>
#include <iostream>

class Tile {
private:
    int number; // 1 to 13
    std::string color; // "red", "black", "blue", "yellow"
    bool isJoker;
    bool isFakeJoker;
    int PerCount;
    bool committed = false;


public:
    // Constructor
    Tile(int num = 0, std::string col = "", bool joker = false, bool fakeJoker = false,int PerCount=0);

    // Getters
    int getNumber() const;
    int getPerCount() const;
    std::string getColor() const;
    bool getIsJoker() const;
    bool getIsFakeJoker() const;

    // Setters
    void setNumber(int num);
    void setPerCount(int num);
    void setColor(std::string col);
    void setIsJoker(bool joker);
    void setIsFakeJoker(bool fakeJoker);

    // Print tile details
    void print() const;
    void setCommitted(bool value);
    bool isCommitted() const ;
    void incrementPerCount();

   
};

#endif // TILE_H