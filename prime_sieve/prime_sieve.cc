/**
 * Implementation Erathostenes sieve to find all primes upp to a limit n.
 *
 * Time complexity: O(n log log n) where n is the upper limit of the sieve.
 * Space complexity: O(n)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>

using std::cout, std::cin, std::vector;

class Erathostenes
{
private:
    vector<bool> prime_table;

public:
    int number_of_primes;

    /**
     * This constructor uses the Erathostenes sieve to generate a lookup table
     * up to n to make fast lookups to check if a number is prime for all
     * integers from 0 up to n.
     *
     * The lookup table "prime_table" is constructed by using the idea that if a
     * number x is prime, then all multiples of x are non-prime since they have
     * x as a factor which contradicts the fact that they are prime so they
     * are marked as non-prime in the lookup table.
     *
     * The algorithm only checks if a number is prime up to sqrt(n) because any
     * composite number <= n must have a factor <= to sqrt(n) and if no smaller
     * prime divides it then it must be prime which means there is no need to
     * mark it as non-prime.
     *
     * Time complexity: O(n log log n) where n is the upper limit of the sieve.
     * The outer loop runs up to sqrt(n) but it only enters the inner loop when
     * i is prime. For each such prime i, the inner loop marks n / i numbers as
     * non-prime. The total number of markings over all primes p <= n is the sum
     * n/p which equals n(1/2 + 1/3 + 1/5 + ...) and is less than
     * n(1 + 1/2 + 1/3 + ... + 1/n) = O(n log n) (logn from harmonic series).
     * n(1/2 + 1/3 + 1/5 + ...) is less because we only sum over primes which are
     * less frequent than all integers and n/p because the inner loop runs once
     * every p steps up to n. The actual sum of 1/p over primes is known to be
     * O(log log n) which makes the total complexity O(n log log n).
     *
     * Space complexity: O(n) for the "prime_table" vector
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

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n{}, queries{}, query{};

    cin >> n >> queries;

    Erathostenes erathostenes(n);

    cout << erathostenes.number_of_primes << "\n";
    for (int i = 0; i < queries; ++i)
    {
        cin >> query;
        cout << erathostenes.is_prime(query) << "\n";
    }

    return 0;
}