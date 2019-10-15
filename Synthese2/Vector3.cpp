//
//  Vector3.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <string>
#include "Vector3.hpp"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

// Repris de l'ancienne version
Vector3 Vector3::Normalize() const
{
    const double norme = sqrt(Dot(*this, *this));
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

void Vector3::SetX(const double x) {
    m_x = x;
}

void Vector3::SetY(const double y) {
    m_y = y;
}

void Vector3::SetZ(const double z) {
    m_z = z;
}

// Repris de l'ancienne version
double Vector3::Dot(const Vector3& pA, const Vector3& pB)
{
    return pA.m_x * pB.m_x + pA.m_y * pB.m_y + pA.m_z * pB.m_z;
}

// Repris de l'ancienne version
double Vector3::Dist2(const Vector3& pA)
{
    return Vector3::Dot(pA, pA);
}

Vector3 Vector3::Negate(const Vector3& v)
{
    return Vector3{-v.m_x, -v.m_y, -v.m_z};
}
//void Vector3::Negate()
//{
//    m_x = -m_x;
//    m_y = -m_y;
//    m_z = -m_z;
//}

Vector3 Vector3::GetDirection(const Vector3 &from, const Vector3 &to)
{
    return (to - from).Normalize();
}

double Vector3::GetDistance(const Vector3 &pointA, const Vector3 &pointB) {
    // @TODO: vérifier ce qui est le plus optimisé entre cette version et l'ancienne version :
    //            return sqrt(((pointA.GetX() - pointB.GetX()) * (pointA.GetX() - pointB.GetX())) + ((pointA.GetY() - pointB.GetY()) * (pointA.GetY() - pointB.GetY())) + ((pointA.GetZ() - pointB.GetZ()) * (pointA.GetZ() - pointB.GetZ())));


    const Vector3 v = (pointA - pointB) * (pointA - pointB);
    const double dist = sqrt(Vector3::GetSum(v));
    
//    const double oldDist = sqrt(((pointA.GetX() - pointB.GetX()) * (pointA.GetX() - pointB.GetX())) + ((pointA.GetY() - pointB.GetY()) * (pointA.GetY() - pointB.GetY())) + ((pointA.GetZ() - pointB.GetZ()) * (pointA.GetZ() - pointB.GetZ())));
    
//    cout << "dist nouvelle methode : " << dist << endl;
//    cout << "dist ancienne methode : " << oldDist << endl << endl;

    if (dist < 0)
    {
        exit(3);
        // EXIT CODE: 3 --> Une distance ne peut être négative !
    }

    return dist;
}

double Vector3::GetSum(const Vector3& vector)
{
    return vector.m_x + vector.m_y + vector.m_z;
}

void Vector3::Print() const
{
    cout << "Vector3(" << m_x << ", " << m_y << ", " << m_z << ")" << endl;
}

string Vector3::ToString() const
{
    return "Vector3(" + to_string(m_x) + ", " + to_string(m_y) + ", " + to_string(m_z) + ")";
}

//////////////////////////////
//         Operator         //
//////////////////////////////
// Repris de l'ancienne version
//Vector3 Vector3::operator*=(const Vector3 &other) const
//{
//    return Vector3{m_x * other.m_x, m_y * other.m_y, m_z * other.m_z};
//}
//Vector3 Vector3::operator+=(const Vector3 &other) const
//{
//    return Vector3{m_x + other.m_x, m_y + other.m_y, m_z + other.m_z};
//}
Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3{m_x + other.m_x, m_y + other.m_y, m_z + other.m_z};;
}
Vector3 Vector3::operator*(const Vector3& other) const
{
    return Vector3{m_x * other.m_x, m_y * other.m_y, m_z * other.m_z};
}
Vector3 Vector3::operator*(const double other) const
{
    return Vector3{m_x * other, m_y * other, m_z * other};
}
Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3{m_x - other.m_x, m_y - other.m_y, m_z - other.m_z};
}
bool Vector3::operator<(const Vector3& other) const
{
    return (m_x + m_y + m_z) < (other.m_x + other.m_y + other.m_z);
}
bool Vector3::operator>(const Vector3& other) const
{
    return (m_x + m_y + m_z) > (other.m_x + other.m_y + other.m_z);
}
bool Vector3::operator==(const Vector3& other) const
{
    return (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z);
}

Vector3 Vector3::CrossProduct(const Vector3 &vA, const Vector3 &vB) {
        double x = vA.m_y * vB.m_z - vA.m_z * vB.m_y ;
        double y = vA.m_z * vB.m_x - vA.m_x * vB.m_z ;
        double z = vA.m_x * vB.m_y - vA.m_y * vB.m_x ;

    return Vector3(x, y, z);
}
