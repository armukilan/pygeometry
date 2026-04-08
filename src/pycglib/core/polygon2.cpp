#include "polygon2.h"
#include <sstream>

// ─── Helpers ──────────────────────────────────────────────────────────────────
// Convert our wrapper Point2 → CGALPoint2 and back.
static inline CGALPoint2 to_cgal(const Point2& p)  { return p.p; }
static inline Point2     to_wrap(const CGALPoint2& p) { return Point2(p); }

// Build a CGALPolygon2 from a vector of wrapper Point2.
static CGALPolygon2 poly_from_vec(const std::vector<Point2>& pts) {
    CGALPolygon2 poly;
    for (const auto& p : pts) poly.push_back(to_cgal(p));
    return poly;
}

// Extract vertices of a CGALPolygon2 as wrapper Point2 list.
static std::vector<Point2> verts_to_vec(const CGALPolygon2& poly) {
    std::vector<Point2> out;
    for (auto it = poly.vertices_begin(); it != poly.vertices_end(); ++it)
        out.push_back(to_wrap(*it));
    return out;
}

// ─────────────────────────────────────────────────────────────────────────────
// Polygon2
// Stored internally as CGALPolygon2. Python sees Point2/Segment2/Bbox2.
// ─────────────────────────────────────────────────────────────────────────────
void bind_polygon2(py::module_& m) {
    py::class_<CGALPolygon2>(m, "Polygon2")

        // ── Constructors ──────────────────────────────────────
        .def(py::init<>(),
             "Creates an empty polygon.")
        .def(py::init([](const std::vector<Point2>& pts) {
                 return poly_from_vec(pts);
             }), py::arg("points"),
             "Creates a polygon from a list of Point2.")

        // ── Modifiers ─────────────────────────────────────────
        .def("push_back", [](CGALPolygon2& poly, const Point2& p) {
                 poly.push_back(to_cgal(p));
             }, py::arg("point"),
             "Appends a vertex to the polygon.")
        .def("clear", &CGALPolygon2::clear,
             "Removes all vertices.")
        .def("reverse_orientation", &CGALPolygon2::reverse_orientation,
             "Reverses the orientation of the polygon (CCW ↔ CW).")
        .def("resize", &CGALPolygon2::resize, py::arg("n"),
             "Resizes the vertex container.")
        .def("reserve", &CGALPolygon2::reserve, py::arg("n"),
             "Reserves capacity in the vertex container.")

        // ── Random access ─────────────────────────────────────
        .def("vertex", [](const CGALPolygon2& poly, std::size_t i) {
                 return to_wrap(poly.vertex(i));
             }, py::arg("i"),
             "Returns the i-th vertex as Point2.")
        .def("__getitem__", [](const CGALPolygon2& poly, std::size_t i) {
                 return to_wrap(poly.vertex(i));
             }, py::arg("i"))
        .def("__setitem__", [](CGALPolygon2& poly, std::size_t i, const Point2& q) {
                 poly[i] = to_cgal(q);
             }, py::arg("i"), py::arg("point"))
        .def("edge", [](const CGALPolygon2& poly, std::size_t i) {
                 return Segment2(poly.edge(i));
             }, py::arg("i"),
             "Returns the i-th edge as Segment2.")

        // ── Vertices / edges as Python lists ──────────────────
        .def("vertices", [](const CGALPolygon2& poly) {
                 return verts_to_vec(poly);
             }, "Returns all vertices as a list of Point2.")
        .def("edges", [](const CGALPolygon2& poly) {
                 std::vector<Segment2> out;
                 for (auto it = poly.edges_begin(); it != poly.edges_end(); ++it)
                     out.push_back(Segment2(*it));
                 return out;
             }, "Returns all edges as a list of Segment2.")

        // ── Predicates ────────────────────────────────────────
        .def("is_simple", &CGALPolygon2::is_simple,
             "Returns True if the polygon has no self-intersecting edges.")
        .def("is_convex", &CGALPolygon2::is_convex,
             "Returns True if the polygon is convex.")
        .def("is_empty", &CGALPolygon2::is_empty,
             "Returns True if the polygon has no vertices.")
        .def("orientation", [](const CGALPolygon2& poly) {
                 return static_cast<int>(poly.orientation());
             }, "Returns orientation: COUNTERCLOCKWISE=1, COLLINEAR=0, CLOCKWISE=-1.")
        .def("oriented_side", [](const CGALPolygon2& poly, const Point2& q) {
                 return static_cast<int>(poly.oriented_side(to_cgal(q)));
             }, py::arg("point"),
             "Returns ON_POSITIVE_SIDE=1, ON_ORIENTED_BOUNDARY=0, ON_NEGATIVE_SIDE=-1.")
        .def("bounded_side", [](const CGALPolygon2& poly, const Point2& q) {
                 return static_cast<int>(poly.bounded_side(to_cgal(q)));
             }, py::arg("point"),
             "Returns ON_BOUNDED_SIDE=1, ON_BOUNDARY=0, ON_UNBOUNDED_SIDE=-1.")

        // ── Convenience orientation booleans ──────────────────
        .def("is_counterclockwise_oriented", &CGALPolygon2::is_counterclockwise_oriented)
        .def("is_clockwise_oriented",        &CGALPolygon2::is_clockwise_oriented)
        .def("is_collinear_oriented",        &CGALPolygon2::is_collinear_oriented)
        .def("has_on_positive_side",  [](const CGALPolygon2& p, const Point2& q) {
                 return p.has_on_positive_side(to_cgal(q));
             }, py::arg("point"))
        .def("has_on_negative_side",  [](const CGALPolygon2& p, const Point2& q) {
                 return p.has_on_negative_side(to_cgal(q));
             }, py::arg("point"))
        .def("has_on_boundary",       [](const CGALPolygon2& p, const Point2& q) {
                 return p.has_on_boundary(to_cgal(q));
             }, py::arg("point"))
        .def("has_on_bounded_side",   [](const CGALPolygon2& p, const Point2& q) {
                 return p.has_on_bounded_side(to_cgal(q));
             }, py::arg("point"))
        .def("has_on_unbounded_side", [](const CGALPolygon2& p, const Point2& q) {
                 return p.has_on_unbounded_side(to_cgal(q));
             }, py::arg("point"))

        // ── Geometry ──────────────────────────────────────────
        .def("area", [](const CGALPolygon2& poly) {
                 return CGAL::to_double(poly.area());
             }, "Returns the signed area (positive=CCW, negative=CW).")
        .def("bbox", [](const CGALPolygon2& poly) {
                 return Bbox2(poly.bbox());
             }, "Returns the bounding box as Bbox2.")

        // ── Extreme vertices ──────────────────────────────────
        .def("left_vertex",   [](const CGALPolygon2& p) { return to_wrap(*p.left_vertex()); },
             "Leftmost vertex (smallest x; ties: smallest y).")
        .def("right_vertex",  [](const CGALPolygon2& p) { return to_wrap(*p.right_vertex()); },
             "Rightmost vertex (largest x; ties: largest y).")
        .def("top_vertex",    [](const CGALPolygon2& p) { return to_wrap(*p.top_vertex()); },
             "Topmost vertex (largest y; ties: largest x).")
        .def("bottom_vertex", [](const CGALPolygon2& p) { return to_wrap(*p.bottom_vertex()); },
             "Bottommost vertex (smallest y; ties: smallest x).")

        // ── Size ──────────────────────────────────────────────
        .def("size",    &CGALPolygon2::size, "Returns the number of vertices.")
        .def("__len__", &CGALPolygon2::size)

        // ── Equality ──────────────────────────────────────────
        .def("__eq__", [](const CGALPolygon2& a, const CGALPolygon2& b) { return a == b; })
        .def("__ne__", [](const CGALPolygon2& a, const CGALPolygon2& b) { return a != b; })

        // ── Repr ──────────────────────────────────────────────
        .def("__repr__", [](const CGALPolygon2& poly) {
                 std::ostringstream oss;
                 oss << "Polygon2([";
                 bool first = true;
                 for (auto it = poly.vertices_begin(); it != poly.vertices_end(); ++it) {
                     if (!first) oss << ", ";
                     oss << "(" << CGAL::to_double(it->x())
                         << ", " << CGAL::to_double(it->y()) << ")";
                     first = false;
                 }
                 oss << "])";
                 return oss.str();
             });
}

