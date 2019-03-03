//
//  Color.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 22/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <iostream>

using std::to_string;

class Color {
public:
    double r, g, b;
    
    std::string ToString()
    {
        return "(" + to_string(int(r)) + ", " + to_string(int(g)) + ", " + to_string(int(b)) + ")";
    }
};
