#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "core/points.h"
#include "core/orientation.h"

// ============================================================
// WHAT IS THIS FILE?
// This is the pybind11 bridge between your pure CGAL C++ code
// and Python. It declares functions from cgal/distance.cpp
// and exposes them to Python.
// To add a new function:
//   Step 1: Write the function in cgal/your_file.cpp
//   Step 2: Declare it here under FUNCTION DECLARATIONS
//   Step 3: Expose it inside PYBIND11_MODULE using m.def()
//   Step 4: Add the .cpp file to CMakeLists.txt
//   Step 5: Run pip install -e . to rebuild
// ============================================================

namespace py = pybind11;

// ============================================================
// FUNCTION DECLARATIONS
// Declare all functions from your CGAL C++ files here.
// ============================================================

// From cgal/distance.cpp
double squared_distance(double x1, double y1, double x2, double y2);

// ============================================================
// PYTHON MODULE
// The module is named pycglib_core.
// __init__.py imports everything from this module
// so users just do: import pycglib as pg
// ============================================================
PYBIND11_MODULE(pycglib_core, m) {
    m.doc() = "pycglib - CGAL Python bindings";

    // --- Distance (original) ---
    m.def("squared_distance",
        [](py::tuple a, py::tuple b) {
            double x1 = a[0].cast<double>();
            double y1 = a[1].cast<double>();
            double x2 = b[0].cast<double>();
            double y2 = b[1].cast<double>();
            return squared_distance(x1, y1, x2, y2);
        },
        py::arg("a"), py::arg("b"),
        "Compute squared distance between two 2D points passed as tuples");

    // --- Point2 ---
    py::class_<Point2>(m, "Point2")
        .def(py::init<double, double>())
        .def_property_readonly("x", &Point2::x)
        .def_property_readonly("y", &Point2::y)
        .def("__sub__",  &point2_sub)
        .def("__add__",  &point2_add_vector)
        .def("__repr__", [](const Point2& p) {
            return "Point2(" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + ")";
        });

    // --- Vector2 ---
    py::class_<Vector2>(m, "Vector2")
        .def(py::init<double, double>())
        .def_property_readonly("x", &Vector2::x)
        .def_property_readonly("y", &Vector2::y)
        .def("__add__",  &vector2_add)
        .def("__mul__",  &vector2_mul)
        .def("__rmul__", &vector2_mul)
        .def("__repr__", [](const Vector2& v) {
            return "Vector2(" + std::to_string(v.x()) + ", " + std::to_string(v.y()) + ")";
        });

    // --- Orientation ---
    py::class_<OrientationResult>(m, "OrientationResult")
        .def("left_turn",  &OrientationResult::left_turn)
        .def("right_turn", &OrientationResult::right_turn)
        .def("collinear",  &OrientationResult::collinear)
        .def("__repr__",   &OrientationResult::str);

    m.def("orientation", &orientation_2,
          py::arg("p1"), py::arg("p2"), py::arg("p3"),
          "Returns orientation of three Point2 objects");
}