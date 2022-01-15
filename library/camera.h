#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
    public: 
        camera(
            point3 lookfrom,
            point3 lookat,
            vec3 vup,
            double vfov,    // vertical fov in degrees
            double aspectRatio
        ) {
            const auto theta = degreesToRadians(vfov);
            auto h = tan(theta/2);
            auto viewportHeight = 2.0 * h;
            auto viewportWidth = aspectRatio * viewportHeight;

            auto w = unitVector(lookfrom - lookat);
            auto u = unitVector(cross(vup, w));
            auto v = cross(w, u);
            
            auto focalLength = 1.0;

            origin = lookfrom;
            horizontal = viewportWidth * u;
            vertical = viewportHeight * v;
            lowerLeftCorner = origin - horizontal/2 - vertical/2 - w;
        }

        ray getRay(double s, double t) const {
            return ray(origin, lowerLeftCorner + s*horizontal + t*vertical - origin);
        }
        
    private:
        point3 origin;
        point3 lowerLeftCorner;
        vec3 horizontal;
        vec3 vertical;
};
#endif