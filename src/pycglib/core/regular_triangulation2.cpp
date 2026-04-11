/**
 * @file regular_triangulation2.cpp
 * @brief Implementation of Regular_triangulation_2 wrapper.
 *
 * WeightedPoint2 conversion:
 *   Our Python WeightedPoint2 wraps CGALWeightedPoint2 directly as member .wp
 *   So to_cgal_wp just returns wp.wp (the inner CGAL object directly).
 *   from_cgal_wp constructs via WeightedPoint2(Point2, weight) constructor.
 *
 * Edge construction:
 *   CGALRegular2::Edge is std::pair<Face_handle, int>.
 *   On MSVC, brace-initialisation of pairs can fail.
 *   Use std::make_pair(fh, i) explicitly everywhere.
 *
 * Handle wrapping:
 *   All functions use RVertexHandle2, RFaceHandle2, REdgeHandle2 throughout.
 *   These wrap CGALRegular2::Vertex_handle and Face_handle respectively.
 */

#include "core/regular_triangulation2.h"
#include <stdexcept>

// The Regular triangulation's own weighted point type
typedef CGALRegular2::Weighted_point  RTWeightedPoint;

CGALWeightedPoint2 to_cgal_wp(const WeightedPoint2& wp) {
    return wp.wp;
}

// NEW: convert to the RT's internal weighted point type
static inline RTWeightedPoint to_rt_wp(const WeightedPoint2& wp) {
    return RTWeightedPoint(
        CGALBarePoint2(wp.wp.point().x(), wp.wp.point().y()),
        wp.wp.weight()
    );
}

// NEW: convert RT weighted point back
static inline WeightedPoint2 from_rt_wp(const RTWeightedPoint& rtwp) {
    Point2 bare(CGAL::to_double(rtwp.point().x()),
                CGAL::to_double(rtwp.point().y()));
    return WeightedPoint2(bare, CGAL::to_double(rtwp.weight()));
}

// ─── Conversion helpers ───────────────────────────────────────────────────────

// CGALWeightedPoint2 to_cgal_wp(const WeightedPoint2& wp) {
//     // WeightedPoint2 stores its CGAL object as member .wp directly
//     return wp.wp;
// }

WeightedPoint2 from_cgal_wp(const CGALWeightedPoint2& cwp) {
    // Construct WeightedPoint2(Point2, weight) using the existing constructor
    Point2 bare(CGAL::to_double(cwp.point().x()),
                CGAL::to_double(cwp.point().y()));
    return WeightedPoint2(bare, CGAL::to_double(cwp.weight()));
}

CGALBarePoint2 to_cgal_bare(const Point2& p) {
    return CGALBarePoint2(p.x(), p.y());
}

Point2 from_cgal_bare(const CGALBarePoint2& p) {
    return Point2(CGAL::to_double(p.x()), CGAL::to_double(p.y()));
}

static inline Point2 from_cgal_pt(const T2Kernel::Point_2& p) {
    return Point2(CGAL::to_double(p.x()), CGAL::to_double(p.y()));
}

// Get CGAL::Object for a Regular edge dual
static inline CGAL::Object get_rt_dual_obj(const RegularTriangulation2& rt,
                                            const REdgeHandle2& e) {
    return rt.rt.dual(std::make_pair(e.face.fh, e.index));
}


// ═══════════════════════════════════════════════════════════════════════════
// CONSTRUCTION / MANAGEMENT
// ═══════════════════════════════════════════════════════════════════════════

RegularTriangulation2 rt2_create() { return RegularTriangulation2(); }
void rt2_clear(RegularTriangulation2& rt) { rt.rt.clear(); }
void rt2_swap(RegularTriangulation2& a, RegularTriangulation2& b) { a.rt.swap(b.rt); }
int  rt2_dimension(const RegularTriangulation2& rt) { return rt.rt.dimension(); }

