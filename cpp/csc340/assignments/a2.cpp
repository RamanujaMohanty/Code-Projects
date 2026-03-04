#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <limits>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

// Priority Queue ADT Implementation
class PriorityQueue {
private:
    priority_queue<pair<double, int>, vector<pair<double, int>>, 
                   greater<pair<double, int>>> minHeap;
    map<int, double> elementPriorities;
    
public:
    // Constructor
    PriorityQueue() {}
    
    // Insert queue element with priority
    void insert(int element, double priority) {
        minHeap.push(make_pair(priority, element));
        elementPriorities[element] = priority;
    }
    
    // Change priority of queue element
    void changePriority(int element, double newPriority) {
        if (elementPriorities.find(element) != elementPriorities.end()) {
            elementPriorities[element] = newPriority;
            minHeap.push(make_pair(newPriority, element));
        }
    }
    
    // Remove and return minimum priority element
    int minPriority() {
        while (!minHeap.empty()) {
            pair<double, int> top = minHeap.top();
            minHeap.pop();
            
            if (elementPriorities.find(top.second) != elementPriorities.end() &&
                elementPriorities[top.second] == top.first) {
                elementPriorities.erase(top.second);
                return top.second;
            }
        }
        return -1; // Empty queue
    }
    
    // Check if queue contains element
    bool contains(int element) {
        return elementPriorities.find(element) != elementPriorities.end();
    }
    
    // Return top element without removing
    int top() {
        while (!minHeap.empty()) {
            pair<double, int> topElement = minHeap.top();
            if (elementPriorities.find(topElement.second) != elementPriorities.end() &&
                elementPriorities[topElement.second] == topElement.first) {
                return topElement.second;
            }
            minHeap.pop();
        }
        return -1;
    }
    
    // Return queue size
    size_t size() {
        return elementPriorities.size();
    }
    
    // Check if queue is empty
    bool empty() {
        return elementPriorities.empty();
    }
};

// Graph ADT Implementation
class Graph {
private:
    int numVertices;
    vector<vector<pair<int, double>>> adjacencyList;
    vector<double> nodeValues;
    mutable random_device rd;
    mutable mt19937 gen;
    
public:
    // Constructors
    Graph() : numVertices(0), gen(rd()) {}
    
    Graph(int vertices) : numVertices(vertices), gen(rd()) {
        adjacencyList.resize(vertices);
        nodeValues.resize(vertices, 0.0);
    }
    
    Graph(int vertices, double density, double minDistance, double maxDistance) 
        : numVertices(vertices), gen(rd()) {
        adjacencyList.resize(vertices);
        nodeValues.resize(vertices, 0.0);
        generateRandomGraph(density, minDistance, maxDistance);
    }
    
    // Interface methods as specified
    int V() const { return numVertices; }
    
    int E() const {
        int edgeCount = 0;
        for (int i = 0; i < numVertices; i++) {
            edgeCount += adjacencyList[i].size();
        }
        return edgeCount / 2; // Undirected graph
    }
    
    bool adjacent(int x, int y) const {
        if (x < 0 || x >= numVertices || y < 0 || y >= numVertices) return false;
        
        for (const auto& edge : adjacencyList[x]) {
            if (edge.first == y) return true;
        }
        return false;
    }
    
    vector<int> neighbors(int x) const {
        vector<int> result;
        if (x >= 0 && x < numVertices) {
            for (const auto& edge : adjacencyList[x]) {
                result.push_back(edge.first);
            }
        }
        return result;
    }
    
    void add(int x, int y, double weight = 1.0) {
        if (x >= 0 && x < numVertices && y >= 0 && y < numVertices && x != y) {
            if (!adjacent(x, y)) {
                adjacencyList[x].push_back(make_pair(y, weight));
                adjacencyList[y].push_back(make_pair(x, weight));
            }
        }
    }
    
    void deleteEdge(int x, int y) {
        if (x >= 0 && x < numVertices && y >= 0 && y < numVertices) {
            adjacencyList[x].erase(
                remove_if(adjacencyList[x].begin(), adjacencyList[x].end(),
                         [y](const pair<int, double>& edge) { return edge.first == y; }),
                adjacencyList[x].end());
            adjacencyList[y].erase(
                remove_if(adjacencyList[y].begin(), adjacencyList[y].end(),
                         [x](const pair<int, double>& edge) { return edge.first == x; }),
                adjacencyList[y].end());
        }
    }
    
    double getNodeValue(int x) const {
        return (x >= 0 && x < numVertices) ? nodeValues[x] : 0.0;
    }
    
