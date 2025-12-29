/**
 * Solves the "Happy Happy Prime Prime" problem using Erathostenes sieve and
 * simple digit square summing with cycle detection to determine if a number
 * is happy.
 *
 * Time Complexity: O(n log log n + q * log m) where n is largest number, q
 * is queries, m is query value.
 * Space Complexity: O(n + q)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <unordered_set>

using std::cout, std::cin, std::vector;

class Erathostenes
{
private:
    vector<bool> prime_table;

public:
    int number_of_primes;

    /**
     * This constructor uses the Erathostenes sieve to generate a lookup table
     * up to n so that we can later make fast lookups to check if a number
     * is prime for all integers from 0 up to n.
     *
     * The lookup table is constructed by using the idea that if a
     * number x is prime, then all multiples of x is not prime since they have
     * x as a multiple which contradicts the fact that they are prime.
     *
     * Time complexity: O(n log log n) where n is the upper limit of the sieve.
     * Space complexity: O(n)
     */
    Erathostenes(int n) : prime_table(n + 1, true), number_of_primes(0)
    {
        prime_table[0] = false;
        prime_table[1] = false;

        for (int i = 2; i * i <= n; ++i)
        {
            if (prime_table[i])
            {
                for (int j = 2 * i; j <= n; j += i)
                {
                    prime_table[j] = false;
                }
            }
        }

        for (int i = 2; i <= n; ++i)
        {
            if (prime_table[i])
                number_of_primes++;
        }
    }

    bool is_prime(int n)
    {
        return prime_table[n];
    }
};

/**
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
int sum_of_digit_squares(int n)
{

    int sum{};
    while (n != 0)
    {
        int digit = n % 10;
        digit = digit * digit;
        sum += digit;
        n = n / 10;
    }
    return sum;
}

bool is_happy(int n)
{
    std::unordered_set<int> seen;
    int x{};

    while (!seen.count(n))
    {
        seen.insert(n);
        x = sum_of_digit_squares(n);

        if (x == 1)
            return true;

        n = x;
    }

    return false;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int nr_tests{}, query{}, K{}, largest_number{};
    vector<int> queries{};

    cin >> nr_tests;
    for (int i = 0; i < nr_tests; ++i)
    {
        cin >> K;
        cin >> query;
        queries.push_back(query);

        if (query > largest_number)
            largest_number = query;
    }

    Erathostenes erathostenes(largest_number);

    for (int i = 0; i < queries.size(); ++i)
    {

        cout << i + 1 << " " << queries[i];

        if (erathostenes.is_prime(queries[i]) && is_happy(queries[i]))
            cout << " YES\n";
        else
            cout << " NO\n";
    }
    cout << std::flush;

    return 0;
}