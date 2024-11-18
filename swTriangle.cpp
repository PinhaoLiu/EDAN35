#include "swTriangle.h"

namespace sw {

bool Triangle::intersect(const Ray &r, Intersection &isect) const {
    // TODO: Implement ray-triangle intersection
    auto p = r.orig;
    auto d = r.dir;

    // Find Q
    auto v0 = vertices[0];
    auto v1 = vertices[1];
    auto v2 = vertices[2];
    auto e1 = v1 - v0;
    auto e2 = v2 - v0;
    auto n = e1 % e2; // Plane normal

    // Plane equation
    auto m = -n * v0;

    // Plane intersection
    auto t = (n * p + m) / (-n * d);
    auto q = p + t * d;

    // Must also make sure that t_min < t < t_max
    if (t <= r.minT || t >= r.maxT) return false;

    // Create vector r, which is coplanar with e_1 and e_2
    auto rr = q - v0;

    // Barycentric v and w
    auto v = (e1 % rr).norm() / n.norm();
    auto w = (rr % e2).norm() / n.norm();

    if ((e1 % rr) * n < 0) return false;
    if ((rr % e2) * n < 0) return false;
    if (v + w >= 1) return false;

    isect.hitT = t;
    isect.normal = n;
    isect.normal.normalize();
    isect.frontFacing = (-d * isect.normal) > 0.0f;
    if (!isect.frontFacing) isect.normal = -isect.normal;
    isect.position = q;
    isect.material = material;
    isect.ray = r;

    return true;
}

} // namespace sw
