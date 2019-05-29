//
//  Camera.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <vector>
#include <Pixel.hpp>
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
    Vector3 m_position, m_dir;
    int m_width, m_height, m_focalDist;
    vector<Pixel> m_pixels;
    bool m_useFocal;
    EImageFormat m_imageFormat = EImageFormat::BMP;
    
    const string source = "/Users/Raph/Desktop/TestSynthese/";
    const string nomImage = "theImage0";
    
    void InitPixelsArray();
    inline void SaveImageWithFocal();
    inline void SaveImageWithoutFocal();
    inline void SavePPM();
    inline void SaveBMP();
    
public:
    Camera(const Vector3& position, const int width, const int height, Vector3& direction) :
    m_position{position},
    m_width{width},
    m_height{height},
    m_dir{direction.Normalize()}
    {
        InitPixelsArray();
        m_focalDist = 1000;
        m_useFocal = true;
        m_imageFormat = EImageFormat::BMP;
    }
    
    Camera(const Vector3& position, const int width, const int height, Vector3& direction, const int focalDistance) :
    m_position{position},
    m_width{width},
    m_height{height},
    m_dir{direction.Normalize()},
    m_focalDist{focalDistance}
    {
        InitPixelsArray();
        m_useFocal = false;
        m_imageFormat = EImageFormat::BMP;
    }
    
    Vector3 GetPosition() const;
    void SetPosition(Vector3 position);
    Vector3 GetDirection() const;
    void SetDirection(Vector3 direction);
    inline int GetWidth() const;
    inline int GetHeight() const;
    inline int GetFocalDist() const;
    void SetUseFocal(bool value);
    inline void SetFocalDist(int focalDistance);
    void SetImageFormat(EImageFormat format);
    void SaveImage();
    
};