int rt2_number_of_vertices(const RegularTriangulation2& rt) {
    return static_cast<int>(rt.rt.number_of_vertices());
}
int rt2_number_of_hidden_vertices(const RegularTriangulation2& rt) {
    return static_cast<int>(rt.rt.number_of_hidden_vertices());
}
int rt2_number_of_faces(const RegularTriangulation2& rt) {
    return static_cast<int>(rt.rt.number_of_faces());
}
bool rt2_is_valid(const RegularTriangulation2& rt, bool verbose) {
    return rt.rt.is_valid(verbose);
}


// ═══════════════════════════════════════════════════════════════════════════
// SPECIAL VERTICES / FACES
// ═══════════════════════════════════════════════════════════════════════════

RVertexHandle2 rt2_infinite_vertex(const RegularTriangulation2& rt) {
    return RVertexHandle2(rt.rt.infinite_vertex());
}
RFaceHandle2 rt2_infinite_face(const RegularTriangulation2& rt) {
    return RFaceHandle2(rt.rt.infinite_face());
}
RVertexHandle2 rt2_finite_vertex(const RegularTriangulation2& rt) {
    return RVertexHandle2(rt.rt.finite_vertex());
}


// ═══════════════════════════════════════════════════════════════════════════
// INSERT / REMOVE
// ═══════════════════════════════════════════════════════════════════════════

RVertexHandle2 rt2_insert_weighted_point(RegularTriangulation2& rt,
                                          const WeightedPoint2& wp) {
    return RVertexHandle2(rt.rt.insert(to_rt_wp(wp)));
}

RVertexHandle2 rt2_insert_weighted_point_hint(RegularTriangulation2& rt,
                                               const WeightedPoint2& wp,
                                               const RFaceHandle2& hint) {
    return RVertexHandle2(rt.rt.insert(to_rt_wp(wp), hint.fh));
}

int rt2_insert_weighted_points(RegularTriangulation2& rt,
                                const std::vector<WeightedPoint2>& wpts) {
    // std::vector<CGALWeightedPoint2> cwpts;
    // cwpts.reserve(wpts.size());
    // for (const auto& wp : wpts) cwpts.push_back(to_rt_wp(wp));
    // return static_cast<int>(rt.rt.insert(cwpts.begin(), cwpts.end()));
    std::vector<RTWeightedPoint> cwpts;
    cwpts.reserve(wpts.size());
    for (const auto& wp : wpts) cwpts.push_back(to_rt_wp(wp));
    return static_cast<int>(rt.rt.insert(cwpts.begin(), cwpts.end()));
}

void rt2_remove(RegularTriangulation2& rt, const RVertexHandle2& v) {
    rt.rt.remove(v.vh);
}


// ═══════════════════════════════════════════════════════════════════════════
// QUERIES
// ═══════════════════════════════════════════════════════════════════════════

RVertexHandle2 rt2_nearest_power_vertex(const RegularTriangulation2& rt,
                                         const Point2& p) {
    return RVertexHandle2(rt.rt.nearest_power_vertex(to_cgal_bare(p)));
}


// ═══════════════════════════════════════════════════════════════════════════
// CONFLICT ZONE
// ═══════════════════════════════════════════════════════════════════════════

std::vector<RFaceHandle2> rt2_get_conflicts(const RegularTriangulation2& rt,
                                             const WeightedPoint2& wp,
                                             const RFaceHandle2& start) {
    std::vector<CGALRegular2::Face_handle> raw;
    rt.rt.get_conflicts(to_rt_wp(wp), std::back_inserter(raw), start.fh);
    std::vector<RFaceHandle2> out;
    out.reserve(raw.size());
    for (const auto& fh : raw) out.emplace_back(fh);
    return out;
}

std::vector<REdgeHandle2> rt2_get_boundary_of_conflicts(const RegularTriangulation2& rt,
                                                         const WeightedPoint2& wp,
                                                         const RFaceHandle2& start) {
    std::vector<CGALRegular2::Edge> raw;
    rt.rt.get_boundary_of_conflicts(to_rt_wp(wp), std::back_inserter(raw), start.fh);
    std::vector<REdgeHandle2> out;
    out.reserve(raw.size());
    for (const auto& e : raw) out.emplace_back(RFaceHandle2(e.first), e.second);
    return out;
}

