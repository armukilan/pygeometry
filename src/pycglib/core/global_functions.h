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

// ============================================================
// COMPARE X
// ============================================================
int compare_x_pt2(const Point2& p, const Point2& q);
int compare_x_pt3(const Point3& p, const Point3& q);
int compare_x_pt2_l1_l2(const Point2& p, const Line2& l1, const Line2& l2);
int compare_x_l_h1_h2(const Line2& l, const Line2& h1, const Line2& h2);
int compare_x_l1_l2_h1_h2(const Line2& l1, const Line2& l2,
                            const Line2& h1, const Line2& h2);

// ============================================================
// COMPARE XY
// ============================================================
int compare_xy_pt2(const Point2& p, const Point2& q);
int compare_xy_pt3(const Point3& p, const Point3& q);

// ============================================================
// COMPARE XYZ
// ============================================================
int compare_xyz_pt3(const Point3& p, const Point3& q);

// ============================================================
// COMPARE X AT Y
// ============================================================
int compare_x_at_y_pt_h(const Point2& p, const Line2& h);
int compare_x_at_y_pt_h1_h2(const Point2& p, const Line2& h1, const Line2& h2);
int compare_x_at_y_l1_l2_h(const Line2& l1, const Line2& l2, const Line2& h);
int compare_x_at_y_l1_l2_h1_h2(const Line2& l1, const Line2& l2,
                                 const Line2& h1, const Line2& h2);

// ============================================================
// COMPARE Y
// ============================================================
int compare_y_pt2(const Point2& p, const Point2& q);
int compare_y_pt3(const Point3& p, const Point3& q);
int compare_y_pt2_l1_l2(const Point2& p, const Line2& l1, const Line2& l2);
int compare_y_l_h1_h2(const Line2& l, const Line2& h1, const Line2& h2);
int compare_y_l1_l2_h1_h2(const Line2& l1, const Line2& l2,
                            const Line2& h1, const Line2& h2);

// ============================================================
// COMPARE Y AT X
// ============================================================
int compare_y_at_x_pt_h(const Point2& p, const Line2& h);
int compare_y_at_x_pt_h1_h2(const Point2& p, const Line2& h1, const Line2& h2);
int compare_y_at_x_l1_l2_h(const Line2& l1, const Line2& l2, const Line2& h);
int compare_y_at_x_l1_l2_h1_h2(const Line2& l1, const Line2& l2,
                                 const Line2& h1, const Line2& h2);
int compare_y_at_x_pt_seg(const Point2& p, const Segment2& s);
int compare_y_at_x_pt_seg1_seg2(const Point2& p, const Segment2& s1, const Segment2& s2);

// ============================================================
// COMPARE YX
// ============================================================
int compare_yx_pt2(const Point2& p, const Point2& q);

// ============================================================
// COMPARE Z
// ============================================================
int compare_z_pt3(const Point3& p, const Point3& q);


// ============================================================
// COPLANAR
// ============================================================
bool coplanar_4(const Point3& p, const Point3& q, const Point3& r, const Point3& s);

// ============================================================
// COPLANAR ORIENTATION
// ============================================================
int coplanar_orientation_3(const Point3& p, const Point3& q, const Point3& r);
int coplanar_orientation_4(const Point3& p, const Point3& q,
                           const Point3& r, const Point3& s);

// ============================================================
// COPLANAR SIDE OF BOUNDED CIRCLE
// ============================================================
int coplanar_side_of_bounded_circle(const Point3& p, const Point3& q,
                                    const Point3& r, const Point3& s);

// ============================================================
// CROSS PRODUCT
// ============================================================
Vector3 cross_product(const Vector3& u, const Vector3& v);

// ============================================================
// DETERMINANT
// ============================================================
double determinant_2(const Vector2& v, const Vector2& w);
double determinant_3(const Vector3& u, const Vector3& v, const Vector3& w);

