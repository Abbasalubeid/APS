/**
 * Solves the "Dvaput" problem.
 *
 * Finds the length of the longest substring that appears at least twice by first
 * building a suffix array (array of sorted suffixes alphabetically) and then
 * building the LCP (Longest Common Prefix) array which measures how many starting
 * characters adjacent suffixes from suffix array share) using Kasai’s algorithm.
 *
 * Once the LCP array is built, the maximum value in it gives the length of the
 * longest repeated substring because it represents the largest common prefix
 * between any two neighboring suffixes.
 *
 * Time Complexity: O(n log n) where n is the length of the input string.
 * Space Complexity: O(n)
 *
 * @author Abbas Alubeid
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout, std::cin, std::string, std::vector;

string global_text{};
vector<int> global_rank;
int global_length{};
int global_n{};

/**
 * Comparison function used while sorting suffix indices.
 *
 * Each suffix is represented by its starting index in the string. When sorting,
 * this function decides which suffix should come first in lexicographic order.
 *
 * It first compares the current ranks of the two suffixes. If their ranks are
 * different, the one with the smaller rank (meaning it starts with a smaller
 * substring so far) comes first. If the ranks are the same, it means the first
 * part of both suffixes is identical in the current round so we look further
 * ahead by comparing the ranks of the parts that come right after.
 *
 * For example, if we are currently comparing by 4 character prefixes and two
 * suffixes are identical in those 4 characters, we compare the next 4 characters
 * by checking the ranks at positions i + 4 and j + 4. If a suffix goes over the
 * end of the string, it gets a rank of -1 to make sure shorter suffixes come
 * first.
 *
 */
bool compare_suffixes(int i, int j)
{
    if (global_rank[i] != global_rank[j])
        return global_rank[i] < global_rank[j];

    int next_i = i + global_length;
    int next_j = j + global_length;

    int rank_next_i;
    if (next_i < global_n)
        rank_next_i = global_rank[next_i];
    else
        rank_next_i = -1;

    int rank_next_j;
    if (next_j < global_n)
        rank_next_j = global_rank[next_j];
    else
        rank_next_j = -1;

    return rank_next_i < rank_next_j;
}

/**
 * Builds the suffix array of a string using the prefix doubling algorithm.
 *
 * The function starts by appending a $ symbol to the end of the string to
 * mark its true end so no suffix is a prefix of another. It then gives each
 * suffix an initial rank based on its first character. These ranks are just
 * the ASCI values of the letters so at first, suffixes are only compared
 * by their starting letter.
 *
 * After that, the algorithm sorts all suffixes using their current ranks
 * in rounds. Each round uses twice as many starting characters as the previous one.
 * Twice as many because each rank from the previous round already represents a
 * block of that many characters so combining two consecutive ranks lets the
 * algorithm compare prefixes twice as long without rechecking every character
 *
 * This process continue while the compared prefix length is smaller than the
 * string length. Because the number of compared characters doubles every round,
 * the algorithm only needs log n rounds to finish. The result array lists
 * all suffixes in alphabetical order by their starting positions in the text.
 *
 * Time Complexity: O(n log^2 n) where n is the length of the input string.
 * This is because the string is resorted in log n rounds and each round
 * performs an O(n log n) sort from std::sort (could be even better with radix sort)
 *
 * Space Complexity: O(n) for the suffix array and rank arrays.
 */
vector<int> build_suffix_array(const string &input)
{
    global_text = input + "$";
    global_n = global_text.size();

    vector<int> suffix_array(global_n);
    global_rank.resize(global_n);

    for (int i = 0; i < global_n; ++i)
    {
        suffix_array[i] = i;
        global_rank[i] = global_text[i];
    }

    global_length = 1;
    while (global_length < global_n)
    {
        std::sort(suffix_array.begin(), suffix_array.end(), compare_suffixes);

        vector<int> new_rank(global_n);
        new_rank[suffix_array[0]] = 0;

        for (int i = 1; i < global_n; ++i)
        {
            int prev_suffix = suffix_array[i - 1];
            int curr_suffix = suffix_array[i];

            if (compare_suffixes(prev_suffix, curr_suffix))
                new_rank[curr_suffix] = new_rank[prev_suffix] + 1;
            else
                new_rank[curr_suffix] = new_rank[prev_suffix];
        }

        global_rank = new_rank;
        global_length = global_length * 2;
    }

    suffix_array.erase(suffix_array.begin());
    return suffix_array;
}

/**
 * Builds the LCP (Longest Common Prefix) array.
 *
 * For each suffix, finds how many starting characters it shares with the
 * next suffix in sorted order. Uses Kasai’s algorithm which avoids repeated
 * comparisons by remembering part of the previous result.  The remembering
 * is done by keeping track of how many characters matched in the last step
 * (k) and reusing that value as a starting point for the next.
 *
 * Time Complexity: O(n) where n is the length of the input string. This is because
 * each character is compared at most twice, once when increasing k while characters
 * match and once when decreasing k after moving to the next suffix.
 * Space Complexity: O(n)
 */
vector<int> build_lcp(const string &s, const vector<int> &suffix_array)
{
    int n = s.size();
    vector<int> rank(n, 0), lcp(n - 1, 0);

    for (int i = 0; i < n; ++i)
        rank[suffix_array[i]] = i;

    int k{};
    for (int i = 0; i < n; ++i)
    {
        if (rank[i] == n - 1)
        {
            k = 0;
            continue;
        }

        int j = suffix_array[rank[i] + 1];

        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            ++k;

        lcp[rank[i]] = k;

        if (k)
            --k;
    }
    return lcp;
}

/**
 * Finds and returns the maximum LCP value.
 * This value represents the length of the longest substring
 * that occurs more than once.
 *
 * The idea is that after sorting all suffixes alphabetically,
 * any that start the same way end up right next to each other.
 * That means the longest repeated substring must appear as the
 * longest shared beginning (LCP) between two neighboring suffixes
 * in that sorted list. So by building the suffix array and then
 * searching for the maximum LCP value, we find the answer.
 *
 * Time Complexity: O(n log^2 n) because of the suffix array building
 * Space Complexity: O(n)
 */
int solve(const string &s)
{
    vector<int> suffix_array = build_suffix_array(s);
    vector<int> lcp = build_lcp(s, suffix_array);
    int max_lcp{};
    for (int val : lcp)
    {
        max_lcp = std::max(max_lcp, val);
    }
    return max_lcp;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int l{};
    string s{};

    cin >> l >> s;
    cout << solve(s) << "\n";

    return 0;
}