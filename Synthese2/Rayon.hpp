//
//  Rayon.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <Vector3.hpp>

class Rayon
{
private:
    Vector3 m_origine, m_direction;
public:
    Rayon(Vector3 origine, Vector3 direction)
    {
        m_origine = origine;
//        m_direction = Normalize(direction);
        m_direction = direction.Normalize();
    };
    
    Vector3 GetOrigine() const
    {
        return m_origine;
    }
    
    Vector3 GetDirection() const
    {
        return m_direction;
    }
};
