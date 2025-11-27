/**
 * Solves the single source shortest path with time table graphs using Dijkstras
 * algorithm with extra functionality to handle that edges can only be used at
 * certain times
 *
 * Time complexity: O((V + E) log V) where V is the number of nodes and E is
 * the number of edges.
 *
 * Space complexity: O(V)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <utility>
#include <queue>
#include <algorithm>
#include <climits>
#include <algorithm>
#include <vector>

using std::cout, std::cin, std::vector, std::pair,
    std::priority_queue, std::greater;

const int INF = INT_MAX;
const int MAX_N = 10001;

struct Edge
{
    int to, t0, P, d;
};

vector<vector<Edge>> graph;

/**
 * Helper to get the next possible depart.
 * If the time is larger that t0 and p != 0, it jumps to the next available depart
 * using the fact that departure times form an arithmetic sequence: t0, t0 + P, t0 +
 * 2P ... so we find the smallest such time that is >= now. This is done by first
 * checking how far past t0 we are and using modulo to figure out how much we need
 * to wait until the next multiple of P.
 * If its already exactly on a valid time, we return it. Otherwise, we add the
 * remaining wait time (P - remainder) to now and return that.
 */
int next_departure(int now, int t0, int p)
{
    if (now <= t0)
        return t0;
    if (p == 0)
        return -1;

    int rem = (now - t0) % p;
    if (rem == 0)
        return now;
    else
        return now + (p - rem);
}

/**
 *
 * Finds the shortest distance from the start node to all other nodes in a graph
 * where edges can only be used at certain times. It starts by setting the start
 * node's time to 0 and all others to infinity. Then it uses a priority queue to
 * always pick the node we can reach the soonest. For each edge from the current
 * node, it uses the next_departure function to check when is the next allowed
 * time to take that edge (can be now or after some wait). If taking that edge
 * gives a faster arrival time at the destination node, it updates that node’s
 * time and stores the current node in the prev vector to remember
 * the path. It then pushes that neighbor into the queue to check it later.
 * This continues until the queue is empty and we have found the shortest arrival
 * time for all reachable nodes.
 *
 * The fastest path is guaranteed since the function always checks the
 * fastest known arrival times first and only updates a node’s time if a quicker
 * route is found so no faster path to a node can be missed.
 *
 * Time complexity: O((V + E) log V) where V is the number of nodes and E is
 * the number of edges. This is because each node is popped from the queue once,
 * taking O(log V) time per pop and each edge leads to at most one push into the
 * queue also requiring O(log V) per operation.
 *
 * Space complexity: O(V) because of the storage of distance values for each node
 * and the priority queue which may have up to V elements at once.
 *
 * @returns A vector of shortest times from start to each other reachable node
 * and a prev vector that stores the previous node on the shortest time path to
 * each node.
 */
pair<vector<int>, vector<int>> dijkstras(int start, int n)
{
    vector<int> dist(n + 1, INF);
    vector<int> prev(n, -1);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        auto [t, u] = pq.top();
        pq.pop();

        if (t > dist[u])
            continue;

        for (auto &e : graph[u])
        {
            int depart = next_departure(t, e.t0, e.P);
            if (depart == -1)
                continue;
            int new_t = depart + e.d;
            if (new_t < dist[e.to])
            {
                dist[e.to] = new_t;
                prev[e.to] = u;
                pq.push({new_t, e.to});
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
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nodes{}, edges{}, queries{}, source{};
    while (cin >> nodes >> edges >> queries >> source)
    {
        if (!cin || (nodes == 0 && edges == 0 && queries == 0 && source == 0))
            break;

        graph = vector<vector<Edge>>(nodes);

        for (int i = 0; i < edges; ++i)
        {
            int u, v, t0, P, d;
            cin >> u >> v >> t0 >> P >> d;
            graph[u].push_back({v, t0, P, d});
        }

        auto [distances, prev] = dijkstras(source, nodes);

        int goal{};
        for (int i = 0; i < queries; ++i)
        {
            cin >> goal;
            if (distances[goal] != INF)
                cout << distances[goal] << '\n';
            else
                cout << "Impossible\n";
        }
        cout << '\n';
    }
    cout << std::flush;
    return 0;
}
