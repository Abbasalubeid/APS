/**
 * Dynamic programming solution to the classic 0/1 knapsack problem.
 *
 * Time complexity:
 * Space complexity:
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <map>

using std::cout, std::cin, std::endl, std::vector, std::map;

/**
 * Solves the knapsack problem using dynamic programming
 *
 * Time complexity: *** where *** because
 * Space complexity: *** because
 */
vector<int> knapsack_solver(int capacity, map<int, int>)
{
    return;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int capacity{};
    int nr_objects{};
    map<int, int> objects;

    while (cin >> capacity)
    {
        cin >> nr_objects;
        int value{}, weight{};
        for (int i = 0; i < nr_objects; ++i)
        {
            cin >> value >> weight;
            objects[value] = weight;
        }
        for (auto &[key, value] : objects)
            cout << key << " " << value << endl;

        cout << endl
             << endl;

        objects.clear();
    }

    return 0;
}