/**
 * Solves the "Hiding Places" problem using BFS.
 *
 * Time Complexity: O(t) where t is the number of test cases
 * Space Complexity: O(1)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>
#include <algorithm>

using std::cout, std::cin, std::flush, std::vector, std::pair, std::queue, std::unordered_map, std::max, std::sort;

struct node
{
    int row{}, col{}, dist{};
};

vector<vector<int>> construct_map()
{

    vector<vector<int>> map(9, vector<int>(9));
    for (int i = 1; i <= 8; ++i)
    {
        for (int j = 1; j <= 8; ++j)
        {
            map[i][j] = 0;
        }
    }

    return map;
}

/**
 * BFS from a starting position to find all positions at maximum
 * distance from the start. Cheks all reachable positions using knight moves
 * and tracks positions at the maximum distance.
 *
 * Time Complexity: O(1) because constant 8x8 board with 8 knight moves per position
 * Space Complexity: O(1) because of onstant size queue and result vector
 *
 */
pair<vector<node>, int> bfs(node &start_pos, vector<vector<int>> &map)
{
    queue<node> queue;
    queue.push(start_pos);

    bool visited[9][9] = {false};
    visited[start_pos.row][start_pos.col] = true;

    vector<pair<int, int>> directions = {
        {2, 1},
        {2, -1},
        {-2, 1},
        {-2, -1},
        {1, 2},
        {1, -2},
        {-1, 2},
        {-1, -2},
    };

    vector<node> result;
    int max_jumps{};
    while (!queue.empty())
    {
        node current = queue.front();
        queue.pop();

        for (auto &[row, col] : directions)
        {
            node new_node{current.row + row, current.col + col, current.dist + 1};

            if (0 < new_node.row && new_node.row <= 8 &&
                0 < new_node.col && new_node.col <= 8 &&
                !visited[new_node.row][new_node.col])
            {
                queue.push(new_node);
                visited[new_node.row][new_node.col] = true;
                map[new_node.row][new_node.col] = new_node.dist;

                if (new_node.dist > max_jumps)
                {
                    result.clear();
                    max_jumps = new_node.dist;
                }

                if (new_node.dist == max_jumps)
                    result.push_back(new_node);
            }
        }
    }
    return {result, max_jumps};
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    unordered_map<char, int> file_to_number{
        {'a', 1},
        {'b', 2},
        {'c', 3},
        {'d', 4},
        {'e', 5},
        {'f', 6},
        {'g', 7},
        {'h', 8}};

    unordered_map<int, char> number_to_file{
        {1, 'a'},
        {2, 'b'},
        {3, 'c'},
        {4, 'd'},
        {5, 'e'},
        {6, 'f'},
        {7, 'g'},
        {8, 'h'}};

    int tests{};
    cin >> tests;
    while (tests--)
    {

        vector<vector<int>> map = construct_map();

        char file{};
        int rank{};
        cin >> file >> rank;
        node start_pos{rank, file_to_number[file], 0};

        auto [result, max_jumps] = bfs(start_pos, map);

        cout << max_jumps << " ";

        sort(result.begin(), result.end(), [](const node &n1, const node &n2)
             {
                if (n1.row != n2.row)
                    return n1.row > n2.row;
                else    
                    return n1.col < n2.col; });

        for (auto &node : result)
        {
            cout << number_to_file[node.col] << node.row << " ";
        }
        cout << "\n";
    }
    cout << flush;

    return 0;
}