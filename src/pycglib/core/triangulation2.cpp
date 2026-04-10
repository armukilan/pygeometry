#include "core/triangulation2.h"
#include <stdexcept>

// ─── Helper: Point2 <-> CGALTPoint2 ──────────────────────────────────────────
static inline CGALTPoint2 to_cgal(const Point2& p) {
	return CGALTPoint2(p.x(), p.y());
}
static inline Point2 from_cgal(const CGALTPoint2& p) {
	return Point2(CGAL::to_double(p.x()), CGAL::to_double(p.y()));
}

// ─── Construction / management ────────────────────────────────────────────────
Triangulation2 t2_create() { return Triangulation2(); }

void t2_clear(Triangulation2& t) { t.t.clear(); }

void t2_swap(Triangulation2& a, Triangulation2& b) { a.t.swap(b.t); }

int t2_dimension(const Triangulation2& t) { return t.t.dimension(); }

int t2_number_of_vertices(const Triangulation2& t) {
	return static_cast<int>(t.t.number_of_vertices());
}

int t2_number_of_faces(const Triangulation2& t) {
	return static_cast<int>(t.t.number_of_faces());
}

bool t2_is_valid(const Triangulation2& t, bool verbose) {
	return t.t.is_valid(verbose);
}

// ─── Special vertices / faces ─────────────────────────────────────────────────
VertexHandle2 t2_infinite_vertex(const Triangulation2& t) {
	return VertexHandle2(t.t.infinite_vertex());
}

FaceHandle2 t2_infinite_face(const Triangulation2& t) {
	return FaceHandle2(t.t.infinite_face());
}

VertexHandle2 t2_finite_vertex(const Triangulation2& t) {
	return VertexHandle2(t.t.finite_vertex());
}

// ─── Insert / remove ──────────────────────────────────────────────────────────
VertexHandle2 t2_insert_point(Triangulation2& t, const Point2& p) {
	return VertexHandle2(t.t.insert(to_cgal(p)));
}

VertexHandle2 t2_insert_point_hint(Triangulation2& t, const Point2& p, const FaceHandle2& hint) {
	return VertexHandle2(t.t.insert(to_cgal(p), hint.fh));
}

int t2_insert_points(Triangulation2& t, const std::vector<Point2>& pts) {
	std::vector<CGALTPoint2> cpts;
	cpts.reserve(pts.size());
	for (const auto& p : pts) cpts.push_back(to_cgal(p));
	return static_cast<int>(t.t.insert(cpts.begin(), cpts.end()));
}

void t2_remove(Triangulation2& t, const VertexHandle2& v) {
	t.t.remove(v.vh);
}

VertexHandle2 t2_push_back(Triangulation2& t, const Point2& p) {
	return VertexHandle2(t.t.push_back(to_cgal(p)));
}

void t2_flip(Triangulation2& t, const FaceHandle2& f, int i) {
	t.t.flip(f.fh, i);
}

// ─── Specialised insert ───────────────────────────────────────────────────────
VertexHandle2 t2_insert_first(Triangulation2& t, const Point2& p) {
	return VertexHandle2(t.t.insert_first(to_cgal(p)));
}

VertexHandle2 t2_insert_second(Triangulation2& t, const Point2& p) {
	return VertexHandle2(t.t.insert_second(to_cgal(p)));
}

VertexHandle2 t2_insert_in_face(Triangulation2& t, const Point2& p, const FaceHandle2& f) {
	return VertexHandle2(t.t.insert_in_face(to_cgal(p), f.fh));
}

VertexHandle2 t2_insert_in_edge(Triangulation2& t, const Point2& p, const FaceHandle2& f, int i) {
	return VertexHandle2(t.t.insert_in_edge(to_cgal(p), f.fh, i));
}

VertexHandle2 t2_insert_outside_convex_hull(Triangulation2& t, const Point2& p, const FaceHandle2& f) {
	return VertexHandle2(t.t.insert_outside_convex_hull(to_cgal(p), f.fh));
}

VertexHandle2 t2_insert_outside_affine_hull(Triangulation2& t, const Point2& p) {
	return VertexHandle2(t.t.insert_outside_affine_hull(to_cgal(p)));
}

// ─── Specialised remove ───────────────────────────────────────────────────────
void t2_remove_degree_3(Triangulation2& t, const VertexHandle2& v) {
	t.t.remove_degree_3(v.vh);
}

void t2_remove_first(Triangulation2& t, const VertexHandle2& v) {
	t.t.remove_first(v.vh);
}

void t2_remove_second(Triangulation2& t, const VertexHandle2& v) {
	t.t.remove_second(v.vh);
}

