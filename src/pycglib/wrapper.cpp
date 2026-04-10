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
#include "core/aff_transformation2.h"

#include "core/point3.h"
#include "core/direction3.h"
#include "core/segment3.h"
#include "core/line3.h"
#include "core/ray3.h"
#include "core/plane3.h"
#include "core/triangle3.h"
#include "core/sphere3.h"
#include "core/tetrahedron3.h"
#include "core/iso_cuboid3.h"
#include "core/circle3.h"
#include "core/weighted_point3.h"
#include "core/aff_transformation3.h"
#include <CGAL/enum.h>
#include "core/global_functions.h"
#include <pybind11/stl.h>
#include "core/polygon2.h"

// ============================================================
// ADD TO INCLUDES at top of cgal_wrapper.cpp:
# include "core/triangulation2.h"
// ============================================================

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
    // py::class_<Point2>(m, "Point2")
    // .def(py::init<double, double>())
    // .def_property_readonly("x", &Point2::x)
    // .def_property_readonly("y", &Point2::y)
    // .def("__sub__",  &point2_sub)
    // .def("__add__",  &point2_add_vector)
    // .def("__repr__", [](const Point2& p) {
    //     return "Point2(" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + ")";
    // })                                          // ← close __repr__ here
    // .def("transform", [](const Point2& p, const AffTransformation2& t) {
    //     return aff2_transform_point(t, p);
    // }, py::arg("t"));                           // ← semicolon ends the class

    
    // // --- New: Vector2 class ---
    // py::class_<Vector2>(m, "Vector2")
    // .def(py::init<double, double>())
    // .def_property_readonly("x", &Vector2::x)
    // .def_property_readonly("y", &Vector2::y)
    // .def("__add__",  &vector2_add)
    // .def("__mul__",  &vector2_mul)
    // .def("__rmul__", &vector2_mul)
    // .def("__repr__", [](const Vector2& v) {
    //     return "Vector2(" + std::to_string(v.x()) + ", " + std::to_string(v.y()) + ")";
    // })                                          // ← close __repr__ here
    // .def("transform", [](const Vector2& v, const AffTransformation2& t) {
    //     return aff2_transform_vector(t, v);
    // }, py::arg("t"));                           // ← semicolon ends the class


    // --- Point2 ---
py::class_<Point2>(m, "Point2")
    .def(py::init<>())
    .def(py::init<double, double>(),  py::arg("x"), py::arg("y"))
    .def(py::init<int, int>(),        py::arg("x"), py::arg("y"))
    // .def(py::init(&point2_from_weighted), py::arg("wp"))
    .def(py::init([](const WeightedPoint2& wp) {
    return point2_from_weighted(wp);
    }), py::arg("wp"))
    .def_property_readonly("x",  &Point2::x)
    .def_property_readonly("y",  &Point2::y)
    .def_property_readonly("hx", &Point2::hx)
    .def_property_readonly("hy", &Point2::hy)
    .def_property_readonly("hw", &Point2::hw)
    .def("cartesian",    &Point2::cartesian,   py::arg("i"))
    .def("homogeneous",  &Point2::homogeneous, py::arg("i"))
    .def("dimension",    &Point2::dimension)
    .def("bbox",         &point2_bbox)
    .def("__getitem__",  &Point2::operator[],  py::arg("i"))
    .def("__sub__",      &point2_sub)
    .def("__add__",      &point2_add_vector)
    .def("__sub__",      &point2_sub_vector)
    .def("__iadd__",     &point2_iadd)
    .def("__isub__",     &point2_isub)
    .def("__eq__",       &point2_eq)
    .def("__ne__",       &point2_neq)
    .def("__lt__",       &point2_lt)
    .def("__gt__",       &point2_gt)
    .def("__le__",       &point2_le)
    .def("__ge__",       &point2_ge)
    .def("transform", [](const Point2& p, const AffTransformation2& t) {
        return aff2_transform_point(t, p);
    }, py::arg("t"))
    .def("__repr__", [](const Point2& p) {
        return "Point2(" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + ")";
    });

// --- Vector2 ---
py::class_<Vector2>(m, "Vector2")
    .def(py::init<double, double>(), py::arg("x"), py::arg("y"))
    .def_property_readonly("x", &Vector2::x)
    .def_property_readonly("y", &Vector2::y)
    .def("__add__",  &vector2_add)
    .def("__sub__",  &vector2_sub)
    .def("__mul__",  &vector2_mul)
    .def("__rmul__", &vector2_mul)
    .def("__neg__",  &vector2_neg)
    .def("transform", [](const Vector2& v, const AffTransformation2& t) {
        return aff2_transform_vector(t, v);
    }, py::arg("t"))
    .def("__repr__", [](const Vector2& v) {
        return "Vector2(" + std::to_string(v.x()) + ", " + std::to_string(v.y()) + ")";
    });


    // Orientation
    // py::class_<OrientationResult>(m, "OrientationResult")
    // .def("left_turn",  &OrientationResult::left_turn)
    // .def("right_turn", &OrientationResult::right_turn)
    // .def("collinear",  &OrientationResult::collinear)
    // .def("__repr__",   &OrientationResult::str);

    // m.def("orientation", &orientation_2,
    //       py::arg("p1"), py::arg("p2"), py::arg("p3"),
    //       "Returns orientation of three Point2 objects");


    

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
                               std::to_string(d.dy()) + ")";})

    .def("transform", [](const Direction2& d, const AffTransformation2& t) {
        return aff2_transform_direction(t, d);
    }, py::arg("t"));

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
                             std::to_string(l.c()) + ")";})
    .def("transform", [](const Line2& l, const AffTransformation2& t) {
        return aff2_transform_line(t, l);
    }, py::arg("t"));

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
                               std::to_string(tgt.y()) + "))";})

    .def("transform", [](const Segment2& s, const AffTransformation2& t) {
    auto result = s.s.transform(t.t);
    return Segment2(result);
    }, py::arg("t"));


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
                             + std::to_string(r.x()) + ", " + std::to_string(r.y()) + "))";})
    .def("transform", [](const Triangle2& tri, const AffTransformation2& t) {
    return Triangle2(tri.t.transform(t.t));
    }, py::arg("t"));


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
                                    std::to_string(circle2_squared_radius(c)) + ")";})
    .def("orthogonal_transform", [](const Circle2& c, const AffTransformation2& t) {
        return Circle2(c.c.orthogonal_transform(t.t));
    }, py::arg("t"));


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
                            ", ymax=" + std::to_string(iso_rect2_ymax(r)) + ")";})
    .def("transform", [](const IsoRectangle2& r, const AffTransformation2& t) {
    return IsoRectangle2(r.r.transform(t.t));
    }, py::arg("t"));


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
               std::to_string(wp2_weight(wp)) + ")";})
    .def("transform", [](const WeightedPoint2& wp, const AffTransformation2& t) {
    return WeightedPoint2(wp.wp.transform(t.t));
    }, py::arg("t"));


    // --- AffTransformation2 ---
py::class_<AffTransformation2>(m, "AffTransformation2")
    // Identity
    .def(py::init<>())
    // Translation from vector
    .def(py::init<const Vector2&>(),         py::arg("v"))
    // Scaling from scalar
    .def(py::init<double>(),                 py::arg("s"))
    // Reflection from line
    .def(py::init<const Line2&>(),           py::arg("l"))
    // Rotation from sine/cosine
    .def(py::init<double, double>(),         py::arg("sine"), py::arg("cosine"))
    // General affine with translation
    .def(py::init<double, double, double,
                  double, double, double>(),
         py::arg("m00"), py::arg("m01"), py::arg("m02"),
         py::arg("m10"), py::arg("m11"), py::arg("m12"))
    // General linear no translation
    .def(py::init<double, double,
                  double, double>(),
         py::arg("m00"), py::arg("m01"),
         py::arg("m10"), py::arg("m11"))
    // Transform operations
    .def("transform_point",     &aff2_transform_point,     py::arg("p"))
    .def("transform_vector",    &aff2_transform_vector,    py::arg("v"))
    .def("transform_direction", &aff2_transform_direction, py::arg("d"))
    .def("transform_line",      &aff2_transform_line,      py::arg("l"))
    // Call operators
    .def("__call__", &aff2_transform_point,     py::arg("p"))
    // Miscellaneous
    .def("inverse",         &aff2_inverse)
    .def("is_even",         &aff2_is_even)
    .def("is_odd",          &aff2_is_odd)
    .def("is_scaling",      &aff2_is_scaling)
    .def("is_translation",  &aff2_is_translation)
    .def("is_rotation",     &aff2_is_rotation)
    .def("is_reflection",   &aff2_is_reflection)
    .def("cartesian",       &aff2_cartesian,   py::arg("i"), py::arg("j"))
    .def("homogeneous",     &aff2_homogeneous, py::arg("i"), py::arg("j"))
    .def("__mul__",         &aff2_mul)
    .def("__eq__",          &aff2_eq)
    .def("__repr__", [](const AffTransformation2& t) {
        return "AffTransformation2(m00=" + std::to_string(aff2_cartesian(t, 0, 0)) +
               ", m01=" + std::to_string(aff2_cartesian(t, 0, 1)) +
               ", m10=" + std::to_string(aff2_cartesian(t, 1, 0)) +
               ", m11=" + std::to_string(aff2_cartesian(t, 1, 1)) + ")";
    });




// --- Bbox3 ---
py::class_<Bbox3>(m, "Bbox3")
    .def(py::init<>())
    .def(py::init<double, double, double, double, double, double>(),
         py::arg("xmin"), py::arg("ymin"), py::arg("zmin"),
         py::arg("xmax"), py::arg("ymax"), py::arg("zmax"))
    .def_property_readonly("xmin", &Bbox3::xmin)
    .def_property_readonly("ymin", &Bbox3::ymin)
    .def_property_readonly("zmin", &Bbox3::zmin)
    .def_property_readonly("xmax", &Bbox3::xmax)
    .def_property_readonly("ymax", &Bbox3::ymax)
    .def_property_readonly("zmax", &Bbox3::zmax)
    .def("__repr__", [](const Bbox3& b) {
        return "Bbox3(" + std::to_string(b.xmin()) + ", " +
                          std::to_string(b.ymin()) + ", " +
                          std::to_string(b.zmin()) + ", " +
                          std::to_string(b.xmax()) + ", " +
                          std::to_string(b.ymax()) + ", " +
                          std::to_string(b.zmax()) + ")";
    });

// --- Point3 ---
py::class_<Point3>(m, "Point3")
    .def(py::init<>())
    .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
    .def(py::init<int, int, int>(),          py::arg("x"), py::arg("y"), py::arg("z"))
    .def_property_readonly("x",  &Point3::x)
    .def_property_readonly("y",  &Point3::y)
    .def_property_readonly("z",  &Point3::z)
    .def_property_readonly("hx", &Point3::hx)
    .def_property_readonly("hy", &Point3::hy)
    .def_property_readonly("hz", &Point3::hz)
    .def_property_readonly("hw", &Point3::hw)
    .def("cartesian",   &Point3::cartesian,   py::arg("i"))
    .def("homogeneous", &Point3::homogeneous, py::arg("i"))
    .def("dimension",   &Point3::dimension)
    .def("bbox",        &point3_bbox)
    .def("__getitem__", &Point3::operator[],  py::arg("i"))
    .def("__sub__",     &point3_sub)
    .def("__add__",     &point3_add_vector)
    .def("__sub__",     &point3_sub_vector)
    .def("__iadd__",    &point3_iadd)
    .def("__isub__",    &point3_isub)
    .def("__eq__",      &point3_eq)
    .def("__ne__",      &point3_neq)
    .def("__lt__",      &point3_lt)
    .def("__gt__",      &point3_gt)
    .def("__le__",      &point3_le)
    .def("__ge__",      &point3_ge)
    .def("transform", [](const Point3& p, const AffTransformation3& t) {
    return aff3_transform_point(t, p);
    }, py::arg("t"))
    .def("__repr__", [](const Point3& p) {
        return "Point3(" + std::to_string(p.x()) + ", " +
                           std::to_string(p.y()) + ", " +
                           std::to_string(p.z()) + ")";
    });

