/**
 * Solves the "Help" problem by constructing a unified phrase from two patterns
 * with placeholders using constraint propagation over multiple passes.
 *
 * Time Complexity: O(n^2) where n is the pattern length
 * Space Complexity: O(n)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using std::cout, std::cin, std::string, std::vector, std::unordered_map, std::endl, std::stringstream;

/**
 * Reads input for two lines from standard input and adds their content to two vectors.
 */
void read_input(vector<string> &line1, vector<string> &line2)
{
    string str1, str2;
    getline(cin, str1);
    getline(cin, str2);
    stringstream stream1{str1};
    stringstream stream2{str2};

    string word1{}, word2{};
    while (stream1 >> word1)
    {
        line1.push_back(word1);
    }

    while (stream2 >> word2)
    {
        line2.push_back(word2);
    }
}

void print_output(vector<string> &phrase, bool conflict)
{

    if (conflict)
        cout << "-" << "\n";
    else
    {
        for (string const &word : phrase)
        {
            cout << word << " ";
        }
        cout << "\n";
    }

    cout << std::flush;
}

/**
 * Constructs a unified phrase from two patterns using constraint propagation.
 * Uses two hashmaps to track placeholder mappings and iterates until no changes
 * occur or a conflict is detected.
 *
 * Time Complexity: O(n^2) where n is the pattern length
 * Space Complexity: O(n)
 */
void solve(vector<string> &pattern1, vector<string> &pattern2)
{
    int n = pattern1.size();

    unordered_map<string, string> map1;
    unordered_map<string, string> map2;

    vector<string> phrase(n);

    bool conflict = false;
    bool changed = true;

    for (int pass = 0; pass < n && !conflict && changed; ++pass)
    {
        changed = false;

        // O(n^2) is ok since n is small
        for (int i = 0; i < n; i++)
        {
            if (conflict)
                break;

            const string &p1 = pattern1[i];
            const string &p2 = pattern2[i];

            bool p1_placeholder = p1.starts_with("<");
            bool p2_placeholder = p2.starts_with("<");

            if (!p1_placeholder && !p2_placeholder)
            {
                if (p1 != p2)
                {
                    conflict = true;
                    break;
                }
                else
                    phrase[i] = p1;
            }

            else if (!p1_placeholder && p2_placeholder)
            {

                if (!map2.contains(p2))
                {
                    map2[p2] = p1;
                    changed = true;
                }
                else
                {
                    if (map2[p2] != p1)
                    {
                        conflict = true;
                        break;
                    }
                }
                phrase[i] = p1;
            }

            else if (p1_placeholder && !p2_placeholder)
            {
                if (!map1.contains(p1))
                {
                    map1[p1] = p2;
                    changed = true;
                }
                else
                {
                    if (map1[p1] != p2)
                    {
                        conflict = true;
                        break;
                    }
                }
                phrase[i] = p2;
            }

            else
            {
                bool has1 = map1.contains(p1);
                bool has2 = map2.contains(p2);
                string w1 = has1 ? map1[p1] : "";
                string w2 = has2 ? map2[p2] : "";

                if (has1 && has2)
                {
                    if (w1 != w2)
                    {
                        conflict = true;
                        break;
                    }
                    phrase[i] = w1;
                }
                else if (has1 && !has2)
                {
                    map2[p2] = w1;
                    changed = true;
                    phrase[i] = w1;
                }
                else if (!has1 && has2)
                {
                    map1[p1] = w2;
                    changed = true;
                    phrase[i] = w2;
                }
                else
                    phrase[i] = "help";
            }
        }
    }

    print_output(phrase, conflict);
}

int main(int argc, char *argv[])
{
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int test_cases{};
    cin >> test_cases;
    cin.ignore();

    for (int i = 0; i < test_cases; ++i)
    {
        vector<string> pattern1, pattern2;

        read_input(pattern1, pattern2);

        if (pattern1.size() != pattern2.size())
        {
            cout << "-" << "\n";
            continue;
        }

        solve(pattern1, pattern2);
    }
    return 0;
}
