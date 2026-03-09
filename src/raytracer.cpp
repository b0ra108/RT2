
#include "vecs.hpp"
#include "objects.hpp"
#include "interval.hpp"

// Vec3f class implementations
Vec3f::Vec3f(float x, float y, float z) : x(x), y(y), z(z) {}
float Vec3f::getX() const { return x; }
float Vec3f::getY() const { return y; }
float Vec3f::getZ() const { return z; }
void Vec3f::setX(float x) { this->x = x; }
void Vec3f::setY(float y) { this->y = y; }
void Vec3f::setZ(float z) { this->z = z; }

Vec3f Vec3f::operator*(const Vec3f& vec) const{
    return Vec3f(x * vec.x, y * vec.y, z * vec.z);
}
Vec3f Vec3f::operator+(const Vec3f& vec) const{
    return Vec3f(x + vec.x, y + vec.y, z + vec.z);
}
Vec3f Vec3f::operator-(const Vec3f& vec) const{
    return Vec3f(x - vec.x, y - vec.y, z - vec.z);
}

Vec3f Vec3f::operator*(float scalar) const {
    return Vec3f(x * scalar, y * scalar, z * scalar);
}
Vec3f Vec3f::operator/(float scalar) const {
    return Vec3f(x / scalar, y / scalar, z / scalar);
}
float Vec3f::dot(const Vec3f& vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
}
Vec3f Vec3f::cross(const Vec3f& vec) const {
    return Vec3f(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}
Vec3f Vec3f::normalized() const {
    float length = this->dot(*this);
    return *this / sqrt(length);
}

// RGB class implementations
RGB::RGB(float r, float g, float b) : 
    r(std::fmax(0.0f, std::fmin(1.0f, r))), 
    g(std::fmax(0.0f, std::fmin(1.0f, g))), 
    b(std::fmax(0.0f, std::fmin(1.0f, b))) {}
RGB::RGB(int r, int g, int b) : r(std::fmax(0.0f, std::fmin(1.0f, r / 255.0f))), 
                                g(std::fmax(0.0f, std::fmin(1.0f, g / 255.0f))), 
                                b(std::fmax(0.0f, std::fmin(1.0f, b / 255.0f))) {}
float RGB::getR() const { return r; }
float RGB::getG() const { return g; }
float RGB::getB() const { return b; }

void RGB::setR(float r) { this->r = std::fmax(0.0f, std::fmin(1.0f, r)); }
void RGB::setG(float g) { this->g = std::fmax(0.0f, std::fmin(1.0f, g)); }
void RGB::setB(float b) { this->b = std::fmax(0.0f, std::fmin(1.0f, b)); }

void RGB::operator+=(const RGB& other) {
    this->r = std::fmax(0.0f, std::fmin(1.0f, this->r + other.r));
    this->g = std::fmax(0.0f, std::fmin(1.0f, this->g + other.g));
    this->b = std::fmax(0.0f, std::fmin(1.0f, this->b + other.b));
}

void RGB::operator-=(const RGB& other) {
    this->r = std::fmax(0.0f, std::fmin(1.0f, this->r - other.r));
    this->g = std::fmax(0.0f, std::fmin(1.0f, this->g - other.g));
    this->b = std::fmax(0.0f, std::fmin(1.0f, this->b - other.b));
}

void RGB::operator*=(const RGB& other) {
    this->r = std::fmax(0.0f, std::fmin(1.0f, this->r * other.r));
    this->g = std::fmax(0.0f, std::fmin(1.0f, this->g * other.g));
    this->b = std::fmax(0.0f, std::fmin(1.0f, this->b * other.b));
}

void RGB::operator/=(const RGB& other) {
    this->r = std::fmax(0.0f, std::fmin(1.0f, this->r / other.r));
    this->g = std::fmax(0.0f, std::fmin(1.0f, this->g / other.g));
    this->b = std::fmax(0.0f, std::fmin(1.0f, this->b / other.b));
}

RGB RGB::operator*(const RGB& other) const {
    return RGB(r * other.r, g * other.g, b * other.b);
}

RGB RGB::operator+(const RGB& other) const {
    return RGB(r + other.r, g + other.g, b + other.b);
}

RGB RGB::operator*(const Vec3f& vec) const {
    return RGB(r * vec.getX(), g * vec.getY(), b * vec.getZ());
}

RGB RGB::operator+(const Vec3f& vec) const {
    return RGB(r + vec.getX(), g + vec.getY(), b + vec.getZ());
}

RGB RGB::operator*(float scalar) const {
    return RGB(r * scalar, g * scalar, b * scalar);
}

RGB RGB::operator/(float scalar) const {
    return RGB(r / scalar, g / scalar, b / scalar);
} 

RGB RGB::operator+(float scalar) const {
    return RGB(r + scalar, g + scalar, b + scalar);
}

RGB RGB::operator-(float scalar) const {
    return RGB(r - scalar, g - scalar, b - scalar);
}


// Ray class implementations
Ray::Ray(const Vec3f& origin, const Vec3f& direction) : origin(origin), direction(direction) {}
Vec3f Ray::getOrigin() const { return origin; }
Vec3f Ray::getDirection() const { return direction; }
void Ray::setOrigin(const Vec3f& origin) { this->origin = origin; }
void Ray::setDirection(const Vec3f& direction) { this->direction = direction; }
Vec3f Ray::pointAt(float t) const {return origin + direction * t;}

// LightSource class implementations
LightSource::LightSource(const Vec3f& position, const RGB& color, const Vec3f& intensity) : 
    position(position), color(color), intensity(intensity) {}
LightSource::LightSource(const Vec3f& position, const Vec3f& intensity) : 
    position(position), color(RGB(1.0f, 1.0f, 1.0f)), intensity(intensity) {}
Vec3f LightSource::getPosition() const { return position; }
Vec3f LightSource::getIntensity() const { return intensity; }



bool Scene::isShadowed(const Vec3f& hitPoint,const std::shared_ptr<LightSource>& lightSource) const{
    Vec3f hitPoint_to_light = lightSource->getPosition() - hitPoint;
    Ray ray(hitPoint,hitPoint_to_light);
    for(const auto& hittable : hittables){
        float t = hittable->hit(ray,Interval(0,std::numeric_limits<float>::infinity()));
        if(t >= 0)
            return true;
    }
    return false;
}

RGB Scene::getPixelColor(const Ray& ray,int maxRecursionDepth) const{
    if(maxRecursionDepth){
        RGB pixelColor(AmbientLight); // start with ambient light
        Hittable* closestHittable = nullptr;
        float closestHit = std::numeric_limits<float>::max();
        for (const auto& hittable : hittables) {
            float hitT = hittable->hit(ray,Interval(0,std::numeric_limits<float>::infinity()));
            if (hitT > 0 && hitT < closestHit) {
                closestHit = hitT;
                closestHittable = hittable.get();
            }
        }

        if(closestHit < std::numeric_limits<float>::max()) {
            Vec3f hitPoint = ray.pointAt(closestHit) + closestHittable->getNormal(ray.pointAt(closestHit)) * shadowRayEpsilon;
            Vec3f surfaceNormal = closestHittable->getNormal(hitPoint);
            for(const auto& lightSource : lightSources) {
                if(!isShadowed(hitPoint,lightSource)){
                    Vec3f hitPoint_to_light = lightSource->getPosition() - hitPoint;
                    Ray ray_hitPoint_to_light(hitPoint,hitPoint_to_light);
                    float r_square = hitPoint_to_light.dot(hitPoint_to_light);
                    Vec3f lightDir = hitPoint_to_light.normalized();
                    pixelColor += (closestHittable->getMaterial()->getColor() * 
                            std::max(0.0f, lightDir.dot(surfaceNormal)) *
                            (lightSource->getIntensity() / r_square));
                }
            }
            return pixelColor * getPixelColor(Ray(hitPoint,surfaceNormal + randomUnitVec3f()),maxRecursionDepth - 1);
        }
    }

    return BackgroundColor;
}

// Camera class implementations
Camera::Camera(const Vec3f& position) : position(position) {}

// since t and b depend on the l and r, I assumed that camera is relatively in the middle vertically,
// but it can not be in the middle horizontally.This not a good design choice, but I will fix it 
// in the future when I add more features to the camera class.
void Camera::updateCamera() {
    Vec3f w = u.cross(v);
    Vec3f m = position - w * focalLength;
    ny = (int)(nx / aspectRatio);
    t = (r - l) / aspectRatio / 2.0f;
    b = -t;
    deltau = u * ((r - l) / (float)nx);
    deltav = v * ((b - t) / (float)ny);
    Viewport00 = m + u * l + v * t + deltau * 0.5f + deltav * 0.5f;
}

Ray Camera::generateRay(int i, int j){
    auto offset = Vec3f(random_float() - 0.5f,random_float() - 0.5f,0.0f);
    Vec3f rayDirection = (Viewport00 + 
                        deltau * (j + offset.getX()) + 
                        deltav * (i + offset.getY()) - position).normalized();
    return Ray(this->position,rayDirection);
}

// This function will be responsible for rendering the scene by generating rays for 
// each pixel and checking for intersections with objects in the scene.
void Camera::render(const Scene& scene) {
    updateCamera();
    // setting backgrouund color for each pixel
    image.assign(ny, std::vector<RGB>(nx, scene.BackgroundColor));
    for(int i = 0; i < ny; i++) {
        for(int j = 0; j < nx; j++) {
            RGB pixelColor(0,0,0);
            for(int k = 0;k < samplePerPixel;k++){
                Ray ray = generateRay(i,j);
                pixelColor += scene.getPixelColor(ray,maxRecursionDepth) / samplePerPixel;
            }
            image[i][j] = pixelColor;// DO IT LATER !!division can be done at the end of the loop as image[i][j] = pixelColor / samplePerPixel
        }
    }
    writePPM();
}

void Camera::writePPM() {
    std::ofstream wstream("output.ppm");
    wstream << "P3\n" << nx << " " << ny << "\n255\n";
    for (int i = 0; i < ny; i++) {
        for(int j = 0; j < nx; j++) {
            wstream << (int)(image[i][j].getR() * 255.999) << " " 
                    << (int)(image[i][j].getG() * 255.999) << " " 
                    << (int)(image[i][j].getB() * 255.999) << "\t";
        }
        wstream << "\n";
    }
}

void Camera::setPosition(const Vec3f& position) {    
    this->position = position;
    updateCamera();
}

Material::Material(const RGB& DiffuseReflectance) : DiffuseReflectance(DiffuseReflectance) {}
RGB Material::getColor() const { return DiffuseReflectance; }

// Hittable class implementations
Hittable::Hittable(const std::shared_ptr<Material>& material) : material(material) {}
const std::shared_ptr<Material>& Hittable::getMaterial() const { return material; }

// Sphere class implementations
Sphere::Sphere(const std::shared_ptr<Material>& material, const Vec3f& center, float radius) : 
                                    Hittable(material), center(center), radius(radius) {}
Vec3f Sphere::getCenter() const { return center; }
float Sphere::getRadius() const { return radius; }
Vec3f Sphere::getNormal(const Vec3f& point) const {
    return (point - center).normalized();
}
float Sphere::hit(const Ray& ray,const Interval& interval) const {
    float A = ray.getDirection().dot(ray.getDirection());
    float B = -2 * ray.getDirection().dot(center - ray.getOrigin());
    float C = (center - ray.getOrigin()).dot(center - ray.getOrigin()) - radius*radius;

    float discriminant = B * B - 4 * A * C;

    if(discriminant == 0) {// 1 hit (line hits tangently)
        float t = -B / (2 * A);
        if(interval.contains(t)){
            return t;
        }
    }
    else if(discriminant > 0){ // 2 hits, return the closer one
        float t = (-B - sqrt(discriminant)) / (2 * A);
        if(interval.contains(t)){
            return t;
        }
    }

    return -1.0f;
}