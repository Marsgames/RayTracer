//
//  Vector3.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <iostream>
#include "Vector3.hpp"
#include <math.h>

using std::cout;
using std::endl;

// Repris de l'ancienne version
Vector3 Vector3::Normalize() {
    double norme = sqrt(Dot(*this, *this));
    return Vector3(m_x / norme, m_y / norme, m_z / norme);
}

double Vector3::GetX() const {
    return m_x;
}

double Vector3::GetY() const {
    return m_y;
}

double Vector3::GetZ() const {
    return m_z;
}

// Repris de l'ancienne version
double Vector3::Dot(const Vector3& pA, const Vector3& pB)
{
    return pA.GetX() * pB.GetX() + pA.GetY() * pB.GetY() + pA.GetZ() * pB.GetZ();
}

// Repris de l'ancienne version
double Vector3::Dist2(const Vector3& pA)
{
    return Vector3::Dot(pA, pA);
}
