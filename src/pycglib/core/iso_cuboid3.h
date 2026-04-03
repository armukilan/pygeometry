#pragma once
#include "core/types.h"

// --- Operations ---
bool   iso_cuboid3_eq(const IsoCuboid3& a, const IsoCuboid3& b);
bool   iso_cuboid3_neq(const IsoCuboid3& a, const IsoCuboid3& b);
Point3 iso_cuboid3_vertex(const IsoCuboid3& c, int i);
Point3 iso_cuboid3_min(const IsoCuboid3& c);
Point3 iso_cuboid3_max(const IsoCuboid3& c);
double iso_cuboid3_xmin(const IsoCuboid3& c);
double iso_cuboid3_ymin(const IsoCuboid3& c);
double iso_cuboid3_zmin(const IsoCuboid3& c);
double iso_cuboid3_xmax(const IsoCuboid3& c);
double iso_cuboid3_ymax(const IsoCuboid3& c);
double iso_cuboid3_zmax(const IsoCuboid3& c);
double iso_cuboid3_min_coord(const IsoCuboid3& c, int i);
double iso_cuboid3_max_coord(const IsoCuboid3& c, int i);

// --- Predicates ---
bool iso_cuboid3_is_degenerate(const IsoCuboid3& c);
int  iso_cuboid3_bounded_side(const IsoCuboid3& c, const Point3& p);
bool iso_cuboid3_has_on_boundary(const IsoCuboid3& c, const Point3& p);
bool iso_cuboid3_has_on_bounded_side(const IsoCuboid3& c, const Point3& p);
bool iso_cuboid3_has_on_unbounded_side(const IsoCuboid3& c, const Point3& p);

// --- Miscellaneous ---
double iso_cuboid3_volume(const IsoCuboid3& c);
Bbox3  iso_cuboid3_bbox(const IsoCuboid3& c);