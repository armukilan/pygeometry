#include "core/weighted_point2.h"

// --- Bare point and weight accessors ---
Point2 wp2_point(const WeightedPoint2& wp) {
    auto p = wp.wp.point();
    return Point2(CGAL::to_double(p.x()), CGAL::to_double(p.y()));
}

double wp2_weight(const WeightedPoint2& wp) {
    return CGAL::to_double(wp.wp.weight());
}

// --- Operations ---
bool wp2_eq(const WeightedPoint2& a, const WeightedPoint2& b) {
    return a.wp == b.wp;
}

bool wp2_neq(const WeightedPoint2& a, const WeightedPoint2& b) {
    return a.wp != b.wp;
}

// --- Coordinate access ---
double wp2_hx(const WeightedPoint2& wp) {
    return CGAL::to_double(wp.wp.hx());
}

double wp2_hy(const WeightedPoint2& wp) {
    return CGAL::to_double(wp.wp.hy());
}

double wp2_hw(const WeightedPoint2& wp) {
    return CGAL::to_double(wp.wp.hw());
}

double wp2_x(const WeightedPoint2& wp) {
    return CGAL::to_double(wp.wp.x());
}

double wp2_y(const WeightedPoint2& wp) {
    return CGAL::to_double(wp.wp.y());
}

// --- Convenience ---
double wp2_homogeneous(const WeightedPoint2& wp, int i) {
    return CGAL::to_double(wp.wp.homogeneous(i));
}

double wp2_cartesian(const WeightedPoint2& wp, int i) {
    return CGAL::to_double(wp.wp.cartesian(i));
}

int wp2_dimension(const WeightedPoint2& wp) {
    return wp.wp.dimension();
}

Bbox2 wp2_bbox(const WeightedPoint2& wp) {
    auto b = wp.wp.bbox();
    return Bbox2(b.xmin(), b.ymin(), b.xmax(), b.ymax());
}