//
//  Color.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>

using std::string;

enum EColor
{
    Black,
    Red,
    Green,
    Blue,
    White,
    Other,
    Pink,
    Yellow
};

class Color {
    double m_r, m_g, m_b;
    
    EColor m_colorName;
    
public:
    Color() :
    m_r{0},
    m_g{0},
    m_b{0}
    {
        SetColorName();
    };
    
//    Color(int r, int g, int b) :
//    m_r{static_cast<double>(r)},
//    m_g{static_cast<double>(g)},
//    m_b{static_cast<double>(b)}
//    {
//        SetColorName();
//    };
    
    Color(double r, double g, double b) :
    m_r{r},
    m_g{g},
    m_b{b}
    {
//        if ((r + g + b) > 3)
//        {
//            std::cout << "LES COULEURS NE PEUVENT PAS ÊTRE SUPÉRIEUR À 3" << std::endl;
//        }
        
        SetColorName();
    };
    
    double GetR() const;
    double GetG() const;
    double GetB() const;
    void SetR(double value);
    void SetG(double value);
    void SetB(double value);
    
    Color operator*(const Color& other) const;
    Color operator*(const double other) const;
    bool operator==(const Color& other) const;
    void operator+=(const Color& other);
    Color operator/(const int value) const;
    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;

    void Print() const;
    string ToString() const;
    void SetColorName();
    EColor GetColorName() const;
    static Color GetColor(EColor colorName);
};
