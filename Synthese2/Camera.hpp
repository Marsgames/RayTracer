//
//  Camera.h
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <math.h>
#include <Pixel.hpp>
#include <Vector3.hpp>

using std::vector;

class Camera
{
private:
    int m_height, m_width;
    Vector3 m_origin, m_direction;
    float m_focal;
    vector<Pixel> m_image;
    
    void InitImage()
    {
        Vector3 sample{0,0,1};
        const double teta1 = acos((Vector3::Dot(sample, m_direction)));
        const double teta = m_direction.GetX() >= 0 ? m_direction.GetZ() >= 0 ? teta1 : teta1 * -1 : m_direction.GetZ() >= 0 ? teta1 * -1 : teta1;
        m_image.reserve(m_height * m_width);
        Color defaultColor {0, 0, 0};
        
        for (int index = 0; index < m_height * m_width; index++)
        {
            // Pour un écran de 1000 * 1000
            // 0 * 0  -->  1000 * 1000
            //const int x = index % m_width;
            //const int y = index / m_width;
            
            // -500, -500  -->  500, 500
            const int indexX = (index % m_width - m_width / 2);// + m_origin.GetX();
            const int indexY = (index / m_width - m_height / 2);// + m_origin.GetY();
            
            const Vector3 actualPos {indexX, indexY, static_cast<int>(m_origin.GetZ())};
            const Vector3 newPos = Vector3(cos(teta) * actualPos.GetX() + sin(teta) * actualPos.GetZ(), actualPos.GetY(), -sin(teta) * actualPos.GetX() + cos(teta) * actualPos.GetZ());
            m_image.push_back(Pixel(newPos, defaultColor));
        }
    }
    
public:
    Camera(const Vector3& origin, const int width, const int height, Vector3& direction, float focal) :
    m_origin{origin},
    m_height{height},
    m_width{width},
    m_direction{direction.Normalize()}
    {
        if (focal < 0)
        {
            throw "Focal cannot be less than 0 !";
        }
        else
        {
            m_focal = focal;
        }
        
        InitImage();
    };
    
    int GetHeight() const
    {
        return m_height;
    }
    
    int GetWidth() const
    {
        return m_width;
    }
    
    Vector3 GetPosition() const
    {
        return m_origin;
    }
    void SetPosition(Vector3& position)
    {
        m_origin = position;
    }
    
    Vector3 GetDirection() const
    {
        return m_direction;
    }
    void SetDirection(Vector3& direction)
    {
        m_direction = direction.Normalize();
        InitImage();
    }
    
    Vector3 GetFocalDirection(const Vector3& toThatPoint) const
    {
        const Vector3 startPoint = m_origin + Vector3(toThatPoint.GetX(), toThatPoint.GetY(), m_origin.GetZ());
        const Vector3 focalStart = m_origin + Negate(m_direction * m_focal);
        
        return (startPoint - focalStart).Normalize();
    }
    
    vector<Pixel>& GetImage()
    {
        return m_image;
    }
};

Vector3 MoveCameraOnCircle(const Vector3& circleOrigin, const double rayon, Camera& cam, const double index)
{
    Vector3 newPosition = Vector3((circleOrigin.GetX() + rayon * cos(index)), circleOrigin.GetY(), (circleOrigin.GetZ() + rayon * sin(index)));
    return newPosition;
}


double fDeX(const double petitX, const Vector3& circleOrigin, const float rayon)
{
    //  sqrt(r²-(x-xO)²)+yO
    return sqrt((rayon * rayon) - ((petitX - circleOrigin.GetX()) * (petitX - circleOrigin.GetX()))) + circleOrigin.GetZ();
}