// ─── Move ─────────────────────────────────────────────────────────────────────
VertexHandle2 t2_move(Triangulation2& t, const VertexHandle2& v, const Point2& p) {
	return VertexHandle2(t.t.move(v.vh, to_cgal(p)));
}

VertexHandle2 t2_move_if_no_collision(Triangulation2& t, const VertexHandle2& v, const Point2& p) {
	return VertexHandle2(t.t.move_if_no_collision(v.vh, to_cgal(p)));
}

// ─── Locate ───────────────────────────────────────────────────────────────────
FaceHandle2 t2_locate(const Triangulation2& t, const Point2& query) {
	return FaceHandle2(t.t.locate(to_cgal(query)));
}

FaceHandle2 t2_locate_hint(const Triangulation2& t, const Point2& query, const FaceHandle2& hint) {
	return FaceHandle2(t.t.locate(to_cgal(query), hint.fh));
}

py::tuple t2_locate_full(const Triangulation2& t, const Point2& query) {
	CGALTriangulation2::Locate_type lt;
	int li;
	auto fh = t.t.locate(to_cgal(query), lt, li);
	return py::make_tuple(FaceHandle2(fh), static_cast<int>(lt), li);
}

FaceHandle2 t2_inexact_locate(const Triangulation2& t, const Point2& query) {
	return FaceHandle2(t.t.inexact_locate(to_cgal(query)));
}

// ─── Predicates ───────────────────────────────────────────────────────────────
bool t2_is_infinite_vertex(const Triangulation2& t, const VertexHandle2& v) {
	return t.t.is_infinite(v.vh);
}

bool t2_is_infinite_face(const Triangulation2& t, const FaceHandle2& f) {
	return t.t.is_infinite(f.fh);
}

bool t2_is_infinite_edge(const Triangulation2& t, const FaceHandle2& f, int i) {
	return t.t.is_infinite(f.fh, i);
}

bool t2_is_edge(const Triangulation2& t, const VertexHandle2& va, const VertexHandle2& vb) {
	return t.t.is_edge(va.vh, vb.vh);
}

py::tuple t2_is_edge_full(const Triangulation2& t, const VertexHandle2& va, const VertexHandle2& vb) {
	CGALFaceHandle2 fr;
	int i;
	bool result = t.t.is_edge(va.vh, vb.vh, fr, i);
	return py::make_tuple(result, FaceHandle2(fr), i);
}

bool t2_is_face3(const Triangulation2& t, const VertexHandle2& v1,
				 const VertexHandle2& v2, const VertexHandle2& v3) {
	return t.t.is_face(v1.vh, v2.vh, v3.vh);
}

py::tuple t2_is_face3_full(const Triangulation2& t, const VertexHandle2& v1,
							const VertexHandle2& v2, const VertexHandle2& v3) {
	CGALFaceHandle2 fr;
	bool result = t.t.is_face(v1.vh, v2.vh, v3.vh, fr);
	return py::make_tuple(result, FaceHandle2(fr));
}

py::tuple t2_includes_edge(const Triangulation2& t,
							const VertexHandle2& va, const VertexHandle2& vb) {
	CGALVertexHandle2 vbb;
	CGALFaceHandle2 fr;
	int i;
	bool result = t.t.includes_edge(va.vh, vb.vh, vbb, fr, i);
	return py::make_tuple(result, VertexHandle2(vbb), FaceHandle2(fr), i);
}

// ─── Oriented / bounded side ──────────────────────────────────────────────────
int t2_oriented_side(const Triangulation2& t, const FaceHandle2& f, const Point2& p) {
	auto side = t.t.oriented_side(f.fh, to_cgal(p));
	if (side == CGAL::ON_POSITIVE_SIDE)  return  1;
	if (side == CGAL::ON_NEGATIVE_SIDE)  return -1;
	return 0;
}

int t2_side_of_oriented_circle(const Triangulation2& t, const FaceHandle2& f, const Point2& p) {
	auto side = t.t.side_of_oriented_circle(f.fh, to_cgal(p));
	if (side == CGAL::ON_POSITIVE_SIDE)  return  1;
	if (side == CGAL::ON_NEGATIVE_SIDE)  return -1;
	return 0;
}

// ─── Geometry helpers ─────────────────────────────────────────────────────────
Triangle2 t2_triangle(const Triangulation2& t, const FaceHandle2& f) {
	auto tri = t.t.triangle(f.fh);
	return Triangle2(
		Point2(CGAL::to_double(tri[0].x()), CGAL::to_double(tri[0].y())),
		Point2(CGAL::to_double(tri[1].x()), CGAL::to_double(tri[1].y())),
		Point2(CGAL::to_double(tri[2].x()), CGAL::to_double(tri[2].y()))
	);
}

