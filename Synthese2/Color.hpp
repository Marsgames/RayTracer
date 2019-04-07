//
//  Color.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 22/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <algorithm>
#include <iostream>
#include <Vector3.hpp>

using std::to_string;
using std::string;
using std::tolower;

class Color {
private:
    double m_r, m_g, m_b;
    
public:    
    inline Color() {}
    
    inline Color(double r, double g, double b) :
    m_r{r},
    m_g{g},
    m_b{b}
    {}
    
//    inline Color(int r, int g, int b) :
//    m_r{static_cast<double>(r)},
//    m_g{static_cast<double>(g)},
//    m_b{static_cast<double>(b)}
//    {}
    
    inline Color(Vector3 color)
    {
        m_r = color.GetX() * 255;
        m_g = color.GetY() * 255;
        m_b = color.GetZ() * 255;
    }
    
    inline double GetR() const
    {
        return m_r;
    }
    inline double GetG() const
    {
        return m_g;
    }
    inline double GetB() const
    {
        return m_b;
    }
    
    inline void SetR(double r)
    {
        m_r = r;
    }
    inline void SetG(double g)
    {
        m_g = g;
    }
    inline void SetB(double b)
    {
        m_b = b;
    }
    
    inline string ToString()
    {
        return "(" + to_string(static_cast<int>(m_r)) + ", " + to_string(static_cast<int>(m_g)) + ", " + to_string(static_cast<int>(m_b)) + ")";
    }
    
    inline Color operator*(const double v)
    {
        return Color{m_r * v, m_g * v, m_b * v};
    }
};
