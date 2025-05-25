/**
 * Solves the maximum flow problem using the Ford-Fulkerson algorithm.
 *
 * Time complexity: O(F * E) where F is the value of the maximum flow
 * and E is the number of edges.
 *
 * Space complexity: O(V + E) for storing the graph and flow values.
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <climits>
#include <tuple>

using std::cin, std::cout, std::endl, std::vector, std::tuple;

const int INF = INT_MAX;
const int MAX_N = 501;

struct Edge
{
    int to, rev;
    int cap, flow;
};

vector<vector<Edge>> graph(MAX_N);
bool visited[MAX_N];

/**
 * Adds a forward and backward edge to the residual graph.
 * The reverse edge has initial capacity 0 but is updated
 * during flow pushes to allow backtracking.
 */
void add_edge(int u, int v, int c)
{
    graph[u].push_back({v, (int)graph[v].size(), c, 0});
    graph[v].push_back({u, (int)graph[u].size() - 1, 0, 0});
}

/**
 * Recursive DFS to find an augmenting path from node u to sink t in the residual
 * graph. Only paths with positive residual capacity are considered because they
 * represent valid routes where additional flow can be pushed.
 *
 * Updates the flow along the path if an augmenting path is found.
 * Returns the amount of flow that can be pushed through the path or 0 if no
 * exists.
 */
int dfs(int u, int t, int flow, vector<bool> &visited)
{
    if (u == t)
        return flow;

    visited[u] = true;

    for (Edge &e : graph[u])
    {
        if (!visited[e.to] && e.cap - e.flow > 0)
        {
            int pushed = dfs(e.to, t, std::min(flow, e.cap - e.flow), visited);
            if (pushed > 0)
            {
                e.flow += pushed;
                graph[e.to][e.rev].flow -= pushed;
                return pushed;
            }
        }
    }

    return 0;
}

/**
 * Ford-Fulkerson algorithm to find the maximum flow using DFS to find augmenting
 * paths.
 *
 * Uses DFS to repeatedly find augmenting paths in the residual graph. The
 * algorithm terminates when no more augmenting paths exist. For each found path,
 * the flow is increased by the minimum residual capacity along the path.
 *
 * Time complexity: O(F * E) where F is the value of the maximum flow and E is the
 * number of edges. This is because in each iteration, DFS finds one augmenting
 * path and increases the flow by at least 1 unit and each DFS call checks at
 * most E edges, which can happen up to F times.
 *
 * Space complexity: O(V + E) for storing the graph and flow values.
 */
int ford_fulkerson(int s, int t)
{
    int flow = 0;

    while (true)
    {
        vector<bool> visited(MAX_N, false);
        int pushed = dfs(s, t, INF, visited);
        if (pushed == 0)
            break;
        flow += pushed;
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

    int flow = ford_fulkerson(source, sink);

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
