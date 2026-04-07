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