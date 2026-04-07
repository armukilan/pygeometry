#include "core/global_functions.h"

// Helper to convert CGAL::Angle to int
static int angle_to_int(CGAL::Angle a) {
    if (a == CGAL::ACUTE)  return 1;
    if (a == CGAL::OBTUSE) return -1;
    return 0;  // RIGHT
}

// ============================================================
// ANGLE
// ============================================================

int angle_vec2_vec2(const Vector2& u, const Vector2& v) {
    return angle_to_int(CGAL::angle(u.v, v.v));
}

int angle_pt2_pt2_pt2(const Point2& p, const Point2& q, const Point2& r) {
    return angle_to_int(CGAL::angle(
        CGALPoint2(p.x(), p.y()),
        CGALPoint2(q.x(), q.y()),
        CGALPoint2(r.x(), r.y())));
}

int angle_pt2_pt2_pt2_pt2(const Point2& p, const Point2& q,
                           const Point2& r, const Point2& s) {
    return angle_to_int(CGAL::angle(
        CGALPoint2(p.x(), p.y()),
        CGALPoint2(q.x(), q.y()),
        CGALPoint2(r.x(), r.y()),
        CGALPoint2(s.x(), s.y())));
}

int angle_vec3_vec3(const Vector3& u, const Vector3& v) {
    return angle_to_int(CGAL::angle(u.v, v.v));
}

int angle_pt3_pt3_pt3(const Point3& p, const Point3& q, const Point3& r) {
    return angle_to_int(CGAL::angle(
        CGALPoint3(p.x(), p.y(), p.z()),
        CGALPoint3(q.x(), q.y(), q.z()),
        CGALPoint3(r.x(), r.y(), r.z())));
}

int angle_pt3_pt3_pt3_pt3(const Point3& p, const Point3& q,
                           const Point3& r, const Point3& s) {
    return angle_to_int(CGAL::angle(
        CGALPoint3(p.x(), p.y(), p.z()),
        CGALPoint3(q.x(), q.y(), q.z()),
        CGALPoint3(r.x(), r.y(), r.z()),
        CGALPoint3(s.x(), s.y(), s.z())));
}

int angle_pt3_pt3_pt3_vec3(const Point3& p, const Point3& q,
                            const Point3& r, const Vector3& v) {
    return angle_to_int(CGAL::angle(
        CGALPoint3(p.x(), p.y(), p.z()),
        CGALPoint3(q.x(), q.y(), q.z()),
        CGALPoint3(r.x(), r.y(), r.z()),
        v.v));
}

// ============================================================
// APPROXIMATE ANGLE
// ============================================================

double approximate_angle_pt3(const Point3& p, const Point3& q, const Point3& r) {
    return CGAL::to_double(CGAL::approximate_angle(
        CGALPoint3(p.x(), p.y(), p.z()),
        CGALPoint3(q.x(), q.y(), q.z()),
        CGALPoint3(r.x(), r.y(), r.z())));
}

double approximate_angle_vec3(const Vector3& u, const Vector3& v) {
    return CGAL::to_double(CGAL::approximate_angle(u.v, v.v));
}

// ============================================================
// APPROXIMATE DIHEDRAL ANGLE
// ============================================================

double approximate_dihedral_angle(const Point3& p, const Point3& q,
                                  const Point3& r, const Point3& s) {
    return CGAL::to_double(CGAL::approximate_dihedral_angle(
        CGALPoint3(p.x(), p.y(), p.z()),
        CGALPoint3(q.x(), q.y(), q.z()),
        CGALPoint3(r.x(), r.y(), r.z()),
        CGALPoint3(s.x(), s.y(), s.z())));
}

// ============================================================
// ARE ORDERED ALONG LINE
// ============================================================

bool are_ordered_along_line_2(const Point2& p, const Point2& q, const Point2& r) {
    return CGAL::are_ordered_along_line(
        CGALPoint2(p.x(), p.y()),
        CGALPoint2(q.x(), q.y()),
        CGALPoint2(r.x(), r.y()));
}

bool are_ordered_along_line_3(const Point3& p, const Point3& q, const Point3& r) {
    return CGAL::are_ordered_along_line(
        CGALPoint3(p.x(), p.y(), p.z()),
        CGALPoint3(q.x(), q.y(), q.z()),
        CGALPoint3(r.x(), r.y(), r.z()));
}

// ============================================================
// ARE STRICTLY ORDERED ALONG LINE
// ============================================================

bool are_strictly_ordered_along_line_2(const Point2& p, const Point2& q, const Point2& r) {
    return CGAL::are_strictly_ordered_along_line(
        CGALPoint2(p.x(), p.y()),
        CGALPoint2(q.x(), q.y()),
        CGALPoint2(r.x(), r.y()));
}

bool are_strictly_ordered_along_line_3(const Point3& p, const Point3& q, const Point3& r) {
    return CGAL::are_strictly_ordered_along_line(
        CGALPoint3(p.x(), p.y(), p.z()),
        CGALPoint3(q.x(), q.y(), q.z()),
        CGALPoint3(r.x(), r.y(), r.z()));
}