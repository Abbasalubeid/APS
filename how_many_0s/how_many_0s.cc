/**
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>

using std::cout, std::cin;

/**
 * Time complexity: O(log x) where x is the input number because each digit
 * position is processed once starting from the least significant digit.
 *
 * Space complexity: O(1).
 */
long long count_zeros(long long x)
{
    long long tot = 1;

    for (long long i = 1; i <= x; i *= 10)
    {
        long long right = x % i;
        long long current = (x / i) % 10;
        long long left = x / (i * 10);

        if (current == 0)
        {
            if (left != 0)
                tot += (left - 1) * i + (right + 1);
        }
        else
            tot += left * i;
    }
    return tot;
}

long long solve(long long m, long long n)
{

    if (m == 0)
        return count_zeros(n);
    else if (n == 0)
        return count_zeros(m);
    else
        return count_zeros(n) - count_zeros(m - 1);
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long m{}, n{};

    while (cin >> m >> n && !(m < 0))
    {
        cout << solve(m, n) << "\n";
    }
    cout << std::flush;
}