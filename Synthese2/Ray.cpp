//
//  Ray.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include "Ray.hpp"
#include <Vector3.hpp>

void Ray::SetOrigin(const Vector3& origin) {
    m_origin = origin;
}

Vector3 Ray::GetOrigin() const {
    return m_origin;
}

Vector3 Ray::GetDirection() const {
    return m_direction;
}

void Ray::SetDirection(const Vector3& direction) {
    m_direction = direction;
}



