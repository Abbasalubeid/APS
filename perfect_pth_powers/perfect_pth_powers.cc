/**
 * Solves the perfect pth powers problem by finding the largest integer p such that
 * x = b^p where x is an input integer and b is an integer base.
 *
 * Time Complexity: O(sqrt(|x|))
 * Space Complexity: O(1)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <cmath>

using std::cout, std::cin, std::flush, std::abs, std::ceil, std::sqrt, std::log;

/**
 * Finds the largest integer p such that x = b^p for some
 * integer b.
 *
 * Time complexity: O(sqrt(|x|)) because the loop iterates
 * up to square root of |x|.
 * Space complexity: O(1).
 *
 */
long long largest_p(long long x)
{

    if (x == 1 || x == -1)
        return 1;

    int max_b = ceil(sqrt(abs(x)));

    // Check for all possible bases up to max_b
    for (int b = 2; b <= max_b; ++b)
    {
        // Check if b is a divisor of x to skip unnecessary log calculations
        if (x % b != 0)
            continue;

        double potential_p = log(abs(x)) / log(b);

        double fraction_part = potential_p - floor(potential_p);

        if (fraction_part < 1e-10)
        {
            int p = floor(potential_p);

            if ((x > 0) || (x < 0 && p % 2 != 0))
                return p;
        }
    }

    return 1;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long x{};
    while (cin >> x && x != 0)
        cout << largest_p(x) << "\n";

    cout << flush;
    return 0;
}