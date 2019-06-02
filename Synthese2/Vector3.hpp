//
//  Vector3.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

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
    
    Vector3(const Vector3& vector):
    m_x{vector.m_x},
    m_y{vector.m_y},
    m_z{vector.m_z}
    {};
    
    Vector3(const double number):
    m_x{number},
    m_y{number},
    m_z{number}
    {};
    
    Vector3(const int number):
    m_x{static_cast<double>(number)},
    m_y{static_cast<double>(number)},
    m_z{static_cast<double>(number)}
    {};
        
    double GetX() const;
    double GetY() const;
    double GetZ() const;
    void SetX(const double x);
    void SetY(const double y);
    void SetZ(const double z);
//    inline void Normalize();
    Vector3 Normalize() const;
    
    //////////////////////////////
    //         Operator         //
    //////////////////////////////
    // Repris de l'ancienne version
//    Vector3 operator*=(const Vector3& other) const;
//    Vector3 operator+=(const Vector3& other) const;
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator*(const Vector3& other) const;
    Vector3 operator*(const double other) const;
    Vector3 operator-(const Vector3 &other) const;
    bool operator<(const Vector3& other) const;
    bool operator>(const Vector3& other) const;
    bool operator==(const Vector3& other) const;
    //////////////////////////////
    
    static double Dot(const Vector3& pA, const Vector3& pB);
    static double Dist2(const Vector3& pA);
    
    static Vector3 Negate(const Vector3& v);
//    inline void Negate();
    
    static Vector3 GetDirection(const Vector3& from, const Vector3& to) ;
    static double GetSum(const Vector3 vector);
    static double GetDistance(const Vector3& pointA, const Vector3& pointB);
    
    void Print() const;
    
    string ToString() const;
    
};

//void Normalize(Vector3 vector)
//{
//    Vector3 newVector = vector.Normalize();
//    vector = newVector;
//}
