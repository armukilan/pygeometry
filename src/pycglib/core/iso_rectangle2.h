#pragma once
#include "core/types.h"

// --- Operations ---
bool   iso_rect2_eq(const IsoRectangle2& a, const IsoRectangle2& b);
bool   iso_rect2_neq(const IsoRectangle2& a, const IsoRectangle2& b);
Point2 iso_rect2_vertex(const IsoRectangle2& r, int i);
Point2 iso_rect2_min(const IsoRectangle2& r);
Point2 iso_rect2_max(const IsoRectangle2& r);
double iso_rect2_xmin(const IsoRectangle2& r);
double iso_rect2_ymin(const IsoRectangle2& r);
double iso_rect2_xmax(const IsoRectangle2& r);
double iso_rect2_ymax(const IsoRectangle2& r);
double iso_rect2_min_coord(const IsoRectangle2& r, int i);
double iso_rect2_max_coord(const IsoRectangle2& r, int i);

// --- Predicates ---
bool iso_rect2_is_degenerate(const IsoRectangle2& r);
int  iso_rect2_bounded_side(const IsoRectangle2& r, const Point2& p);  // 1=inside, -1=outside, 0=boundary
bool iso_rect2_has_on_boundary(const IsoRectangle2& r, const Point2& p);
bool iso_rect2_has_on_bounded_side(const IsoRectangle2& r, const Point2& p);
bool iso_rect2_has_on_unbounded_side(const IsoRectangle2& r, const Point2& p);

// --- Miscellaneous ---
double       iso_rect2_area(const IsoRectangle2& r);
Bbox2        iso_rect2_bbox(const IsoRectangle2& r);