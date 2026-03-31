#include "points.h"

Point2::Point2(double x, double y) : p(x, y) {}
double Point2::x() const { return p.x(); }
double Point2::y() const { return p.y(); }

Vector2::Vector2(double x, double y) : v(x, y) {}
double Vector2::x() const { return v.x(); }
double Vector2::y() const { return v.y(); }

Vector2 point2_sub(const Point2& a, const Point2& b) {
    return Vector2((a.p - b.p).x(), (a.p - b.p).y());
}

Vector2 vector2_add(const Vector2& a, const Vector2& b) {
    return Vector2((a.v + b.v).x(), (a.v + b.v).y());
}

Vector2 vector2_mul(const Vector2& a, double scalar) {
    return Vector2((a.v * scalar).x(), (a.v * scalar).y());
}

Point2 point2_add_vector(const Point2& p, const Vector2& vec) {
    return Point2((p.p + vec.v).x(), (p.p + vec.v).y());
}