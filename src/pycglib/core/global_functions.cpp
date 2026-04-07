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

// ============================================================
// AREA
// ============================================================
double area_2(const Point2& p, const Point2& q, const Point2& r) {
    return CGAL::to_double(CGAL::area(
        CGALPoint2(p.x(), p.y()),
        CGALPoint2(q.x(), q.y()),
        CGALPoint2(r.x(), r.y())));
}

// ============================================================
// BARYCENTER 2D
// ============================================================
static CGALPoint2 toP2(const Point2& p) { return CGALPoint2(p.x(), p.y()); }
static CGALPoint3 toP3(const Point3& p) { return CGALPoint3(p.x(), p.y(), p.z()); }
static Point2 fromP2(const CGALPoint2& p) {
    return Point2(CGAL::to_double(p.x()), CGAL::to_double(p.y()));
}
static Point3 fromP3(const CGALPoint3& p) {
    return Point3(CGAL::to_double(p.x()),
                  CGAL::to_double(p.y()),
                  CGAL::to_double(p.z()));
}

Point2 barycenter_2_2(const Point2& p1, double w1, const Point2& p2) {
    return fromP2(CGAL::barycenter(toP2(p1), w1, toP2(p2)));
}
Point2 barycenter_2_22(const Point2& p1, double w1, const Point2& p2, double w2) {
    return fromP2(CGAL::barycenter(toP2(p1), w1, toP2(p2), w2));
}
Point2 barycenter_2_3(const Point2& p1, double w1, const Point2& p2,
                      double w2, const Point2& p3) {
    return fromP2(CGAL::barycenter(toP2(p1), w1, toP2(p2), w2, toP2(p3)));
}
Point2 barycenter_2_33(const Point2& p1, double w1, const Point2& p2,
                       double w2, const Point2& p3, double w3) {
    return fromP2(CGAL::barycenter(toP2(p1), w1, toP2(p2), w2, toP2(p3), w3));
}
Point2 barycenter_2_4(const Point2& p1, double w1, const Point2& p2,
                      double w2, const Point2& p3, double w3, const Point2& p4) {
    return fromP2(CGAL::barycenter(toP2(p1), w1, toP2(p2), w2, toP2(p3), w3, toP2(p4)));
}
Point2 barycenter_2_44(const Point2& p1, double w1, const Point2& p2, double w2,
                       const Point2& p3, double w3, const Point2& p4, double w4) {
    return fromP2(CGAL::barycenter(toP2(p1), w1, toP2(p2), w2, toP2(p3), w3, toP2(p4), w4));
}

// ============================================================
// BARYCENTER 3D
// ============================================================
Point3 barycenter_3_2(const Point3& p1, double w1, const Point3& p2) {
    return fromP3(CGAL::barycenter(toP3(p1), w1, toP3(p2)));
}
Point3 barycenter_3_22(const Point3& p1, double w1, const Point3& p2, double w2) {
    return fromP3(CGAL::barycenter(toP3(p1), w1, toP3(p2), w2));
}
Point3 barycenter_3_3(const Point3& p1, double w1, const Point3& p2,
                      double w2, const Point3& p3) {
    return fromP3(CGAL::barycenter(toP3(p1), w1, toP3(p2), w2, toP3(p3)));
}
Point3 barycenter_3_33(const Point3& p1, double w1, const Point3& p2,
                       double w2, const Point3& p3, double w3) {
    return fromP3(CGAL::barycenter(toP3(p1), w1, toP3(p2), w2, toP3(p3), w3));
}
Point3 barycenter_3_4(const Point3& p1, double w1, const Point3& p2,
                      double w2, const Point3& p3, double w3, const Point3& p4) {
    return fromP3(CGAL::barycenter(toP3(p1), w1, toP3(p2), w2, toP3(p3), w3, toP3(p4)));
}
Point3 barycenter_3_44(const Point3& p1, double w1, const Point3& p2, double w2,
                       const Point3& p3, double w3, const Point3& p4, double w4) {
    return fromP3(CGAL::barycenter(toP3(p1), w1, toP3(p2), w2,
                                   toP3(p3), w3, toP3(p4), w4));
}

// ============================================================
// BISECTOR
// ============================================================
Line2 bisector_pt2(const Point2& p, const Point2& q) {
    return Line2(CGAL::bisector(toP2(p), toP2(q)));
}
Line2 bisector_ln2(const Line2& l1, const Line2& l2) {
    return Line2(CGAL::bisector(l1.l, l2.l));
}
Plane3 bisector_pt3(const Point3& p, const Point3& q) {
    return Plane3(CGAL::bisector(toP3(p), toP3(q)));
}
Plane3 bisector_pl3(const Plane3& h1, const Plane3& h2) {
    return Plane3(CGAL::bisector(h1.p, h2.p));
}

// ============================================================
// CENTROID 2D
// ============================================================
Point2 centroid_2_3(const Point2& p, const Point2& q, const Point2& r) {
    return fromP2(CGAL::centroid(toP2(p), toP2(q), toP2(r)));
}
Point2 centroid_2_4(const Point2& p, const Point2& q,
                    const Point2& r, const Point2& s) {
    return fromP2(CGAL::centroid(toP2(p), toP2(q), toP2(r), toP2(s)));
}
Point2 centroid_2_tri(const Triangle2& t) {
    return fromP2(CGAL::centroid(t.t));
}

