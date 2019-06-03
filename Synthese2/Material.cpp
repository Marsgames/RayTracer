//
//  Material.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 03/06/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <Color.hpp>
#include "Material.hpp"

Color Material::GetColor() const
{
    return m_color;
}

double Material::GetAlbedo() const
{
    return m_albedo;
}
