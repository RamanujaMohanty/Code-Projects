#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>

class Graph {
private:
    int numVertices;
    std::vector<std::vector<std::pair<int, double>>> adjacencyList;

public:
    Graph(int vertices) : numVertices(vertices), adjacencyList(vertices) {}

    void addEdge(int u, int v, double weight) {
        adjacencyList[u].emplace_back(v, weight);
        adjacencyList[v].emplace_back(u, weight); // Since the graph is undirected
    }

    const std::vector<std::pair<int, double>>& neighbors(int u) const {
        return adjacencyList[u];
    }

    int vertices() const {
        return numVertices;
    }
};

class Dijkstra {
public:
    static double shortestPath(const Graph& graph, int start, int end) {
        int n = graph.vertices();
        std::vector<double> dist(n, std::numeric_limits<double>::infinity());
        dist[start] = 0;

        using Node = std::pair<double, int>;
        std::priority_queue<Node, std::vector<Node>, std::greater<>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            auto [currentDist, u] = pq.top();
            pq.pop();

            if (u == end) return currentDist;

            for (const auto& [v, weight] : graph.neighbors(u)) {
                double newDist = currentDist + weight;
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    pq.emplace(newDist, v);
                }
            }
        }

        return std::numeric_limits<double>::infinity(); // No path found
    }
};

class MonteCarloSimulation {
public:
    static Graph generateRandomGraph(int numVertices, double density, double minDistance, double maxDistance) {
        Graph graph(numVertices);
        std::srand(std::time(nullptr));

        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                if ((double)std::rand() / RAND_MAX < density) {
                    double weight = minDistance + (double)std::rand() / RAND_MAX * (maxDistance - minDistance);
                    graph.addEdge(i, j, weight);
                }
            }
        }

        return graph;
    }

    static double averageShortestPath(const Graph& graph, int source) {
        int count = 0;
        double totalDistance = 0;
        
        for (int target = 0; target < graph.vertices(); ++target) {
            if (target == source) continue;

            double distance = Dijkstra::shortestPath(graph, source, target);
            if (distance < std::numeric_limits<double>::infinity()) {
                totalDistance += distance;
                ++count;
            }
        }

        return count > 0 ? totalDistance / count : std::numeric_limits<double>::infinity();
    }
};

int main() {
    int numVertices = 50;
    double density1 = 0.2;
    double density2 = 0.4;
    double minDistance = 1.0;
    double maxDistance = 10.0;

    std::cout << "Graph with density 20%:\n";
    Graph graph1 = MonteCarloSimulation::generateRandomGraph(numVertices, density1, minDistance, maxDistance);
    double avgPath1 = MonteCarloSimulation::averageShortestPath(graph1, 0);
    std::cout << "Average shortest path: " << avgPath1 << "\n\n";

    std::cout << "Graph with density 40%:\n";
    Graph graph2 = MonteCarloSimulation::generateRandomGraph(numVertices, density2, minDistance, maxDistance);
    double avgPath2 = MonteCarloSimulation::averageShortestPath(graph2, 0);
    std::cout << "Average shortest path: " << avgPath2 << "\n";

    return 0;
}
