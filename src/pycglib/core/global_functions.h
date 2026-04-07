#pragma once
#include "core/types.h"
#include <CGAL/Kernel/global_functions.h>

// ============================================================
// ANGLE
// ============================================================

// 2D
int angle_vec2_vec2(const Vector2& u, const Vector2& v);
int angle_pt2_pt2_pt2(const Point2& p, const Point2& q, const Point2& r);
int angle_pt2_pt2_pt2_pt2(const Point2& p, const Point2& q,
                           const Point2& r, const Point2& s);
// 3D
int angle_vec3_vec3(const Vector3& u, const Vector3& v);
int angle_pt3_pt3_pt3(const Point3& p, const Point3& q, const Point3& r);
int angle_pt3_pt3_pt3_pt3(const Point3& p, const Point3& q,
                           const Point3& r, const Point3& s);
int angle_pt3_pt3_pt3_vec3(const Point3& p, const Point3& q,
                            const Point3& r, const Vector3& v);

// ============================================================
// APPROXIMATE ANGLE
// ============================================================
double approximate_angle_pt3(const Point3& p, const Point3& q, const Point3& r);
double approximate_angle_vec3(const Vector3& u, const Vector3& v);

// ============================================================
// APPROXIMATE DIHEDRAL ANGLE
// ============================================================
double approximate_dihedral_angle(const Point3& p, const Point3& q,
                                  const Point3& r, const Point3& s);

// ============================================================
// ARE ORDERED ALONG LINE
// ============================================================
bool are_ordered_along_line_2(const Point2& p, const Point2& q, const Point2& r);
bool are_ordered_along_line_3(const Point3& p, const Point3& q, const Point3& r);

// ============================================================
// ARE STRICTLY ORDERED ALONG LINE
// ============================================================
bool are_strictly_ordered_along_line_2(const Point2& p, const Point2& q, const Point2& r);
bool are_strictly_ordered_along_line_3(const Point3& p, const Point3& q, const Point3& r);

// ============================================================
// AREA
// ============================================================
double area_2(const Point2& p, const Point2& q, const Point2& r);

// ============================================================
// BARYCENTER 2D
// ============================================================
Point2 barycenter_2_2(const Point2& p1, double w1, const Point2& p2);
Point2 barycenter_2_22(const Point2& p1, double w1, const Point2& p2, double w2);
Point2 barycenter_2_3(const Point2& p1, double w1, const Point2& p2,
                      double w2, const Point2& p3);
Point2 barycenter_2_33(const Point2& p1, double w1, const Point2& p2,
                       double w2, const Point2& p3, double w3);
Point2 barycenter_2_4(const Point2& p1, double w1, const Point2& p2,
                      double w2, const Point2& p3, double w3, const Point2& p4);
Point2 barycenter_2_44(const Point2& p1, double w1, const Point2& p2, double w2,
                       const Point2& p3, double w3, const Point2& p4, double w4);

// ============================================================
// BARYCENTER 3D
// ============================================================
Point3 barycenter_3_2(const Point3& p1, double w1, const Point3& p2);
Point3 barycenter_3_22(const Point3& p1, double w1, const Point3& p2, double w2);
Point3 barycenter_3_3(const Point3& p1, double w1, const Point3& p2,
                      double w2, const Point3& p3);
Point3 barycenter_3_33(const Point3& p1, double w1, const Point3& p2,
                       double w2, const Point3& p3, double w3);
Point3 barycenter_3_4(const Point3& p1, double w1, const Point3& p2,
                      double w2, const Point3& p3, double w3, const Point3& p4);
Point3 barycenter_3_44(const Point3& p1, double w1, const Point3& p2, double w2,
                       const Point3& p3, double w3, const Point3& p4, double w4);

// ============================================================
// BISECTOR
// ============================================================
Line2  bisector_pt2(const Point2& p, const Point2& q);
Line2  bisector_ln2(const Line2& l1, const Line2& l2);
Plane3 bisector_pt3(const Point3& p, const Point3& q);
Plane3 bisector_pl3(const Plane3& h1, const Plane3& h2);

// ============================================================
// CENTROID 2D
// ============================================================
Point2 centroid_2_3(const Point2& p, const Point2& q, const Point2& r);
Point2 centroid_2_4(const Point2& p, const Point2& q,
                    const Point2& r, const Point2& s);
Point2 centroid_2_tri(const Triangle2& t);

// ============================================================
// CENTROID 3D
// ============================================================
Point3 centroid_3_3(const Point3& p, const Point3& q, const Point3& r);
Point3 centroid_3_4(const Point3& p, const Point3& q,
                    const Point3& r, const Point3& s);
Point3 centroid_3_tri(const Triangle3& t);
Point3 centroid_3_tet(const Tetrahedron3& t);

