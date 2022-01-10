#include "library/rtweekend.h"

#include "library/color.h"
#include "library/hittable_list.h"
#include "library/sphere.h"
#include "library/camera.h"

#include <iostream>

color rayColor(const ray& r, const hittable& world, int depth) {
    hitRecord rec;

    //If we've exceeded the ray bounce limit, no more light is gathered.
    if(depth <= 0) {
        return color(0, 0, 0);
    }

    if(world.hit(r, 0.001, infinity, rec)) {
        point3 target = rec.p + rec.normal + randomInUnitSphere();
        return 0.5 * rayColor(ray(rec.p, target - rec.p), world, depth-1);
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
    const int samplesPerPixel = 50;
    const int maxDepth = 50;

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
                pixelColor += rayColor(r, world, maxDepth);
            }
            writeColor(std::cout, pixelColor, samplesPerPixel);
        }
    }
    std::cerr << "\nWorks Done\n";
}