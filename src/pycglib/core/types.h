#pragma once
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Bbox_2.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2      CGALPoint2;
typedef Kernel::Vector_2     CGALVector2;
typedef Kernel::Direction_2  CGALDirection2;
typedef Kernel::Segment_2    CGALSegment2;
typedef Kernel::Line_2       CGALLine2;
typedef Kernel::Ray_2 CGALRay2;
typedef Kernel::Triangle_2 CGALTriangle2;
typedef Kernel::Circle_2 CGALCircle2;
typedef Kernel::Iso_rectangle_2 CGALIsoRectangle2;
typedef Kernel::Weighted_point_2 CGALWeightedPoint2;


// ─── Point2 ───────────────────────────────────────────────
struct Point2 {
    CGALPoint2 p;
    Point2(double x, double y) : p(x, y) {}
    Point2(CGALPoint2 pt) : p(pt) {}
    double x() const { return CGAL::to_double(p.x()); }
    double y() const { return CGAL::to_double(p.y()); }
};

// ─── Vector2 ──────────────────────────────────────────────
struct Vector2 {
    CGALVector2 v;
    Vector2(double x, double y) : v(x, y) {}
    Vector2(CGALVector2 vec) : v(vec) {}
    double x() const { return CGAL::to_double(v.x()); }
    double y() const { return CGAL::to_double(v.y()); }
};

// ─── Direction2 ───────────────────────────────────────────
struct Direction2 {
    CGALDirection2 d;
    Direction2(double x, double y) : d(x, y) {}
    Direction2(CGALDirection2 dir) : d(dir) {}
    double dx()       const { return CGAL::to_double(d.dx()); }
    double dy()       const { return CGAL::to_double(d.dy()); }
    double delta(int i) const { return CGAL::to_double(d.delta(i)); }
};

// ─── Bbox2 ────────────────────────────────────────────────
// struct Bbox2 {
//     double xmin, ymin, xmax, ymax;
//     Bbox2(double xmin, double ymin, double xmax, double ymax)
//         : xmin(xmin), ymin(ymin), xmax(xmax), ymax(ymax) {}
// };
// ─── Bbox2 ────────────────────────────────────────────────
struct Bbox2 {
    CGAL::Bbox_2 b;
    Bbox2() : b() {}
    Bbox2(double xmin, double ymin, double xmax, double ymax)
        : b(xmin, ymin, xmax, ymax) {}
    Bbox2(CGAL::Bbox_2 bbox) : b(bbox) {}
    double xmin() const { return b.xmin(); }
    double ymin() const { return b.ymin(); }
    double xmax() const { return b.xmax(); }
    double ymax() const { return b.ymax(); }
};


// ─── Segment2 ─────────────────────────────────────────────
struct Segment2 {
    CGALSegment2 s;
    Segment2(const Point2& p, const Point2& q)
        : s(CGALPoint2(p.x(), p.y()), CGALPoint2(q.x(), q.y())) {}
    Segment2(CGALSegment2 seg) : s(seg) {}
};

// ─── Line2 (stub — full impl later) ──────────────────────
// Replace the Line2 stub with this:
struct Ray2; // forward declare Ray2 before Line2

struct Line2 {
    CGALLine2 l;
    Line2(CGALLine2 line) : l(line) {}
    Line2(double a, double b, double c) : l(a, b, c) {}
    Line2(const Point2& p, const Point2& q) : l(CGALPoint2(p.x(), p.y()), CGALPoint2(q.x(), q.y())) {}
    Line2(const Point2& p, const Direction2& d) : l(CGALPoint2(p.x(), p.y()), d.d) {}
    Line2(const Point2& p, const Vector2& v) : l(CGALPoint2(p.x(), p.y()), v.v) {}
    Line2(const Segment2& s) : l(s.s) {}
    // Line2(const Ray2& r) : l(r.r) {}
    double a() const { return CGAL::to_double(l.a()); }
    double b() const { return CGAL::to_double(l.b()); }
    double c() const { return CGAL::to_double(l.c()); }
};

