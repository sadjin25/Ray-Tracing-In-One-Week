#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
//#include <random>

//Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14;

//Utility Functions

inline double degreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}

inline double randomDouble() {
    //Returns a random real in [0, 1)
    // static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    // static std::mt19937 gen;

    // return distribution(gen);
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
    //Returns a random real in [min, max)
    return min + (max-min) * randomDouble(); 
}

inline double clamp(double x, double min, double max) {
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

//Common Headers

#include "ray.h"
#include "vec3.h"

#endif