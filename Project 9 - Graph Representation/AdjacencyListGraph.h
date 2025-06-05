// Solution 2

#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphInterface.h"

#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <stdexcept>

using namespace std;

template<class LabelType>
class AdjacencyListGraph : public GraphInterface<LabelType> {
private:
    struct Edge {
        int targetIndex;
        int weight;
        Edge(int t, int w) : targetIndex(t), weight(w) {}
    };

    vector<vector<Edge>> adjacencyList;
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
            adjacencyList.emplace_back();
            return newIndex;
        }
        return vertexIndexMap[vertex];
    }

public:
    AdjacencyListGraph(bool isDirected = false, bool isWeighted = false)
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

        for (const Edge& edge : adjacencyList[startIdx]) {
            if (edge.targetIndex == endIdx) {
                return false;
            }
        }

        adjacencyList[startIdx].emplace_back(endIdx, edgeWeight);

        if (!directed) {
            adjacencyList[endIdx].emplace_back(startIdx, edgeWeight);
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
        bool removed = false;

        auto& startEdges = adjacencyList[startIdx];
        for (auto it = startEdges.begin(); it != startEdges.end(); ++it) {
            if (it->targetIndex == endIdx) {
                startEdges.erase(it);
                removed = true;
                break;
            }
        }

        if (removed) {
            if (!directed) {
                auto& endEdges = adjacencyList[endIdx];
                for (auto it = endEdges.begin(); it != endEdges.end(); ++it) {
                    if (it->targetIndex == startIdx) {
                        endEdges.erase(it);
                        break;
                    }
                }
            }
            edgeCount--;
            return true;
        }
        return false;
    }

    int getEdgeWeight(LabelType start, LabelType end) const override {
        if (vertexIndexMap.find(start) == vertexIndexMap.end() ||
            vertexIndexMap.find(end) == vertexIndexMap.end()) {
            return 0;
        }

        int startIdx = vertexIndexMap.at(start);
        int endIdx = vertexIndexMap.at(end);

        for (const Edge& edge : adjacencyList[startIdx]) {
            if (edge.targetIndex == endIdx) {
                return edge.weight;
            }
        }
        return 0;
    }

    void depthFirstTraversal(LabelType start, void visit(LabelType&)) override {
        if (vertexIndexMap.find(start) == vertexIndexMap.end()) return;

        vector<bool> visited(vertices.size(), false);
        stack<int> stack;
        int startIdx = vertexIndexMap[start];
        stack.push(startIdx);

        while (!stack.empty()) {
            int currentIdx = stack.top();
            stack.pop();

            if (!visited[currentIdx]) {
                LabelType vertex = vertices[currentIdx];
                visit(vertex);
                visited[currentIdx] = true;

                for (const Edge& edge : adjacencyList[currentIdx]) {
                    if (!visited[edge.targetIndex]) {
                        stack.push(edge.targetIndex);
                    }
                }
            }
        }
    }

    void breadthFirstTraversal(LabelType start, void visit(LabelType&)) override {
        if (vertexIndexMap.find(start) == vertexIndexMap.end()) return;

        vector<bool> visited(vertices.size(), false);
        queue<int> queue;
        int startIdx = vertexIndexMap[start];
        queue.push(startIdx);
        visited[startIdx] = true;

        while (!queue.empty()) {
            int currentIdx = queue.front();
            queue.pop();

            LabelType vertex = vertices[currentIdx];
            visit(vertex);

            for (const Edge& edge : adjacencyList[currentIdx]) {
                if (!visited[edge.targetIndex]) {
                    queue.push(edge.targetIndex);
                    visited[edge.targetIndex] = true;
                }
            }
        }
    }
};

#endif