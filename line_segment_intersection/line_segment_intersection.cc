/**
 * Solves the Line segment intersection problem.
 *
 * Time Complexity: O(1) for each test case.
 * Space Complexity: O(1)
 *
 * @author Abbas Alubeid - abbal179
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

using std::cout, std::cin, std::vector, std::string, std::abs;

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
 * Fixes negative zero to positive zero for output.
 *
 * Kattis requires 0.00 instead of -0.00 when a coordinate rounds to zero
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
double fix_zero(double x)
{
    if (abs(x) < 1e-9)
        return 0.0;
    return x;
}

/**
 * Finds the intersection between two line segments.
 *
 * The function start by checking if either segment is actually a point by
 * comparing start and end coordinates to see if the segment has zero length.
 * If both are points it checks if they are the same point. If only one is a point
 * it uses on_segment to check if that point lies on the other segment.
 *
 * For regular segments the function computes direction vectors and uses
 * cross products to determine if segments are parallel or collinear. When
 * the cross product of the two direction vectors is zero the segments are
 * parallel. If parallel we check if they are also collinear by testing if
 * the vector between starting points is also parallel to the direction vectors.
 * Parallel but not collinear segments never intersect.
 *
 * For collinear segments we project all four endpoints onto a common axis to
 * convert the problem to finding overlapping intervals on a line. The
 * projection converts each point to a parameter t where the segment AB spans
 * from t=0 to t=1. We find the overlap interval by taking the maximum of the
 * two starting parameters and the minimum of the two ending parameters. If
 * this interval is valid we convert back to actual points. A zero length
 * interval means the segments touch at a single point and otherwise they
 * overlap along a segment which is returned with points ordered by xcoordinate
 * then ycoordinate.
 *
 * For non parallel segments we use parametric equations where any point on AB
 * can be written as a + t * (b - a) with t between 0 and 1 and similarlry for
 * CD with parameter s. We solve for t and s using cross products. The parameter
 * t equals the cross product of the vector from a to c with the direction of CD
 * divided by the cross product of the two dircetion vectors and similarly for s.
 * If both parameters are in the valid range zero to one then the segments intersect
 * and we compute the intersection point using either parametric equation.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
vector<Point> intersect(Point &a, Point &b, Point &c, Point &d)
{
    vector<Point> result{};

    bool ab_is_point = (abs(a.x - b.x) < 1e-9 && abs(a.y - b.y) < 1e-9);
    bool cd_is_point = (abs(c.x - d.x) < 1e-9 && abs(c.y - d.y) < 1e-9);

    if (ab_is_point && cd_is_point)
    {
        if (abs(a.x - c.x) < 1e-9 && abs(a.y - c.y) < 1e-9)
        {
            Point p = a;
            p.x = fix_zero(p.x);
            p.y = fix_zero(p.y);
            result.push_back(p);
        }
        return result;
    }
    else if (ab_is_point)
    {
        if (on_segment(a, c, d))
        {
            Point p = a;
            p.x = fix_zero(p.x);
            p.y = fix_zero(p.y);
            result.push_back(p);
        }
        return result;
    }
    else if (cd_is_point)
    {
        if (on_segment(c, a, b))
        {
            Point p = c;
            p.x = fix_zero(p.x);
            p.y = fix_zero(p.y);
            result.push_back(p);
        }
        return result;
    }

    Point ab = b - a;
    Point cd = d - c;
    Point ac = c - a;

    double cross_ab_cd = ab.cross(cd);
    double cross_ac_cd = ac.cross(cd);
    double cross_ac_ab = ac.cross(ab);

    // Collinear check
    if (abs(cross_ab_cd) < 1e-9)
    {
        // parallel
        if (abs(cross_ac_ab) > 1e-9)
            return result;

        // project all points to one axis
        double t0{}, t1{}, t2{}, t3{};

        if (abs(ab.x) > 1e-9)
        {
            t0 = 0.0;
            t1 = 1.0;
            t2 = (c.x - a.x) / ab.x;
            t3 = (d.x - a.x) / ab.x;
        }
        else
        {
            t0 = 0.0;
            t1 = 1.0;
            t2 = (c.y - a.y) / ab.y;
            t3 = (d.y - a.y) / ab.y;
        }

        if (t2 > t3)
            std::swap(t2, t3);

        double overlap_start = std::max(t0, t2);
        double overlap_end = std::min(t1, t3);

        if (overlap_start > overlap_end)
            return result;

        // find overlapp
        Point p1 = a + ab * overlap_start;
        Point p2 = a + ab * overlap_end;

        p1.x = fix_zero(p1.x);
        p1.y = fix_zero(p1.y);
        p2.x = fix_zero(p2.x);
        p2.y = fix_zero(p2.y);

        if (abs(overlap_start - overlap_end) < 1e-9)
            result.push_back(p1);
        else
        {
            if (p1.x < p2.x || (abs(p1.x - p2.x) < 1e-9 && p1.y < p2.y))
            {
                result.push_back(p1);
                result.push_back(p2);
            }
            else
            {
                result.push_back(p2);
                result.push_back(p1);
            }
        }
    }
    else
    {
        double t = cross_ac_cd / cross_ab_cd;
        double s = cross_ac_ab / cross_ab_cd;

        if (t >= -1e-9 && t <= 1.0 + 1e-9 && s >= -1e-9 && s <= 1.0 + 1e-9)
        {
            Point p = a + ab * t;
            p.x = fix_zero(p.x);
            p.y = fix_zero(p.y);
            result.push_back(p);
        }
    }

    return result;
}

int main()
{
    // Improves IO speed
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n{};
    cin >> n;

    cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < n; ++i)
    {
        double x1{}, y1{}, x2{}, y2{}, x3{}, y3{}, x4{}, y4{};
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        Point a{x1, y1};
        Point b{x2, y2};
        Point c{x3, y3};
        Point d{x4, y4};

        vector<Point> result = intersect(a, b, c, d);

        if (result.size() == 0)
            cout << "none\n";
        else if (result.size() == 1)
            cout << result[0].x << " " << result[0].y << "\n";
        else
            cout << result[0].x << " " << result[0].y << " "
                 << result[1].x << " " << result[1].y << "\n";
    }

    cout << std::flush;
    return 0;
}
