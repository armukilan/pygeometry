#pragma once
#include "core/types.h"

// --- Creation ---
Direction3 direction3_from_vector(const Vector3& v);
Direction3 direction3_from_xyz(double x, double y, double z);
Direction3 direction3_from_segment(const Segment3& s);

// --- Operations ---
bool       direction3_eq(const Direction3& a, const Direction3& b);
bool       direction3_neq(const Direction3& a, const Direction3& b);
Direction3 direction3_opposite(const Direction3& d);
Vector3    direction3_vector(const Direction3& d);