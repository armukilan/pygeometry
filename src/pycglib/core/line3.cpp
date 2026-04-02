#include "core/line3.h"

#include "core/ray3.h"

Line3 line3_from_ray(const Ray3& r) {
    return Line3(r.r.supporting_line());
}

bool line3_eq(const Line3& a, const Line3& b) {
    return a.l == b.l;
}

bool line3_neq(const Line3& a, const Line3& b) {
    return a.l != b.l;
}

Point3 line3_projection(const Line3& l, const Point3& p) {
    auto r = l.l.projection(CGALPoint3(p.x(), p.y(), p.z()));
    return Point3(CGAL::to_double(r.x()),
                  CGAL::to_double(r.y()),
                  CGAL::to_double(r.z()));
}

Point3 line3_point(const Line3& l, double i) {
    auto r = l.l.point(i);
    return Point3(CGAL::to_double(r.x()),
                  CGAL::to_double(r.y()),
                  CGAL::to_double(r.z()));
}

bool line3_is_degenerate(const Line3& l) {
    return l.l.is_degenerate();
}

bool line3_has_on(const Line3& l, const Point3& p) {
    return l.l.has_on(CGALPoint3(p.x(), p.y(), p.z()));
}

Plane3 line3_perpendicular_plane(const Line3& l, const Point3& p) {
    return Plane3(l.l.perpendicular_plane(CGALPoint3(p.x(), p.y(), p.z())));
}

Line3 line3_opposite(const Line3& l) {
    return Line3(l.l.opposite());
}

Vector3 line3_to_vector(const Line3& l) {
    auto v = l.l.to_vector();
    return Vector3(CGAL::to_double(v.x()),
                   CGAL::to_double(v.y()),
                   CGAL::to_double(v.z()));
}

Direction3 line3_direction(const Line3& l) {
    return Direction3(l.l.direction());
}