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

// ============================================================
// COLLINEAR ARE STRICTLY ORDERED ALONG LINE
// ============================================================
bool collinear_are_strictly_ordered_along_line_2(const Point2& p, const Point2& q, const Point2& r) {
    return CGAL::collinear_are_strictly_ordered_along_line(toP2(p), toP2(q), toP2(r));
}

bool collinear_are_strictly_ordered_along_line_3(const Point3& p, const Point3& q, const Point3& r) {
    return CGAL::collinear_are_strictly_ordered_along_line(toP3(p), toP3(q), toP3(r));
}

// ============================================================
// COMPARE SIGNED DISTANCE TO PLANE
// ============================================================
int compare_signed_distance_to_plane_h(const Plane3& h, const Point3& p, const Point3& q) {
    return cmp_to_int(CGAL::compare_signed_distance_to_plane(h.p, toP3(p), toP3(q)));
}

int compare_signed_distance_to_plane_p(const Point3& p, const Point3& q, const Point3& r,
                                       const Point3& s, const Point3& t) {
    return cmp_to_int(CGAL::compare_signed_distance_to_plane(
        toP3(p), toP3(q), toP3(r), toP3(s), toP3(t)));
}

// ============================================================
// COMPARE SLOPE
// ============================================================
int compare_slope_line(const Line2& l1, const Line2& l2) {
    return cmp_to_int(CGAL::compare_slope(l1.l, l2.l));
}

int compare_slope_seg(const Segment2& s1, const Segment2& s2) {
    return cmp_to_int(CGAL::compare_slope(s1.s, s2.s));
}

int compare_slope_pt2(const Point2& s1s, const Point2& s1t,
                      const Point2& s2s, const Point2& s2t) {
    return cmp_to_int(CGAL::compare_slope(toP2(s1s), toP2(s1t), toP2(s2s), toP2(s2t)));
}

int compare_slope_pt3(const Point3& p, const Point3& q,
                      const Point3& r, const Point3& s) {
    return cmp_to_int(CGAL::compare_slope(toP3(p), toP3(q), toP3(r), toP3(s)));
}

// ============================================================
// COMPARE ANGLE
// ============================================================
int compare_angle(const Point3& a, const Point3& b, const Point3& c, double cosine) {
    return cmp_to_int(CGAL::compare_angle(toP3(a), toP3(b), toP3(c), cosine));
}

// ============================================================
// COMPARE DIHEDRAL ANGLE
// ============================================================
int compare_dihedral_angle_pt(const Point3& a1, const Point3& b1,
                               const Point3& c1, const Point3& d1,
                               const Point3& a2, const Point3& b2,
                               const Point3& c2, const Point3& d2) {
    return cmp_to_int(CGAL::compare_dihedral_angle(
        toP3(a1), toP3(b1), toP3(c1), toP3(d1),
        toP3(a2), toP3(b2), toP3(c2), toP3(d2)));
}

int compare_dihedral_angle_pt_cos(const Point3& a1, const Point3& b1,
                                  const Point3& c1, const Point3& d1,
                                  double cosine) {
    return cmp_to_int(CGAL::compare_dihedral_angle(
        toP3(a1), toP3(b1), toP3(c1), toP3(d1), cosine));
}

int compare_dihedral_angle_vec(const Vector3& u1, const Vector3& v1, const Vector3& w1,
                                const Vector3& u2, const Vector3& v2, const Vector3& w2) {
    return cmp_to_int(CGAL::compare_dihedral_angle(u1.v, v1.v, w1.v, u2.v, v2.v, w2.v));
}

int compare_dihedral_angle_vec_cos(const Vector3& u1, const Vector3& v1,
                                   const Vector3& w1, double cosine) {
    return cmp_to_int(CGAL::compare_dihedral_angle(u1.v, v1.v, w1.v, cosine));
}

// ============================================================
// COMPARE SQUARED DISTANCE
// ============================================================
int compare_squared_distance_2(const Point2& p, const Point2& q, double d2) {
    return cmp_to_int(CGAL::compare_squared_distance(toP2(p), toP2(q), d2));
}

int compare_squared_distance_3(const Point3& p, const Point3& q, double d2) {
    return cmp_to_int(CGAL::compare_squared_distance(toP3(p), toP3(q), d2));
}

// ============================================================
// COMPARE SQUARED RADIUS
// ============================================================
int compare_squared_radius_1(const Point3& p, double sr) {
    return cmp_to_int(CGAL::compare_squared_radius(toP3(p), sr));
}

int compare_squared_radius_2(const Point3& p, const Point3& q, double sr) {
    return cmp_to_int(CGAL::compare_squared_radius(toP3(p), toP3(q), sr));
}

int compare_squared_radius_3(const Point3& p, const Point3& q, const Point3& r, double sr) {
    return cmp_to_int(CGAL::compare_squared_radius(toP3(p), toP3(q), toP3(r), sr));
}

int compare_squared_radius_4(const Point3& p, const Point3& q,
                              const Point3& r, const Point3& s, double sr) {
    return cmp_to_int(CGAL::compare_squared_radius(toP3(p), toP3(q), toP3(r), toP3(s), sr));
}

// ============================================================
// COMPARE X
// ============================================================
int compare_x_pt2(const Point2& p, const Point2& q) {
    return cmp_to_int(CGAL::compare_x(toP2(p), toP2(q)));
}
int compare_x_pt3(const Point3& p, const Point3& q) {
    return cmp_to_int(CGAL::compare_x(toP3(p), toP3(q)));
}
int compare_x_pt2_l1_l2(const Point2& p, const Line2& l1, const Line2& l2) {
    return cmp_to_int(CGAL::compare_x(toP2(p), l1.l, l2.l));
}
int compare_x_l_h1_h2(const Line2& l, const Line2& h1, const Line2& h2) {
    return cmp_to_int(CGAL::compare_x(l.l, h1.l, h2.l));
}
int compare_x_l1_l2_h1_h2(const Line2& l1, const Line2& l2,
                            const Line2& h1, const Line2& h2) {
    return cmp_to_int(CGAL::compare_x(l1.l, l2.l, h1.l, h2.l));
}

