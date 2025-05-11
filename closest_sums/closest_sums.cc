/**
 * Solves the closest sums problem using binary search.
 *
 * After parsing the integers, the solution calculates all possible sums of pairs
 * from these integers. These sums are stored in a set to ensure all values are
 * unique and sorted for later lookup.
 *
 * For each query, the solution uses a binary search on the sorted list of sums
 * to efficiently find the sum that is closest to the target specified in the
 * query.
 *
 * Time complexity: O(n^2 log n + m log n)
 * - O(n^2 log n) from generating all unique pairwise sums and inserting them
 * into a set.
 * - O(m log n) from answering m queries using binary search on the sorted list
 * of pairwise sums.
 * Since n ≤ 1000 and m ≤ 25, the n^2 log n term dominates the complexity, so the
 * overall time complexity can be simplified to O(n^2 log n).
 *
 * Space complexity: O(n^2). Storing n integers requires O(n) space and the set
 * of sums can potentially contain up to n(n-1)/2 sums requires O(n^2) space.
 *
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <set>

using std::cout, std::cin, std::vector, std::set, std::abs;
int main(int argc, char *argv[])
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int case_number{1}, n{0};
    while (cin >> n)
    {
        cout << "Case " << case_number << ":\n";
        ++case_number;
        int m{0};
        vector<int> input_nums(n);

        for (int i = 0; i < n; ++i)
            cin >> input_nums[i];

        cin >> m;

        set<int> sums;
        // Find and store all possible sums of pairs of integers
        // O(n^2) but its ok since n is small (2 ≤ n ≤ 1,000)
        for (int i = 0; i < input_nums.size(); ++i)
            for (int j = i + 1; j < input_nums.size(); ++j)
            {
                // Placed in sorted order automatically
                sums.insert(input_nums[i] + input_nums[j]); // O(log n)
            }

        // Convert set to vector to perform binary search
        vector<int> sorted_sums(sums.begin(), sums.end());

        int query{0};
        for (int i = 0; i < m; ++i)
        {
            cin >> query;

            int left{0}, right{(int)sorted_sums.size() - 1};
            int closest_sum = sorted_sums[0];
            int min_diff = abs(closest_sum - query);

            // Binary search to to find closest sum
            while (left <= right)
            {
                int mid = (left + right) / 2;

                int current_diff = abs(sorted_sums[mid] - query);

                if (current_diff < min_diff)
                {
                    closest_sum = sorted_sums[mid];
                    min_diff = current_diff;
                }

                if (sorted_sums[mid] < query)
                    left = mid + 1;
                else if (sorted_sums[mid] > query)
                    right = mid - 1;
                else // Found closest
                    break;
            }
            cout << "Closest sum to " << query
                 << " is " << closest_sum << ".\n";
        }
    }

    return 0;
}