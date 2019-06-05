//
//  Ray.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <Ray.hpp>
//#include <Sphere.hpp>
#include <Vector3.hpp>

void Ray::SetOrigin(const Vector3& origin) {
    m_origin = origin;
}

Vector3 Ray::GetOrigin() const {
    return m_origin;
}

Vector3 Ray::GetDirection() const {
    return m_direction;
}

void Ray::SetDirection(const Vector3& direction) {
    m_direction = direction;
}

Ray Ray::GetReflectDirection(const Ray& ray, const Intersection& intersection, const Sphere& sphere) {
    const Vector3 normal = sphere.GetNormal(intersection.pointCoordonate);
//    const Vector3 dotProduct = Vector3::Dot(ray.GetDirection(), normal);
////    float reflet = (ray.GetDirection() * normal) * 2;
//
//    const Vector3 newDirection = Vector3(ray.GetDirection() - (dotProduct * normal * 2));
//
//    return Ray(intersection.pointCoordonate, newDirection);

    
    const Vector3 newDirection = ray.GetDirection() - (ray.GetDirection() * normal) * 2 * normal;
    return Ray(intersection.pointCoordonate, newDirection);
}




