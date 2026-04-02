#pragma once
#include "core/types.h"

Plane3 plane3_from_ray(const Ray3& r, const Point3& p);
Plane3 plane3_from_segment(const Segment3& s, const Point3& p);

// --- Operations ---
bool       plane3_eq(const Plane3& a, const Plane3& b);
bool       plane3_neq(const Plane3& a, const Plane3& b);
Line3      plane3_perpendicular_line(const Plane3& h, const Point3& p);
Point3     plane3_projection(const Plane3& h, const Point3& p);
Plane3     plane3_opposite(const Plane3& h);
Point3     plane3_point(const Plane3& h);
Vector3    plane3_orthogonal_vector(const Plane3& h);
Direction3 plane3_orthogonal_direction(const Plane3& h);
Vector3    plane3_base1(const Plane3& h);
Vector3    plane3_base2(const Plane3& h);

// --- 2D Conversion ---
Point2     plane3_to_2d(const Plane3& h, const Point3& p);
Point3     plane3_to_3d(const Plane3& h, const Point2& p);

// --- Predicates ---
int  plane3_oriented_side(const Plane3& h, const Point3& p);  // 1, -1, 0
bool plane3_has_on_point(const Plane3& h, const Point3& p);
bool plane3_has_on_positive_side(const Plane3& h, const Point3& p);
bool plane3_has_on_negative_side(const Plane3& h, const Point3& p);
bool plane3_has_on_line(const Plane3& h, const Line3& l);
bool plane3_is_degenerate(const Plane3& h);