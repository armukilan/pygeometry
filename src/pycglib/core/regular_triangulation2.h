/**
 * @file regular_triangulation2.h
 * @brief Python bindings for CGAL::Regular_triangulation_2
 *
 * ═══════════════════════════════════════════════════════════════════════════
 * WHAT IS A REGULAR TRIANGULATION?
 * ═══════════════════════════════════════════════════════════════════════════
 *
 * A regular triangulation generalises Delaunay to WEIGHTED points.
 * Each input is a WeightedPoint2 = (position p, scalar weight w).
 *
 * The POWER of a point x with respect to weighted point (p, w):
 *   π(x, (p,w)) = |xp|² - w
 *
 * The REGULAR property (generalises empty-circle to power):
 *   For every triangle in the triangulation, the power of any other
 *   weighted point w.r.t. the triangle's power circle is NON-NEGATIVE.
 *
 * When all weights are zero → regular triangulation == Delaunay triangulation.
 *
 * ═══════════════════════════════════════════════════════════════════════════
 * HIDDEN VERTICES — the key difference from Delaunay
 * ═══════════════════════════════════════════════════════════════════════════
 *
 * Inserting a weighted point does NOT always create a new visible vertex.
 * If the new point is dominated by heavier-weight neighbours it becomes a
 * HIDDEN VERTEX — stored inside the face that covers its position.
 *
 *   number_of_vertices()        — counts only NON-hidden vertices
 *   number_of_hidden_vertices() — counts only hidden vertices
 *   finite_vertices()           — only non-hidden finite vertices
 *   hidden_vertices()           — only hidden vertices
 *
 * ═══════════════════════════════════════════════════════════════════════════
 * OWN HANDLE TYPES
 * ═══════════════════════════════════════════════════════════════════════════
 *
 * Regular_triangulation_2 uses its own TDS (RTTds with RTVb/RTFb bases).
 * Its vertex/face handles are a DIFFERENT C++ type from Triangulation_2's
 * handles. Therefore we define separate Python handle types:
 *
 *   RVertexHandle2   — handle to a Regular triangulation vertex
 *   RFaceHandle2     — handle to a Regular triangulation face
 *   REdgeHandle2     — edge as (RFaceHandle2, int index)
 *
 * These are analogous to VertexHandle2/FaceHandle2/EdgeHandle2 but for
 * the Regular triangulation's internal data structure.
 *
 * ═══════════════════════════════════════════════════════════════════════════
 * POWER DIAGRAM — dual of the regular triangulation
 * ═══════════════════════════════════════════════════════════════════════════
 *
 * Same typed dual API as DelaunayTriangulation2:
 *   dual_point(face)   → Point2 (weighted circumcenter)
 *   dual_type(edge)    → 'segment', 'ray', or 'line'
 *   dual_segment(edge) → Segment2 or None
 *   dual_ray(edge)     → Ray2 or None
 *   dual_line(edge)    → Line2 or None
 *
 * ═══════════════════════════════════════════════════════════════════════════
 * PYTHON QUICK REFERENCE
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *   import cgal_python as cg
 *
 *   rt = cg.RegularTriangulation2()
 *   rt.insert(cg.WeightedPoint2(cg.Point2(0, 0), 1.0))
 *   rt.insert(cg.WeightedPoint2(cg.Point2(4, 0), 0.5))
 *   rt.insert(cg.WeightedPoint2(cg.Point2(2, 3), 2.0))
 *
 *   print(rt.number_of_vertices())        # non-hidden only
 *   print(rt.number_of_hidden_vertices())  # hidden only
 *
 *   for vh in rt.hidden_vertices():
 *       print(rt.weighted_point(vh))       # WeightedPoint2
 *
 *   for f in rt.finite_faces():
 *       print(rt.dual_point(f))            # Point2 power circle center
 *
 *   for e in rt.finite_edges():
 *       t = rt.dual_type(e)
 *       if t == 'segment': seg = rt.dual_segment(e)
 *       elif t == 'ray':   ray = rt.dual_ray(e)
 *
 *   vh = rt.nearest_power_vertex(cg.Point2(1, 1))
 */

#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Regular_triangulation_2.h>
#include <CGAL/Regular_triangulation_vertex_base_2.h>
#include <CGAL/Regular_triangulation_face_base_2.h>
#include <CGAL/Triangulation_data_structure_2.h>
#include <CGAL/Object.h>
#include "core/types.h"        // WeightedPoint2, Point2, Segment2, Ray2, Line2, Vector2
#include "core/triangulation2.h"  // T2Kernel

