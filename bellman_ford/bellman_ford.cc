/**
 * Implementation of Bellman-fords algorithm to find the shortest path from a node
 * to all other nodes in a graph where edge weights may be negative.
 *
 * Time complexity: O(V * E) Where V is the number of nodes and E is the number
 * of edges.
 *
 * Space complexity: O(V) for storing distances, prevs, and negative cycle flags.
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <utility>
#include <climits>
#include <algorithm>
#include <tuple>
#include <vector>

using std::cout, std::cin, std::endl, std::vector, std::pair, std::tuple;

const int INF = INT_MAX;
const int NEG_INF = INT_MIN;
const int MAX_N = 10001;

/**
 *
 * Finds the shortest path from a node to all other nodes in a graph where edge
 * weights may be negative. It starts by setting the start node's distance to 0
 * and all others to infinity. Then, it loops through the graph nodes-1 times
 * which is enough to find the shortest paths given that there is no negative
 * cycles. In each iteration, it goes through each edge and checks if going
 * through the current edge would give a shorter path to the destination node. If
 * so, it updates that nodes distance and stores current node in the prev vector
 * to remember the path for later. It's necessarry to go through the whole graph
 * again in each iteration because negative weights can cause changes that allows
 * for even shorter paths in later iterations but if no changes are made during
 * a full round, the loop ends early since it means that all distances are
 * already set.
 *
 * After the first loop, it has one more loop through all edges to check for any
 * that can still be relaxed. If such an edge exists, it means there’s a negative
 * weight cycle in the graph that can be reached from the start node. Nodes
 * affected by these cycles are marked (-INF) to show that their distances are
 * not defined. Other nodes that can be reached from those should also be marked
 * since it's possible to keep decrasing their distances by looping through
 * the cycle. This is handeled in a third loop that spreads the -INF value
 * outward from the nodes in the second loop.
 *
 *
 * Time complexity: O(V * E) Where V is the number of nodes and E is the number
 * of edges. This is because in the worst case, the function needs to go through
 * all edges up to V - 1 times to find the correct shortest paths, and then again
 * to check for negative cycles and to propagate their effect.
 *
 * Space complexity: O(V) for storing distances, prevs, and negative cycle flags.
 *
 * @returns A vector of distances from start to each other reachable node and a
 * prev vector that stores the previous node on the shortest path to each node.
 */
pair<vector<int>, vector<int>> bellman_ford(const vector<tuple<int, int, int>> &edge_list, int start, int nodes)
{
    vector<int> dist(nodes, INF);
    vector<int> prev(nodes, -1);
    dist[start] = 0;

    for (int i = 0; i < nodes - 1; ++i)
    {
        bool changed = false;

        for (auto &[u, v, w] : edge_list)
        {
            if (dist[u] != INF && dist[u] != NEG_INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                prev[v] = u;
                changed = true;
            }
        }

        if (!changed)
            break;
    }

    // Negative weight cycle detection
    vector<int> neg(nodes, 0);
    for (auto &[u, v, w] : edge_list)
    {
        if (dist[u] != INF && dist[u] != NEG_INF && dist[u] + w < dist[v])
        {
            dist[v] = NEG_INF;
            neg[v] = 1;
        }
    }

    for (int i = 0; i < nodes - 1; ++i)
    {
        for (auto &[u, v, w] : edge_list)
        {
            if (neg[u])
            {
                dist[v] = NEG_INF;
                neg[v] = 1;
            }
        }
    }

    return {dist, prev};
}

/**
 * Builds and returns the path to a goal by traversing the "prev" vector.
 * Each entry in prev tells which node you came from to reach the current one so
 * this function starts from the goal and walks backward to the start, then
 * reverses the path to have a correct order from start to goal.
 *
 */
vector<int> build_path(vector<int> &prev, int goal)
{
    vector<int> path;

    for (int i = goal; i != -1; i = prev[i])
    {
        path.push_back(i);
    }

    std::reverse(path.begin(), path.end());

    return path;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int nodes{}, edges{}, queries{}, start_node{};

    while (cin >> nodes >> edges >> queries >> start_node &&
           (nodes || edges || queries || start_node))
    {

        vector<tuple<int, int, int>> edge_list;
        for (int i = 0; i < edges; ++i)
        {
            int u{}, v{}, w{};
            cin >> u >> v >> w;
            edge_list.push_back({u, v, w});
        }

        auto [distances, prev] = bellman_ford(edge_list, start_node, nodes);

        int goal{};
        for (int i = 0; i < queries; ++i)
        {

            cin >> goal;

            if (distances[goal] == NEG_INF)
                cout << "-Infinity";
            else if (distances[goal] == INF)
                cout << "Impossible";
            else
            {
                cout << distances[goal];
                // cout << " path:\n";
                // vector<int> path = build_path(prev, goal);

                // for (int node : path)
                // {
                //     cout << node << " ";
                // }
                // cout << "\n";
            }
            cout << "\n";
        }
        cout << endl;
    }

    return 0;
}