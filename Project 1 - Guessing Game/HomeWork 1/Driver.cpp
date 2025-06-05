#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    int integersNumber, eachIntegerBorder;

    cout << "Enter the Number of Integers (n): ";
    cin >> integersNumber;

    cout << "Enter the Number of Each Integers from 1 to (m): ";
    cin >> eachIntegerBorder;

    Game game(integersNumber, eachIntegerBorder);
    game.play();

    char playAgain;
    cout << "Play again? (y/n): ";
    cin >> playAgain;

    while (playAgain == 'y' || playAgain == 'Y') {
        game.play();
        cout << "Play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "Good-bye!" << endl;
    return 0;
}
