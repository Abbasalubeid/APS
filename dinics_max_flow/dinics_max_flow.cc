/**
 * Solves the maximum flow problem using Dinic's algorithm.
 *
 * Time complexity: O(E * V^2) where V is the number of nodes and E is the number
 * of edges.
 *
 * Space complexity: O(V + E).
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <tuple>

using std::cout, std::cin, std::endl, std::vector, std::queue, std::pair, std::tuple;

const int INF = INT_MAX;
const int MAX_N = 501;

struct Edge
{
    int to, rev;
    int cap, flow;
};

vector<vector<Edge>> graph(MAX_N);
vector<int> level(MAX_N);

/**
 * Adds a forward and backward edge to the residual graph.
 * The reverse edge initially has zero capacity and is used for backtracking
 * flow when building the residual network.
 */
void add_edge(int u, int v, int c)
{
    graph[u].push_back({v, (int)graph[v].size(), c, 0});
    graph[v].push_back({u, (int)graph[u].size() - 1, 0, 0});
}

/**
 *
 * Builds the level graph starting from the source node using BFS.
 * Each node is assigned a level (distance from source) and only
 * forward edges with unused capacity are followed.
 *
 * The levels make sure that later DFS calls moves to the correct
 * direction torward the sink.
 *
 * @returns true if the sink is reachable which means there may still
 * be flow to push.
 */
bool bfs(int s, int t, int n)
{
    std::fill(level.begin(), level.begin() + n, -1);
    queue<int> q;
    q.push(s);
    level[s] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (const Edge &e : graph[u])
        {
            if (e.cap - e.flow > 0 && level[e.to] == -1)
            {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }

    return level[t] != -1;
}

/**
 *
 * Sends flow from the current node u toward the sink t by following
 * edges that go to the next level and have capacity left. This is done
 * using DFS and tries to push flow along valid paths in the level graph.
 *
 * @returns The amount of flow successfully pushed from u to t
 * or 0 if no path was found.
 */
int dfs(int u, int t, int pushed)
{
    if (pushed == 0)
        return 0;
    if (u == t)
        return pushed;

    for (Edge &e : graph[u])
    {
        if (level[e.to] == level[u] + 1 && e.cap - e.flow > 0)
        {
            int tr = dfs(e.to, t, std::min(pushed, e.cap - e.flow));
            if (tr > 0)
            {
                e.flow += tr;
                graph[e.to][e.rev].flow -= tr;
                return tr;
            }
        }
    }

    return 0;
}

/**
 *
 * Finds the maximum flow from a source node to a sink node using Dinic’s
 * algorithm. It starts by building a level graph using BFS where each node is
 * assigned a level based on how many steps it takes to reach it from the source.
 *
 * Once the level graph is built, it uses DFS to try and send flow from the
 * source to the sink. During the DFS, it follows only edges that have unused
 * capacity and lead to the next level. If a full path to the sink is found, the
 * algorithm pushes as much flow as it can through that path which is the
 * smallest available capacity along the way.
 *
 * When no more flow can be sent using the current level graph, it builds a new
 * level graph and tries again. If at some point the BFS fails to find a path
 * from the source to the sink, it means that no more flow can be pushed and the
 * algorithm stops.
 *
 * The total flow added up from all the successful DFS calls is then the
 * maximum flow through the network.
 *
 * Time complexity: O(E * V^2) where V is the number of nodes and E is the number
 * of edges. This is because in the worst case, the algorithm runs up to V phases
 * (BFS builds level graphs). In each phase, DFS can push flow through many paths
 * and can visit all E edges and V nodes which leads to O(E × V) per phase and
 * this can be repeated up to V times which makes the total complexity O(E * V^2).
 *
 * Space complexity: O(V + E) because the graph is stored using an adjacency list
 * where each node stores its outgoing edges, and each edge is only stored twice
 * (once in each direction for the residual graph).
 *
 * @returns The total amount of flow from the source to the sink.
 */
int dinic(int s, int t, int n)
{
    int flow = 0;

    while (bfs(s, t, n))
    {
        while (int pushed = dfs(s, t, INF))
        {
            flow += pushed;
        }
    }

    return flow;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int nodes{}, edges{}, source{}, sink{};
    cin >> nodes >> edges >> source >> sink;

    vector<std::tuple<int, int, int>> input_edges;

    for (int i = 0; i < edges; ++i)
    {
        int u{}, v{}, c{};
        cin >> u >> v >> c;
        add_edge(u, v, c);
        input_edges.push_back({u, v, c});
    }

    int flow = dinic(source, sink, nodes);

    vector<tuple<int, int, int>> flow_result;
    for (int u = 0; u < nodes; ++u)
    {
        for (const auto &e : graph[u])
        {
            if (e.flow > 0)
                flow_result.push_back({u, e.to, e.flow});
        }
    }

    cout << nodes << " " << flow << " " << flow_result.size() << "\n";
    for (auto &[u, v, f] : flow_result)
    {
        cout << u << " " << v << " " << f << "\n";
    }

    return 0;
}