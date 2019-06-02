//
//  Color.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include "Color.hpp"
#include <iostream>

using std::cout;
using std::endl;


double Color::GetR() const {
    return m_r;
}

double Color::GetG() const {
    return m_g;
}

double Color::GetB() const {
    return m_b;
}

void Color::Print() const
{
    cout << "Color(" << m_r << ", " << m_g << ", " << m_b << ")" << endl;
}

Color Color::operator*(const double other) const
{
    return Color{static_cast<int>(m_r * other), static_cast<int>(m_g * other), static_cast<int>(m_b * other)};
}

void Color::SetColorName() {
    if (0 == m_r && 0 == m_g && 0 == m_b)
    {
        m_colorName = EColor::Black;
    }
    else if (255 == m_r && 0 == m_g && 0 == m_b)
    {
        m_colorName = EColor::Red;
    }
    else if (0 == m_r && 255 == m_g && 0 == m_b)
    {
        m_colorName = EColor::Green;
    }
    else if (0 == m_r && 0 == m_g && 255 == m_b)
    {
        m_colorName = EColor::Blue;
    }
    else if (255 == m_r && 255 == m_g && 255 == m_b)
    {
        m_colorName = EColor::White;
    }
    else
    {
        m_colorName = EColor::Other;
    }
}

EColor Color::GetColorName() const {
    return m_colorName;
}

Color Color::GetColor(EColor colorName) {
    switch (colorName) {
        case Black:
            return Color{0, 0, 0};
            break;
        case Red:
            return Color{255, 0, 0};
            break;
        case Green:
            return Color{0, 255, 0};
            break;
        case Blue:
            return Color{0, 0, 255};
            break;
        case White:
            return Color{255, 255, 255};
            break;
        case Pink:
            return Color{255, 0, 255};
            break;
        case Yellow:
            return Color{255, 255, 0};
            break;
            
        default:
            return Color{0, 0, 0};
            break;
    }
}

void Color::SetR(double value) {
    m_r = value;
}

void Color::SetG(double value) {
    m_g = value;
}

void Color::SetB(double value) {
    m_b = value;
}
