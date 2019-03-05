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

using std::to_string;
using std::string;
using std::tolower;

class Color {
private:
    double m_r, m_g, m_b;
    
public:    
    Color() {}
    
    Color(double r, double g, double b)
    {
        m_r = r;
        m_g = g;
        m_b = b;
    }
    
    Color(Vector3 color)
    {
        m_r = color.GetX() * 255;
        m_g = color.GetY() * 255;
        m_b = color.GetZ() * 255;
    }
    
//    Color(string color)
//    {
//        std::transform(color.begin(), color.end(), color.begin(), tolower);
//
//        switch (color)
//        {
//            case "red", "rouge":
//                m_r = 255;
//                m_g = 0;
//                m_b = 0;
//                break;
//
//        }
//    }
    
    double GetR() const
    {
        return m_r;
    }
    double GetG() const
    {
        return m_g;
    }
    double GetB() const
    {
        return m_b;
    }
    
    void SetR(double r)
    {
        m_r = r;
    }
    void SetG(double g)
    {
        m_g = g;
    }
    void SetB(double b)
    {
        m_b = b;
    }
    
    
    string ToString()
    {
        return "(" + to_string(int(m_r)) + ", " + to_string(int(m_g)) + ", " + to_string(int(m_b)) + ")";
    }
};
