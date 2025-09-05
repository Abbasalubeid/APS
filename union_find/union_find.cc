/**
 * Implements the Union Find data structure with path compression and union by rank
 * optimization.
 *
 * The Union Find data structure manages a collection of disjoint (non-overlapping)
 * sets. It supports two primary operations: finding the set of an element and
 * merging two sets.
 *
 * The data structure is managed using two vectors (parents and ranks):
 * Parents: Each element points to a parent in the tree structure that represents
 * the set. Initially, every element is its own parent which indicates that each
 * element forms a set by itself.
 * Ranks: This vector keeps track of the tree depth for each root node to help to
 * keep the trees as flat as possible.
 *
 * Operations on Union Find are optimized using:
 * Path Compression: During the recursive find operation, make every node on the
 * path point directly to the root or the representative for that set. This flattens
 * the structure of the union trees and speed up future calls.
 *
 * Union by rank (or size): During the union operation, attach the tree of the lower
 * rank (smaller size) to the root of the higher rank to keep the depth of the tree
 * low.
 *
 * Time complexity: For m operations on n elements, the amortized time complexity is
 * O(m α(n)) where α(n) is the inverse Ackermann function which grows very slowly
 * and is constant for almost all practical purposes.
 *
 * Space complexity: O(n) where n is the number of elements, to store the parent and
 * rank of each element.
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <string>
#include <vector>

using std::cout, std::cin, std::string, std::vector, std::endl;

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

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int elements{};
    cin >> elements;

    union_find uf(elements);

    int operations{};
    cin >> operations;

    string operation{};
    int element1{}, element2{};
    for (int i = 0; i < operations; ++i)
    {
        cin >> operation >> element1 >> element2;

        if (operation == "?")
        {
            if (uf.same(element1, element2))
                cout << "yes" << "\n";
            else
                cout << "no" << "\n";
        }
        else if (operation == "=")
            uf.merge(element1, element2);
    }
}