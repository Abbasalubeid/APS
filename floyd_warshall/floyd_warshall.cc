/**
 * Implementation of Floyd-Warshalls algorithm for finding the shortest distance
 * between all pairs of nodes in a graph with edge weights.
 *
 * Time complexity: O(V^3) where V is the number of nodes in the graph.
 *
 * Space complexity: O(V^2).
 *
 * @author Abbas Alubeid – abbal179
 */

#include <iostream>
#include <utility>
#include <climits>
#include <algorithm>
#include <vector>

using std::cout, std::cin, std::endl, std::vector, std::pair;

const int INF = INT_MAX;

/**
 * Finds the shortest distances between all pairs of nodes in a graph where edge
 * weights can be negative (as long as there are no negative weight cycles).
 * The input is an adjacency matrix where each entry holds the weight of the edge
 * between two nodes or INF if the is no edge.
 *
 * First, the diagonal is set to 0 since the shortest distance from a node to
 * itself is zero. Then the main part of the algorithm uses three nested loops.
 * Loop 1 goes through each node v to treat it as an intermediate node.
 * For each v, loop 2 goes through every source node i and loop 3 through every
 * destination node j. If the path from i to j via v is shorter than the current
 * known path from i to j, the distance is updated, so it basically checks if
 * using v helps create a shorter path between any i and j for all nodes v.
 *
 * After computing all shortest distances, the algorithm looks for negative
 * cycles. This is done by checking if any diagonal entry dist[v][v] is negative.
 * If so, it means there's a negative cycle involving node v since the shortest
 * distacnce from v to itself became smaller than 0 which can only happen if a
 * cycle allows decrasing the total cost infinitely. For each node pair (i, j),
 * if there's a path from i to v and from v to j, then the effect of the
 * negative cycle at v can reach (i, j) making its shortest path undefined, this
 * is marked in a seperate boolean matrix (neg).
 *
 * Time complexity: O(V^3) where V is the number of nodes.
 *
 * Space complexity: O(V^2) for storing the dist and neg matrices.
 *
 * @returns A matrix of distances between all node pairs and a another matrix
 * "neg" that tells which distances are undefined because of negative cycles.
 */
pair<vector<vector<int>>, vector<vector<bool>>> floyd_warshall(vector<vector<int>> &dist)
{

    int n = dist.size();
    vector<vector<bool>> neg(n, vector<bool>(n, false));

    for (int i = 0; i < n; ++i)
        if (dist[i][i] == INF)
            dist[i][i] = 0;

    for (int v = 0; v < n; ++v)
        for (int i = 0; i < n; ++i)
            if (dist[i][v] != INF)
                for (int j = 0; j < n; j++)
                    if (dist[v][j] != INF && dist[i][v] + dist[v][j] < dist[i][j])
                        dist[i][j] = dist[i][v] + dist[v][j];

    for (int v = 0; v < n; ++v)
        if (dist[v][v] < 0)
            for (int i = 0; i < n; ++i)
                if (dist[i][v] != INF)
                    for (int j = 0; j < n; j++)
                        if (dist[v][j] != INF)
                            neg[i][j] = true;

    return {dist, neg};
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int nodes{}, edges{}, queries{};

    while (cin >> nodes >> edges >> queries &&
           (nodes || edges || queries))
    {

        vector<vector<int>> graph(nodes, vector<int>(nodes, INF));

        for (int i = 0; i < edges; ++i)
        {
            int u{}, v{}, w{};
            cin >> u >> v >> w;
            if (u == v && w > 0)
                continue;
            graph[u][v] = std::min(graph[u][v], w);
        }

        auto [distances, neg] = floyd_warshall(graph);

        for (int i = 0; i < queries; ++i)
        {
            int u{}, v{};
            cin >> u >> v;

            if (neg[u][v])
                cout << "-Infinity";
            else if (distances[u][v] == INF)
                cout << "Impossible";
            else
                cout << distances[u][v];
            cout << "\n";
        }
        cout << endl;
    }

    return 0;
}