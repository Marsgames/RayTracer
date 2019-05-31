//
//  Light.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 30/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Color.hpp>
#include <iostream>
#include <Vector3.hpp>

using std::cout;
using std::endl;

class Light {
    Vector3 m_position;
    double m_power;
    Color m_color;
    
public:
    Light(Vector3 position, double power):
    m_position{position},
    m_power{power},
    m_color{Color{255, 255, 255}}
    {};
    
    Light(Vector3 position, double power, Color color):
    m_position{position},
    m_power{power},
    m_color{color}
    {};
    
    Vector3 GetPosition() const;
    double GetPower() const;
//    Color GetColor() const;
    
    static Color GetLightning(const Light& light, Color& color, const double distance)
    {        
//        cout << "affichons RGB : ";
//        color.Print();
        
        if (color.GetR() != 0 || color.GetG() != 0 ||  color.GetB() != 0)
        {
//        cout << "color : (" << color.GetR() << ", " << color.GetG() << ",  " << color.GetB() << ")" << endl;
//        cout << "light power : " << light.GetPower() << endl;
        double puissance = light.GetPower() * (1 / distance);
//        cout << "puissance : " << puissance << endl;
        
        Color newColor = color * puissance;
//        cout << "new color : (" << newColor.GetR() << ", " << newColor.GetG() << ",  " << newColor.GetB() << ")" << endl;
        
//        cout << endl;
            if (newColor.GetR() == 0 && newColor.GetG() == 0 && newColor.GetB() == 0)
            {
                return Color{0, 255, 255} * .2;
            }
            
        return newColor;
        }
        
        return color;
    }
};