// ─────────────────────────────────────────────────────────────────────────────
// General_polygon_with_holes_2  (base class)
// Outer boundary + holes, all as CGALPolygon2 internally.
// Python API accepts/returns our Point2 lists via the Polygon2 binding.
// ─────────────────────────────────────────────────────────────────────────────
void bind_general_polygon_with_holes2(py::module_& m) {
    py::class_<CGALGenPolyWithHoles2>(m, "GeneralPolygonWithHoles2")
        .def(py::init<>(),
             "Creates an empty general polygon with holes.")
        .def(py::init([](const CGALPolygon2& outer) {
                 return CGALGenPolyWithHoles2(outer);
             }), py::arg("outer_boundary"),
             "Creates from a Polygon2 outer boundary.")

        // ── Outer boundary ────────────────────────────────────
        .def("outer_boundary",
             (CGALPolygon2& (CGALGenPolyWithHoles2::*)())
             &CGALGenPolyWithHoles2::outer_boundary,
             py::return_value_policy::reference_internal,
             "Returns the outer boundary as Polygon2.")

        // ── Holes ─────────────────────────────────────────────
        .def("holes", [](const CGALGenPolyWithHoles2& p) {
                 return std::vector<CGALPolygon2>(p.holes_begin(), p.holes_end());
             }, "Returns the list of hole polygons (each is a Polygon2).")
        .def("add_hole", [](CGALGenPolyWithHoles2& p, const CGALPolygon2& hole) {
                 p.add_hole(hole);
             }, py::arg("hole"), "Adds a hole polygon (Polygon2).")
        .def("erase_hole", [](CGALGenPolyWithHoles2& p, std::size_t idx) {
                 auto n = (std::size_t)std::distance(p.holes_begin(), p.holes_end());
                 if (idx >= n) throw py::index_error("hole index out of range");
                 auto it = p.holes_begin();
                 std::advance(it, idx);
                 p.erase_hole(it);
             }, py::arg("index"), "Erases the hole at the given index.")
        .def("number_of_holes", [](const CGALGenPolyWithHoles2& p) {
                 return (std::size_t)std::distance(p.holes_begin(), p.holes_end());
             }, "Returns the number of holes.")
        .def("is_unbounded", &CGALGenPolyWithHoles2::is_unbounded,
             "Returns True if the outer boundary is empty (represents an unbounded region).")

        .def("__repr__", [](const CGALGenPolyWithHoles2& p) {
                 std::ostringstream oss;
                 oss << "GeneralPolygonWithHoles2(outer="
                     << p.outer_boundary().size() << " vertices, holes="
                     << std::distance(p.holes_begin(), p.holes_end()) << ")";
                 return oss.str();
             });
}

