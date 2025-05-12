/**
 * Implementation of Dijkstras algorithm to find the single source
 * shortest path in a weighted graph with non-negative weights.
 *
 * Time complexity: O((V + E) log V) where V is the number of nodes and E is
 * the number of edges.
 *
 * Space complexity: O(V)
 *
 * @author Abbas Alubeid - abbal179
 * @date 2025-03-09
 */

#include <iostream>
#include <utility>
#include <queue>
#include <functional>
#include <climits>
#include <algorithm>

using std::cout, std::cin, std::endl, std::vector, std::pair, std::priority_queue, std::greater;

const int INF = INT_MAX;
const int MAX_N = 10001;

/**
 *
 * Finds the shortest distance between two nodes in a graph with non-negative
 * weights. It starts by setting the start node's distance to 0 and all
 * others to infinity. Then it uses a priority queue to always pick the
 * node with the smallest current distance. For each node it picks,
 * it goes through all its neighbors and if going through the current
 * node gives a shorter path to a neighbor, it updates that neighbor’s
 * distance and stores the current node in the prev list to remember
 * the path. It then pushes that neighbor into the queue to check it later.
 * This continues untill the queue is empty or the goal is reached.
 * The shortest path is then guranteed since function always checks the
 * cheapest options first.
 *
 * Time complexity: O((V + E) log V) where V is the number of nodes and E is
 * the number of edges. This is because each node is popped from the queue once,
 * taking O(log V) time per pop and each edge leads to at most one push into the
 * queue also requiring O(log V) per operation.
 *
 * Space complexity: O(V) because of the storage of distance values for each node
 * and the priority queue which may have up to V elements at once.
 *
 * @returns A vector of distances from start to each other reachable node and a
 * prev vector that stores the previous node on the shortest path to each node.
 */
pair<vector<int>, vector<int>> dijkstras(const vector<vector<pair<int, int>>> &graph, int start, int goal)
{
    vector<int> dist(MAX_N, INF);
    vector<int> prev(MAX_N, -1);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        auto [current_cost, current_node] = pq.top();
        pq.pop();

        if (current_node == goal)
            break;

        if (current_cost > dist[current_node])
            continue;

        for (auto &[neighbour, cost] : graph[current_node])
        {
            int new_cost = current_cost + cost;
            if (new_cost < dist[neighbour])
            {
                dist[neighbour] = new_cost;
                prev[neighbour] = current_node;
                pq.push({new_cost, neighbour});
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
        vector<vector<pair<int, int>>> graph(MAX_N);

        for (int i = 0; i < edges; ++i)
        {
            int u{}, v{}, w{};
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
        }

        int goal{};
        for (int i = 0; i < queries; ++i)
        {

            cin >> goal;
            auto [distances, prev] = dijkstras(graph, start_node, goal);

            if (distances[goal] != INF)
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

            else
                cout << "Impossible";

            cout << "\n";
        }
        cout << endl;
    }

    return 0;
}