// Andrii Malakhovtsev
// CIS 2207 501
// 04.27.2025
// Graph Representation
// Solution 1

#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "GraphInterface.h"

#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <stdexcept>

using namespace std;

template<class LabelType>
class AdjacencyMatrixGraph : public GraphInterface<LabelType> {
private:
	vector<vector<int>> matrix;
	vector<LabelType> vertices;
	unordered_map<LabelType, int> vertexIndexMap;
	bool directed;
	bool weighted;
	int edgeCount;

	int getOrAddVertexIndex(LabelType vertex) {
		if (vertexIndexMap.find(vertex) == vertexIndexMap.end()) {
			int newIndex = vertices.size();
			vertices.push_back(vertex);
			vertexIndexMap[vertex] = newIndex;

			matrix.push_back(vector<int>(newIndex, 0));
			for (auto& row : matrix) {
				row.push_back(0);
			}
			return newIndex;
		}
		return vertexIndexMap[vertex];
	}

public:
	AdjacencyMatrixGraph(bool isDirected = false, bool isWeighted = false)
		: directed(isDirected), weighted(isWeighted), edgeCount(0) {
	}

	int getNumVertices() const override {
		return vertices.size();
	}

	int getNumEdges() const override {
		return edgeCount;
	}

	bool add(LabelType start, LabelType end, int edgeWeight = 1) override {
		if (!weighted && edgeWeight != 1) {
			throw invalid_argument("Unweighted graphs must have edge weight of 1");
		}

		int startIdx = getOrAddVertexIndex(start);
		int endIdx = getOrAddVertexIndex(end);

		if (matrix[startIdx][endIdx] != 0) {
			return false;
		}

		matrix[startIdx][endIdx] = edgeWeight;
		if (!directed) {
			matrix[endIdx][startIdx] = edgeWeight;
		}
		edgeCount++;
		return true;
	}

	bool remove(LabelType start, LabelType end) override {
		if (vertexIndexMap.find(start) == vertexIndexMap.end() ||
			vertexIndexMap.find(end) == vertexIndexMap.end()) {
			return false;
		}

		int startIdx = vertexIndexMap[start];
		int endIdx = vertexIndexMap[end];

		if (matrix[startIdx][endIdx] == 0) {
			return false;
		}

		matrix[startIdx][endIdx] = 0;
		if (!directed) {
			matrix[endIdx][startIdx] = 0;
		}
		edgeCount--;
		return true;
	}

	// Appendix F Algorithm Verification
	// Step 1: Initialization
	// Step 2: Maintenance
	// Step 3: Correctness
	
	// getEdgeWeight returns the weight of the edge from start to end.
	// If either start or end vertex does not exist, it returns 0.

	// Loop Invariant:
	// At every step, the function correctly checks vertex existence
	// and retrieves the correct matrix value if both vertices exist.

	int getEdgeWeight(LabelType start, LabelType end) const override {
		// Step 1: Verify that both start and end vertices exist.
		if (vertexIndexMap.find(start) == vertexIndexMap.end() ||
			vertexIndexMap.find(end) == vertexIndexMap.end()) {
			// If either vertex is missing, there is no edge, so return 0.
			return 0;
		}

		// Step 2: Retrieve the indexes of the start and end vertices.
		int startIdx = vertexIndexMap.at(start);
		int endIdx = vertexIndexMap.at(end);

		// Step 3: Return the weight from the adjacency matrix.
		return matrix[startIdx][endIdx];
	}


	void depthFirstTraversal(LabelType start, void visit(LabelType&)) override {
		if (vertexIndexMap.find(start) == vertexIndexMap.end()) return;

		// Step 1: Initialization
		// Initialize visited array, stack and start node.
		vector<bool> visited(vertices.size(), false);

		stack<int> stack;

		int startIdx = vertexIndexMap[start];
		stack.push(startIdx);

		// Invariant:
		// At the start of each loop iteration:
		// - All nodes that have been visited are reachable from the start node (no unreachable nodes).
		// - Every node currently on the stack has been discovered but not yet fully explored (no need for shortest path).
		// - No node is added to the stack if it has already been visited.
		visit(vertices[startIdx]);  // Visit the start node

		while (!stack.empty()) {
			int currentIdx = stack.top();  // Get the node to explore
			stack.pop();

			// Step 2: Maintenance
			// If we haven't visited this node yet, mark it as visited and explore its neighbors
			if (!visited[currentIdx]) {
				LabelType vertex = vertices[currentIdx];
				visit(vertex);  // Visit the node
				visited[currentIdx] = true;

				// Invariant: After visiting the node, its neighbors are reachable from it
				// We push neighbors onto the stack for future exploration
				for (int neighborIdx = 0; neighborIdx < vertices.size(); ++neighborIdx) {
					if (matrix[currentIdx][neighborIdx] != 0 && !visited[neighborIdx]) {
						stack.push(neighborIdx);
					}
				}
			}
		}
		// Step 3: Correctness
		// At termination all reachable nodes have been visited, and the invariant holds
		// The stack is empty, so the traversal has explored all reachable nodes.
	}


	void breadthFirstTraversal(LabelType start, void visit(LabelType&)) override {
		if (vertexIndexMap.find(start) == vertexIndexMap.end()) return;

		// Step 1: Initialization
		// Initialize visited array, queue, and start node.
		vector<bool> visited(vertices.size(), false);

		queue<int> queue;

		int startIdx = vertexIndexMap[start];
		queue.push(startIdx);
		visited[startIdx] = true;

		// Invariant:
		// At the start of each loop iteration:
		// - All nodes that have been visited are reachable from start (no unreachable nodes).
		// - All nodes in the queue have been discovered but not yet fully explored (future shortest path).
		// - No node is added to the queue twice.
		visit(vertices[startIdx]);  // Visit the start node

		while (!queue.empty()) {
			int currentIdx = queue.front();  // Get the node to explore (make a step)
			queue.pop();

			// Step 2: Maintenance
			// For each unvisited neighbor of the current node, mark as visited and enqueue
			for (int neighborIdx = 0; neighborIdx < vertices.size(); ++neighborIdx) { // Index under the graph size
				if (matrix[currentIdx][neighborIdx] != 0 && !visited[neighborIdx]) { // Reachable index + not visited
					queue.push(neighborIdx); // Enqueue the neighbor, queue ensures the shortest path because of natural sort
					visited[neighborIdx] = true; // Mark as visited
					visit(vertices[neighborIdx]);  // Visit the node
				}
			}
		}

		// Step 3: Correctness
		// At termination all reachable nodes from the start node have been visited.
		// The queue is empty and the traversal has explored all reachable nodes by the SHORTEST path.
	}
};

#endif