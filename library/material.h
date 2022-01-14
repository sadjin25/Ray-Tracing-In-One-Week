#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable_list.h"
#include "rtweekend.h"

struct hitRecord;

class material {
    public:
        virtual bool scatter(
            const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered
        ) const = 0;
};

class lambertian : public material{
    public:
        lambertian(const color& a) : albedo(a) {}

        virtual bool scatter(
            const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered
        ) const override {
            auto scatterDirection = rec.normal + randomUnitVector();

            // Catch degenerate scatter direction
            if(scatterDirection.nearZero())
                scatterDirection = rec.normal;
            
            scattered = ray(rec.p, scatterDirection);
            attenuation = albedo;
            return true;
        }
    public:
        color albedo;
};

class metal : public material {
    public:
        metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
            const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered
        ) const override {
            vec3 reflected = reflect(unitVector(rIn.direction()), rec.normal);
            scattered = ray(rec.p, reflected + fuzz*randomInUnitSphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
    
    public:
        color albedo;
        double fuzz;
};

class dielectric : public material {
    public: 
        dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

        virtual bool scatter(
            const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered
        ) const override {
            attenuation = color(1.0, 1.0, 1.0);
            double refractionRatio = rec.frontFace ? (1.0/ir) : ir;

            vec3 unitDirection = unitVector(rIn.direction());
            double cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0);
            double sinTheta = sqrt(1.0 - cosTheta*cosTheta);

            bool cannotRefract = refractionRatio * sinTheta > 1.0;
            vec3 direction;

            if(cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble())
                direction = reflect(unitDirection, rec.normal);

            else
                direction = refract(unitDirection, rec.normal, refractionRatio);

            scattered = ray(rec.p, direction);
            return true;
        }
    public:
        double ir;  // Index of Refraction

    private:
        static double reflectance(double cosine, double refIdx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1-refIdx) / (1+refIdx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1-cosine), 5);
        }
};

#endif