// --- Vector3 ---
py::class_<Vector3>(m, "Vector3")
        .def(py::init<>())                              // NULL_VECTOR
    .def(py::init(&vector3_from_points),
         py::arg("a"), py::arg("b"))               // from two points
    .def("squared_length", &vector3_squared_length)
    .def("__truediv__",    &vector3_div,    py::arg("scalar"))
    .def("__mul__",        &vector3_dot,    py::arg("w"))      // dot product
    .def("__eq__",         &vector3_eq)
    .def("__ne__",         &vector3_neq)
    .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
    .def(py::init<int, int, int>(),          py::arg("x"), py::arg("y"), py::arg("z"))
    .def_property_readonly("x",  &Vector3::x)
    .def_property_readonly("y",  &Vector3::y)
    .def_property_readonly("z",  &Vector3::z)
    .def_property_readonly("hx", &Vector3::hx)
    .def_property_readonly("hy", &Vector3::hy)
    .def_property_readonly("hz", &Vector3::hz)
    .def_property_readonly("hw", &Vector3::hw)
    .def("cartesian",   &Vector3::cartesian,   py::arg("i"))
    .def("homogeneous", &Vector3::homogeneous, py::arg("i"))
    .def("dimension",   &Vector3::dimension)
    .def("__getitem__", &Vector3::operator[],  py::arg("i"))
    .def("__add__",     &vector3_add)
    .def("__sub__",     &vector3_sub)
    .def("__mul__",     &vector3_mul)
    .def("__rmul__",    &vector3_mul)
    .def("__neg__",     &vector3_neg)
    .def("direction", [](const Vector3& v) {
    return Direction3(CGALDirection3(v.v));
    })
    .def("transform", [](const Vector3& v, const AffTransformation3& t) {
    return aff3_transform_vector(t, v);
    }, py::arg("t"))
    .def("__repr__", [](const Vector3& v) {
        return "Vector3(" + std::to_string(v.x()) + ", " +
                            std::to_string(v.y()) + ", " +
                            std::to_string(v.z()) + ")";
    });


    // --- Direction3 ---
py::class_<Direction3>(m, "Direction3")
    .def(py::init<double, double, double>(),
         py::arg("x"), py::arg("y"), py::arg("z"))
    .def(py::init(&direction3_from_vector), py::arg("v"))
    .def(py::init(&direction3_from_segment), py::arg("s"))
    .def(py::init(&direction3_from_line), py::arg("l"))
    .def(py::init(&direction3_from_ray), py::arg("r"))
    .def_property_readonly("dx",    &Direction3::dx)
    .def_property_readonly("dy",    &Direction3::dy)
    .def_property_readonly("dz",    &Direction3::dz)
    .def("delta",                   &Direction3::delta,  py::arg("i"))
    .def("vector",                  &direction3_vector)
    .def("opposite",                &direction3_opposite)
    .def("__neg__",                 &direction3_opposite)
    .def("__eq__",                  &direction3_eq)
    .def("__ne__",                  &direction3_neq)
    .def("transform", [](const Direction3& d, const AffTransformation3& t) {
    return aff3_transform_direction(t, d);
    }, py::arg("t"))
    .def("__repr__", [](const Direction3& d) {
        return "Direction3(" + std::to_string(d.dx()) + ", " +
                               std::to_string(d.dy()) + ", " +
                               std::to_string(d.dz()) + ")";
    });


// --- Line3 stub (full version comes later) ---
// py::class_<Line3>(m, "Line3")
//     .def("__repr__", [](const Line3&) {
//         return "Line3()";
//     });

// // --- Plane3 stub (full version comes later) ---
// py::class_<Plane3>(m, "Plane3")
//     .def("__repr__", [](const Plane3&) {
//         return "Plane3()";
//     });



// --- Plane3 ---
py::class_<Plane3>(m, "Plane3")
    .def(py::init<double, double, double, double>(),
         py::arg("a"), py::arg("b"), py::arg("c"), py::arg("d"))
    .def(py::init<const Point3&, const Point3&, const Point3&>(),
         py::arg("p"), py::arg("q"), py::arg("r"))
    .def(py::init<const Point3&, const Vector3&>(),
         py::arg("p"), py::arg("v"))
    .def(py::init<const Point3&, const Direction3&>(),
         py::arg("p"), py::arg("d"))
    .def(py::init<const Line3&, const Point3&>(),
         py::arg("l"), py::arg("p"))
    // .def(py::init<const Ray3&, const Point3&>(),
    //      py::arg("r"), py::arg("p"))
    // .def(py::init<const Segment3&, const Point3&>(),
    //      py::arg("s"), py::arg("p"))
    .def_static("from_ray",     &plane3_from_ray,     py::arg("r"), py::arg("p"))
    .def_static("from_segment", &plane3_from_segment, py::arg("s"), py::arg("p"))
    .def_property_readonly("a", &Plane3::a)
    .def_property_readonly("b", &Plane3::b)
    .def_property_readonly("c", &Plane3::c)
    .def_property_readonly("d", &Plane3::d)
    .def("has_on_circle", &plane3_has_on_circle, py::arg("c"))
    .def("perpendicular_line",   &plane3_perpendicular_line,   py::arg("p"))
    .def("projection",           &plane3_projection,           py::arg("p"))
    .def("opposite",             &plane3_opposite)
    .def("point",                &plane3_point)
    .def("orthogonal_vector",    &plane3_orthogonal_vector)
    .def("orthogonal_direction", &plane3_orthogonal_direction)
    .def("base1",                &plane3_base1)
    .def("base2",                &plane3_base2)
    .def("to_2d",                &plane3_to_2d,                py::arg("p"))
    .def("to_3d",                &plane3_to_3d,                py::arg("p"))
    .def("oriented_side",        &plane3_oriented_side,        py::arg("p"))
    .def("has_on",               &plane3_has_on_point,         py::arg("p"))
    .def("has_on_line",          &plane3_has_on_line,          py::arg("l"))
    .def("has_on_positive_side", &plane3_has_on_positive_side, py::arg("p"))
    .def("has_on_negative_side", &plane3_has_on_negative_side, py::arg("p"))
    .def("is_degenerate",        &plane3_is_degenerate)
    .def("__eq__",               &plane3_eq)
    .def("__ne__",               &plane3_neq)
    .def("transform", [](const Plane3& p, const AffTransformation3& t) {
    return aff3_transform_plane(t, p);
    }, py::arg("t"))
    .def("__repr__", [](const Plane3& h) {
        return "Plane3(a=" + std::to_string(h.a()) +
               ", b=" + std::to_string(h.b()) +
               ", c=" + std::to_string(h.c()) +
               ", d=" + std::to_string(h.d()) + ")";
    });

// --- Line3 ---
py::class_<Line3>(m, "Line3")
    .def(py::init<const Point3&, const Point3&>(),
         py::arg("p"), py::arg("q"))
    .def(py::init<const Point3&, const Direction3&>(),
         py::arg("p"), py::arg("d"))
    .def(py::init<const Point3&, const Vector3&>(),
         py::arg("p"), py::arg("v"))
    .def(py::init<const Segment3&>(),
         py::arg("s"))
    // .def("from_ray", &line3_from_ray, py::arg("r"))
    .def_static("from_ray", &line3_from_ray, py::arg("r"))
    .def("projection",          &line3_projection,          py::arg("p"))
    .def("point",               &line3_point,               py::arg("i"))
    .def("is_degenerate",       &line3_is_degenerate)
    .def("has_on",              &line3_has_on,              py::arg("p"))
    .def("perpendicular_plane", &line3_perpendicular_plane, py::arg("p"))
    .def("opposite",            &line3_opposite)
    .def("to_vector",           &line3_to_vector)
    .def("direction",           &line3_direction)
    .def("__eq__",              &line3_eq)
    .def("__ne__",              &line3_neq)
    .def("transform", [](const Line3& l, const AffTransformation3& t) {
    return Line3(l.l.transform(t.t));
    }, py::arg("t"))
    .def("__repr__", [](const Line3& l) {
        auto v = line3_to_vector(l);
        return "Line3(direction=(" + std::to_string(v.x()) + ", " +
                                     std::to_string(v.y()) + ", " +
                                     std::to_string(v.z()) + "))";
    });

// --- Segment3 ---
py::class_<Segment3>(m, "Segment3")
    .def(py::init<const Point3&, const Point3&>(),
         py::arg("p"), py::arg("q"))
    .def("source",          &segment3_source)
    .def("target",          &segment3_target)
    .def("min",             &segment3_min)
    .def("max",             &segment3_max)
    .def("vertex",          &segment3_vertex,       py::arg("i"))
    .def("point",           &segment3_point,        py::arg("i"))
    .def("__getitem__",     &segment3_vertex,       py::arg("i"))
    .def("squared_length",  &segment3_squared_length)
    .def("to_vector",       &segment3_to_vector)
    .def("direction",       &segment3_direction)
    .def("opposite",        &segment3_opposite)
    .def("supporting_line", &segment3_supporting_line)
    .def("is_degenerate",   &segment3_is_degenerate)
    .def("has_on",          &segment3_has_on,       py::arg("p"))
    .def("bbox",            &segment3_bbox)
    .def("__eq__",          &segment3_eq)
    .def("__ne__",          &segment3_neq)
    .def("transform", [](const Segment3& s, const AffTransformation3& t) {
    return Segment3(s.s.transform(t.t));
    }, py::arg("t"))
    .def("__repr__", [](const Segment3& s) {
        auto src = segment3_source(s);
        auto tgt = segment3_target(s);
        return "Segment3((" + std::to_string(src.x()) + ", " +
                               std::to_string(src.y()) + ", " +
                               std::to_string(src.z()) + "), (" +
                               std::to_string(tgt.x()) + ", " +
                               std::to_string(tgt.y()) + ", " +
                               std::to_string(tgt.z()) + "))";
    });


// --- Ray3 ---
py::class_<Ray3>(m, "Ray3")
    .def(py::init<const Point3&, const Point3&>(),
         py::arg("p"), py::arg("q"))
    .def(py::init<const Point3&, const Direction3&>(),
         py::arg("p"), py::arg("d"))
    .def(py::init<const Point3&, const Vector3&>(),
         py::arg("p"), py::arg("v"))
    .def(py::init<const Point3&, const Line3&>(),
         py::arg("p"), py::arg("l"))
    .def("source",          &ray3_source)
    .def("point",           &ray3_point,          py::arg("i"))
    .def("direction",       &ray3_direction)
    .def("to_vector",       &ray3_to_vector)
    .def("supporting_line", &ray3_supporting_line)
    .def("opposite",        &ray3_opposite)
    .def("is_degenerate",   &ray3_is_degenerate)
    .def("has_on",          &ray3_has_on,         py::arg("p"))
    .def("__eq__",          &ray3_eq)
    .def("__ne__",          &ray3_neq)
    .def("transform", [](const Ray3& r, const AffTransformation3& t) {
    return Ray3(r.r.transform(t.t));
    }, py::arg("t"))
    .def("__repr__", [](const Ray3& r) {
        auto s = ray3_source(r);
        auto d = ray3_direction(r);
        return "Ray3(source=(" + std::to_string(s.x()) + ", " +
                                  std::to_string(s.y()) + ", " +
                                  std::to_string(s.z()) + "), direction=(" +
                                  std::to_string(d.dx()) + ", " +
                                  std::to_string(d.dy()) + ", " +
                                  std::to_string(d.dz()) + "))";
    });



