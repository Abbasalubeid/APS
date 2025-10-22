/**
 * Solves the "Chopping Wood" problem.
 *
 * The solution uses a greedy algorithm with a priority queue to determine the order
 * in which tree nodes were removed. Given a sequence of n integers representing
 * the parent nodes that remain after each cut, the algorithm reconstructs which
 * leaf nodes were cut at each step by tracking the degree (number of connections)
 * of each node.
 *
 * Time complexity: O(n log n) where n is the number of cuts.
 *
 * Space complexity: O(n)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using std::cout, std::cin, std::vector, std::priority_queue, std::greater;

/**
 * Reconstructs the sequence of leaf nodes that were cut from the tree.
 * Prints the cutting sequence or "Error" if reconstruction fails.
 *
 * Time complexity: O(n log n) where n is the number of cuts. This is from the
 * priority queue operations (push and pop) which each take O(log n) time.
 *
 * Space complexity: O(n) for storing the degree array, priority queue, and result
 * vector.
 *
 */
void solve(int n, vector<int> &v)
{
    vector<int> degree(n + 2, 1);

    for (int vertex : v)
    {
        ++degree[vertex];
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n + 1; ++i)
    {
        if (degree[i] == 1)
            pq.push(i);
    }

    vector<int> result{};
    for (int i = 0; i < n; ++i)
    {

        int u = pq.top();
        pq.pop();
        result.push_back(u);

        --degree[v[i]];
        if (degree[v[i]] == 1)
            pq.push(v[i]);
    }

    if ((pq.size() != 1 || pq.top() != n + 1))
    {
        cout << "Error\n";
    }
    else
    {
        for (int u : result)
        {
            cout << u << "\n";
        }
    }
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n{};

    while (cin >> n)
    {
        vector<int> v{};
        for (int i = 0; i < n; ++i)
        {
            int num{};
            cin >> num;
            v.push_back(num);
        }

        solve(n, v);
    }

    return 0;
}