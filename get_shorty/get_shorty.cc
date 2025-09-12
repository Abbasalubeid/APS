/**
 * Solves the get shorty problem in Kattis.
 *
 * Time complexity: O((V + E) log V) where V is the number of nodes and E is
 * the number of edges.
 *
 * Space complexity: O(V)
 *
 *  @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <utility>
#include <queue>
#include <functional>
#include <cmath>
#include <iomanip>

using std::cout, std::cin, std::endl, std::vector, std::pair;
using std::priority_queue, std::greater;

const double INF_DOUBLE = 1e15;

double dijkstras(const vector<vector<pair<int, double>>> &graph, int start, int goal)
{
    int n = graph.size();
    vector<double> dist(n, INF_DOUBLE);
    dist[start] = 0;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    pq.push({0, start});

    while (!pq.empty())
    {
        auto [current_cost, current_node] = pq.top();
        pq.pop();

        if (current_node == goal)
            return current_cost;

        if (current_cost > dist[current_node])
            continue;

        for (auto &[neighbour, cost] : graph[current_node])
        {
            double new_cost = current_cost + cost;
            if (new_cost < dist[neighbour])
            {
                dist[neighbour] = new_cost;
                pq.push({new_cost, neighbour});
            }
        }
    }
    return -1;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n{}, m{};
    while (cin >> n >> m && (n || m))
    {

        vector<vector<pair<int, double>>> graph(n);

        for (int i = 0; i < m; ++i)
        {
            int x{}, y{};
            double f{}, cost;
            cin >> x >> y >> f;
            // Change sign because 0 <= f <= 1 which makes log(f) negative
            cost = -std::log(f);

            graph[x].push_back({y, cost});
            graph[y].push_back({x, cost});

            // cout << cost << endl;
        }

        double min_log_sum = dijkstras(graph, 0, n - 1);

        double fraction_left = std::exp(-min_log_sum);

        cout << std::fixed << std::setprecision(4) << fraction_left << "\n";
    }
    cout << std::flush;

    return 0;
}
