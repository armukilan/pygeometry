#include "core/point3.h"

// --- Arithmetic ---
Vector3 point3_sub(const Point3& a, const Point3& b) {
    auto r = a.p - b.p;
    return Vector3(CGAL::to_double(r.x()),
                   CGAL::to_double(r.y()),
                   CGAL::to_double(r.z()));
}

Point3 point3_add_vector(const Point3& p, const Vector3& v) {
    auto r = p.p + v.v;
    return Point3(CGAL::to_double(r.x()),
                  CGAL::to_double(r.y()),
                  CGAL::to_double(r.z()));
}

Point3 point3_sub_vector(const Point3& p, const Vector3& v) {
    auto r = p.p - v.v;
    return Point3(CGAL::to_double(r.x()),
                  CGAL::to_double(r.y()),
                  CGAL::to_double(r.z()));
}

Point3 point3_iadd(Point3& p, const Vector3& v) {
    p.p = p.p + v.v;
    return p;
}

Point3 point3_isub(Point3& p, const Vector3& v) {
    p.p = p.p - v.v;
    return p;
}

// --- Comparison ---
bool point3_eq(const Point3& a, const Point3& b)  { return a.p == b.p; }
bool point3_neq(const Point3& a, const Point3& b) { return a.p != b.p; }
bool point3_lt(const Point3& a, const Point3& b)  { return a.p < b.p; }
bool point3_gt(const Point3& a, const Point3& b)  { return a.p > b.p; }
bool point3_le(const Point3& a, const Point3& b)  { return a.p <= b.p; }
bool point3_ge(const Point3& a, const Point3& b)  { return a.p >= b.p; }

// --- Vector3 operations ---
Vector3 vector3_add(const Vector3& a, const Vector3& b) {
    auto r = a.v + b.v;
    return Vector3(CGAL::to_double(r.x()),
                   CGAL::to_double(r.y()),
                   CGAL::to_double(r.z()));
}

Vector3 vector3_sub(const Vector3& a, const Vector3& b) {
    auto r = a.v - b.v;
    return Vector3(CGAL::to_double(r.x()),
                   CGAL::to_double(r.y()),
                   CGAL::to_double(r.z()));
}

Vector3 vector3_mul(const Vector3& a, double scalar) {
    auto r = a.v * scalar;
    return Vector3(CGAL::to_double(r.x()),
                   CGAL::to_double(r.y()),
                   CGAL::to_double(r.z()));
}

Vector3 vector3_neg(const Vector3& v) {
    auto r = -v.v;
    return Vector3(CGAL::to_double(r.x()),
                   CGAL::to_double(r.y()),
                   CGAL::to_double(r.z()));
}

// --- Miscellaneous ---
Bbox3 point3_bbox(const Point3& p) {
    auto b = p.p.bbox();
    return Bbox3(b.xmin(), b.ymin(), b.zmin(),
                 b.xmax(), b.ymax(), b.zmax());
}