// ─── Ray2 ─────────────────────────────────────────────────
struct Ray2 {
    CGALRay2 r;
    Ray2(CGALRay2 ray) : r(ray) {}
    Ray2(const Point2& p, const Point2& q)
        : r(CGALPoint2(p.x(), p.y()), CGALPoint2(q.x(), q.y())) {}
    Ray2(const Point2& p, const Direction2& d)
        : r(CGALPoint2(p.x(), p.y()), d.d) {}
    Ray2(const Point2& p, const Vector2& v)
        : r(CGALPoint2(p.x(), p.y()), v.v) {}
    Ray2(const Point2& p, const Line2& l)
        : r(CGALPoint2(p.x(), p.y()), l.l) {}
};

// ─── Triangle2 ────────────────────────────────────────────
struct Triangle2 {
    CGALTriangle2 t;
    Triangle2(CGALTriangle2 tri) : t(tri) {}
    Triangle2(const Point2& p, const Point2& q, const Point2& r)
        : t(CGALPoint2(p.x(), p.y()),
            CGALPoint2(q.x(), q.y()),
            CGALPoint2(r.x(), r.y())) {}
};


// ─── Circle2 ──────────────────────────────────────────────
struct Circle2 {
    CGALCircle2 c;
    Circle2(CGALCircle2 circle) : c(circle) {}
    // From center, squared_radius, orientation (1=CCW, -1=CW)
    Circle2(const Point2& center, double squared_radius, int ori = 1)
        : c(CGALPoint2(center.x(), center.y()),
            squared_radius,
            ori >= 0 ? CGAL::COUNTERCLOCKWISE : CGAL::CLOCKWISE) {}
    // From three points
    Circle2(const Point2& p, const Point2& q, const Point2& r)
        : c(CGALPoint2(p.x(), p.y()),
            CGALPoint2(q.x(), q.y()),
            CGALPoint2(r.x(), r.y())) {}
    // From two points (diameter), orientation
    Circle2(const Point2& p, const Point2& q, int ori = 1)
        : c(CGALPoint2(p.x(), p.y()),
            CGALPoint2(q.x(), q.y()),
            ori >= 0 ? CGAL::COUNTERCLOCKWISE : CGAL::CLOCKWISE) {}
    // From center only, orientation
    Circle2(const Point2& center, int ori = 1)
        : c(CGALPoint2(center.x(), center.y()),
            ori >= 0 ? CGAL::COUNTERCLOCKWISE : CGAL::CLOCKWISE) {}
};



// ─── IsoRectangle2 ────────────────────────────────────────
struct IsoRectangle2 {
    CGALIsoRectangle2 r;
    IsoRectangle2(CGALIsoRectangle2 rect) : r(rect) {}
    // From two diagonal opposite vertices
    IsoRectangle2(const Point2& p, const Point2& q)
        : r(CGALPoint2(p.x(), p.y()), CGALPoint2(q.x(), q.y())) {}
    // From four vertices: left, right, bottom, top
    IsoRectangle2(const Point2& left, const Point2& right,
                  const Point2& bottom, const Point2& top)
        : r(CGALPoint2(left.x(),   left.y()),
            CGALPoint2(right.x(),  right.y()),
            CGALPoint2(bottom.x(), bottom.y()),
            CGALPoint2(top.x(),    top.y())) {}
    // From min/max coordinates
    IsoRectangle2(double min_x, double min_y, double max_x, double max_y)
        : r(CGALPoint2(min_x, min_y), CGALPoint2(max_x, max_y)) {}
    // From Bbox2
    // IsoRectangle2(const Bbox2& bbox)
    //     : r(CGALPoint2(bbox.xmin, bbox.ymin),
    //         CGALPoint2(bbox.xmax, bbox.ymax)) {}
        IsoRectangle2(const Bbox2& bbox)
    : r(CGALPoint2(bbox.xmin(), bbox.ymin()),
        CGALPoint2(bbox.xmax(), bbox.ymax())) {}
};


// ─── WeightedPoint2 ───────────────────────────────────────
struct WeightedPoint2 {
    CGALWeightedPoint2 wp;
    WeightedPoint2(CGALWeightedPoint2 p) : wp(p) {}
    // From origin
    WeightedPoint2() : wp(CGAL::ORIGIN) {}
    // From point only, weight 0
    WeightedPoint2(const Point2& p)
        : wp(CGALPoint2(p.x(), p.y())) {}
    // From point and weight
    WeightedPoint2(const Point2& p, double w)
        : wp(CGALPoint2(p.x(), p.y()), w) {}
    // From x, y coordinates, weight 0
    WeightedPoint2(double x, double y)
        : wp(CGALPoint2(x, y)) {}
};