namespace py = pybind11;

// ─── CGAL typedefs ────────────────────────────────────────────────────────────
typedef CGAL::Regular_triangulation_vertex_base_2<T2Kernel>     RTVb;
typedef CGAL::Regular_triangulation_face_base_2<T2Kernel>       RTFb;
typedef CGAL::Triangulation_data_structure_2<RTVb, RTFb>        RTTds;
typedef CGAL::Regular_triangulation_2<T2Kernel, RTTds>          CGALRegular2;

// Bare point type (position without weight)
typedef CGALRegular2::Bare_point   CGALBarePoint2;

// NOTE: CGALWeightedPoint2 is already defined in types.h as Kernel::Weighted_point_2
// We reuse it directly — no redefinition needed here.


// ═══════════════════════════════════════════════════════════════════════════
// HANDLE TYPES — Regular triangulation has its own TDS, so own handle types
// ═══════════════════════════════════════════════════════════════════════════

/**
 * @brief Handle to a vertex in RegularTriangulation2.
 * Analogous to VertexHandle2 but for the Regular TDS.
 * Python usage:
 *   vh = rt.insert(cg.WeightedPoint2(cg.Point2(1, 2), 0.5))
 *   print(rt.weighted_point(vh))
 *   print(rt.bare_point(vh))
 */
struct RVertexHandle2 {
    CGALRegular2::Vertex_handle vh;
    RVertexHandle2() = default;
    explicit RVertexHandle2(CGALRegular2::Vertex_handle v) : vh(v) {}
    bool is_valid() const { return vh != CGALRegular2::Vertex_handle(); }
    bool operator==(const RVertexHandle2& o) const { return vh == o.vh; }
    bool operator!=(const RVertexHandle2& o) const { return vh != o.vh; }
};

/**
 * @brief Handle to a face in RegularTriangulation2.
 * Analogous to FaceHandle2 but for the Regular TDS.
 * Python usage:
 *   for f in rt.finite_faces():
 *       v0 = f.vertex(0)       # RVertexHandle2
 *       nb = f.neighbor(1)     # RFaceHandle2
 */
struct RFaceHandle2 {
    CGALRegular2::Face_handle fh;
    RFaceHandle2() = default;
    explicit RFaceHandle2(CGALRegular2::Face_handle f) : fh(f) {}
    bool is_valid()    const { return fh != CGALRegular2::Face_handle(); }
    RVertexHandle2 vertex(int i)          const { return RVertexHandle2(fh->vertex(i)); }
    RFaceHandle2   neighbor(int i)        const { return RFaceHandle2(fh->neighbor(i)); }
    int            index(const RVertexHandle2& v) const { return fh->index(v.vh); }
    int            index_face(const RFaceHandle2& n) const { return fh->index(n.fh); }
    bool operator==(const RFaceHandle2& o) const { return fh == o.fh; }
    bool operator!=(const RFaceHandle2& o) const { return fh != o.fh; }
};

/**
 * @brief Edge in RegularTriangulation2 as (face, index).
 * Analogous to EdgeHandle2 but for the Regular TDS.
 * The edge is opposite to vertex i of the face.
 */
struct REdgeHandle2 {
    RFaceHandle2 face;
    int          index;
    REdgeHandle2() : index(-1) {}
    REdgeHandle2(RFaceHandle2 f, int i) : face(f), index(i) {}
};


// ═══════════════════════════════════════════════════════════════════════════
// WRAPPER STRUCT
// ═══════════════════════════════════════════════════════════════════════════

/**
 * @brief Python wrapper for CGAL::Regular_triangulation_2.
 *
 * C++ equivalent: CGAL::Regular_triangulation_2<Kernel, Tds>
 *
 * Maintains a regular triangulation of weighted 2D points. Points with
 * high weights can dominate (hide) nearby lower-weight points. The dual
 * is the power diagram.
 *
 * Python usage:
 *   rt = cg.RegularTriangulation2()
 *   rt.insert(cg.WeightedPoint2(cg.Point2(0,0), 1.0))
 *   print(rt)  # RegularTriangulation2(vertices=1, hidden=0, faces=0)
 */
struct RegularTriangulation2 {
    CGALRegular2 rt;
    RegularTriangulation2() = default;
};


