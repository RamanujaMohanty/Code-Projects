#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <tuple>
#include <sstream> // Required for stringstream

// Represents a weighted, undirected graph
class graph {
public:
    int num_vertices;
    std::vector<std::vector<std::pair<int, int>>> adj_list;
    int num_edges;

    graph(int vertices) : num_vertices(vertices), num_edges(0) {
        adj_list.resize(num_vertices);
    }

    // *** MODIFIED CONSTRUCTOR ***
    // This constructor now safely handles malformed lines in the input file.
    graph(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            exit(1);
        }

        // Read the number of vertices from the first valid line
        std::string first_line;
        while(std::getline(file, first_line)) {
            std::stringstream ss(first_line);
            if (ss >> num_vertices) {
                break; // Successfully read the node count
            }
        }

        adj_list.resize(num_vertices);
        num_edges = 0;

        std::string line;
        int u, v, cost;
        // Read the rest of the file line by line
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            // Try to extract three integers. If successful, add the edge.
            if (ss >> u >> v >> cost) {
                // Basic validation to ensure nodes are within bounds
                if (u < num_vertices && v < num_vertices) {
                     add_edge(u, v, cost);
                }
            }
            // Otherwise, the line is malformed and is automatically skipped.
        }
        file.close();
    }

    void add_edge(int u, int v, int weight) {
        adj_list[u].push_back({v, weight});
        adj_list[v].push_back({u, weight}); // For an undirected graph
        num_edges++;
    }

    const std::vector<std::pair<int, int>>& get_neighbors(int u) const {
        return adj_list[u];
    }
};

// Contains the logic for finding the Minimum Spanning Tree (MST)
class MST {
public:
    const graph& graph_obj;

    MST(const graph& g) : graph_obj(g) {}

    std::pair<int, std::vector<std::tuple<int, int, int>>> prim(int start_node = 0) {
        using Edge = std::pair<int, std::pair<int, int>>;
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

        std::vector<bool> in_mst(graph_obj.num_vertices, false);
        std::vector<std::tuple<int, int, int>> mst_edges;
        int total_cost = 0;

        if(start_node >= graph_obj.num_vertices) return {0, {}}; // safety check

        in_mst[start_node] = true;
        for (const auto& neighbor : graph_obj.get_neighbors(start_node)) {
            int v = neighbor.first;
            int weight = neighbor.second;
            pq.push({weight, {start_node, v}});
        }

        while (!pq.empty() && mst_edges.size() < graph_obj.num_vertices - 1) {
            Edge top_edge = pq.top();
            pq.pop();

            int cost = top_edge.first;
            int u = top_edge.second.first;
            int v = top_edge.second.second;

            if (in_mst[v]) {
                continue;
            }

            in_mst[v] = true;
            total_cost += cost;
            mst_edges.emplace_back(u, v, cost);

            for (const auto& neighbor : graph_obj.get_neighbors(v)) {
                int next_v = neighbor.first;
                int next_cost = neighbor.second;
                if (!in_mst[next_v]) {
                    pq.push({next_cost, {v, next_v}});
                }
            }
        }
        return {total_cost, mst_edges};
    }
};


