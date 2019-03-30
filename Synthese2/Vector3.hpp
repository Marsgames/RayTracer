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

using std::to_string;

class Vector3 {
    
//    double Dot(const Vector3& pA, const Vector3& pB);
    
private:
    double m_x{}, m_y{}, m_z{};
    double norme;
public:
    Vector3() {};
//    Vector3(double x, double y, double z)
//    {
//        m_x = x;
//        m_y = y;
//        m_z = z;
//    };
//
//    Vector3(int x, int y, int z)
//    {
//        m_x = x;
//        m_y = y;
//        m_z = z;
//    };
//
//    Vector3(int x, int y) :
//    m_x{static_cast<double>(x)},
//    m_y{static_cast<double>(y)},
//    m_z{}
//    {}
    
    Vector3(int x, int y, int z)
    {
        m_x = static_cast<float>(x);
        m_y = static_cast<float>(y);
        m_z = static_cast<float>(z);
        norme = sqrt(Dot(*this, *this));
    }
    
    Vector3(double x, double y, double z)
    {
        m_x = static_cast<float>(x);
        m_y = static_cast<float>(y);
        m_z = static_cast<float>(z);
        norme = sqrt(Dot(*this, *this));
    }
    
    Vector3(float x, float y, float z)
    {
        m_x = static_cast<float>(x);
        m_y = static_cast<float>(y);
        m_z = static_cast<float>(z);
        norme = sqrt(Dot(*this, *this));
    }
    
    void Print() const
    {
        std::cout << "vector : (" << m_x << ", " << m_y << ", " << m_z << ")" << std::endl;
    };
    
    std::string ToString() const
    {
        return "(" + to_string(float(m_x)) + ", " + to_string(float(m_y)) + ", " + to_string(float(m_z)) + ")";
    }
    
    double GetX() const
    {
        return m_x;
    }
    inline void SetX(const double x)
    {
        m_x = x;
        norme = sqrt(Dot(*this, *this));
    }
    
    double GetY() const
    {
        return m_y;
    }
    void SetY(const double y)
    {
        m_y = y;
        norme = sqrt(Dot(*this, *this));
    }
    
    double GetZ() const
    {
        return m_z;
    }
    void SetZ(const double z)
    {
        m_z = z;
        norme = sqrt(Dot(*this, *this));
    }
    
    Vector3 Normalize()
    {
        return Vector3(m_x / norme, m_y / norme, m_z / norme);
    }
    
    // Magnitude
    static double Dot(const Vector3& pA, const Vector3& pB)
    {
        return pA.GetX() * pB.GetX() + pA.GetY() * pB.GetY() + pA.GetZ() * pB.GetZ();
    }
};

double Dist2(const Vector3& pA)
{
    return Vector3::Dot(pA, pA);
}

//Vector3 Normalize(const Vector3& v){
//    double norme = sqrt(Dot(v, v));
//    
//    return Vector3(v.GetX() / norme, v.GetY() / norme, v.GetZ() / norme);
//}

Vector3 operator*=(const Vector3& leftV, const Vector3& rightV)
{
    return Vector3{leftV.GetX() * rightV.GetX(), leftV.GetY() * rightV.GetY(), leftV.GetZ() * rightV.GetZ()};
}

Vector3 operator+=(const Vector3& leftV, const Vector3& rightV)
{
    return Vector3{leftV.GetX() + rightV.GetX(), leftV.GetY() + rightV.GetY(), leftV.GetZ() + rightV.GetZ()};
}

Vector3 operator+(const Vector3& leftV, const Vector3& rightV)
{
    return Vector3{leftV.GetX() + rightV.GetX(), leftV.GetY() + rightV.GetY(), leftV.GetZ() + rightV.GetZ()};
}

Vector3 operator*(const Vector3& leftV, const Vector3& rightV)
{
    return Vector3{leftV.GetX() * rightV.GetX(), leftV.GetY() * rightV.GetY(), leftV.GetZ() * rightV.GetZ()};
}
Vector3 operator*(const Vector3& leftV, const double rightV)
{
    return Vector3{leftV.GetX() * rightV, leftV.GetY() * rightV, leftV.GetZ() * rightV};
}

Vector3 operator-(const Vector3& leftV, const Vector3 &rightV)
{
    return Vector3{leftV.GetX() - rightV.GetX(), leftV.GetY() - rightV.GetY(), leftV.GetZ() - rightV.GetZ()};
}

bool operator<(const Vector3& leftV, const Vector3& rightV)
{
    return (leftV.GetX() + leftV.GetY() + leftV.GetZ()) < (rightV.GetX() + rightV.GetY() + rightV.GetZ());
}

bool operator>(const Vector3& leftV, const Vector3& rightV)
{
    return (leftV.GetX() + leftV.GetY() + leftV.GetZ()) > (rightV.GetX() + rightV.GetY() + rightV.GetZ());
}

bool operator==(const Vector3& leftV, const Vector3& rightV)
{
    return (leftV.GetX() == rightV.GetX() && leftV.GetY() == rightV.GetY() && leftV.GetZ() == rightV.GetZ());
}

Vector3 Negate(const Vector3& v)
{
    return Vector3{-v.GetX(), -v.GetY(), -v.GetZ()};
}

double GetDistance(const Vector3& pointA, const Vector3& pointB)
{
    return sqrt(((pointA.GetX() - pointB.GetX()) * (pointA.GetX() - pointB.GetX())) + ((pointA.GetY() - pointB.GetY()) * (pointA.GetY() - pointB.GetY())) + ((pointA.GetZ() - pointB.GetZ()) * (pointA.GetZ() - pointB.GetZ())));
}

void Print(const Vector3& v)
{
    std::cout << "vector : (" << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << ")" << std::endl;
}