// ============================================================
// COMPARE XY
// ============================================================
int compare_xy_pt2(const Point2& p, const Point2& q) {
    return cmp_to_int(CGAL::compare_xy(toP2(p), toP2(q)));
}
int compare_xy_pt3(const Point3& p, const Point3& q) {
    return cmp_to_int(CGAL::compare_xy(toP3(p), toP3(q)));
}

// ============================================================
// COMPARE XYZ
// ============================================================
int compare_xyz_pt3(const Point3& p, const Point3& q) {
    return cmp_to_int(CGAL::compare_xyz(toP3(p), toP3(q)));
}

// ============================================================
// COMPARE X AT Y
// ============================================================
int compare_x_at_y_pt_h(const Point2& p, const Line2& h) {
    return cmp_to_int(CGAL::compare_x_at_y(toP2(p), h.l));
}
int compare_x_at_y_pt_h1_h2(const Point2& p, const Line2& h1, const Line2& h2) {
    return cmp_to_int(CGAL::compare_x_at_y(toP2(p), h1.l, h2.l));
}
int compare_x_at_y_l1_l2_h(const Line2& l1, const Line2& l2, const Line2& h) {
    return cmp_to_int(CGAL::compare_x_at_y(l1.l, l2.l, h.l));
}
int compare_x_at_y_l1_l2_h1_h2(const Line2& l1, const Line2& l2,
                                 const Line2& h1, const Line2& h2) {
    return cmp_to_int(CGAL::compare_x_at_y(l1.l, l2.l, h1.l, h2.l));
}

// ============================================================
// COMPARE Y
// ============================================================
int compare_y_pt2(const Point2& p, const Point2& q) {
    return cmp_to_int(CGAL::compare_y(toP2(p), toP2(q)));
}
int compare_y_pt3(const Point3& p, const Point3& q) {
    return cmp_to_int(CGAL::compare_y(toP3(p), toP3(q)));
}
int compare_y_pt2_l1_l2(const Point2& p, const Line2& l1, const Line2& l2) {
    return cmp_to_int(CGAL::compare_y(toP2(p), l1.l, l2.l));
}
int compare_y_l_h1_h2(const Line2& l, const Line2& h1, const Line2& h2) {
    return cmp_to_int(CGAL::compare_y(l.l, h1.l, h2.l));
}
int compare_y_l1_l2_h1_h2(const Line2& l1, const Line2& l2,
                            const Line2& h1, const Line2& h2) {
    return cmp_to_int(CGAL::compare_y(l1.l, l2.l, h1.l, h2.l));
}

// ============================================================
// COMPARE Y AT X
// ============================================================
int compare_y_at_x_pt_h(const Point2& p, const Line2& h) {
    return cmp_to_int(CGAL::compare_y_at_x(toP2(p), h.l));
}
int compare_y_at_x_pt_h1_h2(const Point2& p, const Line2& h1, const Line2& h2) {
    return cmp_to_int(CGAL::compare_y_at_x(toP2(p), h1.l, h2.l));
}
int compare_y_at_x_l1_l2_h(const Line2& l1, const Line2& l2, const Line2& h) {
    return cmp_to_int(CGAL::compare_y_at_x(l1.l, l2.l, h.l));
}
int compare_y_at_x_l1_l2_h1_h2(const Line2& l1, const Line2& l2,
                                 const Line2& h1, const Line2& h2) {
    return cmp_to_int(CGAL::compare_y_at_x(l1.l, l2.l, h1.l, h2.l));
}
int compare_y_at_x_pt_seg(const Point2& p, const Segment2& s) {
    return cmp_to_int(CGAL::compare_y_at_x(toP2(p), s.s));
}
int compare_y_at_x_pt_seg1_seg2(const Point2& p,
                                 const Segment2& s1, const Segment2& s2) {
    return cmp_to_int(CGAL::compare_y_at_x(toP2(p), s1.s, s2.s));
}

// ============================================================
// COMPARE YX
// ============================================================
int compare_yx_pt2(const Point2& p, const Point2& q) {
    return cmp_to_int(CGAL::compare_yx(toP2(p), toP2(q)));
}

// ============================================================
// COMPARE Z
// ============================================================
int compare_z_pt3(const Point3& p, const Point3& q) {
    return cmp_to_int(CGAL::compare_z(toP3(p), toP3(q)));
}

#include <CGAL/intersections.h>

// ============================================================
// COPLANAR
// ============================================================
bool coplanar_4(const Point3& p, const Point3& q, const Point3& r, const Point3& s) {
    return CGAL::coplanar(toP3(p), toP3(q), toP3(r), toP3(s));
}

// ============================================================
// COPLANAR ORIENTATION
// ============================================================
int coplanar_orientation_3(const Point3& p, const Point3& q, const Point3& r) {
    return cmp_to_int(CGAL::coplanar_orientation(toP3(p), toP3(q), toP3(r)));
}

int coplanar_orientation_4(const Point3& p, const Point3& q,
                           const Point3& r, const Point3& s) {
    return cmp_to_int(CGAL::coplanar_orientation(toP3(p), toP3(q), toP3(r), toP3(s)));
}

// ============================================================
// COPLANAR SIDE OF BOUNDED CIRCLE
// ============================================================
int coplanar_side_of_bounded_circle(const Point3& p, const Point3& q,
                                    const Point3& r, const Point3& s) {
    auto side = CGAL::coplanar_side_of_bounded_circle(toP3(p), toP3(q), toP3(r), toP3(s));
    if (side == CGAL::ON_BOUNDED_SIDE)   return 1;
    if (side == CGAL::ON_UNBOUNDED_SIDE) return -1;
    return 0;
}

// ============================================================
// CROSS PRODUCT
// ============================================================
Vector3 cross_product(const Vector3& u, const Vector3& v) {
    auto r = CGAL::cross_product(u.v, v.v);
    return Vector3(CGAL::to_double(r.x()),
                   CGAL::to_double(r.y()),
                   CGAL::to_double(r.z()));
}