std::vector<RVertexHandle2> rt2_get_hidden_vertices(const RegularTriangulation2& rt,
                                                     const WeightedPoint2& wp,
                                                     const RFaceHandle2& start) {
    std::vector<CGALRegular2::Vertex_handle> raw;
    rt.rt.get_hidden_vertices(to_rt_wp(wp), std::back_inserter(raw), start.fh);
    std::vector<RVertexHandle2> out;
    out.reserve(raw.size());
    for (const auto& vh : raw) out.emplace_back(vh);
    return out;
}

py::tuple rt2_get_conflicts_and_boundary(const RegularTriangulation2& rt,
                                          const WeightedPoint2& wp,
                                          const RFaceHandle2& start) {
    std::vector<CGALRegular2::Face_handle> raw_f;
    std::vector<CGALRegular2::Edge>        raw_e;
    rt.rt.get_conflicts_and_boundary(
        to_rt_wp(wp),
        std::back_inserter(raw_f),
        std::back_inserter(raw_e),
        start.fh
    );
    std::vector<RFaceHandle2> faces;
    for (const auto& fh : raw_f) faces.emplace_back(fh);
    std::vector<REdgeHandle2> edges;
    for (const auto& e : raw_e) edges.emplace_back(RFaceHandle2(e.first), e.second);
    return py::make_tuple(faces, edges);
}

py::tuple rt2_get_conflicts_and_hidden_vertices(const RegularTriangulation2& rt,
                                                 const WeightedPoint2& wp,
                                                 const RFaceHandle2& start) {
    std::vector<CGALRegular2::Face_handle>   raw_f;
    std::vector<CGALRegular2::Vertex_handle> raw_v;
    rt.rt.get_conflicts_and_hidden_vertices(
        to_rt_wp(wp),
        std::back_inserter(raw_f),
        std::back_inserter(raw_v),
        start.fh
    );
    std::vector<RFaceHandle2>   faces;
    for (const auto& fh : raw_f) faces.emplace_back(fh);
    std::vector<RVertexHandle2> verts;
    for (const auto& vh : raw_v) verts.emplace_back(vh);
    return py::make_tuple(faces, verts);
}

py::tuple rt2_get_boundary_of_conflicts_and_hidden_vertices(
    const RegularTriangulation2& rt,
    const WeightedPoint2& wp,
    const RFaceHandle2& start)
{
    std::vector<CGALRegular2::Edge>          raw_e;
    std::vector<CGALRegular2::Vertex_handle> raw_v;
    rt.rt.get_boundary_of_conflicts_and_hidden_vertices(
        to_rt_wp(wp),
        std::back_inserter(raw_e),
        std::back_inserter(raw_v),
        start.fh
    );
    std::vector<REdgeHandle2>   edges;
    for (const auto& e : raw_e) edges.emplace_back(RFaceHandle2(e.first), e.second);
    std::vector<RVertexHandle2> verts;
    for (const auto& vh : raw_v) verts.emplace_back(vh);
    return py::make_tuple(edges, verts);
}

py::tuple rt2_get_conflicts_and_boundary_and_hidden_vertices(
    const RegularTriangulation2& rt,
    const WeightedPoint2& wp,
    const RFaceHandle2& start)
{
    std::vector<CGALRegular2::Face_handle>   raw_f;
    std::vector<CGALRegular2::Edge>          raw_e;
    std::vector<CGALRegular2::Vertex_handle> raw_v;
    rt.rt.get_conflicts_and_boundary_and_hidden_vertices(
        to_rt_wp(wp),
        std::back_inserter(raw_f),
        std::back_inserter(raw_e),
        std::back_inserter(raw_v),
        start.fh
    );
    std::vector<RFaceHandle2>   faces;
    for (const auto& fh : raw_f) faces.emplace_back(fh);
    std::vector<REdgeHandle2>   edges;
    for (const auto& e : raw_e) edges.emplace_back(RFaceHandle2(e.first), e.second);
    std::vector<RVertexHandle2> verts;
    for (const auto& vh : raw_v) verts.emplace_back(vh);
    return py::make_tuple(faces, edges, verts);
}