// ═══════════════════════════════════════════════════════════════════════════
// INTERNAL CONVERSION (declared here, defined in .cpp)
// ═══════════════════════════════════════════════════════════════════════════

CGALWeightedPoint2 to_cgal_wp(const WeightedPoint2& wp);
WeightedPoint2     from_cgal_wp(const CGALWeightedPoint2& cwp);
CGALBarePoint2     to_cgal_bare(const Point2& p);
Point2             from_cgal_bare(const CGALBarePoint2& p);


// ═══════════════════════════════════════════════════════════════════════════
// CONSTRUCTION / MANAGEMENT
// ═══════════════════════════════════════════════════════════════════════════

RegularTriangulation2 rt2_create();
void rt2_clear(RegularTriangulation2& rt);
void rt2_swap(RegularTriangulation2& a, RegularTriangulation2& b);
int  rt2_dimension(const RegularTriangulation2& rt);

/** Number of NON-HIDDEN finite vertices. C++: rt.number_of_vertices() */
int  rt2_number_of_vertices(const RegularTriangulation2& rt);

/** Number of HIDDEN vertices. C++: rt.number_of_hidden_vertices() */
int  rt2_number_of_hidden_vertices(const RegularTriangulation2& rt);

int  rt2_number_of_faces(const RegularTriangulation2& rt);
bool rt2_is_valid(const RegularTriangulation2& rt, bool verbose);


// ═══════════════════════════════════════════════════════════════════════════
// SPECIAL VERTICES / FACES
// ═══════════════════════════════════════════════════════════════════════════

RVertexHandle2 rt2_infinite_vertex(const RegularTriangulation2& rt);
RFaceHandle2   rt2_infinite_face(const RegularTriangulation2& rt);
RVertexHandle2 rt2_finite_vertex(const RegularTriangulation2& rt);


// ═══════════════════════════════════════════════════════════════════════════
// INSERT / REMOVE
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Inserts a WeightedPoint2. Returns RVertexHandle2 (may be hidden if dominated).
 * C++: rt.insert(Weighted_point)
 * Python: vh = rt.insert(cg.WeightedPoint2(cg.Point2(x,y), w))
 */
RVertexHandle2 rt2_insert_weighted_point(RegularTriangulation2& rt,
                                          const WeightedPoint2& wp);

/** Insert with a face hint for faster location. */
RVertexHandle2 rt2_insert_weighted_point_hint(RegularTriangulation2& rt,
                                               const WeightedPoint2& wp,
                                               const RFaceHandle2& hint);

/**
 * Bulk insert from Python list. Returns NET change in vertex count
 * (may be negative if points are hidden). Spatial sorting used internally.
 * Python: delta = rt.insert([cg.WeightedPoint2(cg.Point2(x,y), w), ...])
 */
int rt2_insert_weighted_points(RegularTriangulation2& rt,
                                const std::vector<WeightedPoint2>& wpts);

/** Remove a vertex (visible or hidden). C++: rt.remove(v) */
void rt2_remove(RegularTriangulation2& rt, const RVertexHandle2& v);


// ═══════════════════════════════════════════════════════════════════════════
// QUERIES
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Returns the vertex nearest to bare point p by POWER distance.
 * Power distance: |p - site|² - weight. Takes BARE Point2, NOT WeightedPoint2.
 * C++: rt.nearest_power_vertex(p)
 * Python: vh = rt.nearest_power_vertex(cg.Point2(1, 2))
 */
RVertexHandle2 rt2_nearest_power_vertex(const RegularTriangulation2& rt,
                                         const Point2& p);


// ═══════════════════════════════════════════════════════════════════════════
// CONFLICT ZONE — all require a start RFaceHandle2 from rt2_locate()
// ═══════════════════════════════════════════════════════════════════════════

/** Returns list[RFaceHandle2] in conflict with wp. */
std::vector<RFaceHandle2> rt2_get_conflicts(const RegularTriangulation2& rt,
                                             const WeightedPoint2& wp,
                                             const RFaceHandle2& start);

/** Returns list[REdgeHandle2] — CCW boundary of conflict zone. */
std::vector<REdgeHandle2> rt2_get_boundary_of_conflicts(const RegularTriangulation2& rt,
                                                         const WeightedPoint2& wp,
                                                         const RFaceHandle2& start);

