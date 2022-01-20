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
            double aspectRatio,
            double aperture,
            double focusDist
        ) {
            const auto theta = degreesToRadians(vfov);
            auto h = tan(theta/2);
            auto viewportHeight = 2.0 * h;
            auto viewportWidth = aspectRatio * viewportHeight;

            w = unitVector(lookfrom - lookat);
            u = unitVector(cross(vup, w));
            v = cross(w, u);
            
            auto focalLength = 1.0;

            origin = lookfrom;
            horizontal = focusDist * viewportWidth * u;
            vertical = focusDist * viewportHeight * v;
            lowerLeftCorner = origin - horizontal/2 - vertical/2 - focusDist*w;

            lensRadius = aperture / 2;
        }

        ray getRay(double s, double t) const {
            vec3 rd = lensRadius * randomInUnitDisk();
            vec3 offset = u * rd.x() + v * rd.y();
            return ray(
                origin + offset,
                lowerLeftCorner + s*horizontal + t*vertical - origin - offset
            );
        }
        
    private:
        point3 origin;
        point3 lowerLeftCorner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u,v,w;
        double lensRadius;
};
#endif