#include "core/orientation.h"
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 CGALPoint2;

OrientationResult orientation_2(const Point2& p1, const Point2& p2, const Point2& p3) {
    CGALPoint2 a(p1.x(), p1.y());
    CGALPoint2 b(p2.x(), p2.y());
    CGALPoint2 c(p3.x(), p3.y());

    auto result = CGAL::orientation(a, b, c);

    if (result == CGAL::LEFT_TURN)  return {1};
    if (result == CGAL::RIGHT_TURN) return {-1};
    return {0};
}