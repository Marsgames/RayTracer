//
//  Camera.h
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include "Vector3.hpp"

class Camera
{
public:
    int height, width;
    Vector3 position;
    
    Camera(const Vector3 position, const int height, const int width)
    {
        this->position = position;
        this->height = height;
        this->width = width;
    };
};
