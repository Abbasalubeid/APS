/**
 * Solves the Point in Polygon problem using ray casting.
 *
 * Time Complexity: O(n) where n is the number of vertices in the polygon (for each
 * test point).
 * Space Complexity: O(1)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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
 * Checks if point p lies on the line segment from a to b.
 *
 * Uses the cross product to verify collinearity and checks that p is
 * within the bounding box of the segment. The cross product of (b - a)
 * and (p - a) is zero when p is collinear with a and b. To verify p is
 * on the segment (not just the line), we check that p's coordinates are
 * between a and b.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
bool on_segment(Point &p, Point &a, Point &b)
{
    Point ab = b - a;
    Point ap = p - a;

    double cross_product = ab.cross(ap);
    if (std::abs(cross_product) > 1e-9)
        return false;

    double min_x = std::min(a.x, b.x);
    double max_x = std::max(a.x, b.x);
    double min_y = std::min(a.y, b.y);
    double max_y = std::max(a.y, b.y);

    return p.x >= min_x && p.x <= max_x && p.y >= min_y && p.y <= max_y;
}

/**
 * Determines if point p is strictly inside the polygon using ray casting.
 *
 * The idea is to cast a ray from point p in any direction and count how many
 * times it crosses one of the polygon's edges. If the number of crossings is
 * odd then the point is inside the polygon and if it's even the point is outside.
 * This is because every time we cross an edge we're either entering or leaving
 * the polygon so an odd count means we ended up inside and an even count means
 * we ended up outside.
 *
 * For each edge of the polygon we need to check if our ray crosses it. First
 * we check if p.y is between the y coordinates of the edge's endpoints because
 * if it's not then the horizontal ray can't cross the edge. We do this
 * by checking if one endpoint is above p and the other is below.
 *
 * Once we know the ray is at the right height to potentially cross the edge we
 * need to find where exactly the edge intersects the horizontal line at y = p.y.
 * We calculate the x coordinate of this intersection point. The formula for that
 * works by starting at a.x and then adding a fraction of the width (b.x - a.x)
 * based on how far up p.y is between a.y and b.y.
 * The ratio (p.y - a.y) / (b.y - a.y) tells how much of the way up we are and
 * multiplying that by the width gives us how much to add to a.x. If p.x is smaller
 * than this intersection point then the ray going to the right will cross the edge.
 *
 * Time Complexity: O(n) where n is the number of vertices in the polygon
 * Space Complexity: O(1)
 */
bool inside_polygon(Point &p, vector<Point> &poly)
{
    int n = poly.size();
    int crossings{};

    for (int i = 0; i < n; ++i)
    {
        Point &a = poly[i];
        Point &b = poly[(i + 1) % n];

        if ((a.y > p.y) != (b.y > p.y))
        {
            double x_intersection = a.x + (p.y - a.y) * (b.x - a.x) / (b.y - a.y);

            if (p.x < x_intersection)
                crossings++;
        }
    }
    if (crossings % 2)
        return true;
    else
        return false;
}

/**
 * Determines whether point p is on the boundary, inside, or outside the polygon.
 *
 * Time Complexity: O(n) where n is the number of vertices in the polygon
 * Space Complexity: O(1)
 */
string solve(Point &p, vector<Point> &poly)
{
    int n = poly.size();

    for (int i = 0; i < n; ++i)
    {
        if (on_segment(p, poly[i], poly[(i + 1) % n]))
            return "on";
    }

    if (inside_polygon(p, poly))
        return "in";
    else
        return "out";
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n{};

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

        int m{};
        cin >> m;

        for (int i = 0; i < m; ++i)
        {
            double x{}, y{};
            cin >> x >> y;
            Point p{x, y};

            cout << solve(p, poly) << "\n";
        }
    }

    cout << std::flush;
    return 0;
}
