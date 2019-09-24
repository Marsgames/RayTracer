//
//  Pixel.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include "Pixel.hpp"


Vector3 Pixel::GetPosition() const {
    return m_position;
}

 double Pixel::GetPositionX() const {
    return m_position.GetX();
}

 double Pixel::GetPositionY() const {
    return m_position.GetY();
}

 double Pixel::GetPositionZ() const {
    return m_position.GetZ();
}

Color Pixel::GetColor() const {
    return m_color;
}

 double Pixel::GetColorR() const {
    return m_color.GetR();
}

 double Pixel::GetColorG() const {
    return m_color.GetG();
}

 double Pixel::GetColorB() const {
    return m_color.GetB();
 }

void Pixel::SetColor(Color color) {
    m_color = color;
}

