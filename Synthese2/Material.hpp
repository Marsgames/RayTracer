//
//  Material.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 03/03/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Vector3.hpp>
#include <Color.hpp>
#include <map>

using std::map;

enum EMaterialType
{
    DifuseType = 0,
    MirrorType = 1,
    LightType = 2,
    GlassType = 3
};

class Material
{
private:
    Color m_color;
    float m_albedo;
    map<EMaterialType, float> albedoMap =
    {
        {DifuseType, 0},
        {MirrorType, 1},
        {LightType, 0},
        {GlassType, 9},
    };
    
public:
    int m_materialType;
    
    inline Material(){}
    inline Material(const int material, const Color color) :
    m_materialType{material},
    m_color{color}
    {
        SetAlbedo();
    }
    
    inline Color GetColor() const
    {
        return m_color;
    }
    
    inline float GetAlbedo() const
    {
        return m_albedo;
    }
    
private:
    inline void SetAlbedo()
    {
        m_albedo = albedoMap[static_cast<EMaterialType>(m_materialType)];
        
//        switch (m_materialType)
//        {
//            case DifuseType:
//                m_albedo = 0;
//                break;
//
//            case MirrorType:
//                m_albedo = 1;
//                break;
//
//            case LightType:
//                m_albedo = 0;
//                break;
//
//            case GlassType:
//                m_albedo = 9;
//                break;
//        }
    }
};