// ═══════════════════════════════════════════════════════════════════════════
// POWER DIAGRAM
// ═══════════════════════════════════════════════════════════════════════════

Point2 rt2_dual_point(const RegularTriangulation2& rt, const RFaceHandle2& f) {
    return from_cgal_pt(rt.rt.dual(f.fh));
}

Point2 rt2_weighted_circumcenter(const RegularTriangulation2& rt, const RFaceHandle2& f) {
    return from_cgal_pt(rt.rt.weighted_circumcenter(f.fh));
}

std::string rt2_dual_type(const RegularTriangulation2& rt, const REdgeHandle2& e) {
    CGAL::Object obj = get_rt_dual_obj(rt, e);
    T2Kernel::Segment_2 seg;
    if (CGAL::assign(seg, obj)) return "segment";
    T2Kernel::Ray_2 ray;
    if (CGAL::assign(ray, obj)) return "ray";
    T2Kernel::Line_2 line;
    if (CGAL::assign(line, obj)) return "line";
    return "unknown";
}

py::object rt2_dual_segment(const RegularTriangulation2& rt, const REdgeHandle2& e) {
    T2Kernel::Segment_2 seg;
    if (CGAL::assign(seg, get_rt_dual_obj(rt, e)))
        return py::cast(Segment2(from_cgal_pt(seg.source()), from_cgal_pt(seg.target())));
    return py::none();
}

py::object rt2_dual_ray(const RegularTriangulation2& rt, const REdgeHandle2& e) {
    T2Kernel::Ray_2 ray;
    if (CGAL::assign(ray, get_rt_dual_obj(rt, e))) {
        Point2  src(CGAL::to_double(ray.source().x()),
                    CGAL::to_double(ray.source().y()));
        Vector2 dir(CGAL::to_double(ray.direction().dx()),
                    CGAL::to_double(ray.direction().dy()));
        return py::cast(Ray2(src, dir));
    }
    return py::none();
}

py::object rt2_dual_line(const RegularTriangulation2& rt, const REdgeHandle2& e) {
    T2Kernel::Line_2 line;
    if (CGAL::assign(line, get_rt_dual_obj(rt, e)))
        return py::cast(Line2(CGAL::to_double(line.a()),
                              CGAL::to_double(line.b()),
                              CGAL::to_double(line.c())));
    return py::none();
}


// ═══════════════════════════════════════════════════════════════════════════
// PREDICATES
// ═══════════════════════════════════════════════════════════════════════════

int rt2_power_test(const RegularTriangulation2& rt,
                   const RFaceHandle2& f, const WeightedPoint2& wp) {
    auto side = rt.rt.power_test(f.fh, to_rt_wp(wp));
    if (side == CGAL::ON_POSITIVE_SIDE) return  1;
    if (side == CGAL::ON_NEGATIVE_SIDE) return -1;
    return 0;
}

