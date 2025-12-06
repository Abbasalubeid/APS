/**
 * Solves the Islands Hopping problem using Kruskals
 * algorithm.
 *
 * This problem is solved by treating it as a graph
 * problem where each island represents a node and
 * potential bridges between islands represent weighted
 * edges with weights equivalent to the Euclidean distance
 * between islands.
 *
 * The task of finding the minimal set of bridges that connects all islands at
 * the lowest possible total length maps directly into finding a Minimum Spanning
 * Tree (MST) of a graph which can be efficiently solved using Kruskal's
 * algorithm.
 *
 * Time complexity: O(E log E) where E is the number of edges
 *
 * Space complexity: O(N + E) where N is the number of nodes and E is the number
 * of edges
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>

using std::cout, std::cin, std::endl, std::string, std::vector, std::pair, std::sort, std::swap;

struct edge
{
    int u{}, v{};
    double w{};
};

struct point
{
    double x{}, y{};
};

struct union_find
{

    vector<int> parents;
    vector<int> ranks;

    union_find(int elements)
    {
        ranks.assign(elements, 1);

        parents.reserve(elements);
        for (int i = 0; i < elements; ++i)
            parents.push_back(i);
    }

    /**
     * Finds and returns the root or represantative for the set that
     * contains 'a'
     *
     * If 'a' is not its own represantative, traverse upwards untill the root is
     * found. Along the way, update the "parents" list (path compression) to speed up
     * next call
     *
     * Time complexity: Almost constant or O(α(n)) where α(n) is the inverse
     * Ackermann function because of path compression
     */
    int find(int a)
    {
        int current = a;

        while (current != parents[current])
        {
            parents[current] = parents[parents[current]];
            current = parents[current];
        }

        return current;
    }

    /**
     * Test whether a and b are in the same set
     *
     * Time complexity: O(α(n)) because of the two find operations.
     */
    bool same(int a, int b)
    {
        return find(a) == find(b);
    }

    /**
     * Merge (union) the sets containing the elements a and b
     *
     * Find representatives or roots of 'a' and 'b' and merge them based on their
     * ranks to keep the tree shallow
     *
     * Time complexity: O(α(n)) because of the two find operations.
     *
     */
    void merge(int a, int b)
    {
        int root_a = find(a);
        int root_b = find(b);

        if (root_a != root_b)
        {
            if (ranks[root_a] <= ranks[root_b])
            {
                parents[root_a] = root_b;
                ranks[root_b]++;
            }
            else
            {
                parents[root_b] = root_a;
                ranks[root_a]++;
            }
        }
    }
};

double euclidian_distance(point A, point B)
{
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(x * x + y * y);
}

/**
 * Kruskals algoritm to find the minimum spanning tree
 *
 * The algorithm works by first sorting all the edges based on their weights in
 * ascending order.
 * As each sorted edge is processed, the union-find structure is used to check if
 * the current edge’s vertices (u, v) are in the same set:
 * 1. If same(u, v) returns true, adding this edge would form a cycle, so its
 * skipped
 * 2. If false, they are in different sets and adding this edge would not form a
 * cycle so we then perform merge(u, v) to combine the sets and add (u,v) to the
 * result.
 *
 * Time complexity: O(E log E) due to sorting of edges.
 * After sorting, the remaining operations (find and merge in union-find)
 * are almost constant per operation because of path compression and the
 * efficiency of the inverse Ackermann function making the processing of
 * edges after sorting linear with respect to the number of edges.
 *
 * Space complexity: O(N + E) where N is the number of nodes and E is the number
 * of edges, used by the union-find data structure and edge list.
 */
pair<vector<edge>, double> kruskals(vector<edge> &edges, int nr_nodes)
{

    sort(edges.begin(), edges.end(), [](const auto &edge1, const auto &edge2)
         { return edge1.w < edge2.w; });

    union_find uf(nr_nodes);

    vector<edge> result;
    double total_w{};

    for (auto &edge : edges)
    {
        if (uf.same(edge.u, edge.v))
            continue;
        else
        {
            uf.merge(edge.u, edge.v);

            if (edge.u > edge.v)
                swap(edge.u, edge.v);

            result.push_back(edge);
            total_w += edge.w;
        }
    }

    return {result, total_w};
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int test_cases{}, islands{};

    cin >> test_cases;

    while (test_cases--)
    {
        cin >> islands;

        vector<point> coords(islands);

        for (int i = 0; i < islands; ++i)
        {
            cin >> coords[i].x >> coords[i].y;
        }

        vector<edge> edges;

        for (int i = 0; i < islands; ++i)
        {
            for (int j = i + 1; j < islands; ++j)
            {
                double weight = euclidian_distance(coords[i], coords[j]);
                edges.push_back({i, j, weight});
            }
        }

        auto [result, total_w] = kruskals(edges, islands);

        cout << std::fixed << total_w << "\n";
    }
}