/**
 * Solves the Polygon Area problem using the shoelace formula.
 *
 * Time Complexity: O(n) where n is the number of vertices in the polygon.
 * Space Complexity: O(1)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::cout, std::cin, std::vector, std::string;

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
 * Computes the signed area of a polygon using the shoelace method.
 *
 * The shoelace formula adds the cross product of each pair of consecutive
 * points to find twice the total signed area of the polygon. Dividing by
 * 2 gives the final signed area.
 *
 * To do the shoelace formula in code, the function loops through each vertex
 * of the polygon and computes the cross product between the current vertex
 * and the next vertex (wrapping back to the first with modulo). Each
 * cross product gives twice the signed area of a triangle from the origin
 * to those two points. Summing all these cross products gives twice the
 * total signed area of the polygon and dividing by 2 give the final area.
 *
 * A positive result means vertices are ordered counterclockwise (CCW) and
 * a negative result means clockwise (CW). This is because the cross product
 * is positive when the second vector is to the left of the first (CCW) and
 * negative when it's to the right (CW).
 *
 * Time Complexity: O(n) where n is the number of vertices in the polygon
 * because each vertex is used once in the loop.
 * Space Complexity: O(1)
 */
double signed_polygon_area(vector<Point> &poly)
{
    double area2{};
    int n = poly.size();

    for (int i = 0; i < n; ++i)
    {
        Point &curr = poly[i];
        Point &next = poly[(i + 1) % n];
        area2 += curr.cross(next);
    }

    return area2 / 2;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n{};
    cout << std::fixed << std::setprecision(1);

    while (cin >> n && n != 0)
    {
        vector<Point> poly{};
        poly.reserve(n);

        for (int i = 0; i < n; ++i)
        {
            double x{}, y{};
            cin >> x >> y;
            poly.push_back(Point(x, y));
        }

        double area = signed_polygon_area(poly);

        string direction = "CCW";
        if (area < 0)
        {
            area = -area;
            direction = "CW";
        }

        cout << direction << " " << area << "\n";
    }

    cout << std::flush;
    return 0;
}