Segment2 t2_segment_face_i(const Triangulation2& t, const FaceHandle2& f, int i) {
	auto seg = t.t.segment(f.fh, i);
	return Segment2(from_cgal(seg.source()), from_cgal(seg.target()));
}

Segment2 t2_segment_edge(const Triangulation2& t, const EdgeHandle2& e) {
	CGALEdge2 ce(e.face.fh, e.index);
	auto seg = t.t.segment(ce);
	return Segment2(from_cgal(seg.source()), from_cgal(seg.target()));
}

Point2 t2_circumcenter(const Triangulation2& t, const FaceHandle2& f) {
	return from_cgal(t.t.circumcenter(f.fh));
}

Point2 t2_point_face_i(const Triangulation2& t, const FaceHandle2& f, int i) {
	return from_cgal(t.t.point(f.fh, i));
}

Point2 t2_point_vertex(const Triangulation2& t, const VertexHandle2& v) {
	return from_cgal(t.t.point(v.vh));
}

int t2_ccw(const Triangulation2& t, int i) { return t.t.ccw(i); }
int t2_cw(const Triangulation2& t, int i)  { return t.t.cw(i); }

// ─── Adjacency helpers ────────────────────────────────────────────────────────
VertexHandle2 t2_mirror_vertex(const Triangulation2& t, const FaceHandle2& f, int i) {
	return VertexHandle2(t.t.mirror_vertex(f.fh, i));
}

int t2_mirror_index(const Triangulation2& t, const FaceHandle2& f, int i) {
	return t.t.mirror_index(f.fh, i);
}

EdgeHandle2 t2_mirror_edge(const Triangulation2& t, const EdgeHandle2& e) {
	CGALEdge2 ce(e.face.fh, e.index);
	auto me = t.t.mirror_edge(ce);
	return EdgeHandle2(FaceHandle2(me.first), me.second);
}

// ─── VertexHandle2 accessors ──────────────────────────────────────────────────
Point2 vh2_point(const VertexHandle2& v) {
	return from_cgal(v.vh->point());
}

bool vh2_eq(const VertexHandle2& a, const VertexHandle2& b) { return a.vh == b.vh; }
bool vh2_neq(const VertexHandle2& a, const VertexHandle2& b) { return a.vh != b.vh; }

// ─── FaceHandle2 accessors ────────────────────────────────────────────────────
VertexHandle2 fh2_vertex(const FaceHandle2& f, int i) {
	return VertexHandle2(f.fh->vertex(i));
}

FaceHandle2 fh2_neighbor(const FaceHandle2& f, int i) {
	return FaceHandle2(f.fh->neighbor(i));
}

int fh2_index_vertex(const FaceHandle2& f, const VertexHandle2& v) {
	return f.fh->index(v.vh);
}

int fh2_index_face(const FaceHandle2& f, const FaceHandle2& n) {
	return f.fh->index(n.fh);
}

bool fh2_eq(const FaceHandle2& a, const FaceHandle2& b) { return a.fh == b.fh; }
bool fh2_neq(const FaceHandle2& a, const FaceHandle2& b) { return a.fh != b.fh; }

// ─── Iterators → std::vector ──────────────────────────────────────────────────
std::vector<VertexHandle2> t2_finite_vertices(const Triangulation2& t) {
	std::vector<VertexHandle2> out;
	for (auto it = t.t.finite_vertices_begin(); it != t.t.finite_vertices_end(); ++it)
		out.emplace_back(it);
	return out;
}

std::vector<FaceHandle2> t2_finite_faces(const Triangulation2& t) {
	std::vector<FaceHandle2> out;
	for (auto it = t.t.finite_faces_begin(); it != t.t.finite_faces_end(); ++it)
		out.emplace_back(it);
	return out;
}

std::vector<EdgeHandle2> t2_finite_edges(const Triangulation2& t) {
	std::vector<EdgeHandle2> out;
	for (auto it = t.t.finite_edges_begin(); it != t.t.finite_edges_end(); ++it)
		out.emplace_back(FaceHandle2(it->first), it->second);
	return out;
}

std::vector<Point2> t2_points(const Triangulation2& t) {
	std::vector<Point2> out;
	for (auto it = t.t.points_begin(); it != t.t.points_end(); ++it)
		out.push_back(from_cgal(*it));
	return out;
}

