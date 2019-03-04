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
    DifuseType,
    MirrorType,
    LightType,
    GlassType
};

class Material
{
private:
    EMaterials m_material;
    Color m_color;
    float m_albedo;
    
public:
    Material(){}
    Material(const EMaterials material, const Color color)
    {
        m_material = material;
        m_color = color;
        SetAlbedo();
    }
    
    EMaterials GetMaterial() const
    {
        return m_material;
    }
    
    Color GetColor() const
    {
        return m_color;
    }
    
    float GetAlbedo() const
    {
        return m_albedo;
    }
    
private:
    void SetAlbedo()
    {
        switch (m_material)
        {
            case DifuseType:
                m_albedo = 0;
                break;
                
            case MirrorType:
                m_albedo = 1;
                break;
                
            case LightType:
                m_albedo = 0;
                break;
                
            case GlassType:
                m_albedo = 9;
                break;
        }
    }
};