    void setNodeValue(int x, double value) {
        if (x >= 0 && x < numVertices) {
            nodeValues[x] = value;
        }
    }
    
    double getEdgeValue(int x, int y) const {
        if (x >= 0 && x < numVertices && y >= 0 && y < numVertices) {
            for (const auto& edge : adjacencyList[x]) {
                if (edge.first == y) return edge.second;
            }
        }
        return numeric_limits<double>::infinity();
    }
    
    void setEdgeValue(int x, int y, double value) {
        if (x >= 0 && x < numVertices && y >= 0 && y < numVertices) {
            for (auto& edge : adjacencyList[x]) {
                if (edge.first == y) {
                    edge.second = value;
                    break;
                }
            }
            for (auto& edge : adjacencyList[y]) {
                if (edge.first == x) {
                    edge.second = value;
                    break;
                }
            }
        }
    }
    
    // Random graph generation
    void generateRandomGraph(double density, double minDistance, double maxDistance) {
        uniform_real_distribution<double> probabilityDist(0.0, 1.0);
        uniform_real_distribution<double> weightDist(minDistance, maxDistance);
        
        // Clear existing edges
        for (int i = 0; i < numVertices; i++) {
            adjacencyList[i].clear();
        }
        
        // Generate edges based on density probability
        for (int i = 0; i < numVertices; i++) {
            for (int j = i + 1; j < numVertices; j++) {
                if (probabilityDist(gen) < density) {
                    double weight = weightDist(gen);
                    add(i, j, weight);
                }
            }
        }
    }
    
    // Get adjacency list for algorithm access
    const vector<vector<pair<int, double>>>& getAdjacencyList() const {
        return adjacencyList;
    }
    
    void displayStats() const {
        cout << "Graph Statistics:" << endl;
        cout << "  Vertices: " << V() << endl;
        cout << "  Edges: " << E() << endl;
        cout << "  Actual Density: " << fixed << setprecision(3) 
             << (2.0 * E()) / (numVertices * (numVertices - 1)) << endl;
    }
};

// ShortestPath Algorithm Implementation
class ShortestPath {
private:
    Graph* graph;
    vector<int> verticesList;
    
public:
    // Constructor
    ShortestPath(Graph* g) : graph(g) {
        if (graph) {
            for (int i = 0; i < graph->V(); i++) {
                verticesList.push_back(i);
            }
        }
    }
    
    // Get vertices list
    vector<int> vertices() const {
        return verticesList;
    }
    
    // Dijkstra's algorithm implementation
    vector<double> dijkstra(int source) {
        if (!graph || source < 0 || source >= graph->V()) {
            return vector<double>();
        }
        
        int n = graph->V();
        vector<double> distances(n, numeric_limits<double>::infinity());
        vector<int> parent(n, -1);
        vector<bool> visited(n, false);
        
        distances[source] = 0.0;
        
        // Use STL priority queue for efficiency
        priority_queue<pair<double, int>, vector<pair<double, int>>, 
                      greater<pair<double, int>>> minHeap;
        minHeap.push(make_pair(0.0, source));
        
        while (!minHeap.empty()) {
            double currentDistance = minHeap.top().first;
            int currentVertex = minHeap.top().second;
            minHeap.pop();
            
            if (visited[currentVertex]) continue;
            visited[currentVertex] = true;
            
            const auto& neighbors = graph->getAdjacencyList()[currentVertex];
            for (const auto& edge : neighbors) {
                int neighbor = edge.first;
                double weight = edge.second;
                double newDistance = distances[currentVertex] + weight;
                
                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    parent[neighbor] = currentVertex;
                    minHeap.push(make_pair(newDistance, neighbor));
                }
            }
        }
        
