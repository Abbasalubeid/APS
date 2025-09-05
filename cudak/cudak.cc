/**
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout, std::cin, std::endl, std::vector, std::string, std::sort, std::stoll;

int digit_sum(const string &num)
{
    int sum = 0;
    for (char digit : num)
    {
        sum += digit - '0';
    }
    return sum;
}

void find_numbers(const string &low, const string &high, int target_sum, string current_number, int current_sum, vector<long long> &results)
{
    // Base case
    if (!current_number.empty())
    {
        long long num = stoll(current_number);
        if (num >= stoll(low) && num <= stoll(high) && current_sum == target_sum)
        {
            results.push_back(num);
        }
    }

    // Pruning
    if (!current_number.empty() && stoll(current_number) > stoll(high))
    {
        return;
    }

    // Generate the next digit
    for (char digit = '0'; digit <= '9'; ++digit)
    {
        if (current_number.empty() && digit == '0' && target_sum != 0)
            continue;

        string next_number = current_number + digit;
        int next_sum = current_sum + (digit - '0');

        // Pruning
        if (next_sum > target_sum)
            break;

        find_numbers(low, high, target_sum, next_number, next_sum, results);
    }
}

vector<long long> solve(long long a, long long b, int s)
{
    vector<long long> result;
    string low = std::to_string(a);
    string high = std::to_string(b);

    find_numbers(low, high, s, "", 0, result);
    sort(result.begin(), result.end());
    return result;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long a{}, b{};
    int s{};

    cin >> a >> b >> s;

    vector<long long> result = solve(a, b, s);

    cout << result.size() << "\n"
         << result[0] << endl;

    return 0;
}