#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Triangulation_data_structure_2.h>
#include "core/types.h"

namespace py = pybind11;

// ─── Kernel & CGAL typedefs ───────────────────────────────────────────────────
typedef CGAL::Exact_predicates_inexact_constructions_kernel   T2Kernel;
typedef CGAL::Triangulation_vertex_base_2<T2Kernel>           T2Vb;
typedef CGAL::Triangulation_face_base_2<T2Kernel>             T2Fb;
typedef CGAL::Triangulation_data_structure_2<T2Vb, T2Fb>     T2Tds;
typedef CGAL::Triangulation_2<T2Kernel, T2Tds>                CGALTriangulation2;

typedef CGALTriangulation2::Vertex_handle   CGALVertexHandle2;
typedef CGALTriangulation2::Face_handle     CGALFaceHandle2;
typedef CGALTriangulation2::Edge            CGALEdge2;          // std::pair<Face_handle, int>
typedef CGALTriangulation2::Point           CGALTPoint2;

// ─── Wrapper structs ──────────────────────────────────────────────────────────

// Shared pointer to the triangulation so handles stay valid
struct Triangulation2;   // forward

struct VertexHandle2 {
    CGALVertexHandle2 vh;
    VertexHandle2() = default;
    explicit VertexHandle2(CGALVertexHandle2 v) : vh(v) {}
    bool is_valid() const { return vh != CGALVertexHandle2(); }
};

struct FaceHandle2 {
    CGALFaceHandle2 fh;
    FaceHandle2() = default;
    explicit FaceHandle2(CGALFaceHandle2 f) : fh(f) {}
    bool is_valid() const { return fh != CGALFaceHandle2(); }
};

// Edge = (FaceHandle2, int i)  — matches CGAL's pair<Face_handle, int>
struct EdgeHandle2 {
    FaceHandle2 face;
    int         index;
    EdgeHandle2() : index(-1) {}
    EdgeHandle2(FaceHandle2 f, int i) : face(f), index(i) {}
};

struct Triangulation2 {
    CGALTriangulation2 t;
    Triangulation2() = default;
};

// ─── Locate_type constants (exposed as ints in Python) ────────────────────────
// VERTEX=0, EDGE=1, FACE=2, OUTSIDE_CONVEX_HULL=3, OUTSIDE_AFFINE_HULL=4
// (mirror CGALTriangulation2::Locate_type enum values)

// ─── Construction / management ────────────────────────────────────────────────
Triangulation2  t2_create();
void            t2_clear(Triangulation2& t);
void            t2_swap(Triangulation2& a, Triangulation2& b);
int             t2_dimension(const Triangulation2& t);
int             t2_number_of_vertices(const Triangulation2& t);
int             t2_number_of_faces(const Triangulation2& t);
bool            t2_is_valid(const Triangulation2& t, bool verbose);

// ─── Special vertices / faces ─────────────────────────────────────────────────
VertexHandle2   t2_infinite_vertex(const Triangulation2& t);
FaceHandle2     t2_infinite_face(const Triangulation2& t);
VertexHandle2   t2_finite_vertex(const Triangulation2& t);

// ─── Insert / remove ──────────────────────────────────────────────────────────
VertexHandle2   t2_insert_point(Triangulation2& t, const Point2& p);
VertexHandle2   t2_insert_point_hint(Triangulation2& t, const Point2& p, const FaceHandle2& hint);
int             t2_insert_points(Triangulation2& t, const std::vector<Point2>& pts);
void            t2_remove(Triangulation2& t, const VertexHandle2& v);
VertexHandle2   t2_push_back(Triangulation2& t, const Point2& p);
void            t2_flip(Triangulation2& t, const FaceHandle2& f, int i);

// Specialised insert
VertexHandle2   t2_insert_first(Triangulation2& t, const Point2& p);
VertexHandle2   t2_insert_second(Triangulation2& t, const Point2& p);
VertexHandle2   t2_insert_in_face(Triangulation2& t, const Point2& p, const FaceHandle2& f);
VertexHandle2   t2_insert_in_edge(Triangulation2& t, const Point2& p, const FaceHandle2& f, int i);
VertexHandle2   t2_insert_outside_convex_hull(Triangulation2& t, const Point2& p, const FaceHandle2& f);
VertexHandle2   t2_insert_outside_affine_hull(Triangulation2& t, const Point2& p);

// Specialised remove
void            t2_remove_degree_3(Triangulation2& t, const VertexHandle2& v);
void            t2_remove_first(Triangulation2& t, const VertexHandle2& v);
void            t2_remove_second(Triangulation2& t, const VertexHandle2& v);

// Move
VertexHandle2   t2_move(Triangulation2& t, const VertexHandle2& v, const Point2& p);
VertexHandle2   t2_move_if_no_collision(Triangulation2& t, const VertexHandle2& v, const Point2& p);

// ─── Locate ───────────────────────────────────────────────────────────────────
FaceHandle2     t2_locate(const Triangulation2& t, const Point2& query);
FaceHandle2     t2_locate_hint(const Triangulation2& t, const Point2& query, const FaceHandle2& hint);
// Returns (FaceHandle2, locate_type:int, li:int)
py::tuple       t2_locate_full(const Triangulation2& t, const Point2& query);
FaceHandle2     t2_inexact_locate(const Triangulation2& t, const Point2& query);

