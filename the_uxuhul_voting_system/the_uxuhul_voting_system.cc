/**
 * Solves the Uxuhul voting system problem using dynamic programming with
 * backward induction to determine the outcome when priests vote optimally.
 *
 * Time Complexity: O(m) where m is the number of priests
 * Space Complexity: O(m)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <string>
#include <climits>

using std::cout, std::cin, std::endl, std::string, std::vector;

const int INF = INT_MAX;

int flags_table[8][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}};

string label_table[8] = {
    "NNN", "NNY", "NYN", "NYY", "YNN", "YNY", "YYN", "YYY"};

/**
 * Converts a state index to its corresponding flag array representation.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
void state_to_flags(int s, int f[])
{
    f[0] = flags_table[s][0];
    f[1] = flags_table[s][1];
    f[2] = flags_table[s][2];
}

/**
 * Converts a flag array back to its corresponding state index by searching
 * the flags table for a matching configuration.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
int flags_to_state(const int f[])
{
    for (int s = 0; s < 8; ++s)
    {
        if (flags_table[s][0] == f[0] &&
            flags_table[s][1] == f[1] &&
            flags_table[s][2] == f[2])
        {
            return s;
        }
    }
}

/**
 * Computes the new state after flipping one issue from the current state.
 * Converts the state to flags, toggles the specified issue and converts back.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
int flip_issue(int s, int issue)
{
    int f[3];
    state_to_flags(s, f);

    if (issue == 0)
    {
        if (f[0] == 0)
            f[0] = 1;
        else
            f[0] = 0;
    }
    else if (issue == 1)
    {
        if (f[1] == 0)
            f[1] = 1;
        else
            f[1] = 0;
    }
    else
    {
        if (f[2] == 0)
            f[2] = 1;
        else
            f[2] = 0;
    }

    return flags_to_state(f);
}

/**
 * Determines the final voting outcome using backward induction.
 *
 * Uses dynamic programming where dp[i][s] stores the final outcome when
 * starting at priest i in state s with all remaining priests voting optimally.
 * Works backwards from the last priest to the first. Each priest evaluates
 * all three possible flips and chooses the one that leads to their most
 * preferred final outcome based on their preference ranking.
 *
 * Time Complexity: O(m) where m is the number of priests
 * Space Complexity: O(m)
 *
 * @returns The final state index after all priests vote optimally
 */
int solve_round(vector<vector<int>> pref)
{
    int m = pref.size();

    vector<vector<int>> dp(m + 1, vector<int>(8, 0));

    for (int s = 0; s < 8; ++s)
    {
        dp[m][s] = s;
    }

    for (int i = m - 1; i >= 0; --i)
    {
        for (int s = 0; s < 8; ++s)
        {
            int next_states[3];
            next_states[0] = flip_issue(s, 0);
            next_states[1] = flip_issue(s, 1);
            next_states[2] = flip_issue(s, 2);

            int best_final = -1;
            int best_rank = INF;

            for (int k = 0; k < 3; ++k)
            {
                int t = dp[i + 1][next_states[k]];
                int rank = pref[i][t];
                if (rank < best_rank)
                {
                    best_rank = rank;
                    best_final = t;
                }
            }

            dp[i][s] = best_final;
        }
    }

    return dp[0][0];
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int rounds{};
    while (cin >> rounds)
    {
        for (int i = 0; i < rounds; ++i)
        {

            int m = 0;
            cin >> m;

            vector<vector<int>> pref(m, vector<int>(8, 0));

            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < 8; ++j)
                {
                    int rank_value{};
                    cin >> rank_value;
                    pref[i][j] = rank_value;
                }
            }

            int outcome = solve_round(pref);
            cout << label_table[outcome] << "\n";
        }
    }

    return 0;
}