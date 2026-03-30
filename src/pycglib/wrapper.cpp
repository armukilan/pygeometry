#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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
// The module is named pygeometry_core.
// __init__.py imports everything from this module
// so users just do: import pygeometry as pg
// ============================================================
PYBIND11_MODULE(pycglib_core, m) {
    m.doc() = "pycglib - CGAL Python bindings";

    // --------------------------------------------------------
    // Expose squared_distance to Python
    // User calls it as: pg.squared_distance((0,0), (3,4))
    // We unpack the tuples into x1, y1, x2, y2 here
    // --------------------------------------------------------
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
}