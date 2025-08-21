/**
 * Dynamic programming solution to the classic 0/1 knapsack problem.
 *
 * Time complexity: O(n * c) where n is the number of items and c is the
 * knapsack capacity.
 *
 * Space complexity: O(n * c)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl;
using std::pair;
using std::vector;

/**
 * Solves the 0/1 knapsack problem using dynamic programming by building a DP
 * table. dp[i][w] stores the maximum value that can be obtained by
 * considering the first i items with a knapsack of capacity w.
 *
 * It starts by considering the first item and filling in the best possible
 * values for each capacity. Then it moves on to the second item and combines
 * it with the existing values from the first, updating the best values where
 * needed. This continues for all items, always reusing previous results to
 * build better solutions.
 *
 * For each item and capacity, there are two options: either the item is not
 * taken, in which case the value is copied from the row above at the same
 * capacity (the value without using this item), or the item is taken and its
 * value is added. When it's taken, the value from the row above is used,
 * but we move left by the weight of the current item. This shift represents
 * the best value we could get using the previous items and the remaining
 * capacity after fitting the current one. Adding the item's value to that
 * gives the total value if we include it.
 *
 * Once the table is complete, the chosen items are reconstructed by walking
 * backwards through the table. If the value at dp[i][w] differs from the value
 * above it, that means the current item was included in the solution because its
 * presence changed the total value. The item's index is then added to the answer,
 * and the capacity is reduced by that item's weight to continue the backtracking
 * process.
 *
 * Time complexity: O(n * c), where n is the number of items and c is the knapsack
 * capacity, since each item is processed for each possible capacity.
 *
 * Space complexity: O(n * c), because a value is stored for every (item, capacity)
 * pair in the DP table.
 *
 * @returns A list of indices of the items chosen (0-based)
 */

vector<int> knapsack_solver(int capacity, const vector<pair<int, int>> &items)
{
    int n = items.size();

    // dp[i][w] will hold max value using first i items with capacity w
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        int val = items[i - 1].first;
        int weight = items[i - 1].second;

        for (int w = 0; w <= capacity; ++w)
        {
            // not taking the item
            dp[i][w] = dp[i - 1][w];

            if (w >= weight)
                dp[i][w] = std::max(dp[i][w], dp[i - 1][w - weight] + val);
        }
    }

    // reconstruct the items used
    vector<int> chosen;
    int w = capacity;
    for (int i = n; i > 0; --i)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            chosen.push_back(i - 1);
            w -= items[i - 1].second;
        }
    }

    std::reverse(chosen.begin(), chosen.end());
    return chosen;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int capacity{}, nr_objects{};
    while (cin >> capacity >> nr_objects)
    {
        vector<pair<int, int>> items;

        for (int i = 0; i < nr_objects; ++i)
        {
            int value{}, weight{};
            cin >> value >> weight;
            items.push_back({value, weight});
        }

        vector<int> result = knapsack_solver(capacity, items);

        cout << result.size() << "\n";
        for (int i = 0; i < result.size(); ++i)
        {
            cout << result[i];
            if (i + 1 < result.size())
                cout << " ";
            else
                cout << "\n";
        }
    }

    return 0;
}
