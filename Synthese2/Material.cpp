//
//  Material.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 03/06/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <Color.hpp>
#include "Material.hpp"

Color Material::GetDiffuseColor() const
{
    return m_diffuseColor;
}

Color Material::GetSelfIlluminColor() const {
    return m_selfIlluminColor;
}

double Material::GetAlbedo() const
{
    return m_albedo;
//    return 0;
}
void Material::SetAlbedo(const double value)
{
    m_albedo = value;
}


//EMaterials Material::GetMaterialType() const {
//    return  m_material;
//}


const Material MaterialList::NoirMat = Material("Noir mat", Color(0, 0, 0));
const Material MaterialList::RougeMat = Material("Rouge mat", Color(255, 0, 0));
const Material MaterialList::VertMat = Material("Vert mat", Color(0, 255, 0));
const Material MaterialList::BleuMat = Material("Bleu mat", Color(0, 0, 255));
const Material MaterialList::BlancMat = Material("Blanc mat", Color(255, 255, 255));
const Material MaterialList::RoseMat = Material("Rose mat", Color(255, 000, 255));
const Material MaterialList::JauneMat = Material("Jaune mat", Color(255, 255, 000));
const Material MaterialList::BleuCielMat = Material("Bleu ciel mat", Color(000, 255, 255));
const Material MaterialList::Miroir = Material("Miroir", Color(100, 100, 100), 1);
