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

enum EMaterialType
{
    DifuseType,
    MirrorType,
    LightType,
    GlassType
};

class Material
{
private:
    EMaterialType m_materialType;
    Color m_color;
    float m_albedo;
    
public:
    Material(){}
    Material(const EMaterialType material, const Color color)
    {
        m_materialType = material;
        m_color = color;
        SetAlbedo();
    }
    
    EMaterialType GetMaterialType() const
    {
        return m_materialType;
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
        switch (m_materialType)
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
