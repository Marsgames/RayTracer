//
//  Vector3.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 01/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <math.h>

class Vector3 {
public:
    double x, y, z;
    
    Vector3(){};
    Vector3(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    };
    Vector3(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    };
};

double Dot(const Vector3& pA, const Vector3& pB)
{
    return pA.x * pB.x + pA.y * pB.y + pA.z * pB.z;
}

double Dist2(const Vector3& pA)
{
    return Dot(pA, pA);
}

Vector3 Normalize(const Vector3& v){
    double norme = sqrt(Dot(v, v));
    
    return Vector3(v.x / norme, v.y / norme, v.z / norme);
}

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

Vector3 Negate(const Vector3& v)
{
    return Vector3{v.x * -1, v.y * -1, v.z * -1};
}



void Print(const Vector3& v)
{
    std::cout << "vector : (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}