// ─────────────────────────────────────────────────────────────────────────────
// Polygon_with_holes_2  (concrete subclass)
// Inherits from GeneralPolygonWithHoles2 in pybind11.
// Adds bbox() and a convenient list-of-holes constructor.
// ─────────────────────────────────────────────────────────────────────────────
void bind_polygon_with_holes2(py::module_& m) {
    py::class_<CGALPolygonWithHoles2, CGALGenPolyWithHoles2>(m, "PolygonWithHoles2")
        .def(py::init<>(),
             "Creates an empty polygon with holes.")
        .def(py::init<const CGALPolygon2&>(), py::arg("outer_boundary"),
             "Creates from a Polygon2 outer boundary (no holes).")
        .def(py::init([](const CGALPolygon2& outer,
                         const std::vector<CGALPolygon2>& holes) {
                 return CGALPolygonWithHoles2(outer, holes.begin(), holes.end());
             }), py::arg("outer_boundary"), py::arg("holes"),
             "Creates from a Polygon2 outer boundary and a list of hole Polygon2s.")

        .def("bbox", [](const CGALPolygonWithHoles2& p) {
                 return Bbox2(p.bbox());
             }, "Returns the bounding box of the outer boundary as Bbox2.")

        .def("__repr__", [](const CGALPolygonWithHoles2& p) {
                 std::ostringstream oss;
                 oss << "PolygonWithHoles2(outer="
                     << p.outer_boundary().size() << " vertices, holes="
                     << std::distance(p.holes_begin(), p.holes_end()) << ")";
                 return oss.str();
             });
}

