// Header files
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <random>
#include <iomanip>

//Main graph class
class graph {
public:
    int num_vertices;
    // Vector of pairs to contain adjacent nodes and weights.
    std::vector<std::vector<std::pair<int, double>>> adj_list;
    int num_edges;

    graph(int vertices) : num_vertices(vertices), num_edges(0)  {
        adj_list.resize(num_vertices);
    }
    // Adds edge to existing node.
    void add_edge(int u, int v, double weight) {
        adj_list[u].push_back({v, weight});
        adj_list[v].push_back({u, weight});
        num_edges++;
    }
    // Returns adjacent vertices.
    const std::vector<std::pair<int, double>>& get_neighbors(int u) const {
        return adj_list[u];
    }
};

class shortest_path_algo {
public:
    const graph& graph_obj;

    shortest_path_algo(const graph& g) : graph_obj(g) {}
    // Main Dijkstra's Algorithm implementation.
    std::vector<double> dijkstra(int start_vertex) {
        std::vector<double> distances(graph_obj.num_vertices, std::numeric_limits<double>::infinity());
        distances[start_vertex] = 0;
        // using pdi statement to increase readability of code.
        using pdi = std::pair<double, int>;
        std::priority_queue<pdi, std::vector<pdi>, std::greater<pdi>> pq;
        pq.push({0.0, start_vertex});

        while (!pq.empty()) {
            int u = pq.top().second;
            double d = pq.top().first;
            pq.pop();

            if (d > distances[u]) {
                continue;
            }

            for (const auto& edge : graph_obj.get_neighbors(u)) {
                int v = edge.first;
                double weight = edge.second;
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    pq.push({distances[v], v});
                }
            }
        }
        // Return distances of adjacent nodes.
        return distances;
    }
};

// Main Monte Carlo Simulation
class monte_carlo {
public:
    int num_nodes;
    double density;
    std::pair<double, double> dist_range;
    graph graph_obj;

    monte_carlo(int nodes, double d, std::pair<double, double> range)
        : num_nodes(nodes), density(d), dist_range(range), graph_obj(nodes) {
        _create_random_graph();
    }

    void _create_random_graph() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        std::uniform_real_distribution<> weight_dis(dist_range.first, dist_range.second);

        for (int i = 0; i < num_nodes; ++i) {
            for (int j = i + 1; j < num_nodes; ++j) {
                if (dis(gen) < density) {
                    graph_obj.add_edge(i, j, weight_dis(gen));
                }
            }
        }
    }

    double run_simulation() {
        shortest_path_algo path_finder(graph_obj);
        std::vector<double> distances = path_finder.dijkstra(0);

        double total_path_length = 0;
        int valid_paths = 0;

        for (int i = 1; i < num_nodes; ++i) {
            if (distances[i] != std::numeric_limits<double>::infinity()) {
                total_path_length += distances[i];
                valid_paths++;
            }
        }

        if (valid_paths == 0) {
            return 0;
        }
        return total_path_length / valid_paths;
    }
};

// Main method
int main()
{
    // Test cases
    int num_nodes = 50;
    std::pair<double, double> dist_range = {1.0, 10.0};
    std::vector<double> densities = {0.20, 0.40};
    // Title
    std::cout << "monte carlo simulation - dijkstra's algorithm\n\n";
    // Print supplied densities and execute monte_carlo class.
    for (double density : densities) {
        std::cout << "running simulation for density: " << std::fixed << std::setprecision(0) << density * 100 << "%\n";
        monte_carlo mc_simulation(num_nodes, density, dist_range);
        double avg_path_length = mc_simulation.run_simulation();
        std::cout << "graph details:\n";
        std::cout << "nodes: " << mc_simulation.graph_obj.num_vertices << "\n";
        std::cout << "edges: " << mc_simulation.graph_obj.num_edges << "\n";
        std::cout << "average shortest length from node 0 to all nodes: " << std::fixed << std::setprecision(4) << avg_path_length << "\n\n";
    }
    return 0;
}