// --- Triangle3 ---
py::class_<Triangle3>(m, "Triangle3")
    .def(py::init<const Point3&, const Point3&, const Point3&>(),
         py::arg("p"), py::arg("q"), py::arg("r"))
    .def("vertex",           &triangle3_vertex,          py::arg("i"))
    .def("__getitem__",      &triangle3_vertex,          py::arg("i"))
    .def("supporting_plane", &triangle3_supporting_plane)
    .def("is_degenerate",    &triangle3_is_degenerate)
    .def("has_on",           &triangle3_has_on,          py::arg("p"))
    .def("squared_area",     &triangle3_squared_area)
    .def("bbox",             &triangle3_bbox)
    .def("__eq__",           &triangle3_eq)
    .def("__ne__",           &triangle3_neq)
    .def("transform", [](const Triangle3& tri, const AffTransformation3& t) {
    return Triangle3(tri.t.transform(t.t));
    }, py::arg("t"))
    .def("__repr__", [](const Triangle3& t) {
        auto p = triangle3_vertex(t, 0);
        auto q = triangle3_vertex(t, 1);
        auto r = triangle3_vertex(t, 2);
        return "Triangle3((" + std::to_string(p.x()) + ", " +
                                std::to_string(p.y()) + ", " +
                                std::to_string(p.z()) + "), (" +
                                std::to_string(q.x()) + ", " +
                                std::to_string(q.y()) + ", " +
                                std::to_string(q.z()) + "), (" +
                                std::to_string(r.x()) + ", " +
                                std::to_string(r.y()) + ", " +
                                std::to_string(r.z()) + "))";
    });



