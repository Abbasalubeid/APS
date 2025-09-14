/**
 * Solves the "Getting Gold" problem.
 *
 * The solution uses a BFS traversal through the map to simulate collecting as much
 * gold as possible without risking to fall into traps. Each cell in the BFS queue
 * is processed to:
 * 1. Check if it contains gold and collect it.
 * 2. Mark the cell as visited by turning it into a wall (#) to avoid revisiting
 * 3. Explore all four possible directions (up, down, left, right) from the current
 * cell and add unvisited cells to the queue.
 * 4. Skip adding neighbors to the queue if they are adjacent to a trap to
 * simulate the player sensing danger and avoiding those paths.
 *
 * Time complexity: O(W * H) where W is the width and H is the height of the map.
 * Space complexity: O(W * H)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using std::cout, std::cin, std::endl, std::vector, std::pair, std::queue;

int ROWS{}, COLS{};

pair<vector<vector<char>>, pair<int, int>> construct_map()
{

    vector<vector<char>> map(ROWS, vector<char>(COLS));
    char symbol{};
    pair<int, int> start_pos{};
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            cin >> symbol;
            if (symbol == 'P')
                start_pos = {i, j};
            map[i][j] = (symbol);
        }
    }

    return {map, start_pos};
}

/**
 * BFS to collect gold while avoiding traps.
 *
 * Traverses the map from the starting position and avoid any paths that lead
 * directly to traps and counts all accessible and safe gold.
 *
 * Time complexity: O(W * H) where W is the width and H is the height of the map.
 * This is because the algorithm must potentially visit every cell
 * on the map once in the worst case.
 *
 * Space complexity: O(W * H) because of the map and since we may store all cells in
 * the queue in the worst case scenario when no traps prevent movement.
 *
 * @returns The number of pieces of gold that can be safely collected.
 */
int bfs(pair<int, int> start_pos, vector<vector<char>> &map)
{
    queue<pair<int, int>> queue;
    queue.push(start_pos);

    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    vector<pair<int, int>> neighbours_to_add;
    bool no_danger = true;

    int gold_count{};
    while (!queue.empty())
    {
        auto [row, col] = queue.front();
        queue.pop();

        if (map[row][col] == '#')
            continue;

        if (map[row][col] == 'G')
            ++gold_count;

        // Mark as visited
        map[row][col] = '#';

        for (auto &[x, y] : directions)
        {
            int new_x{row + x}, new_y{col + y};

            if (0 <= new_x && new_x < ROWS &&
                0 <= new_y && new_y < COLS &&
                map[new_x][new_y] != '#')
            {
                // Avoid directions with danger
                if (map[new_x][new_y] == 'T')
                    no_danger = false;
                else
                    neighbours_to_add.push_back({new_x, new_y});
            }
        }

        if (no_danger)
        {
            for (auto &[x, y] : neighbours_to_add)
                queue.push({x, y});
        }
        neighbours_to_add = {};
        no_danger = true;
    }

    return gold_count;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> COLS >> ROWS;
    auto [map, start_pos] = construct_map();

    cout << bfs(start_pos, map) << endl;

    return 0;
}