// ============================================================
// DETERMINANT
// ============================================================
double determinant_2(const Vector2& v, const Vector2& w) {
    return CGAL::to_double(CGAL::determinant(v.v, w.v));
}

double determinant_3(const Vector3& u, const Vector3& v, const Vector3& w) {
    return CGAL::to_double(CGAL::determinant(u.v, v.v, w.v));
}

// ============================================================
// DO INTERSECT 2D
// ============================================================
bool do_intersect_seg2_seg2(const Segment2& s1, const Segment2& s2) {
    return CGAL::do_intersect(s1.s, s2.s);
}
bool do_intersect_seg2_line2(const Segment2& s, const Line2& l) {
    return CGAL::do_intersect(s.s, l.l);
}
bool do_intersect_seg2_ray2(const Segment2& s, const Ray2& r) {
    return CGAL::do_intersect(s.s, r.r);
}
bool do_intersect_seg2_tri2(const Segment2& s, const Triangle2& t) {
    return CGAL::do_intersect(s.s, t.t);
}
bool do_intersect_seg2_iso2(const Segment2& s, const IsoRectangle2& r) {
    return CGAL::do_intersect(s.s, r.r);
}
bool do_intersect_line2_line2(const Line2& l1, const Line2& l2) {
    return CGAL::do_intersect(l1.l, l2.l);
}
bool do_intersect_line2_ray2(const Line2& l, const Ray2& r) {
    return CGAL::do_intersect(l.l, r.r);
}
bool do_intersect_line2_tri2(const Line2& l, const Triangle2& t) {
    return CGAL::do_intersect(l.l, t.t);
}
bool do_intersect_ray2_ray2(const Ray2& r1, const Ray2& r2) {
    return CGAL::do_intersect(r1.r, r2.r);
}
bool do_intersect_ray2_tri2(const Ray2& r, const Triangle2& t) {
    return CGAL::do_intersect(r.r, t.t);
}
bool do_intersect_tri2_tri2(const Triangle2& t1, const Triangle2& t2) {
    return CGAL::do_intersect(t1.t, t2.t);
}
bool do_intersect_iso2_iso2(const IsoRectangle2& r1, const IsoRectangle2& r2) {
    return CGAL::do_intersect(r1.r, r2.r);
}
bool do_intersect_pt2_iso2(const Point2& p, const IsoRectangle2& r) {
    return CGAL::do_intersect(toP2(p), r.r);
}
bool do_intersect_pt2_tri2(const Point2& p, const Triangle2& t) {
    return CGAL::do_intersect(toP2(p), t.t);
}

// ============================================================
// DO INTERSECT 3D
// ============================================================
bool do_intersect_seg3_seg3(const Segment3& s1, const Segment3& s2) {
    return CGAL::do_intersect(s1.s, s2.s);
}
bool do_intersect_seg3_line3(const Segment3& s, const Line3& l) {
    return CGAL::do_intersect(s.s, l.l);
}
bool do_intersect_seg3_ray3(const Segment3& s, const Ray3& r) {
    return CGAL::do_intersect(s.s, r.r);
}
bool do_intersect_seg3_plane3(const Segment3& s, const Plane3& p) {
    return CGAL::do_intersect(s.s, p.p);
}
bool do_intersect_seg3_tri3(const Segment3& s, const Triangle3& t) {
    return CGAL::do_intersect(s.s, t.t);
}
bool do_intersect_seg3_sphere3(const Segment3& s, const Sphere3& sp) {
    return CGAL::do_intersect(s.s, sp.s);
}
bool do_intersect_seg3_bbox3(const Segment3& s, const Bbox3& b) {
    return CGAL::do_intersect(s.s, b.b);
}
bool do_intersect_line3_line3(const Line3& l1, const Line3& l2) {
    return CGAL::do_intersect(l1.l, l2.l);
}
bool do_intersect_line3_ray3(const Line3& l, const Ray3& r) {
    return CGAL::do_intersect(l.l, r.r);
}
bool do_intersect_line3_plane3(const Line3& l, const Plane3& p) {
    return CGAL::do_intersect(l.l, p.p);
}
bool do_intersect_line3_tri3(const Line3& l, const Triangle3& t) {
    return CGAL::do_intersect(l.l, t.t);
}
bool do_intersect_line3_sphere3(const Line3& l, const Sphere3& s) {
    return CGAL::do_intersect(l.l, s.s);
}
bool do_intersect_ray3_ray3(const Ray3& r1, const Ray3& r2) {
    return CGAL::do_intersect(r1.r, r2.r);
}
bool do_intersect_ray3_plane3(const Ray3& r, const Plane3& p) {
    return CGAL::do_intersect(r.r, p.p);
}
bool do_intersect_ray3_tri3(const Ray3& r, const Triangle3& t) {
    return CGAL::do_intersect(r.r, t.t);
}
bool do_intersect_ray3_sphere3(const Ray3& r, const Sphere3& s) {
    return CGAL::do_intersect(r.r, s.s);
}
bool do_intersect_plane3_plane3(const Plane3& p1, const Plane3& p2) {
    return CGAL::do_intersect(p1.p, p2.p);
}
bool do_intersect_plane3_sphere3(const Plane3& p, const Sphere3& s) {
    return CGAL::do_intersect(p.p, s.s);
}
bool do_intersect_plane3_tri3(const Plane3& p, const Triangle3& t) {
    return CGAL::do_intersect(p.p, t.t);
}
bool do_intersect_tri3_tri3(const Triangle3& t1, const Triangle3& t2) {
    return CGAL::do_intersect(t1.t, t2.t);
}
bool do_intersect_sphere3_sphere3(const Sphere3& s1, const Sphere3& s2) {
    return CGAL::do_intersect(s1.s, s2.s);
}
bool do_intersect_pt3_plane3(const Point3& p, const Plane3& pl) {
    return CGAL::do_intersect(toP3(p), pl.p);
}
bool do_intersect_pt3_sphere3(const Point3& p, const Sphere3& s) {
    return CGAL::do_intersect(toP3(p), s.s);
}
bool do_intersect_bbox3_bbox3(const Bbox3& b1, const Bbox3& b2) {
    return CGAL::do_intersect(b1.b, b2.b);
}
bool do_intersect_bbox3_seg3(const Bbox3& b, const Segment3& s) {
    return CGAL::do_intersect(b.b, s.s);
}
bool do_intersect_bbox3_tri3(const Bbox3& b, const Triangle3& t) {
    return CGAL::do_intersect(b.b, t.t);
}

