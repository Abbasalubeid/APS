/**
 * Finds the minimum spanning tree (MST) of a given graph
 * using Kruskal's algorithm.
 *
 * Kruskal's algorithm is a greedy algorithm that constructs
 * an MST by sorting all the edges in the graph by their
 * weight and then adding them one by one to the
 * MST.
 *
 * Time complexity: O(E log E) where E is the number of edges
 *
 * Space complexity: O(N + E) where N is the number of nodes
 * and E is the number of edges
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using std::cout, std::cin, std::endl, std::string, std::vector, std::pair, std::sort, std::swap;

struct edge
{
    int u{}, v{}, w{};
};

struct union_find
{

    vector<int> parents;
    vector<int> ranks;

    union_find(int elements)
    {
        // All elements have same rank initially
        ranks.assign(elements, 1);

        parents.reserve(elements);
        for (int i = 0; i < elements; ++i)
            parents.push_back(i); // Every element is its own represantative
    }

    /**
     * Finds and returns the root or represantative for the set that contains 'a'
     *
     * If 'a' is not its own represantative, traverse upwards untill the root is
     * found.
     * Along the way, update the "parents" list (path compression) to speed up next
     * call
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

/**
 * Kruskals algoritm to find the minimum spanning tree
 *
 * The algorithm works by first sorting all the edges based
 * on their weights in ascending order.
 * As each sorted edge is processed, the union-find structure
 * is used to check if the current edge’s vertices (u, v) are
 * in the same set:
 * 1. If same(u, v) returns true, adding this edge would form
 * a cycle, so itsskipped
 * 2. If false, they are in different sets and adding this
 * edge would not form a cycle so we then perform merge(u, v)
 * to combine the sets and add (u,v) to the result.
 *
 * Time complexity: O(E log E) due to sorting of edges.
 * After sorting, the remaining operations (find and merge in
 * union-find) are almost constant per operation because of
 * path compression and the efficiency of the inverse
 * Ackermann function making the processing of edges after
 * sorting linear with respect to the number of edges.
 *
 * Space complexity: O(N + E) where N is the number of nodes
 * and E is the number of edges, used by the union-find data
 * structure and edge list.
 */
pair<vector<edge>, int> kruskals(vector<edge> &edges, int nr_nodes)
{

    sort(edges.begin(), edges.end(), [](const auto &edge1, const auto &edge2)
         { return edge1.w < edge2.w; });

    union_find uf(nr_nodes);

    vector<edge> result;
    int total_w{};

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

    int nr_nodes{}, nr_edges{};

    int u{}, v{}, w{};

    while (cin >> nr_nodes >> nr_edges && (nr_nodes != 0 || nr_edges != 0))
    {
        vector<edge> edges;
        for (int i = 0; i < nr_edges; ++i)
        {
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
        }
        auto [result, total_w] = kruskals(edges, nr_nodes);

        if (result.size() == nr_nodes - 1 || nr_nodes == 1)
        {

            sort(result.begin(), result.end(), [](const auto &edge1, const auto &edge2)
                 {
               if (edge1.u == edge2.u)
                   return edge1.v < edge2.v; 
               else 
                   return edge1.u < edge2.u; });

            cout << total_w << "\n";
            for (auto &e : result)
            {
                cout << e.u << " " << e.v << " " << "\n";
            }
        }
        else
            cout << "Impossible" << "\n";
    }
}