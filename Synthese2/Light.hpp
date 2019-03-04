//
//  Light.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include "Vector3.hpp"

class Light
{
private:
    Vector3 m_position;
    int m_puissance;
    
public:
    Light() {}
    
    Light(Vector3 position)
    {
        m_position = position;
    }
    
    Light(Vector3 position, int puissance)
    {
        m_position = position;
        m_puissance = puissance;
    }
    
    Vector3 GetPosition() const
    {
        return m_position;
    }
    void SetPosition(Vector3 position)
    {
        m_position = position;
    }
    
    int GetPuissance() const
    {
        return m_puissance;
    }
    void SetPuissance(int puissance)
    {
        m_puissance = puissance;
    }
};
