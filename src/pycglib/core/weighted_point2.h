#pragma once
#include "core/types.h"

// --- Bare point and weight accessors ---
Point2 wp2_point(const WeightedPoint2& wp);
double wp2_weight(const WeightedPoint2& wp);

// --- Operations ---
bool wp2_eq(const WeightedPoint2& a, const WeightedPoint2& b);
bool wp2_neq(const WeightedPoint2& a, const WeightedPoint2& b);

// --- Coordinate access ---
double wp2_hx(const WeightedPoint2& wp);
double wp2_hy(const WeightedPoint2& wp);
double wp2_hw(const WeightedPoint2& wp);
double wp2_x(const WeightedPoint2& wp);
double wp2_y(const WeightedPoint2& wp);

// --- Convenience ---
double wp2_homogeneous(const WeightedPoint2& wp, int i);
double wp2_cartesian(const WeightedPoint2& wp, int i);
int    wp2_dimension(const WeightedPoint2& wp);
Bbox2  wp2_bbox(const WeightedPoint2& wp);