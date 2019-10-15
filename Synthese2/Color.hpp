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
    Color() = delete;
    
    Color(const double c):
    m_r{c},
    m_g{c},
    m_b{c}
    {
        SetColorName();
    };
    
    Color(const double r, const double g, const double b) :
    m_r{r},
    m_g{g},
    m_b{b}
    {
        SetColorName();
    };
    
    double GetR() const;
    double GetG() const;
    double GetB() const;
    void SetR(const double value);
    void SetG(const double value);
    void SetB(const double value);
    
    Color operator*(const Color& other) const;
    Color operator*(const double other) const;
    bool operator==(const Color& other) const;
    void operator+=(const Color& other);
    Color operator/(const double value) const;
    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;

    void Print() const;
    string ToString() const;
    void SetColorName();
    EColor GetColorName() const;
    static Color GetColor(const EColor& colorName);
};
