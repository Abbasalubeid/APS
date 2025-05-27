/**
 * Solves the minimum cut problem using Dinic's max flow algorithm and a final
 * BFS to identify all nodes that are still reachable from the source in the
 * residual graph since these reachable nodes form the source side of the minimum
 * cut (from max-flow min-cut theorem).
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

/**
 *
 * Finds the minimum cut from a given source node to a sink node.
 *
 * It first computes the maximum flow using Dinic’s algorithm. Once the maximum
 * flow is computed, a BFS is performed in the residual graph to find all nodes
 * that are still reachable from the source. These reachable nodes form the set U
 * such that s in U and t not in U. The edges going from U to the rest of the
 * graph (to nodes not reachable from s) are fully saturated (flow equals their
 * capacity) and together these edges define the minimum cut (from max-flow min
 * cut theorem). This is because if any of those edges had remaining capacity,
 * the sink would still be reachable from the source through the residual graph
 * which contradicts the fact that the maximum flow has already been reached.
 *
 * Time complexity: O(E * V^2) where V is the number of nodes and E is the number
 * of edges because of the Dinic’s algorithm step. The additional BFS for
 * finding the reachable nodes takes O(E + V) which is nothing compared to the
 * max-flow computation.
 *
 * Space complexity: O(V + E).
 *
 * @returns A list of nodes representing the source side of the minimum cut set U
 *          where the total capacity of outgoing edges from U to the rest of the
 *          graph is minimized.
 */
vector<int> min_cut(int s, int t, int n)
{
    dinic(s, t, n);

    // BFS to find reachable nodes from source
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (const auto &e : graph[u])
        {
            if (!visited[e.to] && e.cap - e.flow > 0)
            {
                visited[e.to] = true;
                q.push(e.to);
            }
        }
    }

    vector<int> cut_set;
    for (int i = 0; i < n; ++i)
    {
        if (visited[i])
            cut_set.push_back(i);
    }

    return cut_set;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int nodes{}, edges{}, source{}, sink{};
    cin >> nodes >> edges >> source >> sink;

    for (int i = 0; i < edges; ++i)
    {
        int u{}, v{}, c{};
        cin >> u >> v >> c;
        add_edge(u, v, c);
    }

    vector<int> result = min_cut(source, sink, nodes);

    cout << result.size() << "\n";
    for (int u : result)
    {
        cout << u << "\n";
    }
    cout << endl;
    return 0;
}