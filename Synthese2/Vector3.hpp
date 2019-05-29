//
//  Vector3.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

class Vector3 {
private:
    double m_x, m_y, m_z;
    
public:
    Vector3(int x, int y, int z) :
    m_x{static_cast<double>(x)},
    m_y{static_cast<double>(y)},
    m_z{static_cast<double>(z)}
    {};
    
    Vector3(double x, double y, double z) :
    m_x{x},
    m_y{y},
    m_z{z}
    {};
    
    Vector3(const Vector3& vector)
    {
        m_x = vector.m_x;
        m_y = vector.m_y;
        m_z = vector.m_z;
    }
    
    double GetX() const;
    double GetY() const;
    double GetZ() const;
//    inline void Normalize();
    Vector3 Normalize();
    
    //////////////////////////////
    //         Operator         //
    //////////////////////////////
    // Repris de l'ancienne version
    inline friend Vector3 operator-(const Vector3& leftV, const Vector3 &rightV)
    {
        return Vector3{leftV.GetX() - rightV.GetX(), leftV.GetY() - rightV.GetY(), leftV.GetZ() - rightV.GetZ()};
    }
    
    inline friend Vector3 operator+(const Vector3& leftV, const Vector3 &rightV)
    {
        return Vector3{leftV.GetX() + rightV.GetX(), leftV.GetY() + rightV.GetY(), leftV.GetZ() + rightV.GetZ()};
    }
    
    inline friend Vector3 operator*(const Vector3& leftV, const double rightV)
    {
        return Vector3{leftV.GetX() * rightV, leftV.GetY() * rightV, leftV.GetZ() * rightV};
    }
    //////////////////////////////
    
    static double Dot(const Vector3& pA, const Vector3& pB);
    static double Dist2(const Vector3& pA);
    
};

//void Normalize(Vector3 vector)
//{
//    Vector3 newVector = vector.Normalize();
//    vector = newVector;
//}
