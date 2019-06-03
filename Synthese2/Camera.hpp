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
#include <Sphere.hpp>
#include <string>

using std::vector;
using std::string;

enum EImageFormat
{
    BMP,
    PPM
};

class Camera
{
    Vector3 m_position, m_direction;
    int m_width, m_height, m_focalDist, m_maxBounce;
    vector<Pixel> m_pixels;
    bool m_useFocal;
    EImageFormat m_imageFormat = EImageFormat::BMP;
    
    string m_source = "/Users/Raph/Desktop/TestSynthese/";
    string m_name = "theImage0";
    
    void InitPixelsArray();
    inline void SavePPM();
    inline void SaveBMP();
    Vector3 GetRayDirection();
    Vector3 GetRayDirection(const Vector3& toThatPoint) const;
    Color GetColor(const vector<Sphere> spheres, const Ray& ray, const vector<Light> lights) const;
//    void CalculateFocal();

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
        m_maxBounce = 10;
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
        m_maxBounce = 10;
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
    
    void DrawImage(const vector<Sphere>& spheres, const vector<Light>& lights);
    
    
};
