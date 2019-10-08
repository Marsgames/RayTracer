//
//  TreeBox.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <Box.hpp>
#include <float.h>
#include <iostream>
#include <map>
#include <Ray.hpp>
#include <Sphere.hpp>
#include <TreeBox.hpp>

using std::pair;
using std::map;
using std::cout;
using std::endl;

Box TreeBox::GetBox() const {
    return m_box;
}

bool TreeBox::GetIsLeaf() const
{
    return m_isLeaf;
}

map<Sphere, Box> TreeBox::InitDictionary(const vector<Sphere> &spheres) {
    map<Sphere, Box> dictionary;
    
    // Pour chaque sphère on fait un box associée à cette sphere
    for (const Sphere& sphere : spheres)
    {
        Vector3 pMin = Vector3(sphere.GetCenter().GetX() - sphere.GetRayon(), sphere.GetCenter().GetY() - sphere.GetRayon(), sphere.GetCenter().GetZ() - sphere.GetRayon());
        Vector3 pMax = Vector3(sphere.GetCenter().GetX() + sphere.GetRayon(), sphere.GetCenter().GetY() + sphere.GetRayon(), sphere.GetCenter().GetZ() + sphere.GetRayon());
        
        const Box box = Box(pMin, pMax);
        dictionary.insert(pair<Sphere, Box>(sphere, box));
    }
    
    return dictionary;
}

TreeBox* TreeBox::GenerateTree(const vector<Sphere>& spheres) {
    map<Sphere, Box> dictionary = InitDictionary(spheres);
    
    if (1 == spheres.size())
    {
        return new TreeBox(dictionary.at(spheres[0]), spheres[0]);
    }
    
    Vector3 pMin = Vector3(DBL_MAX, DBL_MAX, DBL_MAX);
    Vector3 pMax = Vector3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
    
    //    Box box;
    for (pair<Sphere, Box> pairBS : dictionary)
    {
        Box box = pairBS.second;
        
        if (pMin.GetX() > box.GetPMin().GetX())
        {
            pMin.SetX(box.GetPMin().GetX());
        }
        if (pMin.GetY() > box.GetPMin().GetY())
        {
            pMin.SetY(box.GetPMin().GetY());
        }
        if (pMin.GetZ() > box.GetPMin().GetZ())
        {
            pMin.SetZ(box.GetPMin().GetZ());
        }
        
        if (pMax.GetX() < box.GetPMax().GetX())
        {
            pMax.SetX(box.GetPMax().GetX());
        }
        if (pMax.GetY() < box.GetPMax().GetY())
        {
            pMax.SetY(box.GetPMax().GetY());
        }
        if (pMax.GetZ() < box.GetPMax().GetZ())
        {
            pMax.SetZ(box.GetPMax().GetZ());
        }
    }
        
    vector<Sphere> list1stPart;
    for (unsigned long i = 0; i < spheres.size() / 2; i++)
    {
        list1stPart.push_back(spheres[i]);
    }
    
    vector<Sphere> list2ndPart;
    for (unsigned long i = static_cast<int>(spheres.size() / 2); i < spheres.size(); i++)
    {
        list2ndPart.push_back(spheres[i]);
    }
    
    TreeBox* leftNode = GenerateTree(list1stPart);
    TreeBox*  rightNode = GenerateTree(list2ndPart);
    
    return new TreeBox(leftNode, rightNode, Box(pMin, pMax));
}

Intersection TreeBox::IntersectSphere(const Ray& ray) const {
//    if ()
//    {
//        cout << "m_isLead is null..." << endl;
//    }
    
    if (m_isLeaf)
    {
        //        cout << "name in IntersectSpheres : " << m_sphere.GetName() << endl;
        
        return Sphere::IntersectRaySphere(ray, m_sphere);
    }
    
    Intersection interLeft = m_nodeLeft->IntersectSphere(ray);
    Intersection interRight = m_nodeRight->IntersectSphere(ray);
    
    if (interLeft.intersect && interRight.intersect)
    {
        if (m_nodeLeft->m_box.GetPMin() < m_nodeRight->m_box.GetPMin())
        {
            return interLeft;
        }
        else
        {
            return  interRight;
        }
    }
    else if (interLeft.intersect)
    {
        return interLeft;
    }
    else
    {
        return interRight;
    }
}