/** Returns list[RVertexHandle2] — hidden vertices in conflict zone. */
std::vector<RVertexHandle2> rt2_get_hidden_vertices(const RegularTriangulation2& rt,
                                                     const WeightedPoint2& wp,
                                                     const RFaceHandle2& start);

/** Returns (list[RFaceHandle2], list[REdgeHandle2]). Single traversal. */
py::tuple rt2_get_conflicts_and_boundary(const RegularTriangulation2& rt,
                                          const WeightedPoint2& wp,
                                          const RFaceHandle2& start);

/** Returns (list[RFaceHandle2], list[RVertexHandle2]). Single traversal. */
py::tuple rt2_get_conflicts_and_hidden_vertices(const RegularTriangulation2& rt,
                                                 const WeightedPoint2& wp,
                                                 const RFaceHandle2& start);

/** Returns (list[REdgeHandle2], list[RVertexHandle2]). Single traversal. */
py::tuple rt2_get_boundary_of_conflicts_and_hidden_vertices(
    const RegularTriangulation2& rt,
    const WeightedPoint2& wp,
    const RFaceHandle2& start);

/** Returns (list[RFaceHandle2], list[REdgeHandle2], list[RVertexHandle2]). */
py::tuple rt2_get_conflicts_and_boundary_and_hidden_vertices(
    const RegularTriangulation2& rt,
    const WeightedPoint2& wp,
    const RFaceHandle2& start);


// ═══════════════════════════════════════════════════════════════════════════
// POWER DIAGRAM — dual functions
// ═══════════════════════════════════════════════════════════════════════════

/** Weighted circumcenter of face f as Point2. C++: rt.dual(f) */
Point2 rt2_dual_point(const RegularTriangulation2& rt, const RFaceHandle2& f);

/** Same as dual_point — explicit alias. C++: rt.weighted_circumcenter(f) */
Point2 rt2_weighted_circumcenter(const RegularTriangulation2& rt, const RFaceHandle2& f);

/** Returns 'segment', 'ray', or 'line'. */
std::string rt2_dual_type(const RegularTriangulation2& rt, const REdgeHandle2& e);

/** Returns Segment2 if dual_type=='segment', else None. */
py::object rt2_dual_segment(const RegularTriangulation2& rt, const REdgeHandle2& e);

/** Returns Ray2 if dual_type=='ray', else None. */
py::object rt2_dual_ray(const RegularTriangulation2& rt, const REdgeHandle2& e);

/** Returns Line2 if dual_type=='line', else None. */
py::object rt2_dual_line(const RegularTriangulation2& rt, const REdgeHandle2& e);


// ═══════════════════════════════════════════════════════════════════════════
// PREDICATES
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Power test of WeightedPoint2 wp w.r.t. face f.
 *   +1 = inside power circle (regularity violated)
 *   -1 = outside (regularity satisfied)
 *    0 = on the power circle
 * C++: rt.power_test(f, wp)
 */
int  rt2_power_test(const RegularTriangulation2& rt,
                    const RFaceHandle2& f, const WeightedPoint2& wp);

bool      rt2_is_infinite_vertex(const RegularTriangulation2& rt, const RVertexHandle2& v);
bool      rt2_is_infinite_face(const RegularTriangulation2& rt, const RFaceHandle2& f);
bool      rt2_is_infinite_edge(const RegularTriangulation2& rt, const RFaceHandle2& f, int i);
bool      rt2_is_edge(const RegularTriangulation2& rt,
                      const RVertexHandle2& va, const RVertexHandle2& vb);
py::tuple rt2_is_edge_full(const RegularTriangulation2& rt,
                            const RVertexHandle2& va, const RVertexHandle2& vb);
bool      rt2_is_face3(const RegularTriangulation2& rt,
                       const RVertexHandle2& v1, const RVertexHandle2& v2,
                       const RVertexHandle2& v3);
py::tuple rt2_is_face3_full(const RegularTriangulation2& rt,
                             const RVertexHandle2& v1, const RVertexHandle2& v2,
                             const RVertexHandle2& v3);


// ═══════════════════════════════════════════════════════════════════════════
// LOCATE — takes bare Point2 (no weight)
// ═══════════════════════════════════════════════════════════════════════════

RFaceHandle2 rt2_locate(const RegularTriangulation2& rt, const Point2& query);
RFaceHandle2 rt2_locate_hint(const RegularTriangulation2& rt,
                              const Point2& query, const RFaceHandle2& hint);
