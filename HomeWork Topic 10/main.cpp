// Andrii Malakhovtsev
// CIS 2207 501
// 04.20.2025
// Graph Representation

#include <iostream>
#include <string>

#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"

using namespace std;

// Problem 1: Adjacency Matrix for the Graph
// Problem 2: Adjacency List for the Graph
// Problem 3: Directed/Undirected and Weighted/Unweighted Graph

void visit(string& label) {
    cout << label << " ";
}

int main() {
    cout << "Choose Graph Representation (1 = List, 2 = Matrix): ";
    int choice;
    cin >> choice;

    cout << "Is the graph directed? (1 = Yes, 0 = No): ";
    bool isDirected;
    cin >> isDirected;

    cout << "Is the graph weighted? (1 = Yes, 0 = No): ";
    bool isWeighted;
    cin >> isWeighted;

    GraphInterface<string>* graph = nullptr;

    if (choice == 1) {
        graph = new AdjacencyListGraph<string>(isDirected, isWeighted);
    }
    else {
        graph = new AdjacencyMatrixGraph<string>(isDirected, isWeighted);
    }

    while (true) {
        cout << "\n--- Menu ---\n"
            << "1. Add Edge\n"
            << "2. Remove Edge\n"
            << "3. Get Edge Weight\n"
            << "4. Depths First Traversal\n"
            << "5. Breadth First Traversal\n"
            << "6. Show Vertex and Edge Count\n"
            << "0. Exit\n"
            << "Enter choice: ";

        int cmd;
        cin >> cmd;

        if (cmd == 0) break;

        string start, end;
        int weight;

        switch (cmd) {
        case 1:
            cout << "Enter start vertex: ";
            cin >> start;
            cout << "Enter end vertex: ";
            cin >> end;
            if (isWeighted) {
                cout << "Enter weight: ";
                cin >> weight;
            }
            else {
                weight = 1;
            }
            if (graph->add(start, end, weight))
                cout << "Edge added.\n";
            else
                cout << "Edge already exists.\n";
            break;
        case 2:
            cout << "Enter start vertex: ";
            cin >> start;
            cout << "Enter end vertex: ";
            cin >> end;
            if (graph->remove(start, end))
                cout << "Edge removed.\n";
            else
                cout << "Edge not found.\n";
            break;
        case 3:
            cout << "Enter start vertex: ";
            cin >> start;
            cout << "Enter end vertex: ";
            cin >> end;
            cout << "Weight: " << graph->getEdgeWeight(start, end) << endl;
            break;
        case 4:
            cout << "Enter starting vertex for DFS: ";
            cin >> start;
            graph->depthFirstTraversal(start, visit);
            cout << endl;
            break;
        case 5:
            cout << "Enter starting vertex for BFS: ";
            cin >> start;
            graph->breadthFirstTraversal(start, visit);
            cout << endl;
            break;
        case 6:
            cout << "Vertices: " << graph->getNumVertices() << ", Edges: " << graph->getNumEdges() << endl;
            break;
        default:
            cout << "Invalid option.\n";
            break;
        }
    }

    delete graph;
    return 0;
}
