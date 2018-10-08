//
//  Vector3.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 01/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

class Vector3 {
    //const Vector3 One = Vector3(1, 1, 1);
    
public:
    double x, y, z;
    
//    Vector3(double xx, double yy, double zz){
//        x = xx;
//        y = yy;
//        z = zz;
//    }
//    Vector3(double val)
//    {
//        x = val;
//        y = val;
//        z = val;
//    }
    
    void operator*(Vector3 r)
    {
        x *= r.x;
        y *= r.y;
        z *= r.z;
        
    }
};

Vector3 operator*=(const Vector3 leftV, const Vector3 rightV)
{
    return Vector3{leftV.x * rightV.x, leftV.y * rightV.y, leftV.z * rightV.z};
}

Vector3 operator+(const Vector3 leftV, const Vector3 rightV)
{
    return Vector3{leftV.x + rightV.x, leftV.y + rightV.y, leftV.z + rightV.z};
}

Vector3 operator*(const Vector3 leftV, const Vector3 rightV)
{
    return Vector3{leftV.x * rightV.x, leftV.y * rightV.y, leftV.z * rightV.z};
}
Vector3 operator*(const Vector3 leftV, const double rightV)
{
    return Vector3{leftV.x * rightV, leftV.y * rightV, leftV.z * rightV};
}

Vector3 operator-(const Vector3 leftV, const Vector3 rightV)
{
    return Vector3{leftV.x - rightV.x, leftV.y - rightV.y, leftV.z - rightV.z};
}

double Dot(const Vector3& pA, const Vector3& pB)
{
    return pA.x * pB.x + pA.y * pB.y + pA.z * pB.z;
}

double Dist2(const Vector3& pA)
{
    return Dot(pA, pA);
}

//Vector3 Minus(const Vector3& A, const Vector3& B)
//{
//    return Vector3{A.x - B.x, A.y - B.y, A.z - B.z};
//}
//
//Vector3 Add(const Vector3& vA, const Vector3& vB)
//{
//    return Vector3{vA.x + vB.x, vA.y + vB.y, vA.z + vB.z};
//}
//
//Vector3 Multiply(const Vector3& vA, const Vector3& vB)
//{
//    return Vector3{vA.x * vB.x, vA.y * vB.y, vA.z * vB.z};
//}

Vector3 Negate(const Vector3& v)
{
    return Vector3{v.x * -1, v.y * -1, v.z * -1};
}

Vector3 Normalize(const Vector3& v){
    double max = v.x;
    if (v.y > max)
    {
        max = v.y;
    }
    if (v.z > max)
    {
        max = v.z;
    }
    
//    if(0 != max){
        return Vector3{v.x / max, v.y / max, v.z / max};
//    }
//    return;
}

