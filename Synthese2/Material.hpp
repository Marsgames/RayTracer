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

//enum EMaterials
//{
//    Mirror = 100,
//    Wall = 0,
//    DarkFloor = 15
//};

class Material {
    string m_name;
//    Color m_specularColor; // voila voila
    Color m_diffuseColor; // Couleur de base de l'objet
//    Color m_ambiantColor; // couleur de l'éclairage ambiant
    Color m_selfIlluminColor; // Couleur de la lumière émise
//    double m_shininess; // brillance
//    double m_shineStrength; // puissance de brillance
//    double m_transmittivity; // coéfficient de transmission (réfraction)
//    double m_reflectivity; // coéf de reflexion
//    bool m_permanent; // Permet de savoir si le material doit rester en memoire ou est temporaire.
    
//    Color m_color;
//    EMaterials m_material;
    double m_albedo;
//    string m_name;
    
public:
    Material() = delete;
    
    Material(Color diffuseColor) :
    m_diffuseColor{diffuseColor},
    m_selfIlluminColor{diffuseColor}
    {};
    
    Material(Color diffuseColor, const Color& selfIlluminColor) :
    m_diffuseColor{diffuseColor},
    m_selfIlluminColor{selfIlluminColor}
    {};
    
    Material(const string name, const Color& diffuseColor, const Color& selfIlluminColor = Color(255, 255, 255)) :
    m_name{name},
    m_diffuseColor{diffuseColor},
    m_selfIlluminColor{selfIlluminColor}
    {};
    
    Material(const string name, const Color& diffuseColor, const double albedo) :
    m_name{name},
    m_diffuseColor{diffuseColor},
    m_albedo{albedo}
    {};
    
//    Material(Color color, EMaterials material) :
//    m_color{color},
//    m_albedo{(material / 100.)},
//    m_material{material}
//    {};
    
    Color GetDiffuseColor() const;
    Color GetSelfIlluminColor() const;
    double GetAlbedo() const;
    void SetAlbedo(const double value);
//    EMaterials GetMaterialType() const;
};

struct MaterialList
{
    static const Material NoirMat;
    static const Material RougeMat;
    static const Material RougeDiffus;
    static const Material VertMat;
    static const Material VertDiffus;
    static const Material BleuMat;
    static const Material BlancMat;
    static const Material BlancDiffus;
    static const Material RoseMat;
    static const Material JauneMat;
    static const Material BleuCielMat;
    static const Material Miroir;
};