// ─────────────────────────────────────────────────────────────────────────────
// Multipolygon_with_holes_2
// A collection of PolygonWithHoles2 objects (e.g. disconnected regions).
// Only available on CGAL >= 5.6. On older systems this is a no-op.
// ─────────────────────────────────────────────────────────────────────────────
void bind_multipolygon_with_holes2(py::module_& m) {
#ifdef PYCG_HAS_MULTIPOLYGON
    py::class_<CGALMultipolygon2>(m, "MultipolygonWithHoles2")
        .def(py::init<>(),
             "Creates an empty multipolygon.")
        .def(py::init([](const std::vector<CGALPolygonWithHoles2>& polys) {
                 return CGALMultipolygon2(polys.begin(), polys.end());
             }), py::arg("polygons"),
             "Creates from a list of PolygonWithHoles2.")

        .def("polygons_with_holes", [](const CGALMultipolygon2& mp) {
                 return std::vector<CGALPolygonWithHoles2>(
                     mp.polygons_with_holes_begin(),
                     mp.polygons_with_holes_end());
             }, "Returns the list of PolygonWithHoles2.")
        .def("add_polygon_with_holes",
             [](CGALMultipolygon2& mp, const CGALPolygonWithHoles2& p) {
                 mp.add_polygon_with_holes(p);
             }, py::arg("polygon"),
             "Adds a PolygonWithHoles2.")
        .def("erase_polygon_with_holes",
             [](CGALMultipolygon2& mp, std::size_t idx) {
                 if (idx >= mp.number_of_polygons_with_holes())
                     throw py::index_error("polygon index out of range");
                 auto it = mp.polygons_with_holes_begin();
                 std::advance(it, idx);
                 mp.erase_polygon_with_holes(it);
             }, py::arg("index"), "Erases the polygon at the given index.")
        .def("number_of_polygons_with_holes",
             &CGALMultipolygon2::number_of_polygons_with_holes,
             "Returns the number of polygons with holes.")
        .def("__len__", &CGALMultipolygon2::number_of_polygons_with_holes)

        .def("__repr__", [](const CGALMultipolygon2& mp) {
                 std::ostringstream oss;
                 oss << "MultipolygonWithHoles2("
                     << mp.number_of_polygons_with_holes() << " polygons)";
                 return oss.str();
             });
#else
    (void)m;  // suppress unused parameter warning on old CGAL
#endif
}

