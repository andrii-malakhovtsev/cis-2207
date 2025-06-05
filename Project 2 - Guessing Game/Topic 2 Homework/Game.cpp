#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Game::Game(int size, int maxRange) : size(size), maxRange(maxRange) {
    randomNumbers = new int[size];
    guesses = new int[size];
    srand(time(0));
}

Game::~Game() {
    delete[] randomNumbers;
    delete[] guesses;
}

void Game::generateRandomNumbers() {
    for (int i = 0; i < size; ++i) {
        randomNumbers[i] = rand() % maxRange + 1;
    }
}

bool Game::isCorrectGuess(int value) const {
    for (int i = 0; i < size; ++i) {
        if (randomNumbers[i] == value) {
            return true;
        }
    }
    return false;
}

void Game::getGuesses() {
    cout << "Enter your guesses for the " << size << " integers in the range from 1 to " << maxRange << ": ";

    for (int i = 0; i < size; ++i) {
        cin >> guesses[i];
    }
}

void Game::play() {
    generateRandomNumbers();

    bool correct = false;
    while (!correct) {
        getGuesses();

        int correctCount = 0;
        for (int i = 0; i < size; ++i) {
            if (isCorrectGuess(guesses[i])) {
                ++correctCount;
            }
        }

        if (correctCount == size) {
            cout << "You are correct!" << endl;
            correct = true;
        }
        else {
            cout << correctCount << " of your guesses are correct. Guess again." << endl;
        }
    }
}
