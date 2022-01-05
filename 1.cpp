#include "library/vec3.h"
#include "library/color.h"
#include "library/ray.h"

#include <iostream>

color rayColor(const ray& r) {
    vec3 unitDirection = unitVector(r.direction());
    auto t = 0.5*(unitDirection.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {
    //Image
    const auto aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    //Camera
    auto viewportHeight = 2.0;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewportWidth, 0, 0);
    auto vertical = vec3(0, viewportHeight, 0);
    auto lowerLeftCorner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focalLength);

    //Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = imageHeight-1; j >= 0; j--) {
        std::cerr << "lines remaining : " << j << ' ' << std::flush;
        for(int i = 0; i < imageWidth; i++) {
            auto u = double(i) / (imageWidth-1);
            auto v = double(j) / (imageHeight-1);
            ray r(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
            color pixelColor = rayColor(r);
            writeColor(std::cout, pixelColor);
        }
    }
    std::cerr << "\nWorks Done\n";
}