// --- Sphere3 ---
py::class_<Sphere3>(m, "Sphere3")
    .def(py::init<const Point3&, double, int>(),
         py::arg("center"), py::arg("squared_radius"), py::arg("orientation") = 1)
    .def(py::init<const Point3&, const Point3&,
                  const Point3&, const Point3&>(),
         py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"))
    .def(py::init<const Point3&, const Point3&, const Point3&, int>(),
         py::arg("p"), py::arg("q"), py::arg("r"), py::arg("orientation") = 1)
    .def(py::init<const Point3&, const Point3&, int>(),
         py::arg("p"), py::arg("q"), py::arg("orientation") = 1)
    .def(py::init<const Point3&, int>(),
         py::arg("center"), py::arg("orientation") = 1)
    .def_static("from_circle", &sphere3_from_circle, py::arg("c"))
    .def("has_on_circle",      &sphere3_has_on_circle, py::arg("c"))
    .def("center",                &sphere3_center)
    .def("squared_radius",        &sphere3_squared_radius)
    .def("orientation",           &sphere3_orientation)
    .def("is_degenerate",         &sphere3_is_degenerate)
    .def("oriented_side",         &sphere3_oriented_side,         py::arg("p"))
    .def("bounded_side",          &sphere3_bounded_side,          py::arg("p"))
    .def("has_on_positive_side",  &sphere3_has_on_positive_side,  py::arg("p"))
    .def("has_on_negative_side",  &sphere3_has_on_negative_side,  py::arg("p"))
    .def("has_on_boundary",       &sphere3_has_on_boundary,       py::arg("p"))
    .def("has_on_bounded_side",   &sphere3_has_on_bounded_side,   py::arg("p"))
    .def("has_on_unbounded_side", &sphere3_has_on_unbounded_side, py::arg("p"))
    .def("has_on",                &sphere3_has_on,                py::arg("p"))
    .def("opposite",              &sphere3_opposite)
    .def("bbox",                  &sphere3_bbox)
    .def("__eq__",                &sphere3_eq)
    .def("__ne__",                &sphere3_neq)
    .def("orthogonal_transform", [](const Sphere3& s, const AffTransformation3& t) {
    return Sphere3(s.s.orthogonal_transform(t.t));
    }, py::arg("t"))
    .def("__repr__", [](const Sphere3& s) {
        auto c = sphere3_center(s);
        return "Sphere3(center=(" + std::to_string(c.x()) + ", " +
                                    std::to_string(c.y()) + ", " +
                                    std::to_string(c.z()) + "), squared_radius=" +
                                    std::to_string(sphere3_squared_radius(s)) + ")";
    });


// --- Tetrahedron3 ---
py::class_<Tetrahedron3>(m, "Tetrahedron3")
    .def(py::init<const Point3&, const Point3&,
                  const Point3&, const Point3&>(),
         py::arg("p0"), py::arg("p1"), py::arg("p2"), py::arg("p3"))
    .def("vertex",                &tetra3_vertex,                py::arg("i"))
    .def("__getitem__",           &tetra3_vertex,                py::arg("i"))
    .def("is_degenerate",         &tetra3_is_degenerate)
    .def("orientation",           &tetra3_orientation)
    .def("oriented_side",         &tetra3_oriented_side,         py::arg("p"))
    .def("bounded_side",          &tetra3_bounded_side,          py::arg("p"))
    .def("has_on_positive_side",  &tetra3_has_on_positive_side,  py::arg("p"))
    .def("has_on_negative_side",  &tetra3_has_on_negative_side,  py::arg("p"))
    .def("has_on_boundary",       &tetra3_has_on_boundary,       py::arg("p"))
    .def("has_on_bounded_side",   &tetra3_has_on_bounded_side,   py::arg("p"))
    .def("has_on_unbounded_side", &tetra3_has_on_unbounded_side, py::arg("p"))
    .def("volume",                &tetra3_volume)
    .def("bbox",                  &tetra3_bbox)
    .def("__eq__",                &tetra3_eq)
    .def("__ne__",                &tetra3_neq)
    .def("__repr__", [](const Tetrahedron3& t) {
        auto p0 = tetra3_vertex(t, 0);
        auto p1 = tetra3_vertex(t, 1);
        auto p2 = tetra3_vertex(t, 2);
        auto p3 = tetra3_vertex(t, 3);
        return "Tetrahedron3((" + std::to_string(p0.x()) + ", " +
                                   std::to_string(p0.y()) + ", " +
                                   std::to_string(p0.z()) + "), (" +
                                   std::to_string(p1.x()) + ", " +
                                   std::to_string(p1.y()) + ", " +
                                   std::to_string(p1.z()) + "), (" +
                                   std::to_string(p2.x()) + ", " +
                                   std::to_string(p2.y()) + ", " +
                                   std::to_string(p2.z()) + "), (" +
                                   std::to_string(p3.x()) + ", " +
                                   std::to_string(p3.y()) + ", " +
                                   std::to_string(p3.z()) + "))";
    });



// --- IsoCuboid3 ---
py::class_<IsoCuboid3>(m, "IsoCuboid3")
    .def(py::init<const Point3&, const Point3&>(),
         py::arg("p"), py::arg("q"))
    .def(py::init<const Point3&, const Point3&, const Point3&,
                  const Point3&, const Point3&, const Point3&>(),
         py::arg("left"), py::arg("right"), py::arg("bottom"),
         py::arg("top"),  py::arg("far"),   py::arg("close"))
    .def(py::init<double, double, double, double, double, double>(),
         py::arg("min_x"), py::arg("min_y"), py::arg("min_z"),
         py::arg("max_x"), py::arg("max_y"), py::arg("max_z"))
    .def(py::init<const Bbox3&>(), py::arg("bbox"))
    .def("vertex",                &iso_cuboid3_vertex,                py::arg("i"))
    .def("__getitem__",           &iso_cuboid3_vertex,                py::arg("i"))
    .def("min",                   &iso_cuboid3_min)
    .def("max",                   &iso_cuboid3_max)
    .def("xmin",                  &iso_cuboid3_xmin)
    .def("ymin",                  &iso_cuboid3_ymin)
    .def("zmin",                  &iso_cuboid3_zmin)
    .def("xmax",                  &iso_cuboid3_xmax)
    .def("ymax",                  &iso_cuboid3_ymax)
    .def("zmax",                  &iso_cuboid3_zmax)
    .def("min_coord",             &iso_cuboid3_min_coord,             py::arg("i"))
    .def("max_coord",             &iso_cuboid3_max_coord,             py::arg("i"))
    .def("is_degenerate",         &iso_cuboid3_is_degenerate)
    .def("bounded_side",          &iso_cuboid3_bounded_side,          py::arg("p"))
    .def("has_on_boundary",       &iso_cuboid3_has_on_boundary,       py::arg("p"))
    .def("has_on_bounded_side",   &iso_cuboid3_has_on_bounded_side,   py::arg("p"))
    .def("has_on_unbounded_side", &iso_cuboid3_has_on_unbounded_side, py::arg("p"))
    .def("volume",                &iso_cuboid3_volume)
    .def("bbox",                  &iso_cuboid3_bbox)
    .def("__eq__",                &iso_cuboid3_eq)
    .def("__ne__",                &iso_cuboid3_neq)
    .def("transform", [](const IsoCuboid3& c, const AffTransformation3& t) {
    return IsoCuboid3(c.c.transform(t.t));
    }, py::arg("t"))
    .def("__repr__", [](const IsoCuboid3& c) {
        return "IsoCuboid3(xmin=" + std::to_string(iso_cuboid3_xmin(c)) +
               ", ymin=" + std::to_string(iso_cuboid3_ymin(c)) +
               ", zmin=" + std::to_string(iso_cuboid3_zmin(c)) +
               ", xmax=" + std::to_string(iso_cuboid3_xmax(c)) +
               ", ymax=" + std::to_string(iso_cuboid3_ymax(c)) +
               ", zmax=" + std::to_string(iso_cuboid3_zmax(c)) + ")";
    });


    // --- Circle3 ---
py::class_<Circle3>(m, "Circle3")
    .def(py::init<const Point3&, double, const Plane3&>(),
         py::arg("center"), py::arg("sq_r"), py::arg("plane"))
    .def(py::init<const Point3&, double, const Vector3&>(),
         py::arg("center"), py::arg("sq_r"), py::arg("n"))
    .def(py::init<const Point3&, const Point3&, const Point3&>(),
         py::arg("p"), py::arg("q"), py::arg("r"))
    .def(py::init<const Sphere3&, const Sphere3&>(),
         py::arg("s1"), py::arg("s2"))
    .def(py::init<const Sphere3&, const Plane3&>(),
         py::arg("s"), py::arg("plane"))
    .def(py::init<const Plane3&, const Sphere3&>(),
         py::arg("plane"), py::arg("s"))
    .def("center",                              &circle3_center)
    .def("squared_radius",                      &circle3_squared_radius)
    .def("supporting_plane",                    &circle3_supporting_plane)
    .def("diametral_sphere",                    &circle3_diametral_sphere)
    .def("area_divided_by_pi",                  &circle3_area_divided_by_pi)
    .def("approximate_area",                    &circle3_approximate_area)
    .def("squared_length_divided_by_pi_square", &circle3_squared_length_divided_by_pi_square)
    .def("approximate_squared_length",          &circle3_approximate_squared_length)
    .def("has_on",                              &circle3_has_on, py::arg("p"))
    .def("bbox",                                &circle3_bbox)
    .def("__eq__",                              &circle3_eq)
    .def("__ne__",                              &circle3_neq)
    .def("__repr__", [](const Circle3& c) {
        auto ct = circle3_center(c);
        return "Circle3(center=(" + std::to_string(ct.x()) + ", " +
                                    std::to_string(ct.y()) + ", " +
                                    std::to_string(ct.z()) + "), squared_radius=" +
                                    std::to_string(circle3_squared_radius(c)) + ")";
    });





// --- WeightedPoint3 ---
py::class_<WeightedPoint3>(m, "WeightedPoint3")
    .def(py::init<>())
    .def(py::init<const Point3&>(),         py::arg("p"))
    .def(py::init<const Point3&, double>(), py::arg("p"), py::arg("w"))
    .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
    .def("point",  &wp3_point)
    .def("weight", &wp3_weight)
    .def("__eq__", &wp3_eq)
    .def("__ne__", &wp3_neq)
    .def("__repr__", [](const WeightedPoint3& wp) {
        auto p = wp3_point(wp);
        return "WeightedPoint3(point=(" +
               std::to_string(p.x()) + ", " +
               std::to_string(p.y()) + ", " +
               std::to_string(p.z()) + "), weight=" +
               std::to_string(wp3_weight(wp)) + ")";
    });




// --- AffTransformation3 ---
py::class_<AffTransformation3>(m, "AffTransformation3")
    // Identity
    .def(py::init<>())
    // Translation from vector
    .def(py::init<const Vector3&>(),         py::arg("v"))
    // Scaling from scalar
    .def(py::init<double>(),                 py::arg("s"))
    // General affine with translation (12 params)
    .def(py::init<double, double, double, double,
                  double, double, double, double,
                  double, double, double, double>(),
         py::arg("m00"), py::arg("m01"), py::arg("m02"), py::arg("m03"),
         py::arg("m10"), py::arg("m11"), py::arg("m12"), py::arg("m13"),
         py::arg("m20"), py::arg("m21"), py::arg("m22"), py::arg("m23"))
    // General linear no translation (9 params)
    .def(py::init<double, double, double,
                  double, double, double,
                  double, double, double>(),
         py::arg("m00"), py::arg("m01"), py::arg("m02"),
         py::arg("m10"), py::arg("m11"), py::arg("m12"),
         py::arg("m20"), py::arg("m21"), py::arg("m22"))
    .def("transform_point",     &aff3_transform_point,     py::arg("p"))
    .def("transform_vector",    &aff3_transform_vector,    py::arg("v"))
    .def("transform_direction", &aff3_transform_direction, py::arg("d"))
    .def("transform_plane",     &aff3_transform_plane,     py::arg("p"))
    .def("__call__",            &aff3_transform_point,     py::arg("p"))
    .def("inverse",             &aff3_inverse)
    .def("is_even",             &aff3_is_even)
    .def("is_odd",              &aff3_is_odd)
    .def("is_scaling",          &aff3_is_scaling)
    .def("is_translation",      &aff3_is_translation)
    .def("cartesian",           &aff3_cartesian,   py::arg("i"), py::arg("j"))
    .def("homogeneous",         &aff3_homogeneous, py::arg("i"), py::arg("j"))
    .def("__mul__",             &aff3_mul)
    .def("__eq__",              &aff3_eq)
    .def("__repr__", [](const AffTransformation3& t) {
        return "AffTransformation3(m00=" + std::to_string(aff3_cartesian(t, 0, 0)) +
               ", m11=" + std::to_string(aff3_cartesian(t, 1, 1)) +
               ", m22=" + std::to_string(aff3_cartesian(t, 2, 2)) + ")";
    });


// // ============================================================
// // --- Constants and Enumerations ---
// // ============================================================

// // --- Angle ---
// py::enum_<CGAL::Angle>(m, "Angle")
//     .value("OBTUSE", CGAL::OBTUSE)
//     .value("RIGHT",  CGAL::RIGHT)
//     .value("ACUTE",  CGAL::ACUTE)
//     .export_values();

// // --- Bounded_side ---
// py::enum_<CGAL::Bounded_side>(m, "BoundedSide")
//     .value("ON_UNBOUNDED_SIDE", CGAL::ON_UNBOUNDED_SIDE)
//     .value("ON_BOUNDARY",       CGAL::ON_BOUNDARY)
//     .value("ON_BOUNDED_SIDE",   CGAL::ON_BOUNDED_SIDE)
//     .export_values();

// // --- Comparison_result ---
// py::enum_<CGAL::Comparison_result>(m, "ComparisonResult")
//     .value("SMALLER", CGAL::SMALLER)
//     .value("EQUAL",   CGAL::EQUAL)
//     .value("LARGER",  CGAL::LARGER)
//     .export_values();

// // --- Sign ---
// // py::enum_<CGAL::Sign>(m, "CGALSign")
// //     .value("NEGATIVE", CGAL::NEGATIVE)
// //     .value("ZERO",     CGAL::ZERO)
// //     .value("POSITIVE", CGAL::POSITIVE)
// //     .export_values();

// // --- Orientation (typedef of Sign) ---
// // py::enum_<CGAL::Orientation>(m, "Orientation")
// //     .value("CLOCKWISE",        CGAL::CLOCKWISE)
// //     .value("COUNTERCLOCKWISE", CGAL::COUNTERCLOCKWISE)
// //     .value("COLLINEAR",        CGAL::COLLINEAR)
// //     .value("COPLANAR",         CGAL::COPLANAR)
// //     .value("DEGENERATE",       CGAL::DEGENERATE)
// //     .export_values();

// // Orientation / Sign constants as plain ints
// m.attr("NEGATIVE")         = py::int_(-1);
// m.attr("ZERO")             = py::int_(0);
// m.attr("POSITIVE")         = py::int_(1);
// m.attr("CLOCKWISE")        = py::int_(-1);
// m.attr("COUNTERCLOCKWISE") = py::int_(1);
// m.attr("LEFT_TURN")        = py::int_(1);
// m.attr("RIGHT_TURN")       = py::int_(-1);
// m.attr("COLLINEAR")        = py::int_(0);
// m.attr("COPLANAR")         = py::int_(0);
// m.attr("DEGENERATE")       = py::int_(0);

// // --- Oriented_side ---
// py::enum_<CGAL::Oriented_side>(m, "OrientedSide")
//     .value("ON_NEGATIVE_SIDE",     CGAL::ON_NEGATIVE_SIDE)
//     .value("ON_ORIENTED_BOUNDARY", CGAL::ON_ORIENTED_BOUNDARY)
//     .value("ON_POSITIVE_SIDE",     CGAL::ON_POSITIVE_SIDE)
//     .export_values();

// // --- Orientation aliases as module constants ---
// m.attr("LEFT_TURN")        = py::cast(CGAL::LEFT_TURN);
// m.attr("RIGHT_TURN")       = py::cast(CGAL::RIGHT_TURN);
// m.attr("CLOCKWISE")        = py::cast(CGAL::CLOCKWISE);
// m.attr("COUNTERCLOCKWISE") = py::cast(CGAL::COUNTERCLOCKWISE);
// m.attr("COLLINEAR")        = py::cast(CGAL::COLLINEAR);
// m.attr("COPLANAR")         = py::cast(CGAL::COPLANAR);
// m.attr("DEGENERATE")       = py::cast(CGAL::DEGENERATE);

// // --- Symbolic constants ---
// m.attr("ORIGIN")       = Point2(0.0, 0.0);
// m.attr("ORIGIN3")      = Point3(0.0, 0.0, 0.0);
// m.attr("NULL_VECTOR")  = Vector2(0.0, 0.0);
// m.attr("NULL_VECTOR3") = Vector3(0.0, 0.0, 0.0);

// // --- opposite() for Oriented_side and Bounded_side ---
// m.def("opposite", [](CGAL::Oriented_side o) {
//     return CGAL::opposite(o);
// }, py::arg("o"), "Returns the opposite oriented side");

// m.def("opposite", [](CGAL::Bounded_side o) {
//     return CGAL::opposite(o);
// }, py::arg("o"), "Returns the opposite bounded side");


// ============================================================
// --- Constants and Enumerations ---
// ============================================================

// Angle
m.attr("ACUTE")  = py::int_(1);
m.attr("RIGHT")  = py::int_(0);
m.attr("OBTUSE") = py::int_(-1);

// Bounded_side
m.attr("ON_BOUNDED_SIDE")   = py::int_(1);
m.attr("ON_BOUNDARY")       = py::int_(0);
m.attr("ON_UNBOUNDED_SIDE") = py::int_(-1);

// Comparison_result
m.attr("SMALLER") = py::int_(-1);
m.attr("EQUAL")   = py::int_(0);
m.attr("LARGER")  = py::int_(1);

// Sign / Orientation
m.attr("NEGATIVE")         = py::int_(-1);
m.attr("ZERO")             = py::int_(0);
m.attr("POSITIVE")         = py::int_(1);
m.attr("CLOCKWISE")        = py::int_(-1);
m.attr("COUNTERCLOCKWISE") = py::int_(1);
m.attr("LEFT_TURN")        = py::int_(1);
m.attr("RIGHT_TURN")       = py::int_(-1);
m.attr("COLLINEAR")        = py::int_(0);
m.attr("COPLANAR")         = py::int_(0);
m.attr("DEGENERATE")       = py::int_(0);

// Oriented_side
m.attr("ON_NEGATIVE_SIDE")     = py::int_(-1);
m.attr("ON_ORIENTED_BOUNDARY") = py::int_(0);
m.attr("ON_POSITIVE_SIDE")     = py::int_(1);

// Symbolic constants
m.attr("ORIGIN")       = Point2(0.0, 0.0);
m.attr("ORIGIN3")      = Point3(0.0, 0.0, 0.0);
m.attr("NULL_VECTOR")  = Vector2(0.0, 0.0);
m.attr("NULL_VECTOR3") = Vector3(0.0, 0.0, 0.0);


// ============================================================
// --- Global Functions ---
// ============================================================

// --- angle ---
// Returns: 1=ACUTE, 0=RIGHT, -1=OBTUSE
m.def("angle", &angle_vec2_vec2,
      py::arg("u"), py::arg("v"),
      "Angle between two 2D vectors. Returns 1=ACUTE, 0=RIGHT, -1=OBTUSE");

m.def("angle", &angle_pt2_pt2_pt2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Angle at vertex q formed by 2D points p,q,r");

m.def("angle", &angle_pt2_pt2_pt2_pt2,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "Angle between 2D vectors pq and rs");

m.def("angle", &angle_vec3_vec3,
      py::arg("u"), py::arg("v"),
      "Angle between two 3D vectors");

m.def("angle", &angle_pt3_pt3_pt3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Angle at vertex q formed by 3D points p,q,r");

m.def("angle", &angle_pt3_pt3_pt3_pt3,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "Angle between 3D vectors pq and rs");

m.def("angle", &angle_pt3_pt3_pt3_vec3,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("v"),
      "Angle between normal of triangle pqr and vector v");

// --- approximate_angle ---
m.def("approximate_angle", &approximate_angle_pt3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Approximation of angle between p-q and r-q in degrees");

m.def("approximate_angle", &approximate_angle_vec3,
      py::arg("u"), py::arg("v"),
      "Approximation of angle between vectors u and v in degrees");

// --- approximate_dihedral_angle ---
m.def("approximate_dihedral_angle", &approximate_dihedral_angle,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "Approximation of signed dihedral angle in tetrahedron pqrs of edge pq in degrees");

// --- are_ordered_along_line ---
m.def("are_ordered_along_line", &are_ordered_along_line_2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff 2D points are collinear and q is between p and r (inclusive)");

m.def("are_ordered_along_line", &are_ordered_along_line_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff 3D points are collinear and q is between p and r (inclusive)");

// --- are_strictly_ordered_along_line ---
m.def("are_strictly_ordered_along_line", &are_strictly_ordered_along_line_2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff 2D points are collinear and q lies strictly between p and r");

m.def("are_strictly_ordered_along_line", &are_strictly_ordered_along_line_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff 3D points are collinear and q lies strictly between p and r");


// --- area ---
m.def("area", &area_2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Signed area of triangle defined by 2D points p, q, r");

// --- barycenter 2D ---
m.def("barycenter", &barycenter_2_2,
      py::arg("p1"), py::arg("w1"), py::arg("p2"),
      "Barycenter of p1,p2 with weights w1 and 1-w1");
m.def("barycenter", &barycenter_2_22,
      py::arg("p1"), py::arg("w1"), py::arg("p2"), py::arg("w2"),
      "Barycenter of p1,p2 with weights w1,w2");
m.def("barycenter", &barycenter_2_3,
      py::arg("p1"), py::arg("w1"), py::arg("p2"), py::arg("w2"), py::arg("p3"),
      "Barycenter of p1,p2,p3 with weights w1,w2 and 1-w1-w2");
m.def("barycenter", &barycenter_2_33,
      py::arg("p1"), py::arg("w1"), py::arg("p2"), py::arg("w2"),
      py::arg("p3"), py::arg("w3"),
      "Barycenter of p1,p2,p3 with weights w1,w2,w3");
m.def("barycenter", &barycenter_2_4,
      py::arg("p1"), py::arg("w1"), py::arg("p2"), py::arg("w2"),
      py::arg("p3"), py::arg("w3"), py::arg("p4"),
      "Barycenter of p1,p2,p3,p4 with weights w1,w2,w3 and 1-w1-w2-w3");
m.def("barycenter", &barycenter_2_44,
      py::arg("p1"), py::arg("w1"), py::arg("p2"), py::arg("w2"),
      py::arg("p3"), py::arg("w3"), py::arg("p4"), py::arg("w4"),
      "Barycenter of p1,p2,p3,p4 with weights w1,w2,w3,w4");

// --- barycenter 3D ---
m.def("barycenter", &barycenter_3_2,
      py::arg("p1"), py::arg("w1"), py::arg("p2"),
      "3D barycenter of p1,p2 with weights w1 and 1-w1");
m.def("barycenter", &barycenter_3_22,
      py::arg("p1"), py::arg("w1"), py::arg("p2"), py::arg("w2"),
      "3D barycenter of p1,p2 with weights w1,w2");
m.def("barycenter", &barycenter_3_3,
      py::arg("p1"), py::arg("w1"), py::arg("p2"), py::arg("w2"), py::arg("p3"),
      "3D barycenter of p1,p2,p3 with weights w1,w2 and 1-w1-w2");
m.def("barycenter", &barycenter_3_33,
      py::arg("p1"), py::arg("w1"), py::arg("p2"), py::arg("w2"),
      py::arg("p3"), py::arg("w3"),
      "3D barycenter of p1,p2,p3 with weights w1,w2,w3");
m.def("barycenter", &barycenter_3_4,
      py::arg("p1"), py::arg("w1"), py::arg("p2"), py::arg("w2"),
      py::arg("p3"), py::arg("w3"), py::arg("p4"),
      "3D barycenter of p1,p2,p3,p4 with weights w1,w2,w3 and 1-w1-w2-w3");
m.def("barycenter", &barycenter_3_44,
      py::arg("p1"), py::arg("w1"), py::arg("p2"), py::arg("w2"),
      py::arg("p3"), py::arg("w3"), py::arg("p4"), py::arg("w4"),
      "3D barycenter of p1,p2,p3,p4 with weights w1,w2,w3,w4");

// --- bisector ---
m.def("bisector", &bisector_pt2,
      py::arg("p"), py::arg("q"),
      "Bisector line of two 2D points");
m.def("bisector", &bisector_ln2,
      py::arg("l1"), py::arg("l2"),
      "Bisector line of two 2D lines");
m.def("bisector", &bisector_pt3,
      py::arg("p"), py::arg("q"),
      "Bisector plane of two 3D points");
m.def("bisector", &bisector_pl3,
      py::arg("h1"), py::arg("h2"),
      "Bisector plane of two planes");

// --- centroid 2D ---
m.def("centroid", &centroid_2_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Centroid of three 2D points");
m.def("centroid", &centroid_2_4,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "Centroid of four 2D points");
m.def("centroid", &centroid_2_tri,
      py::arg("t"),
      "Centroid of a 2D triangle");

// --- centroid 3D ---
m.def("centroid", &centroid_3_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Centroid of three 3D points");
m.def("centroid", &centroid_3_4,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "Centroid of four 3D points");
m.def("centroid", &centroid_3_tri,
      py::arg("t"),
      "Centroid of a 3D triangle");
m.def("centroid", &centroid_3_tet,
      py::arg("t"),
      "Centroid of a tetrahedron");

// --- circumcenter 2D ---
m.def("circumcenter", &circumcenter_2_2,
      py::arg("p"), py::arg("q"),
      "Center of smallest circle through two 2D points");
m.def("circumcenter", &circumcenter_2_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Circumcenter of three 2D points");
m.def("circumcenter", &circumcenter_2_tri,
      py::arg("t"),
      "Circumcenter of a 2D triangle");

// --- circumcenter 3D ---
m.def("circumcenter", &circumcenter_3_2,
      py::arg("p"), py::arg("q"),
      "Center of smallest sphere through two 3D points");
m.def("circumcenter", &circumcenter_3_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Circumcenter of three 3D points");
m.def("circumcenter", &circumcenter_3_4,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "Circumcenter of four 3D points");
m.def("circumcenter", &circumcenter_3_tri,
      py::arg("t"),
      "Circumcenter of a 3D triangle");
m.def("circumcenter", &circumcenter_3_tet,
      py::arg("t"),
      "Circumcenter of a tetrahedron");

// --- collinear ---
m.def("collinear", &collinear_2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff three 2D points are collinear");
m.def("collinear", &collinear_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff three 3D points are collinear");

// --- collinear_are_ordered_along_line ---
m.def("collinear_are_ordered_along_line", &collinear_are_ordered_along_line_2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff q lies between p and r. Precondition: p,q,r are collinear");
m.def("collinear_are_ordered_along_line", &collinear_are_ordered_along_line_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff q lies between p and r. Precondition: p,q,r are collinear");

// --- compare_distance_to_point ---
// Returns: -1=SMALLER(q closer), 1=LARGER(r closer), 0=EQUAL
m.def("compare_distance_to_point", &compare_distance_to_point_2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Compare distances of q and r to p. Returns -1=q closer, 1=r closer, 0=equal");
m.def("compare_distance_to_point", &compare_distance_to_point_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Compare distances of q and r to p. Returns -1=q closer, 1=r closer, 0=equal");

// --- compare_lexicographically ---
// Returns: -1=SMALLER, 0=EQUAL, 1=LARGER
m.def("compare_lexicographically", &compare_lexicographically_2,
      py::arg("p"), py::arg("q"),
      "Compare 2D points lexicographically in xy order. Returns -1, 0, or 1");
m.def("compare_lexicographically", &compare_lexicographically_3,
      py::arg("p"), py::arg("q"),
      "Compare 3D points lexicographically in xyz order. Returns -1, 0, or 1");

// --- compare_signed_distance_to_line ---
m.def("compare_signed_distance_to_line", &compare_signed_distance_to_line_l,
      py::arg("l"), py::arg("p"), py::arg("q"),
      "Compare signed distances of p and q to line l. Returns -1, 0, or 1");
m.def("compare_signed_distance_to_line", &compare_signed_distance_to_line_p,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "Compare signed distances of r and s to line through p and q");

// --- collinear_are_strictly_ordered_along_line ---
m.def("collinear_are_strictly_ordered_along_line",
      &collinear_are_strictly_ordered_along_line_2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff q lies strictly between p and r. Precondition: p,q,r collinear");
m.def("collinear_are_strictly_ordered_along_line",
      &collinear_are_strictly_ordered_along_line_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff q lies strictly between p and r. Precondition: p,q,r collinear");

// --- compare_signed_distance_to_plane ---
m.def("compare_signed_distance_to_plane", &compare_signed_distance_to_plane_h,
      py::arg("h"), py::arg("p"), py::arg("q"),
      "Compare signed distances of p and q to plane h. Returns -1, 0, or 1");
m.def("compare_signed_distance_to_plane", &compare_signed_distance_to_plane_p,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"), py::arg("t"),
      "Compare signed distances of s and t to plane through p,q,r");

// --- compare_slope ---
m.def("compare_slope", &compare_slope_line,
      py::arg("l1"), py::arg("l2"),
      "Compare slopes of two 2D lines. Returns -1, 0, or 1");
m.def("compare_slope", &compare_slope_seg,
      py::arg("s1"), py::arg("s2"),
      "Compare slopes of two 2D segments");
m.def("compare_slope", &compare_slope_pt2,
      py::arg("s1s"), py::arg("s1t"), py::arg("s2s"), py::arg("s2t"),
      "Compare slopes of segments (s1s,s1t) and (s2s,s2t)");
m.def("compare_slope", &compare_slope_pt3,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "Compare slopes of 3D segments (p,q) and (r,s)");

// --- compare_angle ---
m.def("compare_angle", &compare_angle,
      py::arg("a"), py::arg("b"), py::arg("c"), py::arg("cosine"),
      "Compare angle at b in triangle (a,b,c) to angle with given cosine");

// --- compare_dihedral_angle ---
m.def("compare_dihedral_angle", &compare_dihedral_angle_pt,
      py::arg("a1"), py::arg("b1"), py::arg("c1"), py::arg("d1"),
      py::arg("a2"), py::arg("b2"), py::arg("c2"), py::arg("d2"),
      "Compare dihedral angles of two tetrahedra at their respective edges");
m.def("compare_dihedral_angle", &compare_dihedral_angle_pt_cos,
      py::arg("a1"), py::arg("b1"), py::arg("c1"), py::arg("d1"), py::arg("cosine"),
      "Compare dihedral angle of tetrahedron to angle with given cosine");
m.def("compare_dihedral_angle", &compare_dihedral_angle_vec,
      py::arg("u1"), py::arg("v1"), py::arg("w1"),
      py::arg("u2"), py::arg("v2"), py::arg("w2"),
      "Compare dihedral angles between vectorial planes");
m.def("compare_dihedral_angle", &compare_dihedral_angle_vec_cos,
      py::arg("u1"), py::arg("v1"), py::arg("w1"), py::arg("cosine"),
      "Compare dihedral angle between vectorial planes to angle with given cosine");

// --- compare_squared_distance ---
m.def("compare_squared_distance", &compare_squared_distance_2,
      py::arg("p"), py::arg("q"), py::arg("d2"),
      "Compare squared distance of 2D points p,q to d2. Returns -1, 0, or 1");
m.def("compare_squared_distance", &compare_squared_distance_3,
      py::arg("p"), py::arg("q"), py::arg("d2"),
      "Compare squared distance of 3D points p,q to d2");

// --- compare_squared_radius ---
m.def("compare_squared_radius", &compare_squared_radius_1,
      py::arg("p"), py::arg("sr"),
      "Compare squared radius of sphere of radius 0 at p to sr");
m.def("compare_squared_radius", &compare_squared_radius_2,
      py::arg("p"), py::arg("q"), py::arg("sr"),
      "Compare squared radius of sphere through p,q to sr");
m.def("compare_squared_radius", &compare_squared_radius_3,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("sr"),
      "Compare squared radius of sphere through p,q,r to sr");
m.def("compare_squared_radius", &compare_squared_radius_4,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"), py::arg("sr"),
      "Compare squared radius of sphere through p,q,r,s to sr");

// --- compare_x ---
m.def("compare_x", &compare_x_pt2,
      py::arg("p"), py::arg("q"),
      "Compare x-coordinates of two 2D points. Returns -1, 0, or 1");
m.def("compare_x", &compare_x_pt3,
      py::arg("p"), py::arg("q"),
      "Compare x-coordinates of two 3D points");
m.def("compare_x", &compare_x_pt2_l1_l2,
      py::arg("p"), py::arg("l1"), py::arg("l2"),
      "Compare x of p and intersection of l1,l2");
m.def("compare_x", &compare_x_l_h1_h2,
      py::arg("l"), py::arg("h1"), py::arg("h2"),
      "Compare x of intersection of l with h1 and h2");
m.def("compare_x", &compare_x_l1_l2_h1_h2,
      py::arg("l1"), py::arg("l2"), py::arg("h1"), py::arg("h2"),
      "Compare x of intersection of l1,l2 and intersection of h1,h2");

// --- compare_xy ---
m.def("compare_xy", &compare_xy_pt2,
      py::arg("p"), py::arg("q"),
      "Compare 2D points lexicographically in xy order");
m.def("compare_xy", &compare_xy_pt3,
      py::arg("p"), py::arg("q"),
      "Compare 3D points lexicographically in xy order");

// --- compare_xyz ---
m.def("compare_xyz", &compare_xyz_pt3,
      py::arg("p"), py::arg("q"),
      "Compare 3D points lexicographically in xyz order");

// --- compare_x_at_y ---
m.def("compare_x_at_y", &compare_x_at_y_pt_h,
      py::arg("p"), py::arg("h"),
      "Compare x of p and horizontal projection of p on h");
m.def("compare_x_at_y", &compare_x_at_y_pt_h1_h2,
      py::arg("p"), py::arg("h1"), py::arg("h2"),
      "Compare x of horizontal projections of p on h1 and h2");
m.def("compare_x_at_y", &compare_x_at_y_l1_l2_h,
      py::arg("l1"), py::arg("l2"), py::arg("h"),
      "Compare x of intersection of l1,l2 and its projection on h");
m.def("compare_x_at_y", &compare_x_at_y_l1_l2_h1_h2,
      py::arg("l1"), py::arg("l2"), py::arg("h1"), py::arg("h2"),
      "Compare x of projections of intersection of l1,l2 on h1 and h2");

// --- compare_y ---
m.def("compare_y", &compare_y_pt2,
      py::arg("p"), py::arg("q"),
      "Compare y-coordinates of two 2D points");
m.def("compare_y", &compare_y_pt3,
      py::arg("p"), py::arg("q"),
      "Compare y-coordinates of two 3D points");
m.def("compare_y", &compare_y_pt2_l1_l2,
      py::arg("p"), py::arg("l1"), py::arg("l2"),
      "Compare y of p and intersection of l1,l2");
m.def("compare_y", &compare_y_l_h1_h2,
      py::arg("l"), py::arg("h1"), py::arg("h2"),
      "Compare y of intersection of l with h1 and h2");
m.def("compare_y", &compare_y_l1_l2_h1_h2,
      py::arg("l1"), py::arg("l2"), py::arg("h1"), py::arg("h2"),
      "Compare y of intersection of l1,l2 and intersection of h1,h2");

// --- compare_y_at_x ---
m.def("compare_y_at_x", &compare_y_at_x_pt_h,
      py::arg("p"), py::arg("h"),
      "Compare y of p and vertical projection of p on h");
m.def("compare_y_at_x", &compare_y_at_x_pt_h1_h2,
      py::arg("p"), py::arg("h1"), py::arg("h2"),
      "Compare y of vertical projections of p on h1 and h2");
m.def("compare_y_at_x", &compare_y_at_x_l1_l2_h,
      py::arg("l1"), py::arg("l2"), py::arg("h"),
      "Compare y of intersection of l1,l2 and its projection on h");
m.def("compare_y_at_x", &compare_y_at_x_l1_l2_h1_h2,
      py::arg("l1"), py::arg("l2"), py::arg("h1"), py::arg("h2"),
      "Compare y of projections of intersection of l1,l2 on h1 and h2");
m.def("compare_y_at_x", &compare_y_at_x_pt_seg,
      py::arg("p"), py::arg("s"),
      "Compare y of p and vertical projection of p on segment s");
m.def("compare_y_at_x", &compare_y_at_x_pt_seg1_seg2,
      py::arg("p"), py::arg("s1"), py::arg("s2"),
      "Compare y of vertical projections of p on s1 and s2");

// --- compare_yx ---
m.def("compare_yx", &compare_yx_pt2,
      py::arg("p"), py::arg("q"),
      "Compare 2D points lexicographically in yx order");

// --- compare_z ---
m.def("compare_z", &compare_z_pt3,
      py::arg("p"), py::arg("q"),
      "Compare z-coordinates of two 3D points");

// --- coplanar ---
m.def("coplanar", &coplanar_4,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "True iff four 3D points are coplanar");

// --- coplanar_orientation ---
m.def("coplanar_orientation", &coplanar_orientation_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Orientation of three coplanar 3D points");
m.def("coplanar_orientation", &coplanar_orientation_4,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "Orientation of s relative to plane defined by p,q,r");

// --- coplanar_side_of_bounded_circle ---
m.def("coplanar_side_of_bounded_circle", &coplanar_side_of_bounded_circle,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "Bounded side of circle through p,q,r on which s lies. Returns 1, 0, or -1");

// --- cross_product ---
m.def("cross_product", &cross_product,
      py::arg("u"), py::arg("v"),
      "Cross product of two 3D vectors");

// --- determinant ---
m.def("determinant", &determinant_2,
      py::arg("v"), py::arg("w"),
      "Determinant of two 2D vectors");
m.def("determinant", &determinant_3,
      py::arg("u"), py::arg("v"), py::arg("w"),
      "Determinant of three 3D vectors");

// --- do_intersect 2D ---
m.def("do_intersect", &do_intersect_seg2_seg2,  py::arg("s1"), py::arg("s2"));
m.def("do_intersect", &do_intersect_seg2_line2, py::arg("s"),  py::arg("l"));
m.def("do_intersect", &do_intersect_seg2_ray2,  py::arg("s"),  py::arg("r"));
m.def("do_intersect", &do_intersect_seg2_tri2,  py::arg("s"),  py::arg("t"));
m.def("do_intersect", &do_intersect_seg2_iso2,  py::arg("s"),  py::arg("r"));
m.def("do_intersect", &do_intersect_line2_line2, py::arg("l1"), py::arg("l2"));
m.def("do_intersect", &do_intersect_line2_ray2,  py::arg("l"),  py::arg("r"));
m.def("do_intersect", &do_intersect_line2_tri2,  py::arg("l"),  py::arg("t"));
m.def("do_intersect", &do_intersect_ray2_ray2,  py::arg("r1"), py::arg("r2"));
m.def("do_intersect", &do_intersect_ray2_tri2,  py::arg("r"),  py::arg("t"));
m.def("do_intersect", &do_intersect_tri2_tri2,  py::arg("t1"), py::arg("t2"));
m.def("do_intersect", &do_intersect_iso2_iso2,  py::arg("r1"), py::arg("r2"));
m.def("do_intersect", &do_intersect_pt2_iso2,   py::arg("p"),  py::arg("r"));
m.def("do_intersect", &do_intersect_pt2_tri2,   py::arg("p"),  py::arg("t"));

// --- do_intersect 3D ---
m.def("do_intersect", &do_intersect_seg3_seg3,    py::arg("s1"), py::arg("s2"));
m.def("do_intersect", &do_intersect_seg3_line3,   py::arg("s"),  py::arg("l"));
m.def("do_intersect", &do_intersect_seg3_ray3,    py::arg("s"),  py::arg("r"));
m.def("do_intersect", &do_intersect_seg3_plane3,  py::arg("s"),  py::arg("p"));
m.def("do_intersect", &do_intersect_seg3_tri3,    py::arg("s"),  py::arg("t"));
m.def("do_intersect", &do_intersect_seg3_sphere3, py::arg("s"),  py::arg("sp"));
m.def("do_intersect", &do_intersect_seg3_bbox3,   py::arg("s"),  py::arg("b"));
m.def("do_intersect", &do_intersect_line3_line3,  py::arg("l1"), py::arg("l2"));
m.def("do_intersect", &do_intersect_line3_ray3,   py::arg("l"),  py::arg("r"));
m.def("do_intersect", &do_intersect_line3_plane3, py::arg("l"),  py::arg("p"));
m.def("do_intersect", &do_intersect_line3_tri3,   py::arg("l"),  py::arg("t"));
m.def("do_intersect", &do_intersect_line3_sphere3,py::arg("l"),  py::arg("s"));
m.def("do_intersect", &do_intersect_ray3_ray3,    py::arg("r1"), py::arg("r2"));
m.def("do_intersect", &do_intersect_ray3_plane3,  py::arg("r"),  py::arg("p"));
m.def("do_intersect", &do_intersect_ray3_tri3,    py::arg("r"),  py::arg("t"));
m.def("do_intersect", &do_intersect_ray3_sphere3, py::arg("r"),  py::arg("s"));
m.def("do_intersect", &do_intersect_plane3_plane3, py::arg("p1"), py::arg("p2"));
m.def("do_intersect", &do_intersect_plane3_sphere3,py::arg("p"),  py::arg("s"));
m.def("do_intersect", &do_intersect_plane3_tri3,  py::arg("p"),  py::arg("t"));
m.def("do_intersect", &do_intersect_tri3_tri3,    py::arg("t1"), py::arg("t2"));
m.def("do_intersect", &do_intersect_sphere3_sphere3,py::arg("s1"),py::arg("s2"));
m.def("do_intersect", &do_intersect_pt3_plane3,   py::arg("p"),  py::arg("pl"));
m.def("do_intersect", &do_intersect_pt3_sphere3,  py::arg("p"),  py::arg("s"));
m.def("do_intersect", &do_intersect_bbox3_bbox3,  py::arg("b1"), py::arg("b2"));
m.def("do_intersect", &do_intersect_bbox3_seg3,   py::arg("b"),  py::arg("s"));
m.def("do_intersect", &do_intersect_bbox3_tri3,   py::arg("b"),  py::arg("t"));

// --- do_overlap ---
m.def("do_overlap", &do_overlap_bbox2,
      py::arg("b1"), py::arg("b2"), "True iff two 2D bboxes overlap");
m.def("do_overlap", &do_overlap_bbox3,
      py::arg("b1"), py::arg("b2"), "True iff two 3D bboxes overlap");

// --- equidistant_line ---
m.def("equidistant_line", &equidistant_line,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Line equidistant from three 3D points. Precondition: p,q,r not collinear");

// --- has_larger_distance_to_point ---
m.def("has_larger_distance_to_point", &has_larger_distance_to_point_2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff distance(q,p) > distance(r,p) in 2D");
m.def("has_larger_distance_to_point", &has_larger_distance_to_point_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff distance(q,p) > distance(r,p) in 3D");

// --- has_larger_signed_distance_to_line ---
m.def("has_larger_signed_distance_to_line", &has_larger_signed_distance_to_line_l,
      py::arg("l"), py::arg("p"), py::arg("q"),
      "True iff signed distance of p to l is larger than that of q");
m.def("has_larger_signed_distance_to_line", &has_larger_signed_distance_to_line_p,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "True iff signed distance of r to line(p,q) is larger than that of s");

// --- has_larger_signed_distance_to_plane ---
m.def("has_larger_signed_distance_to_plane", &has_larger_signed_distance_to_plane_h,
      py::arg("h"), py::arg("p"), py::arg("q"),
      "True iff signed distance of p to plane h is larger than that of q");
m.def("has_larger_signed_distance_to_plane", &has_larger_signed_distance_to_plane_p,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"), py::arg("t"),
      "True iff signed distance of s to plane(p,q,r) is larger than that of t");

// --- has_smaller_distance_to_point ---
m.def("has_smaller_distance_to_point", &has_smaller_distance_to_point_2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff distance(q,p) < distance(r,p) in 2D");
m.def("has_smaller_distance_to_point", &has_smaller_distance_to_point_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff distance(q,p) < distance(r,p) in 3D");

// --- has_smaller_signed_distance_to_line ---
m.def("has_smaller_signed_distance_to_line", &has_smaller_signed_distance_to_line_l,
      py::arg("l"), py::arg("p"), py::arg("q"),
      "True iff signed distance of p to l is smaller than that of q");
m.def("has_smaller_signed_distance_to_line", &has_smaller_signed_distance_to_line_p,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "True iff signed distance of r to line(p,q) is smaller than that of s");

// --- has_smaller_signed_distance_to_plane ---
m.def("has_smaller_signed_distance_to_plane", &has_smaller_signed_distance_to_plane_h,
      py::arg("h"), py::arg("p"), py::arg("q"),
      "True iff signed distance of p to plane h is smaller than that of q");
m.def("has_smaller_signed_distance_to_plane", &has_smaller_signed_distance_to_plane_p,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"), py::arg("t"),
      "True iff signed distance of s to plane(p,q,r) is smaller than that of t");



// --- intersection 2D ---
m.def("intersection", &intersection_seg2_seg2,
      py::arg("s1"), py::arg("s2"),
      "Intersection of two 2D segments. Returns dict with 'type' and 'value'");
m.def("intersection", &intersection_seg2_line2,
      py::arg("s"), py::arg("l"));
m.def("intersection", &intersection_seg2_ray2,
      py::arg("s"), py::arg("r"));
m.def("intersection", &intersection_seg2_tri2,
      py::arg("s"), py::arg("t"));
m.def("intersection", &intersection_line2_line2,
      py::arg("l1"), py::arg("l2"));
m.def("intersection", &intersection_line2_ray2,
      py::arg("l"), py::arg("r"));
m.def("intersection", &intersection_line2_seg2,
      py::arg("l"), py::arg("s"));
m.def("intersection", &intersection_ray2_ray2,
      py::arg("r1"), py::arg("r2"));
m.def("intersection", &intersection_ray2_seg2,
      py::arg("r"), py::arg("s"));

// --- intersection 3D ---
m.def("intersection", &intersection_seg3_seg3,
      py::arg("s1"), py::arg("s2"));
m.def("intersection", &intersection_seg3_line3,
      py::arg("s"), py::arg("l"));
m.def("intersection", &intersection_seg3_plane3,
      py::arg("s"), py::arg("p"));
m.def("intersection", &intersection_seg3_tri3,
      py::arg("s"), py::arg("t"));
m.def("intersection", &intersection_line3_line3,
      py::arg("l1"), py::arg("l2"));
m.def("intersection", &intersection_line3_plane3,
      py::arg("l"), py::arg("p"));
m.def("intersection", &intersection_line3_tri3,
      py::arg("l"), py::arg("t"));
m.def("intersection", &intersection_plane3_plane3,
      py::arg("p1"), py::arg("p2"));
m.def("intersection", &intersection_plane3_plane3_plane3,
      py::arg("p1"), py::arg("p2"), py::arg("p3"));
m.def("intersection", &intersection_plane3_seg3,
      py::arg("p"), py::arg("s"));
m.def("intersection", &intersection_plane3_tri3,
      py::arg("p"), py::arg("t"));

// --- l_infinity_distance ---
m.def("l_infinity_distance", &l_infinity_distance_2,
      py::arg("p"), py::arg("q"),
      "L-infinity distance between two 2D points");
m.def("l_infinity_distance", &l_infinity_distance_3,
      py::arg("p"), py::arg("q"),
      "L-infinity distance between two 3D points");

// --- left_turn ---
m.def("left_turn", &left_turn_2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff p, q, r form a left turn");

// --- lexicographic comparisons ---
m.def("lexicographically_xyz_smaller", &lexicographically_xyz_smaller,
      py::arg("p"), py::arg("q"));
m.def("lexicographically_xyz_smaller_or_equal", &lexicographically_xyz_smaller_or_equal,
      py::arg("p"), py::arg("q"));
m.def("lexicographically_xy_larger", &lexicographically_xy_larger,
      py::arg("p"), py::arg("q"));
m.def("lexicographically_xy_larger_or_equal", &lexicographically_xy_larger_or_equal,
      py::arg("p"), py::arg("q"));
m.def("lexicographically_xy_smaller", &lexicographically_xy_smaller,
      py::arg("p"), py::arg("q"));
m.def("lexicographically_xy_smaller_or_equal", &lexicographically_xy_smaller_or_equal,
      py::arg("p"), py::arg("q"));

// --- max_vertex / min_vertex ---
m.def("max_vertex", &max_vertex_iso_rect,   py::arg("ir"));
m.def("max_vertex", &max_vertex_iso_cuboid, py::arg("ic"));
m.def("min_vertex", &min_vertex_iso_rect,   py::arg("ir"));
m.def("min_vertex", &min_vertex_iso_cuboid, py::arg("ic"));

// --- midpoint ---
m.def("midpoint", &midpoint_pt2,  py::arg("p"), py::arg("q"));
m.def("midpoint", &midpoint_seg2, py::arg("s"));
m.def("midpoint", &midpoint_pt3,  py::arg("p"), py::arg("q"));
m.def("midpoint", &midpoint_seg3, py::arg("s"));

// --- normal ---
m.def("normal", &normal_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Normal vector for vectors q-p and r-p");

// --- orthogonal_vector ---
m.def("orthogonal_vector", &orthogonal_vector_plane,
      py::arg("p"), "Orthogonal vector of a plane");
m.def("orthogonal_vector", &orthogonal_vector_pts,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Orthogonal vector of plane through p,q,r");

// --- orientation (global) ---
// Returns: 1=POSITIVE/LEFT_TURN, -1=NEGATIVE/RIGHT_TURN, 0=COLLINEAR/COPLANAR
m.def("orientation", &orientation_pt2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Orientation of three 2D points. Returns 1, -1, or 0");
m.def("orientation", &orientation_vec2,
      py::arg("u"), py::arg("v"),
      "Orientation of two 2D vectors");
m.def("orientation", &orientation_pt3,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"),
      "Orientation of four 3D points");
m.def("orientation", &orientation_vec3,
      py::arg("u"), py::arg("v"), py::arg("w"),
      "Orientation of three 3D vectors");

// --- parallel ---
m.def("parallel", &parallel_line2,  py::arg("l1"), py::arg("l2"));
m.def("parallel", &parallel_ray2,   py::arg("r1"), py::arg("r2"));
m.def("parallel", &parallel_seg2,   py::arg("s1"), py::arg("s2"));
m.def("parallel", &parallel_line3,  py::arg("l1"), py::arg("l2"));
m.def("parallel", &parallel_plane3, py::arg("h1"), py::arg("h2"));
m.def("parallel", &parallel_ray3,   py::arg("r1"), py::arg("r2"));
m.def("parallel", &parallel_seg3,   py::arg("s1"), py::arg("s2"));

// --- radical_plane / radical_line ---
m.def("radical_plane", &radical_plane,
      py::arg("s1"), py::arg("s2"),
      "Radical plane of two spheres");
m.def("radical_line", &radical_line,
      py::arg("c1"), py::arg("c2"),
      "Radical line of two circles");

// --- right_turn ---
m.def("right_turn", &right_turn_2,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "True iff p, q, r form a right turn");

// --- scalar_product ---
m.def("scalar_product", &scalar_product_2,
      py::arg("u"), py::arg("v"), "Scalar product of two 2D vectors");
m.def("scalar_product", &scalar_product_3,
      py::arg("u"), py::arg("v"), "Scalar product of two 3D vectors");

// --- side_of_bounded_circle ---
m.def("side_of_bounded_circle", &side_of_bounded_circle_4,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("t"),
      "Side of bounded circle through p,q,r on which t lies. Returns 1, 0, -1");
m.def("side_of_bounded_circle", &side_of_bounded_circle_3,
      py::arg("p"), py::arg("q"), py::arg("t"),
      "Side of circle with diameter pq on which t lies");

// --- side_of_bounded_sphere ---
m.def("side_of_bounded_sphere", &side_of_bounded_sphere_5,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"), py::arg("t"));
m.def("side_of_bounded_sphere", &side_of_bounded_sphere_4,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("t"));
m.def("side_of_bounded_sphere", &side_of_bounded_sphere_3,
      py::arg("p"), py::arg("q"), py::arg("t"));

// --- side_of_oriented_circle ---
m.def("side_of_oriented_circle", &side_of_oriented_circle,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("test"),
      "Oriented side of circle through p,q,r on which test lies. Returns 1, 0, -1");

// --- side_of_oriented_sphere ---
m.def("side_of_oriented_sphere", &side_of_oriented_sphere,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"), py::arg("test"),
      "Oriented side of sphere through p,q,r,s on which test lies");

// --- squared_area ---
m.def("squared_area", &squared_area_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Squared area of 3D triangle");

// --- squared_distance 2D ---
m.def("squared_distance", &squared_distance_pt2_pt2,
      py::arg("p"), py::arg("q"));
m.def("squared_distance", &squared_distance_pt2_line2,
      py::arg("p"), py::arg("l"));
m.def("squared_distance", &squared_distance_pt2_ray2,
      py::arg("p"), py::arg("r"));
m.def("squared_distance", &squared_distance_pt2_seg2,
      py::arg("p"), py::arg("s"));
m.def("squared_distance", &squared_distance_pt2_tri2,
      py::arg("p"), py::arg("t"));
m.def("squared_distance", &squared_distance_line2_line2,
      py::arg("l1"), py::arg("l2"));
m.def("squared_distance", &squared_distance_seg2_seg2,
      py::arg("s1"), py::arg("s2"));

// --- squared_distance 3D ---
m.def("squared_distance", &squared_distance_pt3_pt3,
      py::arg("p"), py::arg("q"));
m.def("squared_distance", &squared_distance_pt3_line3,
      py::arg("p"), py::arg("l"));
m.def("squared_distance", &squared_distance_pt3_ray3,
      py::arg("p"), py::arg("r"));
m.def("squared_distance", &squared_distance_pt3_seg3,
      py::arg("p"), py::arg("s"));
m.def("squared_distance", &squared_distance_pt3_plane3,
      py::arg("p"), py::arg("pl"));
m.def("squared_distance", &squared_distance_pt3_tri3,
      py::arg("p"), py::arg("t"));
m.def("squared_distance", &squared_distance_line3_line3,
      py::arg("l1"), py::arg("l2"));
m.def("squared_distance", &squared_distance_seg3_seg3,
      py::arg("s1"), py::arg("s2"));
m.def("squared_distance", &squared_distance_tri3_tri3,
      py::arg("t1"), py::arg("t2"));

// --- squared_radius ---
m.def("squared_radius", &squared_radius_pt2_3,
      py::arg("p"), py::arg("q"), py::arg("r"));
m.def("squared_radius", &squared_radius_pt2_2,
      py::arg("p"), py::arg("q"));
m.def("squared_radius", &squared_radius_pt2_1,
      py::arg("p"));
m.def("squared_radius", &squared_radius_pt3_4,
      py::arg("p"), py::arg("q"), py::arg("r"), py::arg("s"));
m.def("squared_radius", &squared_radius_pt3_3,
      py::arg("p"), py::arg("q"), py::arg("r"));
m.def("squared_radius", &squared_radius_pt3_2,
      py::arg("p"), py::arg("q"));
m.def("squared_radius", &squared_radius_pt3_1,
      py::arg("p"));

// --- unit_normal ---
m.def("unit_normal", &unit_normal_3,
      py::arg("p"), py::arg("q"), py::arg("r"),
      "Unit normal vector for vectors q-p and r-p");

// --- volume ---
m.def("volume", &volume_3,
      py::arg("p0"), py::arg("p1"), py::arg("p2"), py::arg("p3"),
      "Signed volume of tetrahedron defined by four 3D points");

// --- x/y/z equal ---
m.def("x_equal", &x_equal_2, py::arg("p"), py::arg("q"));
m.def("x_equal", &x_equal_3, py::arg("p"), py::arg("q"));
m.def("y_equal", &y_equal_2, py::arg("p"), py::arg("q"));
m.def("y_equal", &y_equal_3, py::arg("p"), py::arg("q"));
m.def("z_equal", &z_equal_3, py::arg("p"), py::arg("q"));

bind_general_polygon_with_holes2(m);  // bind base first
bind_polygon2(m);
bind_polygon_with_holes2(m);
bind_multipolygon_with_holes2(m);
bind_polygon_global_functions(m);



// ─── Locate_type constants ────────────────────────────────────────────────────
// Paste inside PYBIND11_MODULE body, before class definitions:
m.attr("T2_VERTEX")               = static_cast<int>(CGALTriangulation2::VERTEX);
m.attr("T2_EDGE")                 = static_cast<int>(CGALTriangulation2::EDGE);
m.attr("T2_FACE")                 = static_cast<int>(CGALTriangulation2::FACE);
m.attr("T2_OUTSIDE_CONVEX_HULL")  = static_cast<int>(CGALTriangulation2::OUTSIDE_CONVEX_HULL);
m.attr("T2_OUTSIDE_AFFINE_HULL")  = static_cast<int>(CGALTriangulation2::OUTSIDE_AFFINE_HULL);
 
// ─── VertexHandle2 ────────────────────────────────────────────────────────────
py::class_<VertexHandle2>(m, "VertexHandle2")
    .def(py::init<>())
    .def("is_valid",  &VertexHandle2::is_valid)
    .def("point",     &vh2_point)
    .def("__eq__",    &vh2_eq)
    .def("__ne__",    &vh2_neq)
    .def("__hash__", [](const VertexHandle2& v) {
        return std::hash<void*>()(static_cast<void*>(&(*v.vh)));
    })
    .def("__repr__", [](const VertexHandle2& v) {
        if (!v.is_valid()) return std::string("VertexHandle2(invalid)");
        auto p = vh2_point(v);
        return "VertexHandle2(Point2(" + std::to_string(p.x()) + ", "
                                       + std::to_string(p.y()) + "))";
    });
 
// ─── FaceHandle2 ─────────────────────────────────────────────────────────────
py::class_<FaceHandle2>(m, "FaceHandle2")
    .def(py::init<>())
    .def("is_valid",    &FaceHandle2::is_valid)
    .def("vertex",      &fh2_vertex,      py::arg("i"))
    .def("neighbor",    &fh2_neighbor,    py::arg("i"))
    .def("index",       py::overload_cast<const FaceHandle2&, const VertexHandle2&>(&fh2_index_vertex),
                        py::arg("v"))
    .def("index_face",  py::overload_cast<const FaceHandle2&, const FaceHandle2&>(&fh2_index_face),
                        py::arg("n"))
    .def("__eq__",      &fh2_eq)
    .def("__ne__",      &fh2_neq)
    .def("__hash__", [](const FaceHandle2& f) {
        return std::hash<void*>()(static_cast<void*>(&(*f.fh)));
    })
    .def("__repr__", [](const FaceHandle2& f) {
        return f.is_valid() ? "FaceHandle2(<valid>)" : "FaceHandle2(invalid)";
    });
 
// ─── EdgeHandle2 ─────────────────────────────────────────────────────────────
py::class_<EdgeHandle2>(m, "EdgeHandle2")
    .def(py::init<>())
    .def(py::init<FaceHandle2, int>(), py::arg("face"), py::arg("index"))
    .def_readwrite("face",  &EdgeHandle2::face)
    .def_readwrite("index", &EdgeHandle2::index)
    .def("__repr__", [](const EdgeHandle2& e) {
        return "EdgeHandle2(index=" + std::to_string(e.index) + ")";
    });
 
// ─── Triangulation2 ───────────────────────────────────────────────────────────
py::class_<Triangulation2>(m, "Triangulation2")
    .def(py::init<>())
 
    // ── Access ────────────────────────────────────────────────────────────────
    .def("dimension",           &t2_dimension)
    .def("number_of_vertices",  &t2_number_of_vertices)
    .def("number_of_faces",     &t2_number_of_faces)
    .def("is_valid",            &t2_is_valid, py::arg("verbose")=false)
    .def("clear",               &t2_clear)
    .def("swap",                &t2_swap, py::arg("other"))
    .def("infinite_vertex",     &t2_infinite_vertex)
    .def("infinite_face",       &t2_infinite_face)
    .def("finite_vertex",       &t2_finite_vertex)
 
    // ── Insert ────────────────────────────────────────────────────────────────
    .def("insert", py::overload_cast<Triangulation2&, const Point2&>(&t2_insert_point),
         py::arg("p"),
         "Insert a single point. Returns VertexHandle2.")
    .def("insert", py::overload_cast<Triangulation2&, const Point2&, const FaceHandle2&>(&t2_insert_point_hint),
         py::arg("p"), py::arg("hint"),
         "Insert with a face hint for faster location.")
    .def("insert", py::overload_cast<Triangulation2&, const std::vector<Point2>&>(&t2_insert_points),
         py::arg("points"),
         "Insert a list of points. Returns number of inserted points.")
    .def("push_back",                   &t2_push_back,                   py::arg("p"))
    .def("insert_first",                &t2_insert_first,                py::arg("p"))
    .def("insert_second",               &t2_insert_second,               py::arg("p"))
    .def("insert_in_face",              &t2_insert_in_face,              py::arg("p"), py::arg("f"))
    .def("insert_in_edge",              &t2_insert_in_edge,              py::arg("p"), py::arg("f"), py::arg("i"))
    .def("insert_outside_convex_hull",  &t2_insert_outside_convex_hull,  py::arg("p"), py::arg("f"))
    .def("insert_outside_affine_hull",  &t2_insert_outside_affine_hull,  py::arg("p"))
 
    // ── Remove ────────────────────────────────────────────────────────────────
    .def("remove",          &t2_remove,          py::arg("v"))
    .def("remove_degree_3", &t2_remove_degree_3, py::arg("v"))
    .def("remove_first",    &t2_remove_first,    py::arg("v"))
    .def("remove_second",   &t2_remove_second,   py::arg("v"))
 
    // ── Move ──────────────────────────────────────────────────────────────────
    .def("move",                 &t2_move,                 py::arg("v"), py::arg("p"))
    .def("move_if_no_collision", &t2_move_if_no_collision, py::arg("v"), py::arg("p"))
 
    // ── Flip ──────────────────────────────────────────────────────────────────
    .def("flip", &t2_flip, py::arg("f"), py::arg("i"))
 
    // ── Locate ────────────────────────────────────────────────────────────────
    .def("locate", py::overload_cast<const Triangulation2&, const Point2&>(&t2_locate),
         py::arg("query"),
         "Locate query point. Returns FaceHandle2.")
    .def("locate", py::overload_cast<const Triangulation2&, const Point2&, const FaceHandle2&>(&t2_locate_hint),
         py::arg("query"), py::arg("hint"))
    .def("locate_full",    &t2_locate_full,    py::arg("query"),
         "Returns (FaceHandle2, locate_type: int, li: int).")
    .def("inexact_locate", &t2_inexact_locate, py::arg("query"))
 
    // ── Predicates ────────────────────────────────────────────────────────────
    .def("is_infinite",
         py::overload_cast<const Triangulation2&, const VertexHandle2&>(&t2_is_infinite_vertex),
         py::arg("v"))
    .def("is_infinite",
         py::overload_cast<const Triangulation2&, const FaceHandle2&>(&t2_is_infinite_face),
         py::arg("f"))
    .def("is_infinite",
         py::overload_cast<const Triangulation2&, const FaceHandle2&, int>(&t2_is_infinite_edge),
         py::arg("f"), py::arg("i"))
    .def("is_edge",
         py::overload_cast<const Triangulation2&, const VertexHandle2&, const VertexHandle2&>(&t2_is_edge),
         py::arg("va"), py::arg("vb"))
    .def("is_edge_full",  &t2_is_edge_full,  py::arg("va"), py::arg("vb"),
         "Returns (bool, FaceHandle2, index: int).")
    .def("is_face",       &t2_is_face3,      py::arg("v1"), py::arg("v2"), py::arg("v3"))
    .def("is_face_full",  &t2_is_face3_full, py::arg("v1"), py::arg("v2"), py::arg("v3"),
         "Returns (bool, FaceHandle2).")
    .def("includes_edge", &t2_includes_edge, py::arg("va"), py::arg("vb"),
         "Returns (bool, VertexHandle2 vbb, FaceHandle2, index: int).")
 
    // ── Oriented / circle side ────────────────────────────────────────────────
    .def("oriented_side",          &t2_oriented_side,          py::arg("f"), py::arg("p"))
    .def("side_of_oriented_circle",&t2_side_of_oriented_circle,py::arg("f"), py::arg("p"))
 
    // ── Geometry ──────────────────────────────────────────────────────────────
    .def("triangle",             &t2_triangle,        py::arg("f"))
    .def("segment",
         py::overload_cast<const Triangulation2&, const FaceHandle2&, int>(&t2_segment_face_i),
         py::arg("f"), py::arg("i"))
    .def("segment",
         py::overload_cast<const Triangulation2&, const EdgeHandle2&>(&t2_segment_edge),
         py::arg("e"))
    .def("circumcenter", &t2_circumcenter,  py::arg("f"))
    .def("point",
         py::overload_cast<const Triangulation2&, const FaceHandle2&, int>(&t2_point_face_i),
         py::arg("f"), py::arg("i"))
    .def("point",
         py::overload_cast<const Triangulation2&, const VertexHandle2&>(&t2_point_vertex),
         py::arg("v"))
    .def("ccw", &t2_ccw, py::arg("i"))
    .def("cw",  &t2_cw,  py::arg("i"))
 
    // ── Adjacency ─────────────────────────────────────────────────────────────
    .def("mirror_vertex", &t2_mirror_vertex, py::arg("f"), py::arg("i"))
    .def("mirror_index",  &t2_mirror_index,  py::arg("f"), py::arg("i"))
    .def("mirror_edge",   &t2_mirror_edge,   py::arg("e"))
 
    // ── Finite iterators → list ───────────────────────────────────────────────
    .def("finite_vertices", &t2_finite_vertices,
         "Returns list of VertexHandle2 for all finite vertices.")
    .def("finite_faces",    &t2_finite_faces,
         "Returns list of FaceHandle2 for all finite faces.")
    .def("finite_edges",    &t2_finite_edges,
         "Returns list of EdgeHandle2 for all finite edges.")
    .def("points",          &t2_points,
         "Returns list of Point2 for all finite vertices.")
 
    // ── All iterators → list ──────────────────────────────────────────────────
    .def("all_vertices",    &t2_all_vertices,
         "Returns list of VertexHandle2 including the infinite vertex.")
    .def("all_faces",       &t2_all_faces,
         "Returns list of FaceHandle2 including infinite faces.")
    .def("all_edges",       &t2_all_edges,
         "Returns list of EdgeHandle2 including infinite edges.")
 
    // ── Circulators → list ────────────────────────────────────────────────────
    .def("incident_faces",    &t2_incident_faces,    py::arg("v"),
         "Returns list of FaceHandle2 incident to vertex v.")
    .def("incident_edges",    &t2_incident_edges,    py::arg("v"),
         "Returns list of EdgeHandle2 incident to vertex v.")
    .def("incident_vertices", &t2_incident_vertices, py::arg("v"),
         "Returns list of VertexHandle2 adjacent to vertex v.")
 
    // ── Line walk ─────────────────────────────────────────────────────────────
    .def("line_walk", &t2_line_walk, py::arg("p"), py::arg("q"),
         "Returns list of FaceHandle2 intersected by line pq.")
 
    // ── Convex hull ───────────────────────────────────────────────────────────
    .def("convex_hull_vertices", &t2_convex_hull_vertices,
         "Returns list of VertexHandle2 on the convex hull (CCW order).")
    .def("convex_hull_edges",    &t2_convex_hull_edges,
         "Returns list of EdgeHandle2 on the convex hull.")
 
    // ── Advanced ──────────────────────────────────────────────────────────────
    .def("set_infinite_vertex", &t2_set_infinite_vertex, py::arg("v"))
 
    .def("__repr__", [](const Triangulation2& t) {
        return "Triangulation2(vertices=" + std::to_string(t2_number_of_vertices(t))
             + ", faces=" + std::to_string(t2_number_of_faces(t)) + ")";
    });

}