//
//  Material.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 03/06/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Color.hpp>
#include <string>

using std::string;

enum EMaterials
{
    Mirror = 100,
    Wall = 0,
    DarkFloor = 15
};

class Material {
    Color m_color;
    EMaterials m_material;
    double m_albedo;
    string m_name;
    
public:
    Material() = delete;
    
    Material(Color color, EMaterials material) :
    m_color{color},
    m_albedo{(material / 100.)},
    m_material{material}
    {};
    
    Color GetColor() const;
    double GetAlbedo() const;
    EMaterials GetMaterialType() const;
};
