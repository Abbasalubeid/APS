/**
 * Solves the "Suffix Array Re-construction" problem.
 *
 * Time Complexity: O(S * m + L) per test case where S is the number of
 * suffixes, m is the length of each suffix and L is the output string
 * length.
 * Space Complexity: O(L)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cout, std::cin, std::string, std::vector, std::pair;

/**
 * Merges a pattern into the partial reconstruction array at a specific
 * 0 based start index.
 *
 * Time Complexity: O(m) where m is the length of the pattern.
 * Space Complexity: O(1)
 */
bool merge_pattern(const string &pattern, vector<char> &result, int start_index)
{

    if (start_index + pattern.size() > result.size())
        return false;

    for (int i = 0; i < pattern.size(); ++i)
    {
        char want = pattern[i];
        int pos = start_index + i;

        if (result[pos] == '?')
            result[pos] = want;
        else if (result[pos] != want)
            return false;
    }
    return true;
}

/**
 * Applies one suffix constraint to the partial reconstruction at a specific
 * 1 based start position
 *
 * Time Complexity: O(m) where m is the length of the suffix.
 * Space Complexity: O(m)
 */
bool apply_constraint(int pos, const string &suffix, vector<char> &result)
{

    int start_index = pos - 1;

    int start_pos = -1;

    for (int i = 0; i < suffix.size(); ++i)
    {
        if (suffix[i] == '*')
        {
            start_pos = i;
            break;
        }
    }

    if (start_pos == -1)
        return merge_pattern(suffix, result, start_index);

    string left = suffix.substr(0, start_pos);
    string right = suffix.substr(start_pos + 1);

    int total_length = result.size() - start_index;
    int left_len = left.size();
    int right_len = right.size();

    if (!merge_pattern(left, result, start_index))
        return false;

    int right_start = start_index + (total_length - right_len);
    if (!merge_pattern(right, result, right_start))
        return false;

    return true;
}

/**
 * Constructs the final string of the given length by applying all suffix
 * constraints.
 *
 * Time Complexity: O(S * m + L) where S is the number of suffixes, m is
 * the length of each suffix and L is the final string length.
 *
 * Space Complexity: O(L) for the result array.
 *
 */
string reconstruct(int length, const vector<pair<int, string>> &suffixes)
{
    vector<char> result(length, '?');

    for (int i = 0; i < suffixes.size(); ++i)
    {
        int pos = suffixes[i].first;
        string suffix = suffixes[i].second;

        if (!apply_constraint(pos, suffix, result))
            return "IMPOSSIBLE";
    }

    for (int i = 0; i < length; ++i)
    {
        if (result[i] == '?')
            return "IMPOSSIBLE";
    }
    string final(result.begin(), result.end());
    return final;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tests{}, output_length{}, nr_suffixes{}, position{};
    string suffix{};

    cin >> tests;
    while (tests--)
    {
        cin >> output_length >> nr_suffixes;

        vector<pair<int, string>> suffixes(nr_suffixes);

        for (int i = 0; i < nr_suffixes; ++i)
        {
            cin >> position >> suffix;
            suffixes[i] = {position, suffix};
        }

        cout << reconstruct(output_length, suffixes) << "\n";
    }
    return 0;
}