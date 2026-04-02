#include "core/ray3.h"

bool ray3_eq(const Ray3& a, const Ray3& b) {
    return a.r == b.r;
}

bool ray3_neq(const Ray3& a, const Ray3& b) {
    return a.r != b.r;
}

Point3 ray3_source(const Ray3& r) {
    auto p = r.r.source();
    return Point3(CGAL::to_double(p.x()),
                  CGAL::to_double(p.y()),
                  CGAL::to_double(p.z()));
}

Point3 ray3_point(const Ray3& r, double i) {
    auto p = r.r.point(i);
    return Point3(CGAL::to_double(p.x()),
                  CGAL::to_double(p.y()),
                  CGAL::to_double(p.z()));
}

Direction3 ray3_direction(const Ray3& r) {
    return Direction3(r.r.direction());
}

Vector3 ray3_to_vector(const Ray3& r) {
    auto v = r.r.to_vector();
    return Vector3(CGAL::to_double(v.x()),
                   CGAL::to_double(v.y()),
                   CGAL::to_double(v.z()));
}

Line3 ray3_supporting_line(const Ray3& r) {
    return Line3(r.r.supporting_line());
}

Ray3 ray3_opposite(const Ray3& r) {
    return Ray3(r.r.opposite());
}

bool ray3_is_degenerate(const Ray3& r) {
    return r.r.is_degenerate();
}

bool ray3_has_on(const Ray3& r, const Point3& p) {
    return r.r.has_on(CGALPoint3(p.x(), p.y(), p.z()));
}