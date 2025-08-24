/**
 * Solves the longest increasing subsequence problem using patience sort.
 *
 * Time complexity: O(n log n) where n is the size of the input sequence.
 * Space complexity: O(1)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::cin, std::cout, std::endl;
using std::vector;

/**
 * Finds the position of the current element in the existing piles during the
 * patience sorting process using binary search on the pile tops to determine
 * where the current number should be placed.
 *
 * If there is a pile whose top is greater than or equal to the current number,
 * we place it there. If there is no such pile, this number starts a new pile,
 * meaning we have found a longer potential subsequence.
 *
 * The searching follows a greedy rule, for each number, we always place
 * current element on the leftmost pile whose top is greater than or equal to
 * the number. Placing it as far left as possible keeps the pile tops as small
 * as they can be which leaves more flexibility for future elements to extend
 * these subsequences.
 *
 * Time complexity: O(log n) where n is the current number of piles.
 *
 * Space complexity: O(1)
 */
int binary_search(const vector<int> &seq, const vector<int> &pile_tops, int value)
{
    int low{}, high = pile_tops.size();
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (seq[pile_tops[mid]] < value)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}

/**
 * Solves the longest increasing subsequence problem using patience sorting.
 *
 * The function iterates through the sequence from left to right and for each
 * element, we find the first pile whose top card is greater than or equal to
 * it and place it there. If no such pile exists, we start a new pile with this
 * element. By doing this, we build piles where the number of piles at the end
 * represents the length of the longest increasing subsequence. Since the cards
 * within a pile form a decreasing sequence, any increasing subsequence can take
 * at most one card from each pile so the number of piles is always greater than
 * or equeal to the length of the longest increasing subsequence.
 *
 * While building the piles, we also keep track of the position of the element
 * that comes right before the current one in the subsequence we are forming.
 * Each time we place a number on a pile that is not the first pile, we record
 * the index of the top element from the pile just to its left. This creates a
 * simple chain that links every element to the one it follows in the sequence
 * which make it possible to rebuild the longest increasing subsequence later by
 * tracing these links backwards.
 *
 * The efficiency of this approach comes from the binary search that quickly
 * determines the position of each element within the current piles.
 *
 * Time complexity: O(n log n) where n is the size of the input sequence since we
 * do a binary search for each of the n elements.
 *
 * Space complexity: O(n) for pile information and predecessor links
 * for each element to reconstruct the result.
 *
 * @returns A list of indices of the longest increasing subsequences in the input.
 */
vector<int> lis(const vector<int> &seq)
{
    int n = seq.size();
    vector<int> pile_tops, prev(n, -1), result;

    for (int i = 0; i < n; ++i)
    {
        int pos = binary_search(seq, pile_tops, seq[i]);

        if (pos == pile_tops.size())
            pile_tops.push_back(i);
        else
            pile_tops[pos] = i;

        if (pos > 0)
            prev[i] = pile_tops[pos - 1];
    }

    int cur = pile_tops.back();
    while (cur != -1)
    {
        result.push_back(cur);
        cur = prev[cur];
    }

    std::reverse(result.begin(), result.end());
    return result;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n{}, num{};
    while (cin >> n)
    {
        vector<int> seq;
        for (int i = 0; i < n; ++i)
        {
            cin >> num;
            seq.push_back(num);
        }

        vector<int> result = lis(seq);

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
