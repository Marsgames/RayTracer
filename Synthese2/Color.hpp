//
//  Color.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

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
    Color() {
        SetColorName();
    };
    
    Color(int r, int g, int b) :
    m_r{static_cast<double>(r)},
    m_g{static_cast<double>(g)},
    m_b{static_cast<double>(b)}
    {
        SetColorName();
    };
    
    double GetR() const;
    double GetG() const;
    double GetB() const;
    void SetR(double value);
    void SetG(double value);
    void SetB(double value);
    
    Color operator*(const double other) const;
    
    void Print() const;
    void SetColorName();
    EColor GetColorName() const;
    static Color GetColor(EColor colorName);
};