// ============================================================
// DO OVERLAP
// ============================================================
bool do_overlap_bbox2(const Bbox2& b1, const Bbox2& b2) {
    return CGAL::do_overlap(b1.b, b2.b);
}
bool do_overlap_bbox3(const Bbox3& b1, const Bbox3& b2) {
    return CGAL::do_overlap(b1.b, b2.b);
}

// ============================================================
// EQUIDISTANT LINE
// ============================================================
Line3 equidistant_line(const Point3& p, const Point3& q, const Point3& r) {
    return Line3(CGAL::equidistant_line(toP3(p), toP3(q), toP3(r)));
}

// ============================================================
// HAS LARGER DISTANCE TO POINT
// ============================================================
bool has_larger_distance_to_point_2(const Point2& p, const Point2& q, const Point2& r) {
    return CGAL::has_larger_distance_to_point(toP2(p), toP2(q), toP2(r));
}
bool has_larger_distance_to_point_3(const Point3& p, const Point3& q, const Point3& r) {
    return CGAL::has_larger_distance_to_point(toP3(p), toP3(q), toP3(r));
}

// ============================================================
// HAS LARGER SIGNED DISTANCE TO LINE
// ============================================================
bool has_larger_signed_distance_to_line_l(const Line2& l, const Point2& p, const Point2& q) {
    return CGAL::has_larger_signed_distance_to_line(l.l, toP2(p), toP2(q));
}
bool has_larger_signed_distance_to_line_p(const Point2& p, const Point2& q,
                                           const Point2& r, const Point2& s) {
    return CGAL::has_larger_signed_distance_to_line(toP2(p), toP2(q), toP2(r), toP2(s));
}

// ============================================================
// HAS LARGER SIGNED DISTANCE TO PLANE
// ============================================================
bool has_larger_signed_distance_to_plane_h(const Plane3& h, const Point3& p, const Point3& q) {
    return CGAL::has_larger_signed_distance_to_plane(h.p, toP3(p), toP3(q));
}
bool has_larger_signed_distance_to_plane_p(const Point3& p, const Point3& q, const Point3& r,
                                            const Point3& s, const Point3& t) {
    return CGAL::has_larger_signed_distance_to_plane(toP3(p), toP3(q), toP3(r), toP3(s), toP3(t));
}

// ============================================================
// HAS SMALLER DISTANCE TO POINT
// ============================================================
bool has_smaller_distance_to_point_2(const Point2& p, const Point2& q, const Point2& r) {
    return CGAL::has_smaller_distance_to_point(toP2(p), toP2(q), toP2(r));
}
bool has_smaller_distance_to_point_3(const Point3& p, const Point3& q, const Point3& r) {
    return CGAL::has_smaller_distance_to_point(toP3(p), toP3(q), toP3(r));
}

// ============================================================
// HAS SMALLER SIGNED DISTANCE TO LINE
// ============================================================
bool has_smaller_signed_distance_to_line_l(const Line2& l, const Point2& p, const Point2& q) {
    return CGAL::has_smaller_signed_distance_to_line(l.l, toP2(p), toP2(q));
}
bool has_smaller_signed_distance_to_line_p(const Point2& p, const Point2& q,
                                            const Point2& r, const Point2& s) {
    return CGAL::has_smaller_signed_distance_to_line(toP2(p), toP2(q), toP2(r), toP2(s));
}

// ============================================================
// HAS SMALLER SIGNED DISTANCE TO PLANE
// ============================================================
bool has_smaller_signed_distance_to_plane_h(const Plane3& h, const Point3& p, const Point3& q) {
    return CGAL::has_smaller_signed_distance_to_plane(h.p, toP3(p), toP3(q));
}
bool has_smaller_signed_distance_to_plane_p(const Point3& p, const Point3& q, const Point3& r,
                                             const Point3& s, const Point3& t) {
    return CGAL::has_smaller_signed_distance_to_plane(toP3(p), toP3(q), toP3(r), toP3(s), toP3(t));
}

#include <CGAL/intersections.h>
// Helper to disambiguate boost::variant get from boost::tuples::get on MSVC
// template<typename T, typename Variant>
// const T* variant_get(const Variant& v) {
//     return boost::get<T>(&v);
// }
// Helper to disambiguate std::variant get on MSVC
template<typename T, typename Variant>
const T* variant_get(const Variant& v) {
    return std::get_if<T>(&v);
}

// Helper to make empty result
static py::dict none_result() {
    py::dict d;
    d["type"]  = py::str("none");
    d["value"] = py::none();
    return d;
}

// ============================================================
// INTERSECTION 2D
// ============================================================
// py::dict intersection_seg2_seg2(const Segment2& s1, const Segment2& s2) {
//     auto result = CGAL::intersection(s1.s, s2.s);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint2* p = boost::get<CGALPoint2>(&*result)) {
//         d["type"]  = py::str("Point2");
//         d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
//     } else if (const CGALSegment2* s = boost::get<CGALSegment2>(&*result)) {
//         d["type"]  = py::str("Segment2");
//         d["value"] = Segment2(*s);
//     }
//     return d;
// }

// py::dict intersection_seg2_line2(const Segment2& s, const Line2& l) {
//     auto result = CGAL::intersection(s.s, l.l);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint2* p = boost::get<CGALPoint2>(&*result)) {
//         d["type"]  = py::str("Point2");
//         d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
//     } else if (const CGALSegment2* seg = boost::get<CGALSegment2>(&*result)) {
//         d["type"]  = py::str("Segment2");
//         d["value"] = Segment2(*seg);
//     }
//     return d;
// }

