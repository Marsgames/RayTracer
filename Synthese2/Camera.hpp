//
//  Camera.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Light.hpp>
#include <vector>
#include <Pixel.hpp>
#include <Scene.hpp>
#include <Sphere.hpp>
#include <string>

using std::vector;
using std::string;

enum EImageFormat
{
    BMP,
    PPM
};

struct Reflexion
{
    Material material = Material(Color());
    Intersection intersection = Intersection(false, -1, Vector3(0));
    Sphere sphere = Sphere(Vector3(0), -1, material);
    
    Reflexion(){};
    Reflexion(const Material& mat, const Intersection& inter, const Sphere& sph)
    {
        material = mat;
        intersection = inter;
        sphere = sph;
    };
    
};

class Camera
{
    Vector3 m_position, m_direction;
    int m_width, m_height, m_focalDist, m_maxBounce, m_maxMirrorBounce;
    vector<Pixel> m_pixels;
    bool m_useFocal;
    EImageFormat m_imageFormat = EImageFormat::BMP;
    class Scene* m_scene = nullptr;
    
    string m_source = "/Users/Raph/Desktop/TestSynthese/";
    string m_name = "theImage0";
    
    void InitPixelsArray();
    inline void SavePPM();
    inline void SaveBMP();
    Vector3 GetRayDirection();
    Vector3 GetRayDirection(const Vector3& toThatPoint) const;
    Reflexion GetMaterial(const vector<Sphere> spheres, const Ray& ray, const vector<Light> lights) const;
    
    Color GetColor(const Intersection& intersection, const Ray& ray) const;
    Color GetColor(const Intersection& intersection, const Ray& ray, int remainingBounce) const;

    Intersection GetNearestIntersection(const Ray& ray) const;
//    double GetRandomDouble(double min = -1, double max = 1) const;
    
    Color GetLighting(const Intersection& intersection, int remainingBounces = 3) const;
    Color GetDirectLighting(const Light& ligght, const Intersection& intersection, const float distanceToAdd = 0) const;
    Color GetIndirectLighting(const Intersection &intersection, int remainingBounces) const;
    
    void GeneratePartImage(const int departure, const int arrival, Ray ray);

public:
    Camera(const Vector3& position, const int width, const int height, Vector3& direction) :
    m_position{position},
    m_width{width},
    m_height{height},
    m_direction{direction.Normalize()}
    {
        InitPixelsArray();
        m_focalDist = 1000;
        m_useFocal = true;
        m_imageFormat = EImageFormat::BMP;
        m_maxBounce = 0;
        m_maxMirrorBounce = 30;
        
    }
    
    Camera(const Vector3& position, const int width, const int height, Vector3 direction, const int focalDistance) :
    m_position{position},
    m_width{width},
    m_height{height},
    m_direction{direction.Normalize()},
    m_focalDist{focalDistance}
    {
        InitPixelsArray();
        m_useFocal = true;
        m_imageFormat = EImageFormat::BMP;
        m_maxBounce = 0;
        m_maxMirrorBounce = 30;
    }
    
    Vector3 GetPosition() const;
    void SetPosition(Vector3 position);
    
    Vector3 GetDirection() const;
    void SetDirection(Vector3 direction);
    
    int GetWidth() const;
    int GetHeight() const;
    
    int GetFocalDist() const;
    void SetFocalDist(int focalDistance);

    bool GetUseFocal();
    void SetUseFocal(bool value);
    
    void SetImageFormat(EImageFormat format);
    void SaveImage();
    void SetImageName(string name);
    
    void DrawImage();
    void DrawBB();
    void DrawImageWithThread();

    void SetScene(Scene* scene);
    
    
};
