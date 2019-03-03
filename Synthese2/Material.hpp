//
//  Material.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 03/03/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include "Vector3.hpp"
#include "Color.hpp"

enum EMaterials
{
    DifuseType = 0,
    MirrorType = 100,
    LightType = 0,
    GlassType = 90
};

class Material
{
private:
    EMaterials m_mataterial;
    Color m_color;
    float m_albedo;
    
public:
    Material(){}
    Material(const EMaterials material, const Color color)
    {
        m_mataterial = material;
        m_color = color;
        m_albedo = material / 100;
    }
    
    EMaterials GetMaterial()
    {
        return m_mataterial;
    }
    
    Color GetColor()
    {
        return m_color;
    }
    
    float GetAlbedo()
    {
        return m_albedo;
    }
    
};