py::dict intersection_seg2_seg2(const Segment2& s1, const Segment2& s2) {
    auto result = CGAL::intersection(s1.s, s2.s);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint2* p = variant_get<CGALPoint2>(var)) {
        d["type"]  = py::str("Point2");
        d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
    } else if (const CGALSegment2* s = variant_get<CGALSegment2>(var)) {
        d["type"]  = py::str("Segment2");
        d["value"] = Segment2(*s);
    }
    return d;
}

py::dict intersection_seg2_line2(const Segment2& s, const Line2& l) {
    auto result = CGAL::intersection(s.s, l.l);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint2* p = variant_get<CGALPoint2>(var)) {
        d["type"]  = py::str("Point2");
        d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
    } else if (const CGALSegment2* seg = variant_get<CGALSegment2>(var)) {
        d["type"]  = py::str("Segment2");
        d["value"] = Segment2(*seg);
    }
    return d;
}

// py::dict intersection_seg2_ray2(const Segment2& s, const Ray2& r) {
//     auto result = CGAL::intersection(s.s, r.r);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint2* p = boost::get<CGALPoint2>(&*result)) {
//         d["type"]  = py::str("Point2");
//         d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
//     } else if (const CGALSegment2* seg = boost::get<CGALSegment2>(&*result)) {
//         d["type"]  = py::str("Segment2");
//         d["value"] = Segment2(*seg);
//     }
//     return d;
// }

// py::dict intersection_seg2_tri2(const Segment2& s, const Triangle2& t) {
//     auto result = CGAL::intersection(s.s, t.t);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint2* p = boost::get<CGALPoint2>(&*result)) {
//         d["type"]  = py::str("Point2");
//         d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
//     } else if (const CGALSegment2* seg = boost::get<CGALSegment2>(&*result)) {
//         d["type"]  = py::str("Segment2");
//         d["value"] = Segment2(*seg);
//     }
//     return d;
// }

// py::dict intersection_line2_line2(const Line2& l1, const Line2& l2) {
//     auto result = CGAL::intersection(l1.l, l2.l);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint2* p = boost::get<CGALPoint2>(&*result)) {
//         d["type"]  = py::str("Point2");
//         d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
//     } else if (const CGALLine2* l = boost::get<CGALLine2>(&*result)) {
//         d["type"]  = py::str("Line2");
//         d["value"] = Line2(*l);
//     }
//     return d;
// }

// py::dict intersection_line2_ray2(const Line2& l, const Ray2& r) {
//     auto result = CGAL::intersection(l.l, r.r);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint2* p = boost::get<CGALPoint2>(&*result)) {
//         d["type"]  = py::str("Point2");
//         d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
//     } else if (const Kernel::Ray_2* ray = boost::get<Kernel::Ray_2>(&*result)) {
//         d["type"]  = py::str("Ray2");
//         d["value"] = Ray2(*ray);
//     }
//     return d;
// }

// py::dict intersection_line2_seg2(const Line2& l, const Segment2& s) {
//     auto result = CGAL::intersection(l.l, s.s);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint2* p = boost::get<CGALPoint2>(&*result)) {
//         d["type"]  = py::str("Point2");
//         d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
//     } else if (const CGALSegment2* seg = boost::get<CGALSegment2>(&*result)) {
//         d["type"]  = py::str("Segment2");
//         d["value"] = Segment2(*seg);
//     }
//     return d;
// }

// py::dict intersection_ray2_ray2(const Ray2& r1, const Ray2& r2) {
//     auto result = CGAL::intersection(r1.r, r2.r);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint2* p = boost::get<CGALPoint2>(&*result)) {
//         d["type"]  = py::str("Point2");
//         d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
//     } else if (const CGALSegment2* seg = boost::get<CGALSegment2>(&*result)) {
//         d["type"]  = py::str("Segment2");
//         d["value"] = Segment2(*seg);
//     } else if (const Kernel::Ray_2* ray = boost::get<Kernel::Ray_2>(&*result)) {
//         d["type"]  = py::str("Ray2");
//         d["value"] = Ray2(*ray);
//     }
//     return d;
// }

// py::dict intersection_ray2_seg2(const Ray2& r, const Segment2& s) {
//     auto result = CGAL::intersection(r.r, s.s);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint2* p = boost::get<CGALPoint2>(&*result)) {
//         d["type"]  = py::str("Point2");
//         d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
//     } else if (const CGALSegment2* seg = boost::get<CGALSegment2>(&*result)) {
//         d["type"]  = py::str("Segment2");
//         d["value"] = Segment2(*seg);
//     }
//     return d;
// }

// // ============================================================
// // INTERSECTION 3D
// // ============================================================
// py::dict intersection_seg3_seg3(const Segment3& s1, const Segment3& s2) {
//     auto result = CGAL::intersection(s1.s, s2.s);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint3* p = boost::get<CGALPoint3>(&*result)) {
//         d["type"]  = py::str("Point3");
//         d["value"] = fromP3(*p);
//     } else if (const CGALSegment3* s = boost::get<CGALSegment3>(&*result)) {
//         d["type"]  = py::str("Segment3");
//         d["value"] = Segment3(*s);
//     }
//     return d;
// }

// py::dict intersection_seg3_line3(const Segment3& s, const Line3& l) {
//     auto result = CGAL::intersection(s.s, l.l);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint3* p = boost::get<CGALPoint3>(&*result)) {
//         d["type"]  = py::str("Point3");
//         d["value"] = fromP3(*p);
//     } else if (const CGALSegment3* seg = boost::get<CGALSegment3>(&*result)) {
//         d["type"]  = py::str("Segment3");
//         d["value"] = Segment3(*seg);
//     }
//     return d;
// }

