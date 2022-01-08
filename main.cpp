#include "library/rtweekend.h"

#include "library/color.h"
#include "library/hittable_list.h"
#include "library/sphere.h"
#include "library/camera.h"

#include <iostream>

// double hitSphere(const point3& center, double radius, const ray& r)  {
//     if(center.z() > 0) return 0;    //woojin's modification. remove exception of getting out of the ball from the vision. 

//     vec3 oc = r.origin() - center;
//     auto a = r.direction().lengthSquared();
//     auto halfB = dot(oc, r.direction());
//     auto c = oc.lengthSquared() - radius*radius;
//     auto discriminant = halfB * halfB - a*c;
//     if(discriminant < 0) {
//         return -1.0;
//     } else {
//         return (-halfB - sqrt(discriminant)) / a;
//     }
//     return (discriminant > 0);
// }

color rayColor(const ray& r, const hittable& world) {
    hitRecord rec;
    if(world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unitDirection = unitVector(r.direction());
    auto t = 0.5*(unitDirection.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {
    //Image
    const auto aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;

    //World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    //Camera
    camera cam;

    //Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = imageHeight-1; j >= 0; j--) {
        std::cerr << "lines remaining : " << j << ' ' << std::flush;
        for(int i = 0; i < imageWidth; i++) {
            color pixelColor(0, 0, 0);

            for(int s = 0; s < samplesPerPixel; s++) {
                auto u = (i + randomDouble()) / (imageWidth-1);
                auto v = (j + randomDouble()) / (imageHeight-1);
                ray r = cam.getRay(u, v);
                pixelColor += rayColor(r, world);
            }
            writeColor(std::cout, pixelColor, samplesPerPixel);
        }
    }
    std::cerr << "\nWorks Done\n";
}