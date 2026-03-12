#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "interval.hpp"
#include "vecs.hpp"
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>
#include <memory>
#include <iostream>

class Material;
class Hittable;
class Ray;
class LightSource;
class Scene;

class Camera {
private:
    Vec3f position;
    Vec3f Viewport00;
    Vec3f deltau;
    Vec3f deltav;
    Vec3f defocusDisku;
    Vec3f defocusDiskv;
    float viewportHeight;
    float viewportWidth;
    Vec3f u,v,w;
    std::vector<std::vector<RGB>> image;
    void writePPM();
    void updateCamera();

public:
    float aspectRatio = 16.0f / 9.0f;
    int nx = 1200;
    int ny; // will be calculated based on aspect ratio and nx
    float l = -1.0f, r = 1.0f, t, b; // t and b will be calculated based on aspect ratio and l,r
    float vfov = 50;
    Vec3f lookFrom = Vec3f(0,0,0);
    Vec3f lookAt = Vec3f(0,0,-1);
    Vec3f vUp = Vec3f(0,1,0);
    float defocusAngle = 2.5;
    float focusDistance = 2.5;
    int samplePerPixel = 10;
    int maxRecursionDepth = 3;
    Camera(const Vec3f& position);
    Camera() = default;

    void setPosition(const Vec3f& position);
    Ray generateRay(int i, int j);
    void render(const Scene& scene);
    Vec3f random_defocusDiskPoint() const;
};

class Hittable {
private:
    std::shared_ptr<Material> material;
public:
    Hittable(const std::shared_ptr<Material>& material);
    const std::shared_ptr<Material>& getMaterial() const;
    virtual Vec3f getNormal(const Vec3f& point) const = 0;
    virtual float hit(const Ray& ray,const Interval& interval) const = 0;
};

class Sphere : public Hittable {
private:
    Vec3f center;
    float radius;
public:
    Sphere(const std::shared_ptr<Material>& material, const Vec3f& center, float radius);
    Vec3f getCenter() const;
    float getRadius() const;
    Vec3f getNormal(const Vec3f& point) const override;
    float hit(const Ray& ray,const Interval& interval) const override;
};

class Material {
private:
    RGB DiffuseReflectance;
    bool Mirror;
    bool Dielectric;
    float Fuzziness;
    float RefractiveIndex; 
public:
    Material(const RGB& DiffuseReflectance);
    Material(const RGB& DiffuseReflectance,bool Mirror,float Fuzziness);
    Material(float RefractiveIndex); 
    RGB getColor() const;                                                   

    bool isMirrored() const;
    float getFuzziness() const;
    bool isDielectric() const;
    float getRI() const;
};

class LightSource{
private:
    Vec3f position;
    RGB color;
    Vec3f intensity; // this can be used to calculate the brightness of the light source, but for now I will just use the color as the intensity.
public:
    LightSource(const Vec3f& position, const RGB& color, const Vec3f& intensity);
    LightSource(const Vec3f& position, const Vec3f& intensity);
    LightSource() = default;
    Vec3f getPosition() const;
    Vec3f getIntensity() const;
    RGB getColor() const;
};


class Ray {
private:
    Vec3f origin;
    Vec3f direction;

public:
    Ray(const Vec3f& origin, const Vec3f& direction);
    Vec3f getOrigin() const;
    Vec3f getDirection() const;
    void setOrigin(const Vec3f& origin);
    void setDirection(const Vec3f& direction);
    Vec3f pointAt(float t) const;
    Vec3f reflect(const Vec3f& normal,float fuzziness) const;
    Vec3f refract(const Vec3f& normal,float ri) const;
};


class Scene{
public:
    RGB BackgroundColor;
    RGB AmbientLight;
    std::vector<std::shared_ptr<Hittable>> hittables;
    std::vector<std::shared_ptr<LightSource>> lightSources;
    float shadowRayEpsilon;
    Scene() = default;

    bool isShadowed(const Vec3f& hitPoint,const std::shared_ptr<LightSource>& lightSource) const;
    RGB getPixelColor(const Ray& ray,int maxRecursionDepth) const;

};

#endif