#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point;

// Computes squared distance between two 2D points
// Called from wrapper.cpp via pybind11
// Arguments are passed from Python as plain doubles

double squared_distance(double x1, double y1, double x2, double y2) {
    Point p(x1, y1), q(x2, y2);
    return CGAL::to_double(CGAL::squared_distance(p, q));
}