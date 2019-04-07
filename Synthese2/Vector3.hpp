//
//  Vector3.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 01/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <math.h>
#include <iostream>

using std::string;

class Vector3 {
private:
    double m_x{}, m_y{}, m_z{};
//    double norme;
    
public:
    inline Vector3() {};
    
    inline Vector3(int x, int y, int z) :
    m_x{static_cast<float>(x)},
    m_y{static_cast<float>(y)},
    m_z{static_cast<float>(z)}
    {
//        norme = sqrt(Dot(*this, *this));
    }
    
    inline Vector3(double x, double y, double z) :
    m_x{static_cast<float>(x)},
    m_y{static_cast<float>(y)},
    m_z{static_cast<float>(z)}
    {
//        norme = sqrt(Dot(*this, *this));
    }
    
    inline Vector3(float x, float y, float z) :
    m_x{static_cast<float>(x)},
    m_y{static_cast<float>(y)},
    m_z{static_cast<float>(z)}
    {
//        norme = sqrt(Dot(*this, *this));
    }
    
    void Print() const;
    string ToString() const;
    
    inline double GetX() const
    {
        return m_x;
    }
    inline void SetX(const double x)
    {
        m_x = x;
    }
    
    inline double GetY() const
    {
        return m_y;
    }
    inline void SetY(const double y)
    {
        m_y = y;
    }
    
    inline double GetZ() const
    {
        return m_z;
    }
    inline void SetZ(const double z)
    {
        m_z = z;
    }
    
    inline Vector3 Normalize()
    {
        double norme = sqrt(Dot(*this, *this));
        return Vector3(m_x / norme, m_y / norme, m_z / norme);
    }
    
    inline static Vector3 GetDirection(const Vector3& from, const Vector3& to)
    {
        return (to - from).Normalize();
    }
    
    // Magnitude
    static double Dot(const Vector3& pA, const Vector3& pB);
    
    static double Dist2(const Vector3& pA);
    
    static Vector3 Negate(const Vector3& v);
    inline void Negate();
    
    inline static double GetDistance(const Vector3& pointA, const Vector3& pointB)
    {
        const Vector3 v = (pointA - pointB) * (pointA - pointB);
        const double dist = sqrt(Vector3::GetSum(v));
        
        if (dist < 0)
        {
            exit(3);
            // EXIT CODE: 3 --> Une distance ne peut être négative !
        }
        
        return dist;
    }
    
    inline static double GetSum(const Vector3 vector)
    {
        return vector.GetX() + vector.GetY() + vector.GetZ();
    }
    
    inline friend Vector3 operator*=(const Vector3& leftV, const Vector3& rightV)
    {
        return Vector3{leftV.GetX() * rightV.GetX(), leftV.GetY() * rightV.GetY(), leftV.GetZ() * rightV.GetZ()};
    }
    inline friend Vector3 operator+=(const Vector3& leftV, const Vector3& rightV)
    {
        return Vector3{leftV.GetX() + rightV.GetX(), leftV.GetY() + rightV.GetY(), leftV.GetZ() + rightV.GetZ()};
    }
    inline friend Vector3 operator+(Vector3 lhs, const Vector3& rhs)
    {
        return Vector3{lhs.GetX() + rhs.GetX(), lhs.GetY() + rhs.GetY(), lhs.GetZ() + rhs.GetZ()};
    }
    inline friend Vector3 operator*(const Vector3& leftV, const Vector3& rightV)
    {
        return Vector3{leftV.GetX() * rightV.GetX(), leftV.GetY() * rightV.GetY(), leftV.GetZ() * rightV.GetZ()};
    }
    inline friend Vector3 operator*(const Vector3& leftV, const double rightV)
    {
        return Vector3{leftV.GetX() * rightV, leftV.GetY() * rightV, leftV.GetZ() * rightV};
    }
    
    inline friend Vector3 operator-(const Vector3& leftV, const Vector3 &rightV)
    {
        return Vector3{leftV.GetX() - rightV.GetX(), leftV.GetY() - rightV.GetY(), leftV.GetZ() - rightV.GetZ()};
    }
    
    inline friend bool operator<(const Vector3& leftV, const Vector3& rightV)
    {
        return (leftV.GetX() + leftV.GetY() + leftV.GetZ()) < (rightV.GetX() + rightV.GetY() + rightV.GetZ());
    }
    
    inline friend bool operator>(const Vector3& leftV, const Vector3& rightV)
    {
        return (leftV.GetX() + leftV.GetY() + leftV.GetZ()) > (rightV.GetX() + rightV.GetY() + rightV.GetZ());
    }
    
   inline friend bool operator==(const Vector3& leftV, const Vector3& rightV)
    {
        return (leftV.GetX() == rightV.GetX() && leftV.GetY() == rightV.GetY() && leftV.GetZ() == rightV.GetZ());
    }
};
