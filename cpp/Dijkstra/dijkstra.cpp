#include <iostream>
#include <map>
#include <set>
#include <stddef.h>
#include <utility>
#include <vector>

using std::map, std::set, std::pair, std::vector;
using std::cin, std::cout;

// https://www.youtube.com/watch?v=EFg3u_E6eHU
// {0, 1} : 3
// {1, 0} : 3
// {0, 2} : 2
// {2, 0} : 2
size_t findShortestDistance(map<pair<size_t, size_t>, size_t> &neighborWeightMap,
                            size_t vertexCount, size_t sourceVertex, size_t destinationVertex)
{
    // array of sets
    // {
    //    {1, 2},
    //    {0, 2, 3}
    // }
    // make adjacency list
    vector<set<size_t>> adjacencyList(vertexCount, set<size_t>{});
    /*
    for (auto const &neighborWeight : neighborWeightMap) {
        adjacencyList[neighborWeight.first.first].insert(neighborWeight.first.second);
    }
    */

    for (auto const &[neighborPair, weight] : neighborWeightMap) {
        adjacencyList[neighborPair.first].insert(neighborPair.second);
    }

    set<size_t> unexploredVertices;
    for (size_t vertex = 0; vertex < vertexCount; ++vertex)
        unexploredVertices.insert(vertex);

    vector<size_t> vertexTotalCosts(vertexCount, SIZE_MAX - 1);

    vertexTotalCosts[sourceVertex] = 0;

    while (unexploredVertices.count(destinationVertex))  {
        size_t thisVertex;
        // calculate the new lowest cost unexplored vertex -henceforth called this vertex
        size_t lowestCost = SIZE_MAX;
        for (auto unexploredVertex: unexploredVertices) {
            if (lowestCost > vertexTotalCosts[unexploredVertex]) {
                lowestCost = vertexTotalCosts[unexploredVertex];
                thisVertex = unexploredVertex;
            }
        }

        // remove this vertex from unexplored vertices
        unexploredVertices.erase(thisVertex);

        // For this vertex, compute new cumulative weights for each of its neighbors for the
        // paths from this neighbor. If the newly calculated weight is smaller than the
        // neighbor's existing cumulative weight, update the neighbor's cumulative weight
        auto neighborSet = adjacencyList[thisVertex];
        auto thisVertexCost = vertexTotalCosts[thisVertex];
        for (auto neighbor: neighborSet) {
            // neighbor's cumulative cost from this vertex
            auto neighborCumulativeCost = thisVertexCost +
                                          neighborWeightMap[{thisVertex, neighbor}];
            if (neighborCumulativeCost < vertexTotalCosts[neighbor]) {
            vertexTotalCosts[neighbor] = neighborCumulativeCost;
            }
        }

    }

    return vertexTotalCosts[destinationVertex];
}

int main()
{
    map<pair<size_t, size_t>, size_t> neighborWeightMap;
    cout << "Enter the number of vertices: ";
    int vertexCount;
    cin >> vertexCount;
    for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
        cout << "For vertex: " << vertex << ", enter the number of neighbors: ";
        size_t neighborCount;
        cin >> neighborCount;
        for (size_t neighbor = 0; neighbor < neighborCount; ++neighbor) {
            cout << "Enter neighbor number: ";
            size_t neighborNumber;
            cin >> neighborNumber;
            cout << "Enter neighbor weight: ";
            size_t neighborWeight;
            cin >> neighborWeight;
            neighborWeightMap[{vertex, neighborNumber}] = neighborWeight;
            neighborWeightMap[{neighborNumber, vertex}] = neighborWeight;
        }
    }
    size_t shortestDistance = findShortestDistance(neighborWeightMap, vertexCount, 0, vertexCount - 1);

    /*
    // 0 -> A, 1 -> B, 2 -> C, 3 -> D, 4 -> E, 5 -> F, 6 -> G
    neighborWeightMap[{0, 1}] = 3; neighborWeightMap[{1, 0}] = 3;
    neighborWeightMap[{0, 2}] = 2; neighborWeightMap[{2, 0}] = 2;
    neighborWeightMap[{1, 2}] = 2; neighborWeightMap[{2, 1}] = 2;
    neighborWeightMap[{1, 3}] = 1; neighborWeightMap[{3, 1}] = 1;
    neighborWeightMap[{1, 5}] = 4; neighborWeightMap[{5, 1}] = 4;
    neighborWeightMap[{2, 3}] = 3; neighborWeightMap[{3, 2}] = 3;
    neighborWeightMap[{2, 4}] = 5; neighborWeightMap[{4, 2}] = 5;
    neighborWeightMap[{2, 6}] = 6; neighborWeightMap[{6, 2}] = 6;
    neighborWeightMap[{3, 6}] = 2; neighborWeightMap[{6, 3}] = 2;
    neighborWeightMap[{4, 6}] = 2; neighborWeightMap[{6, 4}] = 2;
    neighborWeightMap[{5, 6}] = 1; neighborWeightMap[{6, 5}] = 1;

    size_t shortestDistance = findShortestDistance(neighborWeightMap, 7, 0, 6);
    */

    cout << "Shortest distance: " << shortestDistance << "\n";
    return 0;
}
