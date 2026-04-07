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