        return distances;
    }
    
    // Find shortest path between two vertices
    vector<int> path(int u, int w) {
        vector<int> shortestPath;
        if (!graph || u < 0 || u >= graph->V() || w < 0 || w >= graph->V()) {
            return shortestPath;
        }
        
        vector<double> distances = dijkstra(u);
        if (distances[w] == numeric_limits<double>::infinity()) {
            return shortestPath; // No path exists
        }
        
        // Reconstruct path using parent pointers
        vector<int> parent(graph->V(), -1);
        vector<bool> visited(graph->V(), false);
        distances.assign(graph->V(), numeric_limits<double>::infinity());
        distances[u] = 0.0;
        
        priority_queue<pair<double, int>, vector<pair<double, int>>, 
                      greater<pair<double, int>>> minHeap;
        minHeap.push(make_pair(0.0, u));
        
        while (!minHeap.empty()) {
            double currentDistance = minHeap.top().first;
            int currentVertex = minHeap.top().second;
            minHeap.pop();
            
            if (visited[currentVertex]) continue;
            visited[currentVertex] = true;
            
            const auto& neighbors = graph->getAdjacencyList()[currentVertex];
            for (const auto& edge : neighbors) {
                int neighbor = edge.first;
                double weight = edge.second;
                double newDistance = distances[currentVertex] + weight;
                
                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    parent[neighbor] = currentVertex;
                    minHeap.push(make_pair(newDistance, neighbor));
                }
            }
        }
        
        // Reconstruct path
        int current = w;
        while (current != -1) {
            shortestPath.push_back(current);
            current = parent[current];
        }
        reverse(shortestPath.begin(), shortestPath.end());
        
        return shortestPath;
    }
    
    // Return path cost
    double pathSize(int u, int w) {
        if (!graph) return numeric_limits<double>::infinity();
        
        vector<double> distances = dijkstra(u);
        return (w >= 0 && w < distances.size()) ? distances[w] : 
               numeric_limits<double>::infinity();
    }
};

// Monte Carlo Simulation Workflow Manager
class MonteCarloSimulation {
private:
    int numVertices;
    double density1, density2;
    double minDistance, maxDistance;
    
public:
    MonteCarloSimulation(int vertices, double d1, double d2, 
                        double minDist, double maxDist)
        : numVertices(vertices), density1(d1), density2(d2),
          minDistance(minDist), maxDistance(maxDist) {}
    
    void runSimulation() {
        cout << "Monte Carlo Graph Simulation Analysis" << endl;
        cout << "=====================================" << endl << endl;
        
        // Test with first density
        cout << "Testing with " << (density1 * 100) << "% density:" << endl;
        double avgPath1 = runSingleSimulation(density1);
        cout << "Average shortest path from vertex 1: " 
             << fixed << setprecision(4) << avgPath1 << endl << endl;
        
        cout << "==========================================" << endl << endl;
        
        // Test with second density
        cout << "Testing with " << (density2 * 100) << "% density:" << endl;
        double avgPath2 = runSingleSimulation(density2);
        cout << "Average shortest path from vertex 1: " 
             << fixed << setprecision(4) << avgPath2 << endl << endl;
        
        // Analysis
        cout << "Analysis:" << endl;
        cout << "Higher density (" << (density2 * 100) << "%) resulted in ";
        if (avgPath2 < avgPath1) {
            cout << "shorter average paths due to increased connectivity." << endl;
        } else {
            cout << "longer average paths, possibly due to random variation." << endl;
        }
    }
    
private:
    double runSingleSimulation(double density) {
        Graph graph(numVertices, density, minDistance, maxDistance);
        graph.displayStats();
        cout << endl;
        
        ShortestPath shortestPathAlgo(&graph);
        
        double totalDistance = 0.0;
        int connectedPaths = 0;
        
        cout << "Sample distances from vertex 1:" << endl;
        vector<double> distances = shortestPathAlgo.dijkstra(0);
        
        for (int i = 1; i < min(6, numVertices); i++) {
            if (distances[i] != numeric_limits<double>::infinity()) {
                cout << "  To vertex " << (i + 1) << ": " 
                     << fixed << setprecision(2) << distances[i] << endl;
            } else {
                cout << "  To vertex " << (i + 1) << ": No path" << endl;
            }
        }
        
        // Calculate average for all vertices
        for (int i = 1; i < numVertices; i++) {
            if (distances[i] != numeric_limits<double>::infinity()) {
                totalDistance += distances[i];
                connectedPaths++;
            }
        }
        
        cout << "Connected paths: " << connectedPaths 
             << " out of " << (numVertices - 1) << endl;
        
        return (connectedPaths > 0) ? (totalDistance / connectedPaths) : 0.0;
    }
};

int main() {
    const int NUM_VERTICES = 50;
    const double MIN_DISTANCE = 1.0;
    const double MAX_DISTANCE = 10.0;
    const double DENSITY_LOW = 0.20;
    const double DENSITY_HIGH = 0.40;
    
    // Create and run Monte Carlo simulation
    MonteCarloSimulation simulation(NUM_VERTICES, DENSITY_LOW, DENSITY_HIGH,
                                   MIN_DISTANCE, MAX_DISTANCE);
    simulation.runSimulation();
    
    return 0;
}