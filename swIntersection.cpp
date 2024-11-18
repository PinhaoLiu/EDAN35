#include "swIntersection.h"

namespace sw {

Ray Intersection::getShadowRay(const Vec3 &lightPos) {
    Vec3 L = lightPos - position;
    float tMax = sqrt(L * L);
    return Ray(position, L.normalize(), 0.01f, tMax);
}

Ray Intersection::getReflectedRay(void) {
    Vec3 N = normal;
    const Vec3 D = ray.dir;

    // TODO: Implement reflection
    // -------------------
    Vec3 R = D - 2 * (D * N) * N;
    // -------------------

    return Ray(position, R, 0.01f, FLT_MAX);
}

Ray Intersection::getRefractedRay(void) {
    const Vec3 &D = ray.dir;
    Vec3 N = normal;
    float eta = 1.0f / material.refractiveIndex;
    if (!frontFacing) eta = 1.0f / eta; // Inside material.

    // TODO: Implement refraction
    // -------------------
    auto r = -D * N;
    auto c = 1.0f - powf(eta, 2.0f) * (1.0f - powf(r, 2.0f));
    Vec3 R = eta * D + (eta * r - sqrtf(c)) * N;
    if (c < 0.0f) R = D - 2 * (D * N) * N;
    // -------------------

    return Ray(position, R, 0.01f, FLT_MAX);
}

} // namespace sw