// ============================================================
// DO INTERSECT 2D
// ============================================================
bool do_intersect_seg2_seg2(const Segment2& s1, const Segment2& s2);
bool do_intersect_seg2_line2(const Segment2& s, const Line2& l);
bool do_intersect_seg2_ray2(const Segment2& s, const Ray2& r);
bool do_intersect_seg2_tri2(const Segment2& s, const Triangle2& t);
bool do_intersect_seg2_iso2(const Segment2& s, const IsoRectangle2& r);
bool do_intersect_line2_line2(const Line2& l1, const Line2& l2);
bool do_intersect_line2_ray2(const Line2& l, const Ray2& r);
bool do_intersect_line2_tri2(const Line2& l, const Triangle2& t);
bool do_intersect_ray2_ray2(const Ray2& r1, const Ray2& r2);
bool do_intersect_ray2_tri2(const Ray2& r, const Triangle2& t);
bool do_intersect_tri2_tri2(const Triangle2& t1, const Triangle2& t2);
bool do_intersect_iso2_iso2(const IsoRectangle2& r1, const IsoRectangle2& r2);
bool do_intersect_pt2_iso2(const Point2& p, const IsoRectangle2& r);
bool do_intersect_pt2_tri2(const Point2& p, const Triangle2& t);

// ============================================================
// DO INTERSECT 3D
// ============================================================
bool do_intersect_seg3_seg3(const Segment3& s1, const Segment3& s2);
bool do_intersect_seg3_line3(const Segment3& s, const Line3& l);
bool do_intersect_seg3_ray3(const Segment3& s, const Ray3& r);
bool do_intersect_seg3_plane3(const Segment3& s, const Plane3& p);
bool do_intersect_seg3_tri3(const Segment3& s, const Triangle3& t);
bool do_intersect_seg3_sphere3(const Segment3& s, const Sphere3& sp);
bool do_intersect_seg3_bbox3(const Segment3& s, const Bbox3& b);
bool do_intersect_line3_line3(const Line3& l1, const Line3& l2);
bool do_intersect_line3_ray3(const Line3& l, const Ray3& r);
bool do_intersect_line3_plane3(const Line3& l, const Plane3& p);
bool do_intersect_line3_tri3(const Line3& l, const Triangle3& t);
bool do_intersect_line3_sphere3(const Line3& l, const Sphere3& s);
bool do_intersect_ray3_ray3(const Ray3& r1, const Ray3& r2);
bool do_intersect_ray3_plane3(const Ray3& r, const Plane3& p);
bool do_intersect_ray3_tri3(const Ray3& r, const Triangle3& t);
bool do_intersect_ray3_sphere3(const Ray3& r, const Sphere3& s);
bool do_intersect_plane3_plane3(const Plane3& p1, const Plane3& p2);
bool do_intersect_plane3_sphere3(const Plane3& p, const Sphere3& s);
bool do_intersect_plane3_tri3(const Plane3& p, const Triangle3& t);
bool do_intersect_tri3_tri3(const Triangle3& t1, const Triangle3& t2);
bool do_intersect_sphere3_sphere3(const Sphere3& s1, const Sphere3& s2);
bool do_intersect_pt3_plane3(const Point3& p, const Plane3& pl);
bool do_intersect_pt3_sphere3(const Point3& p, const Sphere3& s);
bool do_intersect_bbox3_bbox3(const Bbox3& b1, const Bbox3& b2);
bool do_intersect_bbox3_seg3(const Bbox3& b, const Segment3& s);
bool do_intersect_bbox3_tri3(const Bbox3& b, const Triangle3& t);

// ============================================================
// DO OVERLAP
// ============================================================
bool do_overlap_bbox2(const Bbox2& b1, const Bbox2& b2);
bool do_overlap_bbox3(const Bbox3& b1, const Bbox3& b2);

// ============================================================
// EQUIDISTANT LINE
// ============================================================
Line3 equidistant_line(const Point3& p, const Point3& q, const Point3& r);

// ============================================================
// HAS LARGER DISTANCE TO POINT
// ============================================================
bool has_larger_distance_to_point_2(const Point2& p, const Point2& q, const Point2& r);
bool has_larger_distance_to_point_3(const Point3& p, const Point3& q, const Point3& r);

// ============================================================
// HAS LARGER SIGNED DISTANCE TO LINE
// ============================================================
bool has_larger_signed_distance_to_line_l(const Line2& l, const Point2& p, const Point2& q);
bool has_larger_signed_distance_to_line_p(const Point2& p, const Point2& q,
                                           const Point2& r, const Point2& s);

// ============================================================
// HAS LARGER SIGNED DISTANCE TO PLANE
// ============================================================
bool has_larger_signed_distance_to_plane_h(const Plane3& h, const Point3& p, const Point3& q);
bool has_larger_signed_distance_to_plane_p(const Point3& p, const Point3& q, const Point3& r,
                                            const Point3& s, const Point3& t);

// ============================================================
// HAS SMALLER DISTANCE TO POINT
// ============================================================
bool has_smaller_distance_to_point_2(const Point2& p, const Point2& q, const Point2& r);
bool has_smaller_distance_to_point_3(const Point3& p, const Point3& q, const Point3& r);

