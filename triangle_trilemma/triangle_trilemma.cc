/**
 * Solves the Triangle Trilemma problem.
 *
 * First checks for validity: the three points must be distinct
 * and not collinear (area != 0). Then, it computes all three side lengths,
 * determines if any are equal, and finally uses the Pythagorean theorem to
 * identify the angle type.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

using std::cout, std::cin, std::string;

/**
 * Represents a 2D point.
 *
 * This class defines basic geometric operations such as vector addition,
 * subtraction, scalar multiplication/division, dot and cross products, and
 * distance computations.
 *
 * Time Complexity: All operations are O(1)
 * Space Complexity: O(1)
 */
class Point
{
public:
    double x;
    double y;

    Point() : x(0.0), y(0.0) {}
    Point(double x, double y) : x(x), y(y) {}

    Point operator+(const Point &other) const
    {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point &other) const
    {
        return {x - other.x, y - other.y};
    }

    // Scalar multiplication
    Point operator*(double k) const
    {
        return {x * k, y * k};
    }

    Point operator/(double k) const
    {
        return {x / k, y / k};
    }

    double dot(const Point &other) const
    {
        return x * other.x + y * other.y;
    }

    double cross(const Point &other) const
    {
        return x * other.y - y * other.x;
    }

    // |v|^2
    double len2() const
    {
        return x * x + y * y;
    }

    // |v|
    double len() const
    {
        return std::sqrt(len2());
    }

    // Squared distance between two points
    double dist2(const Point &other) const
    {
        return (*this - other).len2();
    }
    double dist(const Point &other) const
    {
        return (*this - other).len();
    }

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point &other) const
    {
        return !(*this == other);
    }
};

/**
 * Determines the type of triangle formed by three 2D points.
 *
 * The function first checks if the three points form a valid triangle.
 * It's invalid if any two points are identical or if all three are collinear
 * (zero area).
 *
 * For a valid triangle, it calculates side lengths and classifies the triangle
 * based on its sides (isosceles or scalene) and angles (acute, right, or obtuse).
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
string classify_triangle(const Point &a, const Point &b, const Point &c)
{
    if (a == b || b == c || c == a)
        return "not a triangle";

    // Collinear (area*2 = 0)
    if ((b - a).cross(c - a) == 0.0)
        return "not a triangle";

    // Side length squares
    double ab = a.dist2(b);
    double bc = b.dist2(c);
    double ca = c.dist2(a);

    string side = "scalene";
    if ((bc == ca) || (ca == ab) || (ab == bc))
        side = "isosceles";

    std::vector<double> s{bc, ca, ab};
    std::sort(s.begin(), s.end());

    string angle_str = "obtuse";
    if (s[0] + s[1] == s[2])
        angle_str = "right";
    else if (s[0] + s[1] > s[2])
        angle_str = "acute";

    return side + ' ' + angle_str + "  triangle";
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tests{};
    cin >> tests;

    double x1, y1, x2, y2, x3, y3;
    for (int i = 1; i <= tests; ++i)
    {
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        Point a(x1, y1), b(x2, y2), c(x3, y3);

        cout << "Case #" << i << ": " << classify_triangle(a, b, c) << "\n";
    }
    cout << std::flush;
    return 0;
}
