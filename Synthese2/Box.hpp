//
//  Box.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 19/11/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include "Vector3.hpp"
#include "Sphere.hpp"

class Box
{
public:
    Vector3 pMin;
    Vector3 pMax;
    
    Box(Sphere sphere){
        pMin = Vector3(sphere.origine.x - sphere.rayon, sphere.origine.y - sphere.rayon, sphere.origine.z - sphere.rayon);
        pMax = Vector3(sphere.origine.x + sphere.rayon, sphere.origine.y + sphere.rayon, sphere.origine.z + sphere.rayon);
    }
};
