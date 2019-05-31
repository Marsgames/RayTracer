//
//  Ray.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Vector3.hpp>

class Ray {
    Vector3 m_origin, m_direction;
    
public:
    Ray(Vector3 origin, Vector3 direction) :
    m_origin{origin},
    m_direction{direction.Normalize()}
    {};
    

    Vector3 GetOrigin() const;
    void SetOrigin(const Vector3& origin);
    Vector3 GetDirection() const;
    void SetDirection(const Vector3& direction);
};
