/**
 * Solves the "Evil Straw Warts Live" problem
 * using two pointers.
 *
 * Time Complexity: O(n^2) where n is the length of the input string.
 * Space Complexity: O(min(n, c)) where n is the length of the string and c is the
 * number of unique characters.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::cin, std::cout, std::string;

/**
 * Checks if it is possible to rearrange a string into a palindrome.
 *
 * For a palindrome, characters must appear in mirrored pairs around the center.
 * If the string length is even, every character's frequency must be even,
 * because we can't leave any character unmatched.
 * If the string length is odd, exactly one character is allowed to have an odd
 * frequency (it sits in the middle) and the others must pair up evenly.
 *
 * Time Complexity: O(n) where n is the length of the string.
 *
 * Space Complexity: O(min(n, c)) where n is the length of the string and c is the
 * number of unique characters. This is because the hashmap will have an entry for
 * each unique character found in the string.
 */
bool can_form_palindrome(const string &word)
{
    std::unordered_map<char, int> freqs;

    for (char c : word)
        freqs[c]++;

    int odd_count{};
    for (auto &[character, freq] : freqs)
    {
        if (freq % 2 != 0)
            ++odd_count;
    }

    if (word.length() % 2 == 0 && odd_count > 0 ||
        word.length() % 2 != 0 && odd_count > 1)
        return false;
    else
        return true;
}

/**
 * Calculates the number of swaps necessary to transform a string into a
 * palindrome. Uses a greedy two-pointer approach.
 *
 * Time Complexity: O(n^2) where n is the length of the string.
 * Each pass can involve searching backward for a matching character and "bubbling"
 * it to the right which can take O(n) in the worst case and we may do this n/2
 * times.
 *
 * Space Complexity: O(min(n, c)) where n is the length of the string and c is the
 * number of unique characters because of calling the can_form_palindrome function.
 *
 * @returns The number of swaps or -1 if it is impossible to form a palindrome.
 */
int solve(string &word)
{
    if (!can_form_palindrome(word))
        return -1;

    int left{};
    int right = word.size() - 1;

    int swaps{};
    while (left < right)
    {
        if (word[left] == word[right])
        {
            ++left;
            --right;
        }
        else
        {
            int matching_pos{right};

            // Search for matching character to word[left]
            while (matching_pos > left && word[matching_pos] != word[left])
            {
                matching_pos--;
            }
            // word[left] is middle char in an odd length palindrome.
            if (matching_pos == left)
            {
                std::swap(word[left], word[left + 1]);
                swaps++;
            }
            else
            {
                // We found a matching character for word[left] at word[matching_pos]
                for (int i = matching_pos; i < right; ++i)
                {
                    std::swap(word[i], word[i + 1]);
                    swaps++;
                }

                left++;
                right--;
            }
        }
    }
    return swaps;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tests{};
    string word{};

    cin >> tests;
    for (int i = 0; i < tests; ++i)
    {
        cin >> word;
        int number_of_swaps = solve(word);
        if (number_of_swaps == -1)
            cout << "Impossible\n";
        else
            cout << number_of_swaps << "\n";

        cout << std::flush;
    }

    return 0;
}