bool rt2_is_infinite_vertex(const RegularTriangulation2& rt, const RVertexHandle2& v) {
    return rt.rt.is_infinite(v.vh);
}
bool rt2_is_infinite_face(const RegularTriangulation2& rt, const RFaceHandle2& f) {
    return rt.rt.is_infinite(f.fh);
}
bool rt2_is_infinite_edge(const RegularTriangulation2& rt, const RFaceHandle2& f, int i) {
    return rt.rt.is_infinite(f.fh, i);
}
bool rt2_is_edge(const RegularTriangulation2& rt,
                 const RVertexHandle2& va, const RVertexHandle2& vb) {
    return rt.rt.is_edge(va.vh, vb.vh);
}
py::tuple rt2_is_edge_full(const RegularTriangulation2& rt,
                            const RVertexHandle2& va, const RVertexHandle2& vb) {
    CGALRegular2::Face_handle fr; int i;
    bool r = rt.rt.is_edge(va.vh, vb.vh, fr, i);
    return py::make_tuple(r, RFaceHandle2(fr), i);
}
bool rt2_is_face3(const RegularTriangulation2& rt,
                  const RVertexHandle2& v1, const RVertexHandle2& v2,
                  const RVertexHandle2& v3) {
    return rt.rt.is_face(v1.vh, v2.vh, v3.vh);
}
py::tuple rt2_is_face3_full(const RegularTriangulation2& rt,
                             const RVertexHandle2& v1, const RVertexHandle2& v2,
                             const RVertexHandle2& v3) {
    CGALRegular2::Face_handle fr;
    bool r = rt.rt.is_face(v1.vh, v2.vh, v3.vh, fr);
    return py::make_tuple(r, RFaceHandle2(fr));
}


// ═══════════════════════════════════════════════════════════════════════════
// LOCATE
// ═══════════════════════════════════════════════════════════════════════════

// RFaceHandle2 rt2_locate(const RegularTriangulation2& rt, const Point2& q) {
//     return RFaceHandle2(rt.rt.locate(to_cgal_bare(q)));
// }
// RFaceHandle2 rt2_locate_hint(const RegularTriangulation2& rt,
//                               const Point2& q, const RFaceHandle2& h) {
//     return RFaceHandle2(rt.rt.locate(to_cgal_bare(q), h.fh));
// }
// py::tuple rt2_locate_full(const RegularTriangulation2& rt, const Point2& q) {
//     CGALRegular2::Locate_type lt; int li;
//     auto fh = rt.rt.locate(to_cgal_bare(q), lt, li);
//     return py::make_tuple(RFaceHandle2(fh), static_cast<int>(lt), li);
// }
// RFaceHandle2 rt2_inexact_locate(const RegularTriangulation2& rt, const Point2& q) {
//     return RFaceHandle2(rt.rt.inexact_locate(to_cgal_bare(q)));
// }
// CHANGE TO:
RFaceHandle2 rt2_locate(const RegularTriangulation2& rt, const Point2& q) {
    return RFaceHandle2(rt.rt.locate(RTWeightedPoint(to_cgal_bare(q), 0)));
}
RFaceHandle2 rt2_locate_hint(const RegularTriangulation2& rt,
                              const Point2& q, const RFaceHandle2& h) {
    return RFaceHandle2(rt.rt.locate(RTWeightedPoint(to_cgal_bare(q), 0), h.fh));
}
py::tuple rt2_locate_full(const RegularTriangulation2& rt, const Point2& q) {
    CGALRegular2::Locate_type lt; int li;
    auto fh = rt.rt.locate(RTWeightedPoint(to_cgal_bare(q), 0), lt, li);
    return py::make_tuple(RFaceHandle2(fh), static_cast<int>(lt), li);
}
RFaceHandle2 rt2_inexact_locate(const RegularTriangulation2& rt, const Point2& q) {
    return RFaceHandle2(rt.rt.inexact_locate(RTWeightedPoint(to_cgal_bare(q), 0)));
}


// ═══════════════════════════════════════════════════════════════════════════
// GEOMETRY HELPERS
// ═══════════════════════════════════════════════════════════════════════════

Triangle2 rt2_triangle(const RegularTriangulation2& rt, const RFaceHandle2& f) {
    auto tri = rt.rt.triangle(f.fh);
    return Triangle2(
        Point2(CGAL::to_double(tri[0].x()), CGAL::to_double(tri[0].y())),
        Point2(CGAL::to_double(tri[1].x()), CGAL::to_double(tri[1].y())),
        Point2(CGAL::to_double(tri[2].x()), CGAL::to_double(tri[2].y()))
    );
}
Segment2 rt2_segment_face_i(const RegularTriangulation2& rt,
                              const RFaceHandle2& f, int i) {
    auto seg = rt.rt.segment(f.fh, i);
    return Segment2(from_cgal_pt(seg.source()), from_cgal_pt(seg.target()));
}
Segment2 rt2_segment_edge(const RegularTriangulation2& rt, const REdgeHandle2& e) {
    auto seg = rt.rt.segment(std::make_pair(e.face.fh, e.index));
    return Segment2(from_cgal_pt(seg.source()), from_cgal_pt(seg.target()));
}
Point2 rt2_circumcenter(const RegularTriangulation2& rt, const RFaceHandle2& f) {
    return from_cgal_pt(rt.rt.circumcenter(f.fh));
}

