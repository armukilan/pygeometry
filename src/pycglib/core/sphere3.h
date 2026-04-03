#pragma once
#include "core/types.h"

// --- Access ---
Point3 sphere3_center(const Sphere3& s);
double sphere3_squared_radius(const Sphere3& s);
int    sphere3_orientation(const Sphere3& s);   // 1=CCW, -1=CW
bool   sphere3_eq(const Sphere3& a, const Sphere3& b);
bool   sphere3_neq(const Sphere3& a, const Sphere3& b);

// --- Predicates ---
bool sphere3_is_degenerate(const Sphere3& s);
int  sphere3_oriented_side(const Sphere3& s, const Point3& p);  // 1, -1, 0
int  sphere3_bounded_side(const Sphere3& s, const Point3& p);   // 1=inside, -1=outside, 0=boundary
bool sphere3_has_on_positive_side(const Sphere3& s, const Point3& p);
bool sphere3_has_on_negative_side(const Sphere3& s, const Point3& p);
bool sphere3_has_on_boundary(const Sphere3& s, const Point3& p);
bool sphere3_has_on_bounded_side(const Sphere3& s, const Point3& p);
bool sphere3_has_on_unbounded_side(const Sphere3& s, const Point3& p);
bool sphere3_has_on(const Sphere3& s, const Point3& p);

// --- Miscellaneous ---
Sphere3 sphere3_opposite(const Sphere3& s);
Bbox3   sphere3_bbox(const Sphere3& s);