// ============================================================
// CIRCUMCENTER 2D
// ============================================================
Point2 circumcenter_2_2(const Point2& p, const Point2& q);
Point2 circumcenter_2_3(const Point2& p, const Point2& q, const Point2& r);
Point2 circumcenter_2_tri(const Triangle2& t);

// ============================================================
// CIRCUMCENTER 3D
// ============================================================
Point3 circumcenter_3_2(const Point3& p, const Point3& q);
Point3 circumcenter_3_3(const Point3& p, const Point3& q, const Point3& r);
Point3 circumcenter_3_4(const Point3& p, const Point3& q,
                        const Point3& r, const Point3& s);
Point3 circumcenter_3_tri(const Triangle3& t);
Point3 circumcenter_3_tet(const Tetrahedron3& t);

// ============================================================
// COLLINEAR
// ============================================================
bool collinear_2(const Point2& p, const Point2& q, const Point2& r);
bool collinear_3(const Point3& p, const Point3& q, const Point3& r);

// ============================================================
// COLLINEAR ARE ORDERED ALONG LINE
// ============================================================
bool collinear_are_ordered_along_line_2(const Point2& p, const Point2& q, const Point2& r);
bool collinear_are_ordered_along_line_3(const Point3& p, const Point3& q, const Point3& r);

// ============================================================
// COMPARE DISTANCE TO POINT
// ============================================================
int compare_distance_to_point_2(const Point2& p, const Point2& q, const Point2& r);
int compare_distance_to_point_3(const Point3& p, const Point3& q, const Point3& r);

// ============================================================
// COMPARE LEXICOGRAPHICALLY
// ============================================================
int compare_lexicographically_2(const Point2& p, const Point2& q);
int compare_lexicographically_3(const Point3& p, const Point3& q);

// ============================================================
// COMPARE SIGNED DISTANCE TO LINE
// ============================================================
int compare_signed_distance_to_line_l(const Line2& l, const Point2& p, const Point2& q);
int compare_signed_distance_to_line_p(const Point2& p, const Point2& q,
                                      const Point2& r, const Point2& s);


// ============================================================
// COLLINEAR ARE STRICTLY ORDERED ALONG LINE
// ============================================================
bool collinear_are_strictly_ordered_along_line_2(const Point2& p, const Point2& q, const Point2& r);
bool collinear_are_strictly_ordered_along_line_3(const Point3& p, const Point3& q, const Point3& r);

// ============================================================
// COMPARE SIGNED DISTANCE TO PLANE
// ============================================================
int compare_signed_distance_to_plane_h(const Plane3& h, const Point3& p, const Point3& q);
int compare_signed_distance_to_plane_p(const Point3& p, const Point3& q, const Point3& r,
                                       const Point3& s, const Point3& t);

// ============================================================
// COMPARE SLOPE
// ============================================================
int compare_slope_line(const Line2& l1, const Line2& l2);
int compare_slope_seg(const Segment2& s1, const Segment2& s2);
int compare_slope_pt2(const Point2& s1s, const Point2& s1t,
                      const Point2& s2s, const Point2& s2t);
int compare_slope_pt3(const Point3& p, const Point3& q,
                      const Point3& r, const Point3& s);

// ============================================================
// COMPARE ANGLE
// ============================================================
int compare_angle(const Point3& a, const Point3& b, const Point3& c, double cosine);

// ============================================================
// COMPARE DIHEDRAL ANGLE
// ============================================================
int compare_dihedral_angle_pt(const Point3& a1, const Point3& b1,
                               const Point3& c1, const Point3& d1,
                               const Point3& a2, const Point3& b2,
                               const Point3& c2, const Point3& d2);
int compare_dihedral_angle_pt_cos(const Point3& a1, const Point3& b1,
                                  const Point3& c1, const Point3& d1,
                                  double cosine);
int compare_dihedral_angle_vec(const Vector3& u1, const Vector3& v1, const Vector3& w1,
                                const Vector3& u2, const Vector3& v2, const Vector3& w2);
int compare_dihedral_angle_vec_cos(const Vector3& u1, const Vector3& v1,
                                   const Vector3& w1, double cosine);

// ============================================================
// COMPARE SQUARED DISTANCE
// ============================================================
int compare_squared_distance_2(const Point2& p, const Point2& q, double d2);
int compare_squared_distance_3(const Point3& p, const Point3& q, double d2);

// ============================================================
// COMPARE SQUARED RADIUS
// ============================================================
int compare_squared_radius_1(const Point3& p, double sr);
int compare_squared_radius_2(const Point3& p, const Point3& q, double sr);
int compare_squared_radius_3(const Point3& p, const Point3& q, const Point3& r, double sr);
int compare_squared_radius_4(const Point3& p, const Point3& q,
                              const Point3& r, const Point3& s, double sr);