/** Returns (RFaceHandle2, locate_type: int, li: int). Uses T2_* constants. */
py::tuple    rt2_locate_full(const RegularTriangulation2& rt, const Point2& query);
RFaceHandle2 rt2_inexact_locate(const RegularTriangulation2& rt, const Point2& query);


// ═══════════════════════════════════════════════════════════════════════════
// GEOMETRY HELPERS
// ═══════════════════════════════════════════════════════════════════════════

Triangle2 rt2_triangle(const RegularTriangulation2& rt, const RFaceHandle2& f);
Segment2  rt2_segment_face_i(const RegularTriangulation2& rt,
                               const RFaceHandle2& f, int i);
Segment2  rt2_segment_edge(const RegularTriangulation2& rt, const REdgeHandle2& e);
Point2    rt2_circumcenter(const RegularTriangulation2& rt, const RFaceHandle2& f);

/**
 * Returns the WeightedPoint2 (position + weight) stored at vertex v.
 * C++: v->point()  which is a Weighted_point_2
 * Python: wp = rt.weighted_point(vh)  →  cg.WeightedPoint2
 */
WeightedPoint2 rt2_weighted_point(const RegularTriangulation2& rt,
                                   const RVertexHandle2& v);

/**
 * Returns the bare Point2 (position only, no weight) of vertex v.
 * C++: v->point().point()
 * Python: p = rt.bare_point(vh)  →  cg.Point2
 */
Point2 rt2_bare_point(const RegularTriangulation2& rt, const RVertexHandle2& v);

int rt2_ccw(const RegularTriangulation2& rt, int i);
int rt2_cw(const RegularTriangulation2& rt, int i);


// ═══════════════════════════════════════════════════════════════════════════
// ADJACENCY
// ═══════════════════════════════════════════════════════════════════════════

RVertexHandle2 rt2_mirror_vertex(const RegularTriangulation2& rt,
                                  const RFaceHandle2& f, int i);
int            rt2_mirror_index(const RegularTriangulation2& rt,
                                 const RFaceHandle2& f, int i);
REdgeHandle2   rt2_mirror_edge(const RegularTriangulation2& rt,
                                const REdgeHandle2& e);


// ═══════════════════════════════════════════════════════════════════════════
// ITERATORS → Python lists
// ═══════════════════════════════════════════════════════════════════════════

/** Non-hidden finite vertices only. */
std::vector<RVertexHandle2> rt2_finite_vertices(const RegularTriangulation2& rt);
std::vector<RFaceHandle2>   rt2_finite_faces(const RegularTriangulation2& rt);
std::vector<REdgeHandle2>   rt2_finite_edges(const RegularTriangulation2& rt);
/** Bare Point2 positions of non-hidden finite vertices. */
std::vector<Point2>         rt2_points(const RegularTriangulation2& rt);
/** All non-hidden vertices including infinite vertex. */
std::vector<RVertexHandle2> rt2_all_vertices(const RegularTriangulation2& rt);
std::vector<RFaceHandle2>   rt2_all_faces(const RegularTriangulation2& rt);
std::vector<REdgeHandle2>   rt2_all_edges(const RegularTriangulation2& rt);
/** Hidden vertices — dominated by heavier-weight neighbours. */
std::vector<RVertexHandle2> rt2_hidden_vertices(const RegularTriangulation2& rt);


// ═══════════════════════════════════════════════════════════════════════════
// CIRCULATORS → Python lists
// ═══════════════════════════════════════════════════════════════════════════

std::vector<RFaceHandle2>   rt2_incident_faces(const RegularTriangulation2& rt,
                                                const RVertexHandle2& v);
std::vector<REdgeHandle2>   rt2_incident_edges(const RegularTriangulation2& rt,
                                                const RVertexHandle2& v);
std::vector<RVertexHandle2> rt2_incident_vertices(const RegularTriangulation2& rt,
                                                   const RVertexHandle2& v);
std::vector<RFaceHandle2>   rt2_line_walk(const RegularTriangulation2& rt,
                                          const Point2& p, const Point2& q);


// ═══════════════════════════════════════════════════════════════════════════
// CONVEX HULL
// ═══════════════════════════════════════════════════════════════════════════

std::vector<RVertexHandle2> rt2_convex_hull_vertices(const RegularTriangulation2& rt);
std::vector<REdgeHandle2>   rt2_convex_hull_edges(const RegularTriangulation2& rt);