#include "core/sphere3.h"

Point3 sphere3_center(const Sphere3& s) {
    auto c = s.s.center();
    return Point3(CGAL::to_double(c.x()),
                  CGAL::to_double(c.y()),
                  CGAL::to_double(c.z()));
}

double sphere3_squared_radius(const Sphere3& s) {
    return CGAL::to_double(s.s.squared_radius());
}

int sphere3_orientation(const Sphere3& s) {
    auto o = s.s.orientation();
    if (o == CGAL::COUNTERCLOCKWISE) return 1;
    if (o == CGAL::CLOCKWISE)        return -1;
    return 0;
}

bool sphere3_eq(const Sphere3& a, const Sphere3& b) { return a.s == b.s; }
bool sphere3_neq(const Sphere3& a, const Sphere3& b) { return a.s != b.s; }

bool sphere3_is_degenerate(const Sphere3& s) {
    return s.s.is_degenerate();
}

int sphere3_oriented_side(const Sphere3& s, const Point3& p) {
    auto side = s.s.oriented_side(CGALPoint3(p.x(), p.y(), p.z()));
    if (side == CGAL::ON_POSITIVE_SIDE) return 1;
    if (side == CGAL::ON_NEGATIVE_SIDE) return -1;
    return 0;
}

int sphere3_bounded_side(const Sphere3& s, const Point3& p) {
    auto side = s.s.bounded_side(CGALPoint3(p.x(), p.y(), p.z()));
    if (side == CGAL::ON_BOUNDED_SIDE)   return 1;
    if (side == CGAL::ON_UNBOUNDED_SIDE) return -1;
    return 0;
}

bool sphere3_has_on_positive_side(const Sphere3& s, const Point3& p) {
    return s.s.has_on_positive_side(CGALPoint3(p.x(), p.y(), p.z()));
}

bool sphere3_has_on_negative_side(const Sphere3& s, const Point3& p) {
    return s.s.has_on_negative_side(CGALPoint3(p.x(), p.y(), p.z()));
}

bool sphere3_has_on_boundary(const Sphere3& s, const Point3& p) {
    return s.s.has_on_boundary(CGALPoint3(p.x(), p.y(), p.z()));
}

bool sphere3_has_on_bounded_side(const Sphere3& s, const Point3& p) {
    return s.s.has_on_bounded_side(CGALPoint3(p.x(), p.y(), p.z()));
}

bool sphere3_has_on_unbounded_side(const Sphere3& s, const Point3& p) {
    return s.s.has_on_unbounded_side(CGALPoint3(p.x(), p.y(), p.z()));
}

bool sphere3_has_on(const Sphere3& s, const Point3& p) {
    return s.s.has_on(CGALPoint3(p.x(), p.y(), p.z()));
}

Sphere3 sphere3_opposite(const Sphere3& s) {
    return Sphere3(s.s.opposite());
}

Bbox3 sphere3_bbox(const Sphere3& s) {
    auto b = s.s.bbox();
    return Bbox3(b.xmin(), b.ymin(), b.zmin(),
                 b.xmax(), b.ymax(), b.zmax());
}