//
//  Color.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <iostream>

using std::cout;
using std::endl;

class Color {
    double m_r, m_g, m_b;
    
public:
    Color()
    {
//        m_r = 0;
//        m_g = 0;
//        m_b = 0;
    }
    
    Color(int r, int g, int b) :
    m_r{static_cast<double>(r)},
    m_g{static_cast<double>(g)},
    m_b{static_cast<double>(b)}
    {}
    
    double GetR() const;
    double GetG() const;
    double GetB() const;
    
    inline Color operator*(const double v)
    {
        return Color{static_cast<int>(m_r * v), static_cast<int>(m_g * v), static_cast<int>(m_b * v)};
    }
    
    void Print()
    {
        cout << "Color(" << m_r << ", " << m_g << ", " << m_b << ")" << endl;
    }
};
