/**
 * Solves the babelfish problem using a hashmap (unordered map) to store
 * dictionary entries where the key is the foreign language word and the value is * its English equivalent. This allows for average O(1) time cost for look up
 * when translating each word in the message.
 *
 * Time complexity: O(n + m) where n is the number of dictionary entries and
 * m is the number of words in the message. O(n) because of n insertions (each
 * insertion operation into an unordered map is average O(1)) and O(m) because of
 * m translations (each lookup is O(1)).
 *
 * Space complexity: O(n) for the unordered map storing the dictionary.
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;
int main(int argc, char *argv[])
{
    // Improves IO speed without having to use the cstdio routines,
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    unordered_map<string, string> input_dict;

    while (true)
    {
        string line;
        getline(cin, line);

        if (line.empty())
            break;

        istringstream iss(line);
        string key, value;
        iss >> value >> key;

        input_dict[key] = value;
    }

    string message{};
    while (cin >> message)
    {
        auto it = input_dict.find(message); // Avg O(1)
        if (it != input_dict.end())
            cout << it->second << "\n";
        else
            cout << "eh" << "\n";
    }
    cout << flush;

    return 0;
}