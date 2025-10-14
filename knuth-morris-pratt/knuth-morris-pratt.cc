/**
 * Solves the string matching problem using Knuth-Morris-Pratt (KMP) algorithm
 *
 * Time Complexity: O(n + m) where n is the length of the text and m is the
 * length of the pattern
 * Space Complexity: O(m)
 *
 * The KMP algorithm solves the problem in linear time instead of a simple quadratic
 * comparision.
 * The algorithm uses an LPS array for the pattern to scan through the text.
 * This LPS array tells us for each position i in the pattern, the longest proper
 * prefix of pattern[0..i] that is also a suffix of pattern[0..i].
 *
 * For example, for the pattern "ABAB", the LPS array is built like this:
 * Index 0: Substring is "A". There is no proper prefix that is also a suffix, so
 * LPS[0] = 0.
 * Index 1: Substring is "AB". No common prefix-suffix, so LPS[1] = 0.
 * Index 2: Substring is "ABA". The prefix "A" is also the suffix "A", so LPS[2] =
 * 1.
 * Index 3: Substring is "ABAB". The prefix "AB" is also the suffix "AB",
 * so LPS[3] = 2.
 * So, for "ABAB", the final LPS array is:
 * pattern:    A   B   A   B
 * indices:    0   1   2   3
 * LPS:        0   0   1   2
 *
 * When searching the text, if there is a mismatch after j matched characters, we
 * use the value of LPS[j - 1] to know how far we can skip ahead without losing a
 * possible match. This means we don't start over at the beginning of the pattern
 * and only pass through the text once to find all valid matches.
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <string>
#include <vector>

using std::cout, std::cin, std::string, std::vector;

/**
 * Returns the prefix-suffix table for a given string pattern
 *
 * For each position in the pattern, the LPS vector stores the length of the
 * longest proper prefix of the substring pattern[0...i] which is also a suffix
 * of this substring.
 *
 * Time complexity: O(m) where m is the length of the pattern
 * Space complexity: O(m) for the lps vector
 */
vector<int> get_lps(const string &pattern)
{
    vector<int> lps(pattern.size(), 0);
    int i{1}, j{0};
    while (i < pattern.size())
    {
        if (pattern[i] == pattern[j])
        {
            ++j;
            lps[i++] = j;
        }
        else
        {
            if (j != 0)
                j = lps[j - 1];
            else
                ++i;
        }
    }

    return lps;
}

/**
 * Finds all occurrences of a pattern in a text using the KMP algorithm.
 *
 * This algorithm uses the lps array for the pattern to scan through the text.
 * Each time a mismatch occurs, the LPS vector helps finding how far we can skip
 * without losing a possible match. This makes the funciton going through the
 * the given text only once.
 *
 * Time Complexity: O(n + m) where n is the length of the text and m is the
 * length of the pattern
 * Space Complexity: O(m) for the lps array
 */
vector<int> kmp(const string &pattern, const string &text)
{
    vector<int> result;
    vector<int> lps = get_lps(pattern);
    int i{}, j{};

    while (i < text.size())
    {
        if (pattern[j] == text[i])
        {
            ++i;
            ++j;
        }

        if (j == pattern.size())
        {
            result.push_back(i - j);
            // Continue searching for the next match
            j = lps[j - 1];
        }
        else
        {
            if (i < text.size() && pattern[j] != text[i])
            {
                if (j != 0)
                    j = lps[j - 1];
                else
                    ++i;
            }
        }
    }
    return result;
}

int main()
{
    string pattern{}, text{};
    while (std::getline(cin, pattern) && std::getline(cin, text))
    {

        vector<int> matches = kmp(pattern, text);
        for (auto &i : matches)
        {
            cout << i << " ";
        }
        cout << "\n";
    }

    return 0;
}