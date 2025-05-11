/**
 * Solves the cd problem using a two pointer approach.
 *
 * Time complexity: O(n + m) where n is the number of Jack's CDs and m is the
 * number of Jill's CDs. This is because reading input costs O(n + m)
 * and the two-pointer intersection loop costs O(n + m). Adding them together
 * still gives O(n + m) for each test case.
 *
 * Space complexity: O(n + m). For each test case, the algorithms uses a vector
 * of size n (jack_cds) and a vector of size  m (jill_cds) So, the total
 * auxiliary space per test case is O(n + m)
 *
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
int main(int argc, char *argv[])
{

    while (true)
    {
        ios::sync_with_stdio(false);
        cin.tie(NULL);

        int num_of_cds_jack, num_of_cds_jill;
        cin >> num_of_cds_jack >> num_of_cds_jill;

        // If reading fails or we hit "0 0", break out
        if (!cin || (num_of_cds_jack == 0 && num_of_cds_jill == 0))
            break;

        vector<int> jack_cds(num_of_cds_jack);
        vector<int> jill_cds(num_of_cds_jill);

        // Read Jack's CDs O(n)
        for (int i{0}; i < num_of_cds_jack; ++i)
        {
            cin >> jack_cds[i];
        }

        // Read Jill's CDs O(m)
        for (int i{0}; i < num_of_cds_jill; ++i)
        {
            cin >> jill_cds[i];
        }

        int i{0}, j{0}, result{0};
        // O(n + m)
        while (i < num_of_cds_jack && j < num_of_cds_jill)
        {
            if (jack_cds[i] == jill_cds[j])
            {
                // Common cd found
                ++result;
                ++i;
                ++j;
            }
            else if (jack_cds[i] < jill_cds[j])
                i++;
            else
                j++;
        }

        cout << result << endl;
    }
    return 0;
}