// WeightedPoint2 rt2_weighted_point(const RegularTriangulation2& rt,
//                                    const RVertexHandle2& v) {
//     // v->point() returns CGALWeightedPoint2
//     return from_cgal_wp(v.vh->point());
// }
// CHANGE TO:
WeightedPoint2 rt2_weighted_point(const RegularTriangulation2& rt,
                                   const RVertexHandle2& v) {
    return from_rt_wp(v.vh->point());
}

Point2 rt2_bare_point(const RegularTriangulation2& rt, const RVertexHandle2& v) {
    // v->point().point() gives the bare Point_2
    return from_cgal_bare(v.vh->point().point());
}

int rt2_ccw(const RegularTriangulation2& rt, int i) { return rt.rt.ccw(i); }
int rt2_cw(const RegularTriangulation2& rt, int i)  { return rt.rt.cw(i); }


// ═══════════════════════════════════════════════════════════════════════════
// ADJACENCY
// ═══════════════════════════════════════════════════════════════════════════

RVertexHandle2 rt2_mirror_vertex(const RegularTriangulation2& rt,
                                  const RFaceHandle2& f, int i) {
    return RVertexHandle2(rt.rt.mirror_vertex(f.fh, i));
}
int rt2_mirror_index(const RegularTriangulation2& rt,
                     const RFaceHandle2& f, int i) {
    return rt.rt.mirror_index(f.fh, i);
}
REdgeHandle2 rt2_mirror_edge(const RegularTriangulation2& rt, const REdgeHandle2& e) {
    auto me = rt.rt.mirror_edge(std::make_pair(e.face.fh, e.index));
    return REdgeHandle2(RFaceHandle2(me.first), me.second);
}


// ═══════════════════════════════════════════════════════════════════════════
// ITERATORS
// ═══════════════════════════════════════════════════════════════════════════

std::vector<RVertexHandle2> rt2_finite_vertices(const RegularTriangulation2& rt) {
    std::vector<RVertexHandle2> out;
    for (auto it = rt.rt.finite_vertices_begin();
         it != rt.rt.finite_vertices_end(); ++it)
        out.emplace_back(it);
    return out;
}
std::vector<RFaceHandle2> rt2_finite_faces(const RegularTriangulation2& rt) {
    std::vector<RFaceHandle2> out;
    for (auto it = rt.rt.finite_faces_begin();
         it != rt.rt.finite_faces_end(); ++it)
        out.emplace_back(it);
    return out;
}
std::vector<REdgeHandle2> rt2_finite_edges(const RegularTriangulation2& rt) {
    std::vector<REdgeHandle2> out;
    for (auto it = rt.rt.finite_edges_begin();
         it != rt.rt.finite_edges_end(); ++it)
        out.emplace_back(RFaceHandle2(it->first), it->second);
    return out;
}
std::vector<Point2> rt2_points(const RegularTriangulation2& rt) {
    std::vector<Point2> out;
    for (auto it = rt.rt.finite_vertices_begin();
         it != rt.rt.finite_vertices_end(); ++it)
        out.push_back(from_cgal_bare(it->point().point()));
    return out;
}
std::vector<RVertexHandle2> rt2_all_vertices(const RegularTriangulation2& rt) {
    std::vector<RVertexHandle2> out;
    for (auto it = rt.rt.all_vertices_begin();
         it != rt.rt.all_vertices_end(); ++it)
        out.emplace_back(it);
    return out;
}
std::vector<RFaceHandle2> rt2_all_faces(const RegularTriangulation2& rt) {
    std::vector<RFaceHandle2> out;
    for (auto it = rt.rt.all_faces_begin();
         it != rt.rt.all_faces_end(); ++it)
        out.emplace_back(it);
    return out;
}
std::vector<REdgeHandle2> rt2_all_edges(const RegularTriangulation2& rt) {
    std::vector<REdgeHandle2> out;
    for (auto it = rt.rt.all_edges_begin();
         it != rt.rt.all_edges_end(); ++it)
        out.emplace_back(RFaceHandle2(it->first), it->second);
    return out;
}
std::vector<RVertexHandle2> rt2_hidden_vertices(const RegularTriangulation2& rt) {
    std::vector<RVertexHandle2> out;
    for (auto it = rt.rt.hidden_vertices_begin();
         it != rt.rt.hidden_vertices_end(); ++it)
        out.emplace_back(it);
    return out;
}