// ============================================================
// HAS SMALLER SIGNED DISTANCE TO LINE
// ============================================================
bool has_smaller_signed_distance_to_line_l(const Line2& l, const Point2& p, const Point2& q);
bool has_smaller_signed_distance_to_line_p(const Point2& p, const Point2& q,
                                            const Point2& r, const Point2& s);

// ============================================================
// HAS SMALLER SIGNED DISTANCE TO PLANE
// ============================================================
bool has_smaller_signed_distance_to_plane_h(const Plane3& h, const Point3& p, const Point3& q);
bool has_smaller_signed_distance_to_plane_p(const Point3& p, const Point3& q, const Point3& r,
                                             const Point3& s, const Point3& t);


// ============================================================
// INTERSECTION 2D — returns py::dict with "type" and "value"
// ============================================================
#include <pybind11/pybind11.h>
namespace py = pybind11;

py::dict intersection_seg2_seg2(const Segment2& s1, const Segment2& s2);
py::dict intersection_seg2_line2(const Segment2& s, const Line2& l);
py::dict intersection_seg2_ray2(const Segment2& s, const Ray2& r);
py::dict intersection_seg2_tri2(const Segment2& s, const Triangle2& t);
py::dict intersection_line2_line2(const Line2& l1, const Line2& l2);
py::dict intersection_line2_ray2(const Line2& l, const Ray2& r);
py::dict intersection_line2_seg2(const Line2& l, const Segment2& s);
py::dict intersection_ray2_ray2(const Ray2& r1, const Ray2& r2);
py::dict intersection_ray2_seg2(const Ray2& r, const Segment2& s);

// ============================================================
// INTERSECTION 3D
// ============================================================
py::dict intersection_seg3_seg3(const Segment3& s1, const Segment3& s2);
py::dict intersection_seg3_line3(const Segment3& s, const Line3& l);
py::dict intersection_seg3_plane3(const Segment3& s, const Plane3& p);
py::dict intersection_seg3_tri3(const Segment3& s, const Triangle3& t);
py::dict intersection_line3_line3(const Line3& l1, const Line3& l2);
py::dict intersection_line3_plane3(const Line3& l, const Plane3& p);
py::dict intersection_line3_tri3(const Line3& l, const Triangle3& t);
py::dict intersection_plane3_plane3(const Plane3& p1, const Plane3& p2);
py::dict intersection_plane3_plane3_plane3(const Plane3& p1, const Plane3& p2, const Plane3& p3);
py::dict intersection_plane3_seg3(const Plane3& p, const Segment3& s);
py::dict intersection_plane3_tri3(const Plane3& p, const Triangle3& t);

// ============================================================
// L INFINITY DISTANCE
// ============================================================
double l_infinity_distance_2(const Point2& p, const Point2& q);
double l_infinity_distance_3(const Point3& p, const Point3& q);

// ============================================================
// LEFT TURN
// ============================================================
bool left_turn_2(const Point2& p, const Point2& q, const Point2& r);

// ============================================================
// LEXICOGRAPHIC COMPARISONS
// ============================================================
bool lexicographically_xyz_smaller(const Point3& p, const Point3& q);
bool lexicographically_xyz_smaller_or_equal(const Point3& p, const Point3& q);
bool lexicographically_xy_larger(const Point2& p, const Point2& q);
bool lexicographically_xy_larger_or_equal(const Point2& p, const Point2& q);
bool lexicographically_xy_smaller(const Point2& p, const Point2& q);
bool lexicographically_xy_smaller_or_equal(const Point2& p, const Point2& q);

// ============================================================
// MAX / MIN VERTEX
// ============================================================
Point2 max_vertex_iso_rect(const IsoRectangle2& ir);
Point3 max_vertex_iso_cuboid(const IsoCuboid3& ic);
Point2 min_vertex_iso_rect(const IsoRectangle2& ir);
Point3 min_vertex_iso_cuboid(const IsoCuboid3& ic);

// ============================================================
// MIDPOINT
// ============================================================
Point2 midpoint_pt2(const Point2& p, const Point2& q);
Point2 midpoint_seg2(const Segment2& s);
Point3 midpoint_pt3(const Point3& p, const Point3& q);
Point3 midpoint_seg3(const Segment3& s);

// ============================================================
// NORMAL
// ============================================================
Vector3 normal_3(const Point3& p, const Point3& q, const Point3& r);