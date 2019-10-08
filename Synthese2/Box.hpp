//
//  Box.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Ray.hpp>
#include <Sphere.hpp>
#include <vector>
#include <Vector3.hpp>

enum EBoxType
{
    SphereType, BoundingBoxType, SuperBBoxType
};

class Box {
protected:
    Vector3 m_pMin, m_pMax;
    EBoxType m_source; // Je ne sais plus à quoi ça sert
    Sphere m_mySphere; // Je ne sais plus non plus à quoi ça sert
    
public:
    Box(){};
    
    Box(const Sphere& sphere)
    {
        m_pMin = Vector3(sphere.GetCenter().GetX() - sphere.GetRayon(), sphere.GetCenter().GetY() - sphere.GetRayon(), sphere.GetCenter().GetZ() - sphere.GetRayon());
        m_pMax = Vector3(sphere.GetCenter().GetX() + sphere.GetRayon(), sphere.GetCenter().GetY() + sphere.GetRayon(), sphere.GetCenter().GetZ() + sphere.GetRayon());
        m_source = SphereType;
        m_mySphere = sphere;
    };
    
    Box(const Box& box1, const Box& box2)
    {
        m_pMin = box1.m_pMin < box2.m_pMin ? box1.m_pMin : box2.m_pMin;
        m_pMax = box1.m_pMax > box2.m_pMax ? box1.m_pMax : box2.m_pMax;
        m_source = BoundingBoxType;
    };
    
    Vector3 GetPMin() const;
    void SetPMin(Vector3 pMin);
    Vector3 GetPMax() const;
    void SetPMax(Vector3 pMax);
    EBoxType GetSource() const;
    void SetSource(EBoxType source);
    Sphere GetMySphere() const;
    void SetMySphere(Sphere mySphere);
    
    bool operator<(const Box& other) const;
    
    
    static bool IntersectBox(const Ray& ray, const Box& box);
    static void CreateSpheresBoxes(std::vector<Box>& boxesScene, const std::vector<Sphere>& scene);
    
    
};