// ─── Predicates ───────────────────────────────────────────────────────────────
bool            t2_is_infinite_vertex(const Triangulation2& t, const VertexHandle2& v);
bool            t2_is_infinite_face(const Triangulation2& t, const FaceHandle2& f);
bool            t2_is_infinite_edge(const Triangulation2& t, const FaceHandle2& f, int i);
bool            t2_is_edge(const Triangulation2& t, const VertexHandle2& va, const VertexHandle2& vb);
// Returns (bool, FaceHandle2, int) — face and index if edge found
py::tuple       t2_is_edge_full(const Triangulation2& t, const VertexHandle2& va, const VertexHandle2& vb);
bool            t2_is_face3(const Triangulation2& t, const VertexHandle2& v1, const VertexHandle2& v2, const VertexHandle2& v3);
// Returns (bool, FaceHandle2)
py::tuple       t2_is_face3_full(const Triangulation2& t, const VertexHandle2& v1, const VertexHandle2& v2, const VertexHandle2& v3);
// Returns (bool, VertexHandle2, FaceHandle2, int)
py::tuple       t2_includes_edge(const Triangulation2& t, const VertexHandle2& va, const VertexHandle2& vb);

// ─── Oriented / bounded side ──────────────────────────────────────────────────
int             t2_oriented_side(const Triangulation2& t, const FaceHandle2& f, const Point2& p);
int             t2_side_of_oriented_circle(const Triangulation2& t, const FaceHandle2& f, const Point2& p);

// ─── Geometry helpers ─────────────────────────────────────────────────────────
Triangle2       t2_triangle(const Triangulation2& t, const FaceHandle2& f);
Segment2        t2_segment_face_i(const Triangulation2& t, const FaceHandle2& f, int i);
Segment2        t2_segment_edge(const Triangulation2& t, const EdgeHandle2& e);
Point2          t2_circumcenter(const Triangulation2& t, const FaceHandle2& f);
Point2          t2_point_face_i(const Triangulation2& t, const FaceHandle2& f, int i);
Point2          t2_point_vertex(const Triangulation2& t, const VertexHandle2& v);
int             t2_ccw(const Triangulation2& t, int i);
int             t2_cw(const Triangulation2& t, int i);

// ─── Adjacency helpers ────────────────────────────────────────────────────────
VertexHandle2   t2_mirror_vertex(const Triangulation2& t, const FaceHandle2& f, int i);
int             t2_mirror_index(const Triangulation2& t, const FaceHandle2& f, int i);
EdgeHandle2     t2_mirror_edge(const Triangulation2& t, const EdgeHandle2& e);

// ─── Face / Vertex accessors on handles ──────────────────────────────────────
// VertexHandle2
Point2          vh2_point(const VertexHandle2& v);
bool            vh2_eq(const VertexHandle2& a, const VertexHandle2& b);
bool            vh2_neq(const VertexHandle2& a, const VertexHandle2& b);

// FaceHandle2
VertexHandle2   fh2_vertex(const FaceHandle2& f, int i);
FaceHandle2     fh2_neighbor(const FaceHandle2& f, int i);
int             fh2_index_vertex(const FaceHandle2& f, const VertexHandle2& v);
int             fh2_index_face(const FaceHandle2& f, const FaceHandle2& n);
bool            fh2_eq(const FaceHandle2& a, const FaceHandle2& b);
bool            fh2_neq(const FaceHandle2& a, const FaceHandle2& b);

// ─── Iterators → std::vector (eager) ─────────────────────────────────────────
std::vector<VertexHandle2>  t2_finite_vertices(const Triangulation2& t);
std::vector<FaceHandle2>    t2_finite_faces(const Triangulation2& t);
std::vector<EdgeHandle2>    t2_finite_edges(const Triangulation2& t);
std::vector<Point2>         t2_points(const Triangulation2& t);

std::vector<VertexHandle2>  t2_all_vertices(const Triangulation2& t);
std::vector<FaceHandle2>    t2_all_faces(const Triangulation2& t);
std::vector<EdgeHandle2>    t2_all_edges(const Triangulation2& t);

// ─── Circulators → std::vector (materialized) ────────────────────────────────
std::vector<FaceHandle2>    t2_incident_faces(const Triangulation2& t, const VertexHandle2& v);
std::vector<EdgeHandle2>    t2_incident_edges(const Triangulation2& t, const VertexHandle2& v);
std::vector<VertexHandle2>  t2_incident_vertices(const Triangulation2& t, const VertexHandle2& v);

// line_walk → vector of face handles along the line pq
std::vector<FaceHandle2>    t2_line_walk(const Triangulation2& t, const Point2& p, const Point2& q);

// ─── Convex hull (via infinite vertex circulators) ────────────────────────────
std::vector<VertexHandle2>  t2_convex_hull_vertices(const Triangulation2& t);
std::vector<EdgeHandle2>    t2_convex_hull_edges(const Triangulation2& t);

// ─── set_infinite_vertex (advanced) ──────────────────────────────────────────
void t2_set_infinite_vertex(Triangulation2& t, const VertexHandle2& v);