std::vector<VertexHandle2> t2_all_vertices(const Triangulation2& t) {
	std::vector<VertexHandle2> out;
	for (auto it = t.t.all_vertices_begin(); it != t.t.all_vertices_end(); ++it)
		out.emplace_back(it);
	return out;
}

std::vector<FaceHandle2> t2_all_faces(const Triangulation2& t) {
	std::vector<FaceHandle2> out;
	for (auto it = t.t.all_faces_begin(); it != t.t.all_faces_end(); ++it)
		out.emplace_back(it);
	return out;
}

std::vector<EdgeHandle2> t2_all_edges(const Triangulation2& t) {
	std::vector<EdgeHandle2> out;
	for (auto it = t.t.all_edges_begin(); it != t.t.all_edges_end(); ++it)
		out.emplace_back(FaceHandle2(it->first), it->second);
	return out;
}

// ─── Circulators → std::vector ────────────────────────────────────────────────
std::vector<FaceHandle2> t2_incident_faces(const Triangulation2& t, const VertexHandle2& v) {
	std::vector<FaceHandle2> out;
	auto circ = t.t.incident_faces(v.vh);
	auto done = circ;
	if (circ != nullptr) {
		do { out.emplace_back(circ); ++circ; } while (circ != done);
	}
	return out;
}

std::vector<EdgeHandle2> t2_incident_edges(const Triangulation2& t, const VertexHandle2& v) {
	std::vector<EdgeHandle2> out;
	auto circ = t.t.incident_edges(v.vh);
	auto done = circ;
	if (circ != nullptr) {
		do {
			out.emplace_back(FaceHandle2(circ->first), circ->second);
			++circ;
		} while (circ != done);
	}
	return out;
}

std::vector<VertexHandle2> t2_incident_vertices(const Triangulation2& t, const VertexHandle2& v) {
	std::vector<VertexHandle2> out;
	auto circ = t.t.incident_vertices(v.vh);
	auto done = circ;
	if (circ != nullptr) {
		do { out.emplace_back(circ); ++circ; } while (circ != done);
	}
	return out;
}

std::vector<FaceHandle2> t2_line_walk(const Triangulation2& t, const Point2& p, const Point2& q) {
	std::vector<FaceHandle2> out;
	auto circ = t.t.line_walk(to_cgal(p), to_cgal(q));
	if (circ.is_empty()) return out;
	auto done = circ;
	do { out.emplace_back(circ); ++circ; } while (circ != done);
	return out;
}

// ─── Convex hull via infinite vertex ─────────────────────────────────────────
std::vector<VertexHandle2> t2_convex_hull_vertices(const Triangulation2& t) {
	std::vector<VertexHandle2> out;
	auto inf = t.t.infinite_vertex();
	auto circ = t.t.incident_vertices(inf);
	auto done = circ;
	if (circ != nullptr) {
		do {
			if (!t.t.is_infinite(circ))
				out.emplace_back(circ);
			++circ;
		} while (circ != done);
	}
	return out;
}

// std::vector<EdgeHandle2> t2_convex_hull_edges(const Triangulation2& t) {
// 	std::vector<EdgeHandle2> out;
// 	auto inf = t.t.infinite_vertex();
// 	auto circ = t.t.incident_edges(inf);
// 	auto done = circ;
// 	if (circ != nullptr) {
// 		do {
// 			CGALEdge2 e = *circ;
// 			// The mirror edge (from the finite face's side) is the hull edge
// 			auto mirror = t.t.mirror_edge(e);
// 			if (!t.t.is_infinite(mirror))
// 				out.emplace_back(FaceHandle2(mirror.first), mirror.second);
// 			// if (!t.t.is_infinite(e))
// 			//     out.emplace_back(FaceHandle2(e.first), e.second);
// 			++circ;
// 		} while (circ != done);
// 	}
// 	return out;
// }
std::vector<EdgeHandle2> t2_convex_hull_edges(const Triangulation2& t) {
    std::vector<EdgeHandle2> out;
    auto inf = t.t.infinite_vertex();
    auto circ = t.t.incident_edges(inf);
    auto done = circ;
    if (circ != nullptr) {
        do {
            CGALEdge2 e = *circ;
            CGALEdge2 mirror = t.t.mirror_edge(e);
            out.emplace_back(FaceHandle2(mirror.first), mirror.second);
            ++circ;
        } while (circ != done);
    }
    return out;
}

// ─── Advanced ─────────────────────────────────────────────────────────────────
void t2_set_infinite_vertex(Triangulation2& t, const VertexHandle2& v) {
	t.t.set_infinite_vertex(v.vh);
}