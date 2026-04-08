#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <CGAL/General_polygon_with_holes_2.h>
#include <CGAL/Polygon_2_algorithms.h>
#include <CGAL/version.h>
#include "core/types.h"

// Multipolygon_with_holes_2 was added in CGAL 5.6.
// On older systems (e.g. manylinux dnf CGAL ~5.2) the header doesn't exist.
#if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(5,6,0)
#  define PYCG_HAS_MULTIPOLYGON 1
#  include <CGAL/Multipolygon_with_holes_2.h>
#endif

namespace py = pybind11;

// Internal CGAL polygon types — raw kernel types, NOT exposed to Python.
// Python always sees the project's wrapper structs (Point2, Segment2, Bbox2).
using CGALPolygon2          = CGAL::Polygon_2<Kernel>;
using CGALPolygonWithHoles2 = CGAL::Polygon_with_holes_2<Kernel>;
using CGALGenPolyWithHoles2 = CGAL::General_polygon_with_holes_2<CGALPolygon2>;
#ifdef PYCG_HAS_MULTIPOLYGON
using CGALMultipolygon2     = CGAL::Multipolygon_with_holes_2<Kernel>;
#endif

void bind_polygon2(py::module_& m);
void bind_general_polygon_with_holes2(py::module_& m);
void bind_polygon_with_holes2(py::module_& m);
void bind_multipolygon_with_holes2(py::module_& m);  // no-op on old CGAL
void bind_polygon_global_functions(py::module_& m);