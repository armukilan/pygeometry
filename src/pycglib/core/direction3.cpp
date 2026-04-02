#include "core/direction3.h"

Direction3 direction3_from_vector(const Vector3& v) {
    return Direction3(CGALDirection3(v.v));
}

Direction3 direction3_from_xyz(double x, double y, double z) {
    return Direction3(x, y, z);
}

bool direction3_eq(const Direction3& a, const Direction3& b) {
    return a.d == b.d;
}

bool direction3_neq(const Direction3& a, const Direction3& b) {
    return a.d != b.d;
}

Direction3 direction3_opposite(const Direction3& d) {
    return Direction3(-d.d);
}

Vector3 direction3_vector(const Direction3& d) {
    auto v = d.d.vector();
    return Vector3(CGAL::to_double(v.x()),
                   CGAL::to_double(v.y()),
                   CGAL::to_double(v.z()));
}