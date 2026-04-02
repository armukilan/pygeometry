// -----------------------------------------------------------------------------------------------------------
// The Rule Going Forward
// Every time you add a new .cpp file, you do two things in wrapper.cpp:
// For a new free function (like run_distance):
// 1. Forward declare at the top
// double my_new_function(double a, double b);

// // 2. Register inside the module block
// m.def("my_new_function", &my_new_function, py::arg("a"), py::arg("b"));

// For a new class (like Point2):
// // 1. Include the file at the top
// #include "points.cpp"

// // 2. Bind the class inside the module block
// py::class_<MyClass>(m, "MyClass")
//     .def(...)
// Only one PYBIND11_MODULE block ever. Everything goes inside it.

// ------------------------------------------------------------------------------------------------------------



// ============================================================
// WHAT IS THIS FILE?
// This is the pybind11 wrapper file.
// It acts as a bridge between your pure CGAL C++ code and Python.
// It does not contain any CGAL logic.
// It only declares functions from your C++ files and exposes
// them to Python so they can be called like normal Python functions.
// ============================================================

// ============================================================
// HOW TO ADD A NEW FUNCTION?
// Step 1: Declare the function below under "FUNCTION DECLARATIONS"
// Step 2: Expose it inside PYBIND11_MODULE using m.def()
// Step 3: Add the .cpp file to CMakeLists.txt
// Step 4: Run python setup.py
// Step 5: Call it from main.py
// ============================================================

// ============================================================
// FUNCTION DECLARATIONS
// Declare all functions from your C++ files here.
// This tells the wrapper that these functions exist somewhere
// and will be linked during the build process.
// FORMAT: return_type function_name(argument_types);
// ============================================================


#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "core/types.h"
#include "core/points.h"
#include "core/segment2.h"
#include "core/direction2.h"
#include "core/orientation.h"
#include "core/line2.h"
#include "core/ray2.h"
#include "core/triangle2.h"
#include "core/circle2.h"
#include "core/iso_rectangle2.h"
#include "core/bbox2.h"
#include "core/weighted_point2.h"

// Declared from original/distance.cpp
// double run_distance(double x1, double y1, double x2, double y2);
double squared_distance(double x1, double y1, double x2, double y2);

// Add more declarations here as you add more C++ files
// Example:
// double run_convex_hull(double x1, double y1, double x2, double y2);


namespace py = pybind11;

