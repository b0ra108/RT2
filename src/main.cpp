
#include "objects.hpp"

int main(){
    Camera cam(Vec3f(0.0f, 0.0f, 0.0f));
    auto m1 = std::make_shared<Material>(RGB(215, 32, 93));
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

    lightSources.push_back(std::make_shared<LightSource>(Vec3f(5.0f, 10.0f, 0.0f),Vec3f(100.0f, 100.0f, 100.0f)));

    Scene scene;
    scene.hittables = hittables;
    scene.lightSources = lightSources;
    scene.BackgroundColor = RGB(32,148,215);
    scene.AmbientLight = RGB(0.1f,0.1f,0.1f);
    scene.shadowRayEpsilon = 1e-2f;

    cam.lookFrom = Vec3f(-2,2,1);
    cam.lookAt = Vec3f(0,0,-1);
    cam.samplePerPixel = 20;
    cam.render(scene);

    return 0;
}