#include "core/iso_rectangle2.h"

// --- Operations ---
bool iso_rect2_eq(const IsoRectangle2& a, const IsoRectangle2& b) {
    return a.r == b.r;
}

bool iso_rect2_neq(const IsoRectangle2& a, const IsoRectangle2& b) {
    return a.r != b.r;
}

Point2 iso_rect2_vertex(const IsoRectangle2& r, int i) {
    auto v = r.r.vertex(i);
    return Point2(CGAL::to_double(v.x()), CGAL::to_double(v.y()));
}

Point2 iso_rect2_min(const IsoRectangle2& r) {
    auto v = r.r.min();
    return Point2(CGAL::to_double(v.x()), CGAL::to_double(v.y()));
}

Point2 iso_rect2_max(const IsoRectangle2& r) {
    auto v = r.r.max();
    return Point2(CGAL::to_double(v.x()), CGAL::to_double(v.y()));
}

double iso_rect2_xmin(const IsoRectangle2& r) {
    return CGAL::to_double(r.r.xmin());
}

double iso_rect2_ymin(const IsoRectangle2& r) {
    return CGAL::to_double(r.r.ymin());
}

double iso_rect2_xmax(const IsoRectangle2& r) {
    return CGAL::to_double(r.r.xmax());
}

double iso_rect2_ymax(const IsoRectangle2& r) {
    return CGAL::to_double(r.r.ymax());
}

double iso_rect2_min_coord(const IsoRectangle2& r, int i) {
    return CGAL::to_double(r.r.min_coord(i));
}

double iso_rect2_max_coord(const IsoRectangle2& r, int i) {
    return CGAL::to_double(r.r.max_coord(i));
}

// --- Predicates ---
bool iso_rect2_is_degenerate(const IsoRectangle2& r) {
    return r.r.is_degenerate();
}

int iso_rect2_bounded_side(const IsoRectangle2& r, const Point2& p) {
    auto side = r.r.bounded_side(CGALPoint2(p.x(), p.y()));
    if (side == CGAL::ON_BOUNDED_SIDE)   return 1;
    if (side == CGAL::ON_UNBOUNDED_SIDE) return -1;
    return 0;
}

bool iso_rect2_has_on_boundary(const IsoRectangle2& r, const Point2& p) {
    return r.r.has_on_boundary(CGALPoint2(p.x(), p.y()));
}

bool iso_rect2_has_on_bounded_side(const IsoRectangle2& r, const Point2& p) {
    return r.r.has_on_bounded_side(CGALPoint2(p.x(), p.y()));
}

bool iso_rect2_has_on_unbounded_side(const IsoRectangle2& r, const Point2& p) {
    return r.r.has_on_unbounded_side(CGALPoint2(p.x(), p.y()));
}

// --- Miscellaneous ---
double iso_rect2_area(const IsoRectangle2& r) {
    return CGAL::to_double(r.r.area());
}

Bbox2 iso_rect2_bbox(const IsoRectangle2& r) {
    auto b = r.r.bbox();
    return Bbox2(b.xmin(), b.ymin(), b.xmax(), b.ymax());
}