// py::dict intersection_seg3_plane3(const Segment3& s, const Plane3& p) {
//     auto result = CGAL::intersection(s.s, p.p);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint3* pt = boost::get<CGALPoint3>(&*result)) {
//         d["type"]  = py::str("Point3");
//         d["value"] = fromP3(*pt);
//     } else if (const CGALSegment3* seg = boost::get<CGALSegment3>(&*result)) {
//         d["type"]  = py::str("Segment3");
//         d["value"] = Segment3(*seg);
//     }
//     return d;
// }

// py::dict intersection_seg3_tri3(const Segment3& s, const Triangle3& t) {
//     auto result = CGAL::intersection(s.s, t.t);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint3* p = boost::get<CGALPoint3>(&*result)) {
//         d["type"]  = py::str("Point3");
//         d["value"] = fromP3(*p);
//     } else if (const CGALSegment3* seg = boost::get<CGALSegment3>(&*result)) {
//         d["type"]  = py::str("Segment3");
//         d["value"] = Segment3(*seg);
//     }
//     return d;
// }

// py::dict intersection_line3_line3(const Line3& l1, const Line3& l2) {
//     auto result = CGAL::intersection(l1.l, l2.l);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint3* p = boost::get<CGALPoint3>(&*result)) {
//         d["type"]  = py::str("Point3");
//         d["value"] = fromP3(*p);
//     } else if (const CGALLine3* l = boost::get<CGALLine3>(&*result)) {
//         d["type"]  = py::str("Line3");
//         d["value"] = Line3(*l);
//     }
//     return d;
// }

// py::dict intersection_line3_plane3(const Line3& l, const Plane3& p) {
//     auto result = CGAL::intersection(l.l, p.p);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint3* pt = boost::get<CGALPoint3>(&*result)) {
//         d["type"]  = py::str("Point3");
//         d["value"] = fromP3(*pt);
//     } else if (const CGALLine3* ln = boost::get<CGALLine3>(&*result)) {
//         d["type"]  = py::str("Line3");
//         d["value"] = Line3(*ln);
//     }
//     return d;
// }

// py::dict intersection_line3_tri3(const Line3& l, const Triangle3& t) {
//     auto result = CGAL::intersection(l.l, t.t);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint3* p = boost::get<CGALPoint3>(&*result)) {
//         d["type"]  = py::str("Point3");
//         d["value"] = fromP3(*p);
//     } else if (const CGALSegment3* seg = boost::get<CGALSegment3>(&*result)) {
//         d["type"]  = py::str("Segment3");
//         d["value"] = Segment3(*seg);
//     }
//     return d;
// }

// py::dict intersection_plane3_plane3(const Plane3& p1, const Plane3& p2) {
//     auto result = CGAL::intersection(p1.p, p2.p);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALLine3* l = boost::get<CGALLine3>(&*result)) {
//         d["type"]  = py::str("Line3");
//         d["value"] = Line3(*l);
//     } else if (const CGALPlane3* pl = boost::get<CGALPlane3>(&*result)) {
//         d["type"]  = py::str("Plane3");
//         d["value"] = Plane3(*pl);
//     }
//     return d;
// }

// py::dict intersection_plane3_plane3_plane3(const Plane3& p1, const Plane3& p2, const Plane3& p3) {
//     auto result = CGAL::intersection(p1.p, p2.p, p3.p);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint3* p = boost::get<CGALPoint3>(&*result)) {
//         d["type"]  = py::str("Point3");
//         d["value"] = fromP3(*p);
//     } else if (const CGALLine3* l = boost::get<CGALLine3>(&*result)) {
//         d["type"]  = py::str("Line3");
//         d["value"] = Line3(*l);
//     } else if (const CGALPlane3* pl = boost::get<CGALPlane3>(&*result)) {
//         d["type"]  = py::str("Plane3");
//         d["value"] = Plane3(*pl);
//     }
//     return d;
// }

// py::dict intersection_plane3_seg3(const Plane3& p, const Segment3& s) {
//     auto result = CGAL::intersection(p.p, s.s);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint3* pt = boost::get<CGALPoint3>(&*result)) {
//         d["type"]  = py::str("Point3");
//         d["value"] = fromP3(*pt);
//     } else if (const CGALSegment3* seg = boost::get<CGALSegment3>(&*result)) {
//         d["type"]  = py::str("Segment3");
//         d["value"] = Segment3(*seg);
//     }
//     return d;
// }

// py::dict intersection_plane3_tri3(const Plane3& p, const Triangle3& t) {
//     auto result = CGAL::intersection(p.p, t.t);
//     if (!result) return none_result();
//     py::dict d;
//     if (const CGALPoint3* pt = boost::get<CGALPoint3>(&*result)) {
//         d["type"]  = py::str("Point3");
//         d["value"] = fromP3(*pt);
//     } else if (const CGALSegment3* seg = boost::get<CGALSegment3>(&*result)) {
//         d["type"]  = py::str("Segment3");
//         d["value"] = Segment3(*seg);
//     } else if (const CGALTriangle3* tri = boost::get<CGALTriangle3>(&*result)) {
//         d["type"]  = py::str("Triangle3");
//         d["value"] = Triangle3(*tri);
//     }
//     return d;
// }

py::dict intersection_seg2_ray2(const Segment2& s, const Ray2& r) {
    auto result = CGAL::intersection(s.s, r.r);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint2* p = variant_get<CGALPoint2>(var)) {
        d["type"]  = py::str("Point2");
        d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
    } else if (const CGALSegment2* seg = variant_get<CGALSegment2>(var)) {
        d["type"]  = py::str("Segment2");
        d["value"] = Segment2(*seg);
    }
    return d;
}

py::dict intersection_seg2_tri2(const Segment2& s, const Triangle2& t) {
    auto result = CGAL::intersection(s.s, t.t);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint2* p = variant_get<CGALPoint2>(var)) {
        d["type"]  = py::str("Point2");
        d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
    } else if (const CGALSegment2* seg = variant_get<CGALSegment2>(var)) {
        d["type"]  = py::str("Segment2");
        d["value"] = Segment2(*seg);
    }
    return d;
}

