/**
 * Solves the "George" problem using Dijkstrass algorithm
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <utility>
#include <queue>
#include <algorithm>
#include <climits>

using std::cout, std::cin, std::endl, std::vector, std::pair, std::priority_queue, std::greater, std::find_if;

const int INF = INT_MAX;
const int MAX_N = 1001;

/**
 * graph[u] is a list of (v, cost) pairs
 */
vector<vector<pair<int, int>>> graph(MAX_N);

/**
 * blocked[u][v] = (start_block, end_block).
 * If George blocks (u,v) from minute start_block (inclusive)
 * until minute end_block (exclusive), store that in blocked[u][v].
 * (-1, -1) means "never blocked."
 */
pair<int, int> blocked[MAX_N][MAX_N];

/**
 * Finds the shortest time using Dijkstra’s algorithm,
 * with waiting if roads are blocked.
 *
 */
int dijkstras(int start, int goal, int start_time, int intersections)
{
    vector<int> dist(intersections + 1, INF);
    dist[start] = start_time;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({start_time, start});

    while (!pq.empty())
    {
        auto [t, u] = pq.top();
        pq.pop();

        if (t > dist[u])
            continue;
        if (u == goal)
            break;

        for (auto &[v, cost] : graph[u])
        {
            int effective_time = t;
            auto [start_block, end_block] = blocked[u][v];
            if (start_block != -1 && effective_time >= start_block && effective_time < end_block)
            {
                // Wait until the block is over
                effective_time = end_block;
            }
            int new_time = effective_time + cost;
            if (new_time < dist[v])
            {
                dist[v] = new_time;
                pq.push({new_time, v});
            }
        }
    }

    return dist[goal] - start_time;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int intersections{}, roads{};
    cin >> intersections >> roads;

    int luka_start{}, luka_end{}, luka_start_time{}, george_intersections{};
    cin >> luka_start >> luka_end >> luka_start_time >> george_intersections;

    vector<int> george_route(george_intersections);
    for (int i = 0; i < george_intersections; i++)
    {
        cin >> george_route[i];
    }

    int u{}, v{}, L{};
    for (int i = 0; i < roads; ++i)
    {
        cin >> u >> v >> L;
        graph[u].push_back({v, L});
        graph[v].push_back({u, L});
    }

    for (int i = 0; i <= intersections; ++i)
    {
        for (int j = 0; j <= intersections; j++)
        {
            blocked[i][j] = {-1, -1}; // no block
        }
    }

    // Simulate Georges route
    int current_time{};
    for (int i = 0; i < george_intersections - 1; ++i)
    {
        u = george_route[i];
        v = george_route[i + 1];
        auto it = find_if(graph[u].begin(), graph[u].end(), [&](const pair<int, int> &p)
                          { return p.first == v; });
        if (it != graph[u].end())
        {
            L = it->second;
            blocked[u][v] = {current_time, current_time + L};
            blocked[v][u] = {current_time, current_time + L};
            current_time += L;
        }
    }

    int result = dijkstras(luka_start, luka_end, luka_start_time, intersections);
    cout << result << endl;

    return 0;
}