#pragma once
#include "core/types.h"

// --- Operations ---
bool       segment3_eq(const Segment3& a, const Segment3& b);
bool       segment3_neq(const Segment3& a, const Segment3& b);
Point3     segment3_source(const Segment3& s);
Point3     segment3_target(const Segment3& s);
Point3     segment3_min(const Segment3& s);
Point3     segment3_max(const Segment3& s);
Point3     segment3_vertex(const Segment3& s, int i);
Point3     segment3_point(const Segment3& s, int i);
double     segment3_squared_length(const Segment3& s);
Vector3    segment3_to_vector(const Segment3& s);
Direction3 segment3_direction(const Segment3& s);
Segment3   segment3_opposite(const Segment3& s);
Line3      segment3_supporting_line(const Segment3& s);
bool       segment3_is_degenerate(const Segment3& s);
bool       segment3_has_on(const Segment3& s, const Point3& p);
Bbox3      segment3_bbox(const Segment3& s);