// ─────────────────────────────────────────────────────────────────────────────
// Global polygon functions  (sequence-based, from Polygon_2_algorithms.h)
// All accept a list of Point2 and work on the raw CGALPoint2 sequence.
// ─────────────────────────────────────────────────────────────────────────────
void bind_polygon_global_functions(py::module_& m) {

    // Helper: convert Python list of Point2 → vector of CGALPoint2
    // (used inline in each lambda below)

    m.def("area_2",
          [](const std::vector<Point2>& pts) {
              std::vector<CGALPoint2> cpts;
              for (auto& p : pts) cpts.push_back(to_cgal(p));
              Kernel::FT result;
              CGAL::area_2(cpts.begin(), cpts.end(), result, Kernel());
              return CGAL::to_double(result);
          }, py::arg("points"),
          "Signed area of a polygon (list of Point2). Positive=CCW, negative=CW.");

    m.def("polygon_area_2",
          [](const std::vector<Point2>& pts) {
              std::vector<CGALPoint2> cpts;
              for (auto& p : pts) cpts.push_back(to_cgal(p));
              return CGAL::to_double(
                  CGAL::polygon_area_2(cpts.begin(), cpts.end(), Kernel()));
          }, py::arg("points"),
          "Signed area of a polygon (list of Point2). Same as area_2 but returns directly.");

    m.def("is_simple_2",
          [](const std::vector<Point2>& pts) {
              std::vector<CGALPoint2> cpts;
              for (auto& p : pts) cpts.push_back(to_cgal(p));
              return CGAL::is_simple_2(cpts.begin(), cpts.end(), Kernel());
          }, py::arg("points"),
          "Returns True if the polygon (list of Point2) has no self-intersecting edges. O(n log n).");

    m.def("is_convex_2",
          [](const std::vector<Point2>& pts) {
              std::vector<CGALPoint2> cpts;
              for (auto& p : pts) cpts.push_back(to_cgal(p));
              return CGAL::is_convex_2(cpts.begin(), cpts.end(), Kernel());
          }, py::arg("points"),
          "Returns True if the polygon (list of Point2) is convex.");

    m.def("orientation_2",
          [](const std::vector<Point2>& pts) {
              std::vector<CGALPoint2> cpts;
              for (auto& p : pts) cpts.push_back(to_cgal(p));
              return static_cast<int>(
                  CGAL::orientation_2(cpts.begin(), cpts.end(), Kernel()));
          }, py::arg("points"),
          "Orientation of a polygon (list of Point2): COUNTERCLOCKWISE=1, COLLINEAR=0, CLOCKWISE=-1. "
          "Precondition: polygon must be simple.");

    m.def("oriented_side_2",
          [](const std::vector<Point2>& pts, const Point2& q) {
              std::vector<CGALPoint2> cpts;
              for (auto& p : pts) cpts.push_back(to_cgal(p));
              return static_cast<int>(
                  CGAL::oriented_side_2(cpts.begin(), cpts.end(), to_cgal(q), Kernel()));
          }, py::arg("points"), py::arg("point"),
          "Which oriented side of a polygon a point lies on: "
          "ON_POSITIVE_SIDE=1, ON_ORIENTED_BOUNDARY=0, ON_NEGATIVE_SIDE=-1.");

    m.def("bounded_side_2",
          [](const std::vector<Point2>& pts, const Point2& q) {
              std::vector<CGALPoint2> cpts;
              for (auto& p : pts) cpts.push_back(to_cgal(p));
              return static_cast<int>(
                  CGAL::bounded_side_2(cpts.begin(), cpts.end(), to_cgal(q), Kernel()));
          }, py::arg("points"), py::arg("point"),
          "Which bounded side of a polygon a point lies on (odd-even rule): "
          "ON_BOUNDED_SIDE=1, ON_BOUNDARY=0, ON_UNBOUNDED_SIDE=-1.");

    m.def("left_vertex_2",
          [](const std::vector<Point2>& pts) {
              std::vector<CGALPoint2> cpts;
              for (auto& p : pts) cpts.push_back(to_cgal(p));
              return to_wrap(*CGAL::left_vertex_2(cpts.begin(), cpts.end(), Kernel()));
          }, py::arg("points"),
          "Returns the leftmost Point2 (smallest x; ties: smallest y).");

    m.def("right_vertex_2",
          [](const std::vector<Point2>& pts) {
              std::vector<CGALPoint2> cpts;
              for (auto& p : pts) cpts.push_back(to_cgal(p));
              return to_wrap(*CGAL::right_vertex_2(cpts.begin(), cpts.end(), Kernel()));
          }, py::arg("points"),
          "Returns the rightmost Point2 (largest x; ties: largest y).");

    m.def("top_vertex_2",
          [](const std::vector<Point2>& pts) {
              std::vector<CGALPoint2> cpts;
              for (auto& p : pts) cpts.push_back(to_cgal(p));
              return to_wrap(*CGAL::top_vertex_2(cpts.begin(), cpts.end(), Kernel()));
          }, py::arg("points"),
          "Returns the topmost Point2 (largest y; ties: largest x).");

    m.def("bottom_vertex_2",
          [](const std::vector<Point2>& pts) {
              std::vector<CGALPoint2> cpts;
              for (auto& p : pts) cpts.push_back(to_cgal(p));
              return to_wrap(*CGAL::bottom_vertex_2(cpts.begin(), cpts.end(), Kernel()));
          }, py::arg("points"),
          "Returns the bottommost Point2 (smallest y; ties: smallest x).");
}