//
//  Color.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

class Color {
    int m_r, m_g, m_b;
    
public:
    Color()
    {
//        m_r = 0;
//        m_g = 0;
//        m_b = 0;
    }
    
    Color(int r, int g, int b) :
    m_r{r},
    m_g{g},
    m_b{b}
    {}
    
    int GetR() const;
    int GetG() const;
    int GetB() const;
};
