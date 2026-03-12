
#include "objects.hpp"
#include <cmath>


int main(){
    Camera cam(Vec3f(0.0f, 0.0f, 0.0f));
    /*auto m1 = std::make_shared<Material>(RGB(215, 32, 93));
    auto m2 = std::make_shared<Material>(RGB(22,218,113));
    auto m3 = std::make_shared<Material>(RGB(0.8f, 0.6f, 0.2f),true,0.15f);
    auto m4 = std::make_shared<Material>(1.5f);
    auto m5 = std::make_shared<Material>(1.0f / 1.5f);

    std::vector<std::shared_ptr<Hittable>> hittables;
    std::vector<std::shared_ptr<LightSource>> lightSources;

    hittables.push_back(std::make_shared<Sphere>(m1, Vec3f(0.0f, 0.0f, -1.2f), 0.5f));
    hittables.push_back(std::make_shared<Sphere>(m2, Vec3f(0.0f, -100.5f, -1.0f), 100.0f));
    hittables.push_back(std::make_shared<Sphere>(m3, Vec3f(1.0f, 0.0f, -1.0f), 0.5f));
    hittables.push_back(std::make_shared<Sphere>(m4, Vec3f(-1.0f, 0.0f, -1.0f), 0.5f));
    hittables.push_back(std::make_shared<Sphere>(m5, Vec3f(-1.0f, 0.0f, -1.0f), 0.4f));

    */


    std::vector<std::shared_ptr<Hittable>> hittables;
    std::vector<std::shared_ptr<LightSource>> lightSources;

    Scene scene(hittables,lightSources);

    lightSources.push_back(std::make_shared<LightSource>(Vec3f(5.0f, 10.0f, 0.0f),Vec3f(100.0f, 100.0f, 100.0f)));
    scene.BackgroundColor = RGB(32,148,215);
    scene.AmbientLight = RGB(0.1f,0.1f,0.1f);
    scene.shadowRayEpsilon = 1e-2f;

    cam.lookFrom = Vec3f(13,2,3);
    cam.lookAt = Vec3f(0,0,0);
    cam.samplePerPixel = 3;
    cam.defocusAngle = 0.2f;
    cam.focusDistance = 10.0f;



    auto ground_material = std::make_shared<Material>(RGB(0.5f, 0.5f, 0.5f));

    hittables.push_back(std::make_shared<Sphere>(ground_material,Vec3f(0.0f,-1000.0f,0.0f), 1000.0f));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_float();
            Vec3f center(a + 0.9f * random_float(), 0.2f, b + 0.9f * random_float());
            if (vectorLength(center - Vec3f(4.0f, 0.2f, 0.0f))> 0.9f) {
                std::shared_ptr<Material> sphere_material;
                if (choose_mat < 0.8f) {
                    // diffuse
                    auto dif = (RGB(1.0f,1.0f,1.0f) * randomUnitVec3f());
                    sphere_material = std::make_shared<Material>(dif);
                    hittables.push_back(std::make_shared<Sphere>(sphere_material,center, 0.2f));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto metal = RGB::randomColor(0.5f, 1.0f);
                    auto fuzz = random_float(0.0f, 0.5f);
                    sphere_material = std::make_shared<Material>(metal, true, fuzz);
                    hittables.push_back(std::make_shared<Sphere>(sphere_material,center, 0.2f));
                } else {
                    // glass
                    sphere_material = std::make_shared<Material>(1.5f);
                    hittables.push_back(std::make_shared<Sphere>(sphere_material,center, 0.2f));
                }
            }
        }
    }
    auto material1 = std::make_shared<Material>(1.5f);
    hittables.push_back(std::make_shared<Sphere>(material1,Vec3f(0.0f, 1.0f, 0.0f), 1.0f));

    auto material2 = std::make_shared<Material>(RGB(0.4f, 0.2f, 0.1f));
    hittables.push_back(std::make_shared<Sphere>(material2,Vec3f(-4.0f, 1.0f, 0.0f), 1.0f));

    auto material3 = std::make_shared<Material>(RGB(0.7f,0.6f, 0.5f), true, 0.0f);
    hittables.push_back(std::make_shared<Sphere>(material3,Vec3f(4.0f, 1.0f, 0.0f), 1.0f));
    
    cam.render(scene);
    return 0;
}