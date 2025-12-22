/**
 * Solves the interval cover problem by finding the minimal number of intervals to
 * fully cover a specified range.
 *
 * The solution uses a greedy algorithm to select intervals that progressively cover
 * the target interval from start to finish.
 *
 * Time complexity: O(n log n) where n is the number of input intervals.
 *
 * Space complexity: O(n)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout, std::cin, std::string, std::vector, std::endl, std::sort;

struct interval
{
    double start;
    double finish;
    int index;
};

vector<interval> read_intervals()
{

    vector<interval> intervals;

    int available_intervals{};
    cin >> available_intervals;

    for (int i = 0; i < available_intervals; ++i)
    {
        interval interval;
        cin >> interval.start >> interval.finish;
        interval.index = i;
        intervals.push_back(interval);
    }
    return intervals;
}

void print_output(const vector<int> &indices = {}, bool solvable = false)
{
    if (solvable)
    {
        cout << indices.size() << "\n";
        for (int index : indices)
        {
            cout << index << " ";
        }
        cout << endl;
    }
    else
        cout << "impossible\n";
}

/**
 * Solves the interval cover problem using a greedy algorithm in O(nlogn).
 *
 * Time complexity: O(n log n) because of the sorting.
 *
 * Space complexity: O(n)
 *
 */
void solve(interval target_interval, vector<interval> &all_intervals)
{

    // O(nlogn)
    sort(all_intervals.begin(), all_intervals.end(),
         [](const auto &a, const auto &b)
         { if(a.start == b.start) return a.finish > b.finish; 
            else return a.start < b.start; });

    vector<int> used_indices;
    double current_end = target_interval.start;
    int index = 0;
    bool found_solution = false;

    // singe point interval
    if (target_interval.start == target_interval.finish)
    {
        for (const auto &interval : all_intervals)
        {
            if (interval.start <= target_interval.start &&
                interval.finish >= target_interval.finish)
            {
                cout << "1\n"
                     << interval.index << "\n";
                return;
            }
        }
        print_output();
        return;
    }

    while (current_end < target_interval.finish)
    {
        double best_extend = current_end;
        int best_index = -1;

        while (index < all_intervals.size() &&
               all_intervals[index].start <= current_end)
        {
            if (all_intervals[index].finish > best_extend)
            {
                best_extend = all_intervals[index].finish;
                best_index = index;
            }
            ++index;
        }

        if (best_index == -1)
        {
            print_output();
            return;
        }

        used_indices.push_back(all_intervals[best_index].index);
        current_end = best_extend;

        if (current_end >= target_interval.finish)
        {
            found_solution = true;
            break;
        }
    }
    print_output(used_indices, found_solution);
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    interval target;
    while (cin >> target.start >> target.finish)
    {
        vector<interval> all_intervals = read_intervals();

        solve(target, all_intervals);
    }
}