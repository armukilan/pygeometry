#pragma once
#include "core/types.h"

// --- Arithmetic ---
Vector3 point3_sub(const Point3& a, const Point3& b);
Point3  point3_add_vector(const Point3& p, const Vector3& v);
Point3  point3_sub_vector(const Point3& p, const Vector3& v);
Point3  point3_iadd(Point3& p, const Vector3& v);
Point3  point3_isub(Point3& p, const Vector3& v);

// --- Comparison ---
bool point3_eq(const Point3& a, const Point3& b);
bool point3_neq(const Point3& a, const Point3& b);
bool point3_lt(const Point3& a, const Point3& b);
bool point3_gt(const Point3& a, const Point3& b);
bool point3_le(const Point3& a, const Point3& b);
bool point3_ge(const Point3& a, const Point3& b);

// --- Vector3 operations ---
Vector3 vector3_add(const Vector3& a, const Vector3& b);
Vector3 vector3_sub(const Vector3& a, const Vector3& b);
Vector3 vector3_mul(const Vector3& a, double scalar);
Vector3 vector3_neg(const Vector3& v);

// --- Miscellaneous ---
Bbox3  point3_bbox(const Point3& p);