// ============================================================
// CENTROID 3D
// ============================================================
Point3 centroid_3_3(const Point3& p, const Point3& q, const Point3& r) {
    return fromP3(CGAL::centroid(toP3(p), toP3(q), toP3(r)));
}
Point3 centroid_3_4(const Point3& p, const Point3& q,
                    const Point3& r, const Point3& s) {
    return fromP3(CGAL::centroid(toP3(p), toP3(q), toP3(r), toP3(s)));
}
Point3 centroid_3_tri(const Triangle3& t) {
    return fromP3(CGAL::centroid(t.t));
}
Point3 centroid_3_tet(const Tetrahedron3& t) {
    return fromP3(CGAL::centroid(t.t));
}

// ============================================================
// CIRCUMCENTER 2D
// ============================================================
Point2 circumcenter_2_2(const Point2& p, const Point2& q) {
    return fromP2(CGAL::circumcenter(toP2(p), toP2(q)));
}
Point2 circumcenter_2_3(const Point2& p, const Point2& q, const Point2& r) {
    return fromP2(CGAL::circumcenter(toP2(p), toP2(q), toP2(r)));
}
Point2 circumcenter_2_tri(const Triangle2& t) {
    return fromP2(CGAL::circumcenter(t.t));
}

// ============================================================
// CIRCUMCENTER 3D
// ============================================================
Point3 circumcenter_3_2(const Point3& p, const Point3& q) {
    return fromP3(CGAL::circumcenter(toP3(p), toP3(q)));
}
Point3 circumcenter_3_3(const Point3& p, const Point3& q, const Point3& r) {
    return fromP3(CGAL::circumcenter(toP3(p), toP3(q), toP3(r)));
}
Point3 circumcenter_3_4(const Point3& p, const Point3& q,
                        const Point3& r, const Point3& s) {
    return fromP3(CGAL::circumcenter(toP3(p), toP3(q), toP3(r), toP3(s)));
}
Point3 circumcenter_3_tri(const Triangle3& t) {
    return fromP3(CGAL::circumcenter(t.t));
}
Point3 circumcenter_3_tet(const Tetrahedron3& t) {
    return fromP3(CGAL::circumcenter(t.t));
}

// Helper to convert CGAL::Comparison_result to int
static int cmp_to_int(CGAL::Comparison_result r) {
    if (r == CGAL::SMALLER) return -1;
    if (r == CGAL::LARGER)  return 1;
    return 0;  // EQUAL
}

// ============================================================
// COLLINEAR
// ============================================================
bool collinear_2(const Point2& p, const Point2& q, const Point2& r) {
    return CGAL::collinear(toP2(p), toP2(q), toP2(r));
}

bool collinear_3(const Point3& p, const Point3& q, const Point3& r) {
    return CGAL::collinear(toP3(p), toP3(q), toP3(r));
}

// ============================================================
// COLLINEAR ARE ORDERED ALONG LINE
// ============================================================
bool collinear_are_ordered_along_line_2(const Point2& p, const Point2& q, const Point2& r) {
    return CGAL::collinear_are_ordered_along_line(toP2(p), toP2(q), toP2(r));
}

bool collinear_are_ordered_along_line_3(const Point3& p, const Point3& q, const Point3& r) {
    return CGAL::collinear_are_ordered_along_line(toP3(p), toP3(q), toP3(r));
}

// ============================================================
// COMPARE DISTANCE TO POINT
// ============================================================
int compare_distance_to_point_2(const Point2& p, const Point2& q, const Point2& r) {
    return cmp_to_int(CGAL::compare_distance_to_point(toP2(p), toP2(q), toP2(r)));
}

int compare_distance_to_point_3(const Point3& p, const Point3& q, const Point3& r) {
    return cmp_to_int(CGAL::compare_distance_to_point(toP3(p), toP3(q), toP3(r)));
}

// ============================================================
// COMPARE LEXICOGRAPHICALLY
// ============================================================
int compare_lexicographically_2(const Point2& p, const Point2& q) {
    return cmp_to_int(CGAL::compare_lexicographically(toP2(p), toP2(q)));
}

int compare_lexicographically_3(const Point3& p, const Point3& q) {
    return cmp_to_int(CGAL::compare_lexicographically(toP3(p), toP3(q)));
}

// ============================================================
// COMPARE SIGNED DISTANCE TO LINE
// ============================================================
int compare_signed_distance_to_line_l(const Line2& l, const Point2& p, const Point2& q) {
    return cmp_to_int(CGAL::compare_signed_distance_to_line(l.l, toP2(p), toP2(q)));
}

int compare_signed_distance_to_line_p(const Point2& p, const Point2& q,
                                      const Point2& r, const Point2& s) {
    return cmp_to_int(CGAL::compare_signed_distance_to_line(
        toP2(p), toP2(q), toP2(r), toP2(s)));
}