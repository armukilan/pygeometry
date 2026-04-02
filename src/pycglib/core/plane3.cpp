#include "core/plane3.h"

bool plane3_eq(const Plane3& a, const Plane3& b) {
    return a.p == b.p;
}

bool plane3_neq(const Plane3& a, const Plane3& b) {
    return a.p != b.p;
}

Line3 plane3_perpendicular_line(const Plane3& h, const Point3& p) {
    return Line3(h.p.perpendicular_line(CGALPoint3(p.x(), p.y(), p.z())));
}

Point3 plane3_projection(const Plane3& h, const Point3& p) {
    auto r = h.p.projection(CGALPoint3(p.x(), p.y(), p.z()));
    return Point3(CGAL::to_double(r.x()),
                  CGAL::to_double(r.y()),
                  CGAL::to_double(r.z()));
}

Plane3 plane3_opposite(const Plane3& h) {
    return Plane3(h.p.opposite());
}

Point3 plane3_point(const Plane3& h) {
    auto r = h.p.point();
    return Point3(CGAL::to_double(r.x()),
                  CGAL::to_double(r.y()),
                  CGAL::to_double(r.z()));
}

Vector3 plane3_orthogonal_vector(const Plane3& h) {
    auto v = h.p.orthogonal_vector();
    return Vector3(CGAL::to_double(v.x()),
                   CGAL::to_double(v.y()),
                   CGAL::to_double(v.z()));
}

Direction3 plane3_orthogonal_direction(const Plane3& h) {
    return Direction3(h.p.orthogonal_direction());
}

Vector3 plane3_base1(const Plane3& h) {
    auto v = h.p.base1();
    return Vector3(CGAL::to_double(v.x()),
                   CGAL::to_double(v.y()),
                   CGAL::to_double(v.z()));
}

Vector3 plane3_base2(const Plane3& h) {
    auto v = h.p.base2();
    return Vector3(CGAL::to_double(v.x()),
                   CGAL::to_double(v.y()),
                   CGAL::to_double(v.z()));
}

// --- 2D Conversion ---
Point2 plane3_to_2d(const Plane3& h, const Point3& p) {
    auto r = h.p.to_2d(CGALPoint3(p.x(), p.y(), p.z()));
    return Point2(CGAL::to_double(r.x()), CGAL::to_double(r.y()));
}

Point3 plane3_to_3d(const Plane3& h, const Point2& p) {
    auto r = h.p.to_3d(CGALPoint2(p.x(), p.y()));
    return Point3(CGAL::to_double(r.x()),
                  CGAL::to_double(r.y()),
                  CGAL::to_double(r.z()));
}

// --- Predicates ---
int plane3_oriented_side(const Plane3& h, const Point3& p) {
    auto side = h.p.oriented_side(CGALPoint3(p.x(), p.y(), p.z()));
    if (side == CGAL::ON_POSITIVE_SIDE) return 1;
    if (side == CGAL::ON_NEGATIVE_SIDE) return -1;
    return 0;
}

bool plane3_has_on_point(const Plane3& h, const Point3& p) {
    return h.p.has_on(CGALPoint3(p.x(), p.y(), p.z()));
}

bool plane3_has_on_positive_side(const Plane3& h, const Point3& p) {
    return h.p.has_on_positive_side(CGALPoint3(p.x(), p.y(), p.z()));
}

bool plane3_has_on_negative_side(const Plane3& h, const Point3& p) {
    return h.p.has_on_negative_side(CGALPoint3(p.x(), p.y(), p.z()));
}

bool plane3_has_on_line(const Plane3& h, const Line3& l) {
    return h.p.has_on(l.l);
}

bool plane3_is_degenerate(const Plane3& h) {
    return h.p.is_degenerate();
}

Plane3 plane3_from_ray(const Ray3& r, const Point3& p) {
    return Plane3(CGALPlane3(r.r, CGALPoint3(p.x(), p.y(), p.z())));
}

Plane3 plane3_from_segment(const Segment3& s, const Point3& p) {
    return Plane3(CGALPlane3(s.s, CGALPoint3(p.x(), p.y(), p.z())));
}