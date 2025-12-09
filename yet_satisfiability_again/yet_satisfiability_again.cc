/**
 * Solves the "Yet Satisfiability Again" problem using backtracking.
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::cout, std::cin, std::vector, std::string, std::getline, std::stoi, std::abs;

vector<vector<int>> read_clauses(int nr_clauses)
{
    vector<vector<int>> clauses(nr_clauses);

    string line;
    // extra line
    std::getline(cin, line);

    for (int i = 0; i < nr_clauses; ++i)
    {
        getline(cin, line);
        std::stringstream ss(line);
        string token{};
        vector<int> clause{};

        while (ss >> token)
        {

            if (token == "v")
                continue;

            int variable;

            if (token[0] == '~')
                variable = -stoi(token.substr(2));
            else
                variable = stoi(token.substr(1));
            clause.push_back(variable);
        }
        clauses[i] = clause;
    }
    return clauses;
}

bool clause_contradicted(vector<int> &clause,
                         vector<int> &assign)
{
    for (int lit : clause)
    {
        int idx = abs(lit) - 1;
        int val = assign[idx];
        if (val == -1)
            return false;
        if (lit > 0 && val)
            // Xi true
            return false;
        if (lit < 0 && !val)
            // ~Xi true
            return false;
    }
    return true;
}

bool clause_satisfied(vector<int> &clause,
                      vector<int> &assign)
{
    for (int lit : clause)
    {
        int idx = abs(lit) - 1;
        int val = assign[idx];
        if (val == -1)
            return false;
        if (lit > 0 && val)
            return true;
        if (lit < 0 && !val)
            return true;
    }
    return false;
}

/**
 * Recursively assigns true or false to variables using backtracking.
 * Tries both values for each variable and backtracks if the partial assignment
 * contradicts any clause. Returns true if a satisfying assignment is found.
 *
 * Time Complexity: O(2^n * m * k) in worst case
 * Space Complexity: O(n) for recursion depth
 */
bool dfs(int pos, int n,
         vector<int> &assign,
         vector<vector<int>> &clauses)
{
    // full assignment
    if (pos == n)
    {
        for (vector<int> &c : clauses)
            if (!clause_satisfied(c, assign))
                return false;
        return true;
    }

    // assign false then true
    for (int val : {0, 1})
    {
        assign[pos] = val;

        bool ok = true;
        for (vector<int> &c : clauses)
            if (clause_contradicted(c, assign))
            {
                ok = false;
                break;
            }

        if (ok && dfs(pos + 1, n, assign, clauses))
            return true;
    }

    // backtrack
    assign[pos] = -1;

    return false;
}

bool solve(int n, vector<vector<int>> &clauses)
{

    vector<int> assign(n, -1);
    return dfs(0, n, assign, clauses);
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tests{}, variables{}, nr_clauses{};

    cin >> tests;
    while (tests--)
    {
        cin >> variables >> nr_clauses;

        vector<vector<int>> clauses = read_clauses(nr_clauses);

        if (solve(variables, clauses))
            cout << "satisfiable\n";
        else
            cout << "unsatisfiable\n";

        // for (int i = 0; i < clauses.size(); ++i)
        // {
        //     cout << "  clause " << i + 1 << ':';
        //     for (int lit : clauses[i])
        //         cout << ' ' << lit;
        //     cout << '\n';
        // }
    }
    cout << std::flush;

    return 0;
}