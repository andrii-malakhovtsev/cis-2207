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
