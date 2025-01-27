// Andrii Malakhovtsev
// CIS 2207 501
// 01.26.2025
// Guessing Game

#ifndef GAME_H
#define GAME_H

using namespace std;

class Game {
private:
    int* randomNumbers;
    int* guesses;
    int size;
    int maxRange;

    void generateRandomNumbers();
    bool isCorrectGuess(int value) const;

public:
    Game(int size, int maxRange);
    ~Game();
    void getGuesses();
    void play();
};

#endif
