
#include <cstdlib>
#include <limits>
#include <cmath>
#include "vecs.hpp"



constexpr float PI = 3.14159265359;

// Functions
inline float random_float(){
    return std::rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max){
    return min + (max-min) * random_float();
}

inline Vec3f randomVec3f(){
    return Vec3f(random_float(),random_float(),random_float());
}

inline Vec3f randomVec3f(float min, float max){
    return Vec3f(random_float(min,max),random_float(min,max),random_float(min,max));
}
inline Vec3f randomUnitVec3f(){
    while(true){
        auto v = randomVec3f(-1.0f,1.0f);
        auto lenv_squared = v.dot(v);

        if(lenv_squared > 1e-8f && lenv_squared <= 1){
            return v / sqrt(lenv_squared); 
        }// normalized vec is return, no need to call the normalized(),since 
         // that would result in calculating length again
    }
}

inline Vec3f randomVec3fHemisphere(const Vec3f& normal){
    Vec3f random_unit_vec = randomUnitVec3f(); 

    if(random_unit_vec.dot(normal) > 0){
        return random_unit_vec;
    }
    
    return random_unit_vec * (-1);
}

inline Vec3f randomVec3fDisk(){
    while(true){
        Vec3f p = Vec3f(random_float(-1,1),random_float(-1,1),0);
        if(p.dot(p) <= 1)
            return p;
    }
}

inline float degreeToRadian(float degree){
    return degree * PI / 180;
}
