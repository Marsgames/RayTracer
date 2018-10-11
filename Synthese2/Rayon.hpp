//
//  Rayon.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include "Vector3.hpp"

class Rayon
{
public:
    Vector3 origine;
    Vector3 direction;
    
    Rayon(Vector3 origine, Vector3 direction)
    {
        this->origine = origine;
        this->direction = Normalize(direction);
    };
};