py::dict intersection_line2_line2(const Line2& l1, const Line2& l2) {
    auto result = CGAL::intersection(l1.l, l2.l);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint2* p = variant_get<CGALPoint2>(var)) {
        d["type"]  = py::str("Point2");
        d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
    } else if (const CGALLine2* l = variant_get<CGALLine2>(var)) {
        d["type"]  = py::str("Line2");
        d["value"] = Line2(*l);
    }
    return d;
}

py::dict intersection_line2_ray2(const Line2& l, const Ray2& r) {
    auto result = CGAL::intersection(l.l, r.r);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint2* p = variant_get<CGALPoint2>(var)) {
        d["type"]  = py::str("Point2");
        d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
    } else if (const Kernel::Ray_2* ray = variant_get<Kernel::Ray_2>(var)) {
        d["type"]  = py::str("Ray2");
        d["value"] = Ray2(*ray);
    }
    return d;
}

py::dict intersection_line2_seg2(const Line2& l, const Segment2& s) {
    auto result = CGAL::intersection(l.l, s.s);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint2* p = variant_get<CGALPoint2>(var)) {
        d["type"]  = py::str("Point2");
        d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
    } else if (const CGALSegment2* seg = variant_get<CGALSegment2>(var)) {
        d["type"]  = py::str("Segment2");
        d["value"] = Segment2(*seg);
    }
    return d;
}

py::dict intersection_ray2_ray2(const Ray2& r1, const Ray2& r2) {
    auto result = CGAL::intersection(r1.r, r2.r);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint2* p = variant_get<CGALPoint2>(var)) {
        d["type"]  = py::str("Point2");
        d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
    } else if (const CGALSegment2* seg = variant_get<CGALSegment2>(var)) {
        d["type"]  = py::str("Segment2");
        d["value"] = Segment2(*seg);
    } else if (const Kernel::Ray_2* ray = variant_get<Kernel::Ray_2>(var)) {
        d["type"]  = py::str("Ray2");
        d["value"] = Ray2(*ray);
    }
    return d;
}

py::dict intersection_ray2_seg2(const Ray2& r, const Segment2& s) {
    auto result = CGAL::intersection(r.r, s.s);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint2* p = variant_get<CGALPoint2>(var)) {
        d["type"]  = py::str("Point2");
        d["value"] = Point2(CGAL::to_double(p->x()), CGAL::to_double(p->y()));
    } else if (const CGALSegment2* seg = variant_get<CGALSegment2>(var)) {
        d["type"]  = py::str("Segment2");
        d["value"] = Segment2(*seg);
    }
    return d;
}

// ============================================================
// INTERSECTION 3D
// ============================================================
py::dict intersection_seg3_seg3(const Segment3& s1, const Segment3& s2) {
    auto result = CGAL::intersection(s1.s, s2.s);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint3* p = variant_get<CGALPoint3>(var)) {
        d["type"]  = py::str("Point3");
        d["value"] = fromP3(*p);
    } else if (const CGALSegment3* s = variant_get<CGALSegment3>(var)) {
        d["type"]  = py::str("Segment3");
        d["value"] = Segment3(*s);
    }
    return d;
}

py::dict intersection_seg3_line3(const Segment3& s, const Line3& l) {
    auto result = CGAL::intersection(s.s, l.l);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint3* p = variant_get<CGALPoint3>(var)) {
        d["type"]  = py::str("Point3");
        d["value"] = fromP3(*p);
    } else if (const CGALSegment3* seg = variant_get<CGALSegment3>(var)) {
        d["type"]  = py::str("Segment3");
        d["value"] = Segment3(*seg);
    }
    return d;
}

py::dict intersection_seg3_plane3(const Segment3& s, const Plane3& p) {
    auto result = CGAL::intersection(s.s, p.p);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint3* pt = variant_get<CGALPoint3>(var)) {
        d["type"]  = py::str("Point3");
        d["value"] = fromP3(*pt);
    } else if (const CGALSegment3* seg = variant_get<CGALSegment3>(var)) {
        d["type"]  = py::str("Segment3");
        d["value"] = Segment3(*seg);
    }
    return d;
}

py::dict intersection_seg3_tri3(const Segment3& s, const Triangle3& t) {
    auto result = CGAL::intersection(s.s, t.t);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint3* p = variant_get<CGALPoint3>(var)) {
        d["type"]  = py::str("Point3");
        d["value"] = fromP3(*p);
    } else if (const CGALSegment3* seg = variant_get<CGALSegment3>(var)) {
        d["type"]  = py::str("Segment3");
        d["value"] = Segment3(*seg);
    }
    return d;
}

py::dict intersection_line3_line3(const Line3& l1, const Line3& l2) {
    auto result = CGAL::intersection(l1.l, l2.l);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint3* p = variant_get<CGALPoint3>(var)) {
        d["type"]  = py::str("Point3");
        d["value"] = fromP3(*p);
    } else if (const CGALLine3* l = variant_get<CGALLine3>(var)) {
        d["type"]  = py::str("Line3");
        d["value"] = Line3(*l);
    }
    return d;
}

py::dict intersection_line3_plane3(const Line3& l, const Plane3& p) {
    auto result = CGAL::intersection(l.l, p.p);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint3* pt = variant_get<CGALPoint3>(var)) {
        d["type"]  = py::str("Point3");
        d["value"] = fromP3(*pt);
    } else if (const CGALLine3* ln = variant_get<CGALLine3>(var)) {
        d["type"]  = py::str("Line3");
        d["value"] = Line3(*ln);
    }
    return d;
}

py::dict intersection_line3_tri3(const Line3& l, const Triangle3& t) {
    auto result = CGAL::intersection(l.l, t.t);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint3* p = variant_get<CGALPoint3>(var)) {
        d["type"]  = py::str("Point3");
        d["value"] = fromP3(*p);
    } else if (const CGALSegment3* seg = variant_get<CGALSegment3>(var)) {
        d["type"]  = py::str("Segment3");
        d["value"] = Segment3(*seg);
    }
    return d;
}

