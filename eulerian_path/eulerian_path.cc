/**
 * Solves the Eulerian Path problem using Hierholzer’s algorithm.
 *
 * Time complexity: O(V + E) Where V is the number of nodes and E is the number
 * of edges since each node and edge is visited once.
 *
 * Space complexity: O(V + E) for storing the graph and tracking the path.
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <deque>

using std::cin, std::cout, std::endl;
using std::vector, std::stack, std::deque;

/**
 * Checks whether an Eulerian path can exist in the directed graph
 * by analyzing the in degrees and out degrees (the number of incoming
 * and outgoing edges) of each node.
 *
 * If every node has the same in degree and out degree, there is an Eulerian
 * circuit and we can start at any node that has outgoing edges. Otherwise there
 * must be exactly one node whose out degree is larger than its in degree by one
 * (the start) and exactly one node whose in degree is larger than its out degree by
 * one (the end), and all other nodes must have equal in and out degrees.
 * This is because every time we arrive at a node we also need to leave on an
 * unused edge so arriving and leaving cancel out at the internal nodes while
 * the start has one extra out and the end has one extra in.
 *
 * Time complexity: O(n) where n is the number of nodes because of the loops.
 *
 * Space complexity: O(1)
 *
 * @returns The index of a valid starting node if the graph meets the necessary
 * degree conditions and -1 otherwise.
 */
int find_start_node(const vector<int> &in_deg, const vector<int> &out_deg, int n)
{
    int start = -1;
    int end = -1;

    for (int i = 0; i < n; ++i)
    {
        if (out_deg[i] - in_deg[i] == 1)
        {
            if (start != -1)
                return -1;
            start = i;
        }
        else if (in_deg[i] - out_deg[i] == 1)
        {
            if (end != -1)
                return -1;
            end = i;
        }
        else if (in_deg[i] != out_deg[i])
        {
            return -1;
        }
    }

    // If no special start node is required, pick any node with outgoing edges
    if (start == -1)
    {
        for (int i = 0; i < n; ++i)
        {
            if (out_deg[i] > 0)
                return i;
        }
    }

    return start;
}

/**
 * Hierholzer’s algorithm to walk through the graph using every edge exactly
 * once. The main idea is to perform a DFS until we run out of outgoing edges,
 * then backtrack and record the path. A naive DFS can go to the end node by
 * skipping some edges, this is why we do the backtracking approach to force
 * the DFS to visit all edges before stopping.
 *
 * Time complexity: O(V + E) Where V is the number of nodes and E is the number
 * of edges since each node and edge is visited once.
 * Space complexity: O(V + E) for storing the graph and tracking the path.
 *
 @returns The Eulerian path as a list of node indices.
 */
vector<int> hierholzer(int start, vector<deque<int>> &graph)
{
    vector<int> path;
    stack<int> stack;
    stack.push(start);

    while (!stack.empty())
    {
        int u = stack.top();

        if (!graph[u].empty())
        {
            int v = graph[u].front();
            graph[u].pop_front();
            stack.push(v);
        }
        else
        {
            path.push_back(u);
            stack.pop();
        }
    }

    std::reverse(path.begin(), path.end());
    return path;
}

/**
 * Solves a test case by checking if a valid path is possible using the degree
 * conditions and if the graph is valid, it applies Hierholzer’s algorithm to build
 * the path. Also checks for disconnected edges by making sure the path
 * actually uses every edge in the graph (by comparing edge size to path size).
 *
 * @returns 0 if an Eulerian path is possible and -1 otherwise.
 */
int solve(int n, int m, const vector<deque<int>> &graph,
          const vector<int> &in_deg, const vector<int> &out_deg,
          vector<int> &path_out)
{
    int start_node = find_start_node(in_deg, out_deg, n);

    if (start_node == -1)
        return -1;

    auto graph_copy = graph;
    auto path = hierholzer(start_node, graph_copy);

    if (path.size() != m + 1)
        return -1;

    path_out = path;
    return 0;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n{}, m{};
    while (cin >> n >> m && (n || m))
    {
        vector<deque<int>> graph(n);
        vector<int> in_deg(n, 0), out_deg(n, 0);

        for (int i = 0; i < m; ++i)
        {
            int u{}, v{};
            cin >> u >> v;
            graph[u].push_back(v);
            out_deg[u]++;
            in_deg[v]++;
        }

        vector<int> path;
        int status = solve(n, m, graph, in_deg, out_deg, path);

        if (status == -1)
        {
            cout << "Impossible\n";
        }
        else
        {
            for (size_t i = 0; i < path.size(); ++i)
            {
                cout << path[i] << (i + 1 < path.size() ? " " : "\n");
            }
        }
    }

    return 0;
}
