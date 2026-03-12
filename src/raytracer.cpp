
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

Vec3f Vec3f::operator+=(const Vec3f& vec){
    x += vec.getX();
    y += vec.getY();
    z += vec.getZ();

    return Vec3f(x,y,z);
}

Vec3f Vec3f::operator-=(const Vec3f& vec){
    x -= vec.getX();
    y -= vec.getY();
    z -= vec.getZ();

    return Vec3f(x,y,z);
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
        if(t >= 0 && !hittable->getMaterial()->isDielectric())
            return true;
    }
    return false;
}

RGB Scene::getPixelColor(const Ray& ray,int maxRecursionDepth) const{
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
        Vec3f hitPoint = ray.pointAt(closestHit);
        Vec3f surfaceNormal = closestHittable->getNormal(hitPoint).normalized();

        Vec3f shadowRayEpsilonTerm;

        bool rayFromInside = false;

        if(ray.getDirection().normalized().dot(surfaceNormal) > 0){
            surfaceNormal = surfaceNormal * (-1.0f);
            rayFromInside = true;
        }

        std::shared_ptr<Material> hitMaterial = closestHittable->getMaterial();

        if(hitMaterial->isDielectric() && maxRecursionDepth > 0 ){
            hitPoint -= closestHittable->getNormal(ray.pointAt(closestHit)) * shadowRayEpsilon;
            float RI = (rayFromInside == true ? hitMaterial->getRI() : 
                                                1.0f / hitMaterial->getRI());
            float cos_theta = std::fmin((ray.getDirection().normalized() * (-1)).dot(surfaceNormal),1.0f);
            float sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);

            bool cannnotRefrect = RI * sin_theta > 1.0f;

            auto r0 = (1 - RI) / (1 + RI);
            r0 *= r0;
            float reflactance = r0 + (1-r0)*std::pow((1-cos_theta),5);

            return cannnotRefrect == false || reflactance > random_float() ? getPixelColor(Ray(hitPoint,ray.refract(surfaceNormal,RI)),
                                                                maxRecursionDepth - 1) : 
                                            getPixelColor(Ray(hitPoint,ray.reflect(surfaceNormal,0.0f)),
                                                                maxRecursionDepth - 1);
            
        }

        hitPoint += closestHittable->getNormal(ray.pointAt(closestHit)) * shadowRayEpsilon;
        for(const auto& lightSource : lightSources) {
            if(!isShadowed(hitPoint,lightSource)){
                Vec3f hitPoint_to_light = lightSource->getPosition() - hitPoint;
                Ray ray_hitPoint_to_light(hitPoint,hitPoint_to_light);
                float r_square = hitPoint_to_light.dot(hitPoint_to_light);
                Vec3f lightDir = hitPoint_to_light.normalized();
                pixelColor += (hitMaterial->getColor() * 
                        std::max(0.0f, lightDir.dot(surfaceNormal)) *
                        (lightSource->getIntensity() / r_square));
            }
        }
        if(hitMaterial->isMirrored() && maxRecursionDepth > 0){
            return pixelColor * getPixelColor(Ray(hitPoint,ray.reflect(surfaceNormal,hitMaterial->getFuzziness())),maxRecursionDepth - 1);
        }

        return pixelColor;
    }

    float a = ray.getDirection().getY();
    return RGB(0.5f,0.7f,0.8f) * (1 - a) + RGB(0.5f,0.7f,1.0f) * a;
}

Vec3f Ray::reflect(const Vec3f& normal,float fuzziness) const{
    Vec3f reflected_direction = direction -  normal * 2 * direction.dot(normal);
    return reflected_direction.normalized() + randomUnitVec3f() * fuzziness;
}

Vec3f Ray::refract(const Vec3f& normal,float ri) const{
    Vec3f dir_norm = direction.normalized();
    float dir_dot_normal = -dir_norm.dot(normal);

    auto cos_theta = std::fmin(dir_dot_normal, 1.0f);

    Vec3f horizontal_component = (dir_norm + normal * cos_theta) * ri;
    Vec3f vertical_component = normal * (-std::sqrt(std::fabs(1.0 - horizontal_component.dot(horizontal_component))));

    return horizontal_component + vertical_component;
}


// Camera class implementations
Camera::Camera(const Vec3f& position) : position(position) {}

// since t and b depend on the l and r, I assumed that camera is relatively in the middle vertically,
// but it can not be in the middle horizontally.This not a good design choice, but I will fix it 
// in the future when I add more features to the camera class.
void Camera::updateCamera() {
    Vec3f atToFrom = (lookFrom - lookAt);
    w = atToFrom.normalized();
    u = vUp.cross(w).normalized();
    v = w.cross(u).normalized();

    position = lookFrom;

    Vec3f m = position - w * focusDistance;
    ny = (int)(nx / aspectRatio);

    auto theta = degreeToRadian(vfov);
    auto h = std::tan(theta/2);

    r *= h * focusDistance;
    l *= h * focusDistance;

    t = (r - l) / aspectRatio / 2.0f;
    b = -t;

    deltau = u * ((r - l) / (float)nx);
    deltav = v * ((b - t) / (float)ny);
    Viewport00 = m + u * l + v * t + deltau * 0.5f + deltav * 0.5f;

    auto defocus_radius = focusDistance * std::tan(degreeToRadian(defocusAngle/2));
    defocusDisku = u * defocus_radius;
    defocusDiskv = v * defocus_radius;
}

Ray Camera::generateRay(int i, int j){
    auto offset = Vec3f(random_float() - 0.5f,random_float() - 0.5f,0.0f);
    Vec3f origin = (defocusAngle <= 0) ? this->position : random_defocusDiskPoint();
    Vec3f rayDirection = (Viewport00 + 
                    deltau * (j + offset.getX()) + 
                    deltav * (i + offset.getY()) - origin).normalized();
    return Ray(origin,rayDirection);
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
            image[i][j] = pixelColor + scene.AmbientLight;// DO IT LATER !!division can be done at the end of the loop as image[i][j] = pixelColor / samplePerPixel
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

Vec3f Camera::random_defocusDiskPoint() const{
    auto p = randomVec3fDisk();
    return this->position + (defocusDisku * p.getX()) + (defocusDiskv * p.getY());
}

// Material class implementations
Material::Material(const RGB& DiffuseReflectance) : DiffuseReflectance(DiffuseReflectance), 
                                                    Mirror(false),
                                                    Fuzziness(0.0f),
                                                    Dielectric(false),
                                                    RefractiveIndex(-1.0f) {}

Material::Material(const RGB& DiffuseReflectance,bool Mirror,float Fuzziness) : DiffuseReflectance(DiffuseReflectance), 
                                                                                Mirror(Mirror),
                                                                                Fuzziness(Mirror == true ? 
                                                                                    (Fuzziness > 1.0f ? 1.0f : (Fuzziness < 0.0f ? 0.0f : Fuzziness)) :
                                                                                    0.0f),
                                                                                Dielectric(false),
                                                                                RefractiveIndex(-1.0f){}
                                                                                
Material::Material(float RefractiveIndex): DiffuseReflectance(1.0f,1.0f,1.0f), 
                                                            Mirror(false),
                                                            Fuzziness(0.0f),
                                                            Dielectric(true),
                                                            RefractiveIndex(RefractiveIndex){}

RGB Material::getColor() const { return DiffuseReflectance; }
bool Material::isMirrored() const { return Mirror; }
float Material::getFuzziness() const { return Fuzziness; }
bool Material::isDielectric() const { return Dielectric; }
float Material::getRI() const { return RefractiveIndex; }

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