py::dict intersection_plane3_plane3(const Plane3& p1, const Plane3& p2) {
    auto result = CGAL::intersection(p1.p, p2.p);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALLine3* l = variant_get<CGALLine3>(var)) {
        d["type"]  = py::str("Line3");
        d["value"] = Line3(*l);
    } else if (const CGALPlane3* pl = variant_get<CGALPlane3>(var)) {
        d["type"]  = py::str("Plane3");
        d["value"] = Plane3(*pl);
    }
    return d;
}

py::dict intersection_plane3_plane3_plane3(const Plane3& p1, const Plane3& p2, const Plane3& p3) {
    auto result = CGAL::intersection(p1.p, p2.p, p3.p);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint3* p = variant_get<CGALPoint3>(var)) {
        d["type"]  = py::str("Point3");
        d["value"] = fromP3(*p);
    } else if (const CGALLine3* l = variant_get<CGALLine3>(var)) {
        d["type"]  = py::str("Line3");
        d["value"] = Line3(*l);
    } else if (const CGALPlane3* pl = variant_get<CGALPlane3>(var)) {
        d["type"]  = py::str("Plane3");
        d["value"] = Plane3(*pl);
    }
    return d;
}

py::dict intersection_plane3_seg3(const Plane3& p, const Segment3& s) {
    auto result = CGAL::intersection(p.p, s.s);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint3* pt = variant_get<CGALPoint3>(var)) {
        d["type"]  = py::str("Point3");
        d["value"] = fromP3(*pt);
    } else if (const CGALSegment3* seg = variant_get<CGALSegment3>(var)) {
        d["type"]  = py::str("Segment3");
        d["value"] = Segment3(*seg);
    }
    return d;
}

py::dict intersection_plane3_tri3(const Plane3& p, const Triangle3& t) {
    auto result = CGAL::intersection(p.p, t.t);
    if (!result) return none_result();
    py::dict d;
    const auto& var = *result;
    if (const CGALPoint3* pt = variant_get<CGALPoint3>(var)) {
        d["type"]  = py::str("Point3");
        d["value"] = fromP3(*pt);
    } else if (const CGALSegment3* seg = variant_get<CGALSegment3>(var)) {
        d["type"]  = py::str("Segment3");
        d["value"] = Segment3(*seg);
    } else if (const CGALTriangle3* tri = variant_get<CGALTriangle3>(var)) {
        d["type"]  = py::str("Triangle3");
        d["value"] = Triangle3(*tri);
    }
    return d;
}

// ============================================================
// L INFINITY DISTANCE
// ============================================================
double l_infinity_distance_2(const Point2& p, const Point2& q) {
    return CGAL::to_double(CGAL::l_infinity_distance(toP2(p), toP2(q)));
}

double l_infinity_distance_3(const Point3& p, const Point3& q) {
    return CGAL::to_double(CGAL::l_infinity_distance(toP3(p), toP3(q)));
}

// ============================================================
// LEFT TURN
// ============================================================
bool left_turn_2(const Point2& p, const Point2& q, const Point2& r) {
    return CGAL::left_turn(toP2(p), toP2(q), toP2(r));
}

// ============================================================
// LEXICOGRAPHIC COMPARISONS
// ============================================================
bool lexicographically_xyz_smaller(const Point3& p, const Point3& q) {
    return CGAL::lexicographically_xyz_smaller(toP3(p), toP3(q));
}
bool lexicographically_xyz_smaller_or_equal(const Point3& p, const Point3& q) {
    return CGAL::lexicographically_xyz_smaller_or_equal(toP3(p), toP3(q));
}
bool lexicographically_xy_larger(const Point2& p, const Point2& q) {
    return CGAL::lexicographically_xy_larger(toP2(p), toP2(q));
}
bool lexicographically_xy_larger_or_equal(const Point2& p, const Point2& q) {
    return CGAL::lexicographically_xy_larger_or_equal(toP2(p), toP2(q));
}
bool lexicographically_xy_smaller(const Point2& p, const Point2& q) {
    return CGAL::lexicographically_xy_smaller(toP2(p), toP2(q));
}
bool lexicographically_xy_smaller_or_equal(const Point2& p, const Point2& q) {
    return CGAL::lexicographically_xy_smaller_or_equal(toP2(p), toP2(q));
}

// ============================================================
// MAX / MIN VERTEX
// ============================================================
Point2 max_vertex_iso_rect(const IsoRectangle2& ir) {
    return fromP2(CGAL::max_vertex(ir.r));
}
Point3 max_vertex_iso_cuboid(const IsoCuboid3& ic) {
    return fromP3(CGAL::max_vertex(ic.c));
}
Point2 min_vertex_iso_rect(const IsoRectangle2& ir) {
    return fromP2(CGAL::min_vertex(ir.r));
}
Point3 min_vertex_iso_cuboid(const IsoCuboid3& ic) {
    return fromP3(CGAL::min_vertex(ic.c));
}

// ============================================================
// MIDPOINT
// ============================================================
Point2 midpoint_pt2(const Point2& p, const Point2& q) {
    return fromP2(CGAL::midpoint(toP2(p), toP2(q)));
}
Point2 midpoint_seg2(const Segment2& s) {
    return fromP2(CGAL::midpoint(s.s));
}
Point3 midpoint_pt3(const Point3& p, const Point3& q) {
    return fromP3(CGAL::midpoint(toP3(p), toP3(q)));
}
Point3 midpoint_seg3(const Segment3& s) {
    return fromP3(CGAL::midpoint(s.s));
}

// ============================================================
// NORMAL
// ============================================================
Vector3 normal_3(const Point3& p, const Point3& q, const Point3& r) {
    auto v = CGAL::normal(toP3(p), toP3(q), toP3(r));
    return Vector3(CGAL::to_double(v.x()),
                   CGAL::to_double(v.y()),
                   CGAL::to_double(v.z()));
}