#include "core/iso_cuboid3.h"

bool iso_cuboid3_eq(const IsoCuboid3& a, const IsoCuboid3& b) {
    return a.c == b.c;
}

bool iso_cuboid3_neq(const IsoCuboid3& a, const IsoCuboid3& b) {
    return a.c != b.c;
}

Point3 iso_cuboid3_vertex(const IsoCuboid3& c, int i) {
    auto v = c.c.vertex(i);
    return Point3(CGAL::to_double(v.x()),
                  CGAL::to_double(v.y()),
                  CGAL::to_double(v.z()));
}

Point3 iso_cuboid3_min(const IsoCuboid3& c) {
    auto v = c.c.min();
    return Point3(CGAL::to_double(v.x()),
                  CGAL::to_double(v.y()),
                  CGAL::to_double(v.z()));
}

Point3 iso_cuboid3_max(const IsoCuboid3& c) {
    auto v = c.c.max();
    return Point3(CGAL::to_double(v.x()),
                  CGAL::to_double(v.y()),
                  CGAL::to_double(v.z()));
}

double iso_cuboid3_xmin(const IsoCuboid3& c) { return CGAL::to_double(c.c.xmin()); }
double iso_cuboid3_ymin(const IsoCuboid3& c) { return CGAL::to_double(c.c.ymin()); }
double iso_cuboid3_zmin(const IsoCuboid3& c) { return CGAL::to_double(c.c.zmin()); }
double iso_cuboid3_xmax(const IsoCuboid3& c) { return CGAL::to_double(c.c.xmax()); }
double iso_cuboid3_ymax(const IsoCuboid3& c) { return CGAL::to_double(c.c.ymax()); }
double iso_cuboid3_zmax(const IsoCuboid3& c) { return CGAL::to_double(c.c.zmax()); }

double iso_cuboid3_min_coord(const IsoCuboid3& c, int i) {
    return CGAL::to_double(c.c.min_coord(i));
}

double iso_cuboid3_max_coord(const IsoCuboid3& c, int i) {
    return CGAL::to_double(c.c.max_coord(i));
}

bool iso_cuboid3_is_degenerate(const IsoCuboid3& c) {
    return c.c.is_degenerate();
}

int iso_cuboid3_bounded_side(const IsoCuboid3& c, const Point3& p) {
    auto side = c.c.bounded_side(CGALPoint3(p.x(), p.y(), p.z()));
    if (side == CGAL::ON_BOUNDED_SIDE)   return 1;
    if (side == CGAL::ON_UNBOUNDED_SIDE) return -1;
    return 0;
}

bool iso_cuboid3_has_on_boundary(const IsoCuboid3& c, const Point3& p) {
    return c.c.has_on_boundary(CGALPoint3(p.x(), p.y(), p.z()));
}

bool iso_cuboid3_has_on_bounded_side(const IsoCuboid3& c, const Point3& p) {
    return c.c.has_on_bounded_side(CGALPoint3(p.x(), p.y(), p.z()));
}

bool iso_cuboid3_has_on_unbounded_side(const IsoCuboid3& c, const Point3& p) {
    return c.c.has_on_unbounded_side(CGALPoint3(p.x(), p.y(), p.z()));
}

double iso_cuboid3_volume(const IsoCuboid3& c) {
    return CGAL::to_double(c.c.volume());
}

Bbox3 iso_cuboid3_bbox(const IsoCuboid3& c) {
    auto b = c.c.bbox();
    return Bbox3(b.xmin(), b.ymin(), b.zmin(),
                 b.xmax(), b.ymax(), b.zmax());
}