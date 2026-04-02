#include "core/segment3.h"

bool segment3_eq(const Segment3& a, const Segment3& b) {
    return a.s == b.s;
}

bool segment3_neq(const Segment3& a, const Segment3& b) {
    return a.s != b.s;
}

Point3 segment3_source(const Segment3& s) {
    auto p = s.s.source();
    return Point3(CGAL::to_double(p.x()),
                  CGAL::to_double(p.y()),
                  CGAL::to_double(p.z()));
}

Point3 segment3_target(const Segment3& s) {
    auto p = s.s.target();
    return Point3(CGAL::to_double(p.x()),
                  CGAL::to_double(p.y()),
                  CGAL::to_double(p.z()));
}

Point3 segment3_min(const Segment3& s) {
    auto p = s.s.min();
    return Point3(CGAL::to_double(p.x()),
                  CGAL::to_double(p.y()),
                  CGAL::to_double(p.z()));
}

Point3 segment3_max(const Segment3& s) {
    auto p = s.s.max();
    return Point3(CGAL::to_double(p.x()),
                  CGAL::to_double(p.y()),
                  CGAL::to_double(p.z()));
}

Point3 segment3_vertex(const Segment3& s, int i) {
    auto p = s.s.vertex(i);
    return Point3(CGAL::to_double(p.x()),
                  CGAL::to_double(p.y()),
                  CGAL::to_double(p.z()));
}

Point3 segment3_point(const Segment3& s, int i) {
    auto p = s.s.point(i);
    return Point3(CGAL::to_double(p.x()),
                  CGAL::to_double(p.y()),
                  CGAL::to_double(p.z()));
}

double segment3_squared_length(const Segment3& s) {
    return CGAL::to_double(s.s.squared_length());
}

Vector3 segment3_to_vector(const Segment3& s) {
    auto v = s.s.to_vector();
    return Vector3(CGAL::to_double(v.x()),
                   CGAL::to_double(v.y()),
                   CGAL::to_double(v.z()));
}

Direction3 segment3_direction(const Segment3& s) {
    return Direction3(s.s.direction());
}

Segment3 segment3_opposite(const Segment3& s) {
    return Segment3(s.s.opposite());
}

Line3 segment3_supporting_line(const Segment3& s) {
    return Line3(s.s.supporting_line());
}

bool segment3_is_degenerate(const Segment3& s) {
    return s.s.is_degenerate();
}

bool segment3_has_on(const Segment3& s, const Point3& p) {
    return s.s.has_on(CGALPoint3(p.x(), p.y(), p.z()));
}

Bbox3 segment3_bbox(const Segment3& s) {
    auto b = s.s.bbox();
    return Bbox3(b.xmin(), b.ymin(), b.zmin(),
                 b.xmax(), b.ymax(), b.zmax());
}