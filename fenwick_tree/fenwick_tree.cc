/**
 * Fenwick Tree implementation for efficient query and update of prefix sums.
 *
 * Prefix sums can be calculated directly in O(1) time using a simple
 * prefix array, but then, updating this array is costly requiring O(n) time
 * for each update. The Fenwick Tree provides an efficient compromise
 * allowing both update and query operations to be performed in logarithmic
 * time.
 *
 * Time complexity: O(logn) for both update and sum operations because
 * traversing up or down the tree includes jumping over segments of the tree
 * that double in size at each step leading to a logarithmic number of steps.
 *
 * Space complexity: O(n) because of the vector to maintain the tree.
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>

using std::cout, std::cin, std::vector, std::endl, std::flush;

/**
 * In the Fenwick Tree, each node of the tree covers a range of elements
 * from the input and only a logarithmic number of nodes are involved in
 * each query or update operation.
 *
 * To traverse the tree, we use binary representation of indices and 2's
 * complement. Finding a node's parent is done by flipping the lowest set
 * bit (rightmost 1) of the node's index. For example, the node at index 10
 * (1010 in binary) has a parent at index 8 (1000 in binary). In code, this
 * is done by subtracting the lowest set bit obtained through the operation
 * i & -i where -i is the 2's compliment of i. For example, for i = 10, i &
 * -i gives 0010 and subtracting this from 1010 (10) results in 1000 (8)
 *
 * Prefix sums are computed by moving downward through the tree with
 * i -= i & -i and updates are propagated upward using i += i & -i
 */
struct fenwick_tree
{
    vector<long long> tree;

    fenwick_tree(int size) : tree(size + 1, 0) {}

    /**
     * Compute the sum of the first numbers up to but not including a[end]
     *
     * Time complexity: O(logn)
     */
    long long sum(int i)
    {
        long long result = 0;
        while (i > 0)
        {
            result += tree[i];
            i -= i & -i;
        }
        return result;
    }

    /**
     * Increase a[i] with x
     *
     * Time complexity: O(logn)
     */
    void add(int i, long long x)
    {
        i = i + 1; // 1 based index
        while (i < tree.size())
        {
            tree[i] += x;
            i += i & -i;
        }
    }
};

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int size{}, operations{};
    cin >> size >> operations;

    fenwick_tree tree(size);

    for (int i = 0; i < operations; i++)
    {
        char operation{};
        int index{};
        cin >> operation;
        if (operation == '+')
        {
            long long element{};
            cin >> index >> element;
            tree.add(index, element);
        }
        else if (operation == '?')
        {
            cin >> index;
            cout << tree.sum(index) << "\n";
        }
    }

    cout << flush;
}