int main() {
    // Create a test file with the user-provided malformed data
    std::ofstream outfile("prim_test.txt");
    if (outfile.is_open()) {
        // This is the content from the prim_test.txt file uploaded by the user
        outfile << "20\n0 1 17\n0 2 2\n0 3 9\n0 4 24\n0 5 28\n0 6 29\n0 7 14\n0 8 28\n0 9 13\n0 10 23\n0 11 10\n0 12 15\n0 13 23\n0 14 15\n0 15 18\n0 16 11\n0 17 4\n0 18 27\n0 19 5\n1 0 17\n1 2 9\n1 3 3\n1 5 14\n1 6 1\n1 8 27\n1 9 20\n1 10 16\n1 11 24\n1 12 29\n1 13 6\n1 15 15\n1 16 20\n1 17 1\n1 18 11\n1 19 9\n2 0 2\n2 1 9\n2 3 21\n2 4 21\n2 5 29\n2 6 13\n2 7 19\n2 8 16\n2 9 1\n2 10 11\n2 11 4\n2 12 12\n2 14 26\n2 15 5\n2 16 \n25\n2 17 12\n2 18 5\n2 19 24\n3 0 9\n3 1 3\n3 2 21\n3 4 11\n3 6 22\n3 7 22\n3 8 12\n3 9 16\n3 11 22\n3 12 1\n3 13 12\n3 15 14\n3 16 15\n3 17 23\n3 18 27\n3 19 28\n4 0 24\n4 2 21\n4 3 11\n4 5 25\n4 7 1\n4 8 1\n4 9 5\n4 11 24\n4 12 29\n4 13 9\n4 14 4\n4 15 2\n4 16 5\n4 18 10\n4 19 10\n5 0 28\n5 1 14\n5 2 29\n5 4 25\n5 6 1\n5 7 17\n5 8 22\n5 9 7\n5 10 20\n5 11 7\n5 12 22\n5 13 16\n5 14 11\n5 15 22\n5 16 2\n5 17 \n23\n5 18 1\n5 19 20\n6 0 29\n6 1 1\n6 2 13\n6 3 22\n6 5 1\n6 8 18\n6 9 7\n6 11 4\n6 12 18\n6 13 11\n6 14 14\n6 15 5\n6 16 24\n6 17 5\n6 18 13\n7 0 14\n7 2 19\n7 3 22\n7 4 1\n7 5 17\n7 8 27\n7 9 7\n7 10 2\n7 11 5\n7 13 29\n7 14 16\n7 15 25\n7 16 8\n7 17 19\n7 18 26\n7 19 23\n8 0 28\n8 1 27\n8 2 16\n8 3 12\n8 4 1\n8 5 22\n8 6 18\n8 7 27\n8 9 3\n8 10 3\n8 11 26\n8 12 9\n8 13 25\n8 14 16\n8 15 7\n8 16 4\n8 17 \n23\n8 18 7\n9 0 13\n9 1 20\n9 2 1\n9 3 16\n9 4 5\n9 5 7\n9 6 7\n9 7 7\n9 8 3\n9 11 23\n9 12 3\n9 13 3\n9 14 28\n9 15 24\n9 16 12\n9 17 20\n9 18 25\n9 19 25\n10 0 23\n10 1 16\n10 2 11\n10 5 20\n10 7 2\n10 8 3\n10 12 27\n10 13 13\n10 14 25\n10 15 2\n10 16 3\n10 17 4\n10 18 4\n10 19 15\n11 0 10\n11 1 24\n11 2 4\n11 3 22\n11 4 24\n11 5 7\n11 6 4\n11 7 5\n11 8 26\n11 9 23\n11 12 1\n11 14 1\n11 15 20\n11 16 20\n11 17 22\n11 18 19\n11 19 \n28\n12 0 15\n12 1 29\n12 2 12\n12 3 1\n12 4 29\n12 5 22\n12 6 18\n12 8 9\n12 9 3\n12 10 27\n12 11 1\n12 13 23\n12 14 6\n12 15 9\n12 16 28\n12 17 1\n12 18 6\n12 19 13\n13 0 23\n13 1 6\n13 3 12\n13 4 9\n13 5 16\n13 6 11\n13 7 29\n13 8 25\n13 9 3\n13 10 13\n13 12 23\n13 14 5\n13 15 19\n13 16 18\n13 17 4\n13 18 16\n13 19 12\n14 0 15\n14 2 26\n14 4 4\n14 5 11\n14 6 14\n14 7 16\n14 8 16\n14 9 28\n14 10 25\n14 11 1\n14 12 6\n14 13 5\n14 15 6\n14 16 27\n14 17 \n15\n14 18 1\n14 19 28\n15 0 18\n15 1 15\n15 2 5\n15 3 14\n15 4 2\n15 5 22\n15 6 5\n15 7 25\n15 8 7\n15 9 24\n15 10 2\n15 11 20\n15 12 9\n15 13 19\n15 14 6\n15 16 23\n15 17 21\n15 18 28\n15 19 2\n16 0 11\n16 1 20\n16 2 25\n16 3 15\n16 4 5\n16 5 2\n16 6 24\n16 7 8\n16 8 4\n16 9 12\n16 10 3\n16 11 20\n16 12 28\n16 13 18\n16 14 27\n16 15 23\n16 17 9\n16 18 11\n16 19 12\n17 0 4\n17 1 1\n17 2 12\n17 3 23\n17 5 23\n17 6 5\n17 7 19\n17 8 23\n17 9 20\n17 10 \n4\n17 11 22\n17 12 1\n17 13 4\n17 14 15\n17 15 21\n17 16 9\n17 18 20\n17 19 9\n18 0 27\n18 1 11\n18 2 5\n18 3 27\n18 4 10\n18 5 1\n18 6 13\n18 7 26\n18 8 7\n18 9 25\n18 10 4\n18 11 19\n18 12 6\n18 13 16\n18 14 1\n18 15 28\n18 16 11\n18 17 20\n18 19 11\n19 0 5\n19 1 9\n19 2 24\n19 3 28\n19 4 10\n19 5 20\n19 7 23\n19 9 25\n19 10 15\n19 11 28\n19 12 13\n19 13 12\n19 14 28\n19 15 2\n19 16 12\n19 17 9\n19 18 11";
        outfile.close();
    }

    std::cout << "--- Computing Minimum Spanning Tree from prim_test.txt ---" << std::endl;

    // Create graph object by reading from the file
    graph my_graph("prim_test.txt");
    std::cout << "Graph loaded from file. Nodes: " << my_graph.num_vertices << ", Edges Parsed: " << my_graph.num_edges << std::endl;

    // Create MST solver and run Prim's algorithm
    MST mst_solver(my_graph);
    auto result = mst_solver.prim(0);

    int mst_cost = result.first;
    std::vector<std::tuple<int, int, int>> mst_edges = result.second;

    // Print the output
    std::cout << "\nTotal cost of MST: " << mst_cost << std::endl;
    std::cout << "Edges in the MST (u, v, cost):" << std::endl;
    for (const auto& edge : mst_edges) {
        std::cout << "(" << std::get<0>(edge) << ", " << std::get<1>(edge) << ", " << std::get<2>(edge) << ")" << std::endl;
    }

    return 0;
}
