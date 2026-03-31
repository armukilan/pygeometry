#pragma once
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2  CGALPoint2;
typedef Kernel::Vector_2 CGALVector2;

struct Point2 {
    CGALPoint2 p;
    Point2(double x, double y);
    double x() const;
    double y() const;
};

struct Vector2 {
    CGALVector2 v;
    Vector2(double x, double y);
    double x() const;
    double y() const;
};

Vector2 point2_sub(const Point2& a, const Point2& b);
Vector2 vector2_add(const Vector2& a, const Vector2& b);
Vector2 vector2_mul(const Vector2& a, double scalar);
Point2  point2_add_vector(const Point2& p, const Vector2& vec);