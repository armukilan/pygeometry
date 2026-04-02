#pragma once
#include "core/types.h"

Line3 line3_from_ray(const Ray3& r);
// --- Operations ---
bool       line3_eq(const Line3& a, const Line3& b);
bool       line3_neq(const Line3& a, const Line3& b);
Point3     line3_projection(const Line3& l, const Point3& p);
Point3     line3_point(const Line3& l, double i);

// --- Predicates ---
bool line3_is_degenerate(const Line3& l);
bool line3_has_on(const Line3& l, const Point3& p);

// --- Miscellaneous ---
Plane3     line3_perpendicular_plane(const Line3& l, const Point3& p);
Line3      line3_opposite(const Line3& l);
Vector3    line3_to_vector(const Line3& l);
Direction3 line3_direction(const Line3& l);