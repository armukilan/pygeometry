#include "core/bbox2.h"

bool bbox2_eq(const Bbox2& a, const Bbox2& b) {
    return a.b == b.b;
}

bool bbox2_neq(const Bbox2& a, const Bbox2& b) {
    return a.b != b.b;
}

int bbox2_dimension(const Bbox2& b) {
    return b.b.dimension();
}

double bbox2_min(const Bbox2& b, int i) {
    return b.b.min(i);
}

double bbox2_max(const Bbox2& b, int i) {
    return b.b.max(i);
}

Bbox2 bbox2_add(const Bbox2& a, const Bbox2& b) {
    return Bbox2(a.b + b.b);
}

Bbox2 bbox2_iadd(Bbox2& a, const Bbox2& b) {
    a.b += b.b;
    return a;
}

void bbox2_dilate(Bbox2& b, int dist) {
    b.b.dilate(dist);
}

// void bbox2_scale(Bbox2& b, double factor) {
//     b.b.scale(factor);
// }
void bbox2_scale(Bbox2& b, double factor) {
    double cx     = (b.b.xmin() + b.b.xmax()) / 2.0;
    double cy     = (b.b.ymin() + b.b.ymax()) / 2.0;
    double half_w = (b.b.xmax() - b.b.xmin()) / 2.0 * factor;
    double half_h = (b.b.ymax() - b.b.ymin()) / 2.0 * factor;
    b.b = CGAL::Bbox_2(cx - half_w, cy - half_h,
                       cx + half_w, cy + half_h);
}

bool bbox2_do_overlap(const Bbox2& a, const Bbox2& b) {
    return CGAL::do_overlap(a.b, b.b);
}