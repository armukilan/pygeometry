#include "core/line2.h"

// --- Operations ---
bool line2_eq(const Line2& a, const Line2& b) {
    return a.l == b.l;
}

bool line2_neq(const Line2& a, const Line2& b) {
    return a.l != b.l;
}

Point2 line2_point(const Line2& l, double i) {
    auto p = l.l.point(i);
    return Point2(CGAL::to_double(p.x()), CGAL::to_double(p.y()));
}

Point2 line2_projection(const Line2& l, const Point2& p) {
    auto proj = l.l.projection(CGALPoint2(p.x(), p.y()));
    return Point2(CGAL::to_double(proj.x()), CGAL::to_double(proj.y()));
}

double line2_x_at_y(const Line2& l, double y) {
    return CGAL::to_double(l.l.x_at_y(y));
}

double line2_y_at_x(const Line2& l, double x) {
    return CGAL::to_double(l.l.y_at_x(x));
}

// --- Predicates ---
bool line2_is_degenerate(const Line2& l) {
    return l.l.is_degenerate();
}

bool line2_is_horizontal(const Line2& l) {
    return l.l.is_horizontal();
}

bool line2_is_vertical(const Line2& l) {
    return l.l.is_vertical();
}

int line2_oriented_side(const Line2& l, const Point2& p) {
    auto side = l.l.oriented_side(CGALPoint2(p.x(), p.y()));
    if (side == CGAL::ON_POSITIVE_SIDE)   return 1;
    if (side == CGAL::ON_NEGATIVE_SIDE)   return -1;
    return 0;  // ON_ORIENTED_BOUNDARY
}

// --- Convenience ---
bool line2_has_on(const Line2& l, const Point2& p) {
    return l.l.has_on(CGALPoint2(p.x(), p.y()));
}

bool line2_has_on_positive_side(const Line2& l, const Point2& p) {
    return l.l.has_on_positive_side(CGALPoint2(p.x(), p.y()));
}

bool line2_has_on_negative_side(const Line2& l, const Point2& p) {
    return l.l.has_on_negative_side(CGALPoint2(p.x(), p.y()));
}

// --- Miscellaneous ---
Vector2 line2_to_vector(const Line2& l) {
    auto v = l.l.to_vector();
    return Vector2(CGAL::to_double(v.x()), CGAL::to_double(v.y()));
}

Direction2 line2_direction(const Line2& l) {
    return Direction2(l.l.direction());
}

Line2 line2_opposite(const Line2& l) {
    return Line2(l.l.opposite());
}

Line2 line2_perpendicular(const Line2& l, const Point2& p) {
    return Line2(l.l.perpendicular(CGALPoint2(p.x(), p.y())));
}