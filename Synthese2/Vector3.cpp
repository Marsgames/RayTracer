//
//  Vector3.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 31/03/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//
#include <iostream>
#include <Vector3.hpp>

using std::cout;
using std::string;
using std::to_string;

void Vector3::Print() const
{
    std::cout << "vector : (" << m_x << ", " << m_y << ", " << m_z << ")" << std::endl;
}

string Vector3::ToString() const
{
    return "(" + to_string(static_cast<float>(m_x)) + ", " + to_string(static_cast<float>(m_y)) + ", " + to_string(static_cast<float>(m_z)) + ")";
}

double Vector3::Dot(const Vector3& pA, const Vector3& pB)
{
    return pA.GetX() * pB.GetX() + pA.GetY() * pB.GetY() + pA.GetZ() * pB.GetZ();
}

double Vector3::Dist2(const Vector3& pA)
{
    return Vector3::Dot(pA, pA);
}

Vector3 Vector3::Negate(const Vector3& v)
{
    return Vector3{-v.GetX(), -v.GetY(), -v.GetZ()};
}
void Vector3::Negate()
{
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
}
