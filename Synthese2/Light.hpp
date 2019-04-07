//
//  Light.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <Color.hpp>
#include <Pixel.hpp>
#include <Sphere.hpp>
#include <Vector3.hpp>

using std::vector;

class Light
{
private:
    Vector3 m_position;
    int m_puissance;
    
public:
    inline Light() {}
    
    inline Light(Vector3 position) :
    m_position{position}
    {}
    
    inline Light(Vector3 position, int puissance) :
    m_position{position},
    m_puissance{puissance}
    {}
    
    static bool CanSeeLight(const Vector3& point, const Light& light, const vector<Sphere>* scene);
    static void SetLightning(const Vector3& point, const int index, const Light& light,  vector<Pixel>& image);
    
    inline Vector3 GetPosition() const
    {
        return m_position;
    }
    inline void SetPosition(Vector3 position)
    {
        m_position = position;
    }
    
    inline int GetPuissance() const
    {
        return m_puissance;
    }
    inline void SetPuissance(int puissance)
    {
        m_puissance = puissance;
    }
};