// ============================================================
// PYBIND11_MODULE
// This creates the Python module named "cgal_python"
// When Python does "import cgal_python", this block is what
// Python loads and uses.
// The "m" here represents the module object.
// ============================================================
PYBIND11_MODULE(pycglib_core, m) {

    // --------------------------------------------------------
    // MODULE DESCRIPTION
    // Optional: describe what this module does
    // Accessible in Python via: help(cgal_python)
    // --------------------------------------------------------
    m.doc() = "CGAL Python bindings — call CGAL C++ functions from Python";

    // --------------------------------------------------------
    // EXPOSE FUNCTIONS TO PYTHON
    // FORMAT:
    // m.def("python_function_name", &cpp_function_name,
    //       py::arg("arg1_name"), py::arg("arg2_name"), ...);
    //
    // "python_function_name" — what Python will call it as
    // &cpp_function_name     — the actual C++ function to call
    // py::arg()              — names the arguments for Python
    // --------------------------------------------------------

    // Exposes run_distance() from original/distance.cpp to Python
    // Python calls it as: cgal_python.run_distance(x1, y1, x2, y2)
    m.def("squared_distance", &squared_distance,
          py::arg("x1"), py::arg("y1"),
          py::arg("x2"), py::arg("y2"));

    // Add more functions here as you add more C++ files
    // Example:
    // m.def("run_convex_hull", &run_convex_hull,
    //       py::arg("x1"), py::arg("y1"),
    //       py::arg("x2"), py::arg("y2"));
    
    // --- New: Point2 class ---
    py::class_<Point2>(m, "Point2")
        .def(py::init<double, double>())
        .def_property_readonly("x", &Point2::x)
        .def_property_readonly("y", &Point2::y)
        .def("__sub__",  &point2_sub)
        .def("__add__",  &point2_add_vector)
        .def("__repr__", [](const Point2& p) {
            return "Point2(" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + ")";
        });

    
    // --- New: Vector2 class ---
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


    // Orientation
    py::class_<OrientationResult>(m, "OrientationResult")
    .def("left_turn",  &OrientationResult::left_turn)
    .def("right_turn", &OrientationResult::right_turn)
    .def("collinear",  &OrientationResult::collinear)
    .def("__repr__",   &OrientationResult::str);

    m.def("orientation", &orientation_2,
          py::arg("p1"), py::arg("p2"), py::arg("p3"),
          "Returns orientation of three Point2 objects");

    // --- Bbox2 ---
    // py::class_<Bbox2>(m, "Bbox2")
    //     .def(py::init<double, double, double, double>())
    //     .def_readonly("xmin", &Bbox2::xmin)
    //     .def_readonly("ymin", &Bbox2::ymin)
    //     .def_readonly("xmax", &Bbox2::xmax)
    //     .def_readonly("ymax", &Bbox2::ymax)
    //     .def("__repr__", [](const Bbox2& b) {
    //         return "Bbox2(" + std::to_string(b.xmin) + ", " +
    //                           std::to_string(b.ymin) + ", " +
    //                           std::to_string(b.xmax) + ", " +
    //                           std::to_string(b.ymax) + ")";
    //     });
    // --- Bbox2 ---
    py::class_<Bbox2>(m, "Bbox2")
        .def(py::init<>())
        .def(py::init<double, double, double, double>(),
             py::arg("xmin"), py::arg("ymin"),
             py::arg("xmax"), py::arg("ymax"))
        .def_property_readonly("xmin",  &Bbox2::xmin)
        .def_property_readonly("ymin",  &Bbox2::ymin)
        .def_property_readonly("xmax",  &Bbox2::xmax)
        .def_property_readonly("ymax",  &Bbox2::ymax)
        .def("dimension",   &bbox2_dimension)
        .def("min",         &bbox2_min,         py::arg("i"))
        .def("max",         &bbox2_max,         py::arg("i"))
        .def("dilate",      &bbox2_dilate,      py::arg("dist"))
        .def("scale",       &bbox2_scale,       py::arg("factor"))
        .def("do_overlap",  &bbox2_do_overlap,  py::arg("other"))
        .def("__add__",     &bbox2_add)
        .def("__iadd__",    &bbox2_iadd)
        .def("__eq__",      &bbox2_eq)
        .def("__ne__",      &bbox2_neq)
        .def("__repr__", [](const Bbox2& b) {
            return "Bbox2(" + std::to_string(b.xmin()) + ", " +
                              std::to_string(b.ymin()) + ", " +
                              std::to_string(b.xmax()) + ", " +
                              std::to_string(b.ymax()) + ")";
        });


// --- Direction2 ---
// py::class_<Direction2>(m, "Direction2")
//     // .def("dx", &Direction2::dx)
//     // .def("dy", &Direction2::dy)
//     .def_property_readonly("dx", &Direction2::dx)
//     .def_property_readonly("dy", &Direction2::dy)
//     .def("__repr__", [](const Direction2& d) {
//         return "Direction2(" + std::to_string(d.dx()) + ", " +
//                                std::to_string(d.dy()) + ")";
//     });
// Inside PYBIND11_MODULE block — replace old Direction2 stub with:
py::class_<Direction2>(m, "Direction2")
    .def(py::init<double, double>(),
         py::arg("x"), py::arg("y"))
    .def(py::init(&direction2_from_vector),
         py::arg("v"))
    .def(py::init(&direction2_from_segment),
         py::arg("s"))
    .def(py::init(&direction2_from_ray), py::arg("r"))
    .def_property_readonly("dx",    &Direction2::dx)
    .def_property_readonly("dy",    &Direction2::dy)
    .def("delta",                   &Direction2::delta)
    .def("counterclockwise_in_between", &direction2_counterclockwise_in_between,
         py::arg("d1"), py::arg("d2"))
    .def("vector",                  &direction2_vector)
    .def("opposite",                &direction2_opposite)
    .def("__neg__",                 &direction2_opposite)
    .def("__eq__",                  &direction2_eq)
    .def("__ne__",                  &direction2_neq)
    .def("__lt__",                  &direction2_lt)
    .def("__gt__",                  &direction2_gt)
    .def("__le__",                  &direction2_le)
    .def("__ge__",                  &direction2_ge)
    .def("__repr__", [](const Direction2& d) {
        return "Direction2(" + std::to_string(d.dx()) + ", " +
                               std::to_string(d.dy()) + ")";
    });

// --- Line2 (stub for now, full version comes later) ---
// py::class_<Line2>(m, "Line2")
//     // .def("a", &Line2::a)
//     // .def("b", &Line2::b)
//     // .def("c", &Line2::c)
//     .def_property_readonly("a", &Line2::a)
//     .def_property_readonly("b", &Line2::b)
//     .def_property_readonly("c", &Line2::c)
//     .def("__repr__", [](const Line2& l) {
//         return "Line2(a=" + std::to_string(l.a()) + ", b=" +
//                              std::to_string(l.b()) + ", c=" +
//                              std::to_string(l.c()) + ")";
//     });
// --- Line2 ---
py::class_<Line2>(m, "Line2")
    .def(py::init<double, double, double>(),
         py::arg("a"), py::arg("b"), py::arg("c"))
    .def(py::init<const Point2&, const Point2&>(),
         py::arg("p"), py::arg("q"))
    .def(py::init<const Point2&, const Direction2&>(),
         py::arg("p"), py::arg("d"))
    .def(py::init<const Point2&, const Vector2&>(),
         py::arg("p"), py::arg("v"))
    .def(py::init<const Segment2&>(),
         py::arg("s"))
    // .def(py::init<const Ray2&>(), py::arg("r"))
    // .def("from_ray", &line2_from_ray, py::arg("r"))
    // .def("from_ray", [](const Line2&, const Ray2& r) { return line2_from_ray(r); }, py::arg("r"))
    .def(py::init([](const Ray2& r) { return Line2(r.r.supporting_line()); }),
         py::arg("r"))
    .def_static("from_ray", &line2_from_ray, py::arg("r"))
    .def_property_readonly("a",   &Line2::a)
    .def_property_readonly("b",   &Line2::b)
    .def_property_readonly("c",   &Line2::c)
    .def("point",                 &line2_point,        py::arg("i"))
    .def("projection",            &line2_projection,   py::arg("p"))
    .def("x_at_y",                &line2_x_at_y,       py::arg("y"))
    .def("y_at_x",                &line2_y_at_x,       py::arg("x"))
    .def("is_degenerate",         &line2_is_degenerate)
    .def("is_horizontal",         &line2_is_horizontal)
    .def("is_vertical",           &line2_is_vertical)
    .def("oriented_side",         &line2_oriented_side,         py::arg("p"))
    .def("has_on",                &line2_has_on,                py::arg("p"))
    .def("has_on_positive_side",  &line2_has_on_positive_side,  py::arg("p"))
    .def("has_on_negative_side",  &line2_has_on_negative_side,  py::arg("p"))
    .def("to_vector",             &line2_to_vector)
    .def("direction",             &line2_direction)
    .def("opposite",              &line2_opposite)
    .def("perpendicular",         &line2_perpendicular,         py::arg("p"))
    .def("__eq__",                &line2_eq)
    .def("__ne__",                &line2_neq)
    .def("__repr__", [](const Line2& l) {
        return "Line2(a=" + std::to_string(l.a()) + ", b=" +
                             std::to_string(l.b()) + ", c=" +
                             std::to_string(l.c()) + ")";
    });

// --- Segment2 ---
py::class_<Segment2>(m, "Segment2")
    .def(py::init<const Point2&, const Point2&>())
    .def("source",            &segment2_source)
    .def("target",            &segment2_target)
    .def("min",               &segment2_min)
    .def("max",               &segment2_max)
    .def("vertex",            &segment2_vertex)
    .def("point",             &segment2_point)
    .def("__getitem__",       &segment2_vertex)
    .def("squared_length",    &segment2_squared_length)
    .def("direction",         &segment2_direction)
    .def("to_vector",         &segment2_to_vector)
    .def("opposite",          &segment2_opposite)
    .def("supporting_line",   &segment2_supporting_line)
    .def("is_degenerate",     &segment2_is_degenerate)
    .def("is_horizontal",     &segment2_is_horizontal)
    .def("is_vertical",       &segment2_is_vertical)
    .def("has_on",            &segment2_has_on)
    .def("collinear_has_on",  &segment2_collinear_has_on)
    .def("bbox",              &segment2_bbox)
    .def("__eq__",            &segment2_eq)
    .def("__ne__",            &segment2_neq)
    .def("__repr__", [](const Segment2& s) {
        auto src = segment2_source(s);
        auto tgt = segment2_target(s);
        return "Segment2((" + std::to_string(src.x()) + ", " +
                               std::to_string(src.y()) + "), (" +
                               std::to_string(tgt.x()) + ", " +
                               std::to_string(tgt.y()) + "))";
    });


// --- Ray2 ---
py::class_<Ray2>(m, "Ray2")
    .def(py::init<const Point2&, const Point2&>(),
         py::arg("p"), py::arg("q"))
    .def(py::init<const Point2&, const Direction2&>(),
         py::arg("p"), py::arg("d"))
    .def(py::init<const Point2&, const Vector2&>(),
         py::arg("p"), py::arg("v"))
    .def(py::init<const Point2&, const Line2&>(),
         py::arg("p"), py::arg("l"))
    .def("source",           &ray2_source)
    .def("point",            &ray2_point,            py::arg("i"))
    .def("direction",        &ray2_direction)
    .def("to_vector",        &ray2_to_vector)
    .def("supporting_line",  &ray2_supporting_line)
    .def("opposite",         &ray2_opposite)
    .def("is_degenerate",    &ray2_is_degenerate)
    .def("is_horizontal",    &ray2_is_horizontal)
    .def("is_vertical",      &ray2_is_vertical)
    .def("has_on",           &ray2_has_on,           py::arg("p"))
    .def("collinear_has_on", &ray2_collinear_has_on, py::arg("p"))
    .def("__eq__",           &ray2_eq)
    .def("__ne__",           &ray2_neq)
    .def("__repr__", [](const Ray2& r) {
        auto s = ray2_source(r);
        auto d = ray2_direction(r);
        return "Ray2(source=(" + std::to_string(s.x()) + ", " +
                                  std::to_string(s.y()) + "), direction=(" +
                                  std::to_string(d.dx()) + ", " +
                                  std::to_string(d.dy()) + "))";
    });


// --- Triangle2 ---
py::class_<Triangle2>(m, "Triangle2")
    .def(py::init<const Point2&, const Point2&, const Point2&>(),
         py::arg("p"), py::arg("q"), py::arg("r"))
    .def("vertex",                &triangle2_vertex,              py::arg("i"))
    .def("__getitem__",           &triangle2_vertex,              py::arg("i"))
    .def("is_degenerate",         &triangle2_is_degenerate)
    .def("orientation",           &triangle2_orientation)
    .def("oriented_side",         &triangle2_oriented_side,       py::arg("p"))
    .def("bounded_side",          &triangle2_bounded_side,        py::arg("p"))
    .def("has_on_positive_side",  &triangle2_has_on_positive_side,  py::arg("p"))
    .def("has_on_negative_side",  &triangle2_has_on_negative_side,  py::arg("p"))
    .def("has_on_boundary",       &triangle2_has_on_boundary,       py::arg("p"))
    .def("has_on_bounded_side",   &triangle2_has_on_bounded_side,   py::arg("p"))
    .def("has_on_unbounded_side", &triangle2_has_on_unbounded_side, py::arg("p"))
    .def("opposite",              &triangle2_opposite)
    .def("area",                  &triangle2_area)
    .def("bbox",                  &triangle2_bbox)
    .def("__eq__",                &triangle2_eq)
    .def("__ne__",                &triangle2_neq)
    .def("__repr__", [](const Triangle2& t) {
        auto p = triangle2_vertex(t, 0);
        auto q = triangle2_vertex(t, 1);
        auto r = triangle2_vertex(t, 2);
        return "Triangle2((" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + "), ("
                             + std::to_string(q.x()) + ", " + std::to_string(q.y()) + "), ("
                             + std::to_string(r.x()) + ", " + std::to_string(r.y()) + "))";
    });


// --- Circle2 ---
py::class_<Circle2>(m, "Circle2")
    .def(py::init<const Point2&, double, int>(),
         py::arg("center"), py::arg("squared_radius"), py::arg("orientation") = 1)
    .def(py::init<const Point2&, const Point2&, const Point2&>(),
         py::arg("p"), py::arg("q"), py::arg("r"))
    .def(py::init<const Point2&, const Point2&, int>(),
         py::arg("p"), py::arg("q"), py::arg("orientation") = 1)
    .def(py::init<const Point2&, int>(),
         py::arg("center"), py::arg("orientation") = 1)
    .def("center",                &circle2_center)
    .def("squared_radius",        &circle2_squared_radius)
    .def("orientation",           &circle2_orientation)
    .def("is_degenerate",         &circle2_is_degenerate)
    .def("oriented_side",         &circle2_oriented_side,         py::arg("p"))
    .def("bounded_side",          &circle2_bounded_side,          py::arg("p"))
    .def("has_on_positive_side",  &circle2_has_on_positive_side,  py::arg("p"))
    .def("has_on_negative_side",  &circle2_has_on_negative_side,  py::arg("p"))
    .def("has_on_boundary",       &circle2_has_on_boundary,       py::arg("p"))
    .def("has_on_bounded_side",   &circle2_has_on_bounded_side,   py::arg("p"))
    .def("has_on_unbounded_side", &circle2_has_on_unbounded_side, py::arg("p"))
    .def("opposite",              &circle2_opposite)
    .def("bbox",                  &circle2_bbox)
    .def("__eq__",                &circle2_eq)
    .def("__ne__",                &circle2_neq)
    .def("__repr__", [](const Circle2& c) {
        auto ct = circle2_center(c);
        return "Circle2(center=(" + std::to_string(ct.x()) + ", " +
                                    std::to_string(ct.y()) + "), squared_radius=" +
                                    std::to_string(circle2_squared_radius(c)) + ")";
    });


// --- IsoRectangle2 ---
py::class_<IsoRectangle2>(m, "IsoRectangle2")
    .def(py::init<const Point2&, const Point2&>(),
         py::arg("p"), py::arg("q"))
    .def(py::init<const Point2&, const Point2&,
                  const Point2&, const Point2&>(),
         py::arg("left"), py::arg("right"),
         py::arg("bottom"), py::arg("top"))
    .def(py::init<double, double, double, double>(),
         py::arg("min_x"), py::arg("min_y"),
         py::arg("max_x"), py::arg("max_y"))
    .def(py::init<const Bbox2&>(), py::arg("bbox"))
    .def("vertex",                &iso_rect2_vertex,              py::arg("i"))
    .def("__getitem__",           &iso_rect2_vertex,              py::arg("i"))
    .def("min",                   &iso_rect2_min)
    .def("max",                   &iso_rect2_max)
    .def("xmin",                  &iso_rect2_xmin)
    .def("ymin",                  &iso_rect2_ymin)
    .def("xmax",                  &iso_rect2_xmax)
    .def("ymax",                  &iso_rect2_ymax)
    .def("min_coord",             &iso_rect2_min_coord,           py::arg("i"))
    .def("max_coord",             &iso_rect2_max_coord,           py::arg("i"))
    .def("is_degenerate",         &iso_rect2_is_degenerate)
    .def("bounded_side",          &iso_rect2_bounded_side,        py::arg("p"))
    .def("has_on_boundary",       &iso_rect2_has_on_boundary,     py::arg("p"))
    .def("has_on_bounded_side",   &iso_rect2_has_on_bounded_side, py::arg("p"))
    .def("has_on_unbounded_side", &iso_rect2_has_on_unbounded_side, py::arg("p"))
    .def("area",                  &iso_rect2_area)
    .def("bbox",                  &iso_rect2_bbox)
    .def("__eq__",                &iso_rect2_eq)
    .def("__ne__",                &iso_rect2_neq)
    .def("__repr__", [](const IsoRectangle2& r) {
        return "IsoRectangle2(xmin=" + std::to_string(iso_rect2_xmin(r)) +
                            ", ymin=" + std::to_string(iso_rect2_ymin(r)) +
                            ", xmax=" + std::to_string(iso_rect2_xmax(r)) +
                            ", ymax=" + std::to_string(iso_rect2_ymax(r)) + ")";
    });


    // --- WeightedPoint2 ---
py::class_<WeightedPoint2>(m, "WeightedPoint2")
    .def(py::init<>())
    .def(py::init<const Point2&>(),         py::arg("p"))
    .def(py::init<const Point2&, double>(), py::arg("p"), py::arg("w"))
    .def(py::init<double, double>(),        py::arg("x"), py::arg("y"))
    .def("point",       &wp2_point)
    .def("weight",      &wp2_weight)
    .def("hx",          &wp2_hx)
    .def("hy",          &wp2_hy)
    .def("hw",          &wp2_hw)
    .def("x",           &wp2_x)
    .def("y",           &wp2_y)
    .def("homogeneous", &wp2_homogeneous,   py::arg("i"))
    .def("cartesian",   &wp2_cartesian,     py::arg("i"))
    .def("__getitem__", &wp2_cartesian,     py::arg("i"))
    .def("dimension",   &wp2_dimension)
    .def("bbox",        &wp2_bbox)
    .def("__eq__",      &wp2_eq)
    .def("__ne__",      &wp2_neq)
    .def("__repr__", [](const WeightedPoint2& wp) {
        return "WeightedPoint2(point=(" +
               std::to_string(wp2_x(wp)) + ", " +
               std::to_string(wp2_y(wp)) + "), weight=" +
               std::to_string(wp2_weight(wp)) + ")";
    });


}