// ═══════════════════════════════════════════════════════════════════════════
// CIRCULATORS
// ═══════════════════════════════════════════════════════════════════════════

std::vector<RFaceHandle2> rt2_incident_faces(const RegularTriangulation2& rt,
                                              const RVertexHandle2& v) {
    std::vector<RFaceHandle2> out;
    auto c = rt.rt.incident_faces(v.vh), done = c;
    if (c != nullptr) do { out.emplace_back(c); ++c; } while (c != done);
    return out;
}
std::vector<REdgeHandle2> rt2_incident_edges(const RegularTriangulation2& rt,
                                              const RVertexHandle2& v) {
    std::vector<REdgeHandle2> out;
    auto c = rt.rt.incident_edges(v.vh), done = c;
    if (c != nullptr) do {
        out.emplace_back(RFaceHandle2(c->first), c->second); ++c;
    } while (c != done);
    return out;
}
std::vector<RVertexHandle2> rt2_incident_vertices(const RegularTriangulation2& rt,
                                                   const RVertexHandle2& v) {
    std::vector<RVertexHandle2> out;
    auto c = rt.rt.incident_vertices(v.vh), done = c;
    if (c != nullptr) do { out.emplace_back(c); ++c; } while (c != done);
    return out;
}
std::vector<RFaceHandle2> rt2_line_walk(const RegularTriangulation2& rt,
                                         const Point2& p, const Point2& q) {
    std::vector<RFaceHandle2> out;
    // auto c = rt.rt.line_walk(to_cgal_bare(p), to_cgal_bare(q));
    // CHANGE TO:
    auto c = rt.rt.line_walk(RTWeightedPoint(to_cgal_bare(p), 0),
                             RTWeightedPoint(to_cgal_bare(q), 0));
    if (c.is_empty()) return out;
    auto done = c;
    do { out.emplace_back(c); ++c; } while (c != done);
    return out;
}


// ═══════════════════════════════════════════════════════════════════════════
// CONVEX HULL
// ═══════════════════════════════════════════════════════════════════════════

std::vector<RVertexHandle2> rt2_convex_hull_vertices(const RegularTriangulation2& rt) {
    std::vector<RVertexHandle2> out;
    auto inf = rt.rt.infinite_vertex();
    auto c = rt.rt.incident_vertices(inf), done = c;
    if (c != nullptr) do {
        if (!rt.rt.is_infinite(c)) out.emplace_back(c);
        ++c;
    } while (c != done);
    return out;
}
std::vector<REdgeHandle2> rt2_convex_hull_edges(const RegularTriangulation2& rt) {
    std::vector<REdgeHandle2> out;
    auto inf = rt.rt.infinite_vertex();
    auto c = rt.rt.incident_edges(inf), done = c;
    if (c != nullptr) do {
        auto mirror = rt.rt.mirror_edge(*c);
        out.emplace_back(RFaceHandle2(mirror.first), mirror.second);
        ++c;
    } while (c != done);
    return out;
}