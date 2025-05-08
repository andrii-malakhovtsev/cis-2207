// Andrii Malakhovtsev
// CIS 2207 501
// 05.06.2025
// Final Project - Binary Tree Comparison

#include <iostream>
#include <string>

#include "BinarySearchTree.h"

using namespace std;

void buildTreeFromInput(BinarySearchTree<string>& tree);
void compareTrees();
void showMenu();

int main() {
    showMenu();
    cout << "Exiting...\n";
    return 0;
}

void buildTreeFromInput(BinarySearchTree<string>& tree) {
    cout << "Enter items to insert in the tree (type 'done' to finish):\n";
    while (true) {
        string input;
        cout << "> ";
        getline(cin, input);

        if (input == "done") {
            break;
        }

        if (!input.empty()) {
            tree.add(input);
            cout << "Added: " << input << endl;
        }
    }
}

void compareTrees() {
    BinarySearchTree<string> tree1, tree2;

    cout << "\n=== Building First Tree ===\n";
    buildTreeFromInput(tree1);

    cout << "\n=== Building Second Tree ===\n";
    buildTreeFromInput(tree2);

    cout << "\n=== Result ===\n";
    if (tree1.isSameTree(tree2)) {
        cout << "The trees are EQUIVALENT\n";
    }
    else {
        cout << "The trees are DIFFERENT\n";
    }
}

void showMenu() {
    while (true) {
        cout << "\n=== Binary Tree Comparator | Menu ===\n"
            << "1. Compare two trees\n"
            << "2. Exit\n"
            << "Choose an option: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            compareTrees();
        }
        else if (choice == "2") {
            break;
        }
        else {
            cout << "Invalid option. Please try again.\n";
        }
    }
}