#pragma once
#include "core/types.h"

// --- Operations ---
bool   line2_eq(const Line2& a, const Line2& b);
bool   line2_neq(const Line2& a, const Line2& b);
Point2 line2_point(const Line2& l, double i);
Point2 line2_projection(const Line2& l, const Point2& p);
double line2_x_at_y(const Line2& l, double y);
double line2_y_at_x(const Line2& l, double x);

// --- Predicates ---
bool line2_is_degenerate(const Line2& l);
bool line2_is_horizontal(const Line2& l);
bool line2_is_vertical(const Line2& l);
int  line2_oriented_side(const Line2& l, const Point2& p);  // -1, 0, 1

// --- Convenience ---
bool line2_has_on(const Line2& l, const Point2& p);
bool line2_has_on_positive_side(const Line2& l, const Point2& p);
bool line2_has_on_negative_side(const Line2& l, const Point2& p);

// --- Miscellaneous ---
Vector2    line2_to_vector(const Line2& l);
Direction2 line2_direction(const Line2& l);
Line2      line2_opposite(const Line2& l);
Line2      line2_perpendicular(const Line2& l, const Point2& p);