#pragma once
#include "core/types.h"

// --- Operations ---
bool       ray3_eq(const Ray3& a, const Ray3& b);
bool       ray3_neq(const Ray3& a, const Ray3& b);
Point3     ray3_source(const Ray3& r);
Point3     ray3_point(const Ray3& r, double i);
Direction3 ray3_direction(const Ray3& r);
Vector3    ray3_to_vector(const Ray3& r);
Line3      ray3_supporting_line(const Ray3& r);
Ray3       ray3_opposite(const Ray3& r);

// --- Predicates ---
bool ray3_is_degenerate(const Ray3& r);
bool ray3_has_on(const Ray3& r, const Point3& p);