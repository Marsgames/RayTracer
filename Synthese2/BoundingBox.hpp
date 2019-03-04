//
//  BoundingBox.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 19/11/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <vector>
#include "Box.hpp"

class BoundingBox : public Box
{
public:
    Box bA;
    Box bB;
    bool isLeave = false;
    
    BoundingBox(){}
    
    BoundingBox(const Box& leave)
    {
        isLeave = true;
    }
    
    BoundingBox(vector<Box>& boxes)
    {
       CreateTree(boxes);
    }
    
    BoundingBox(const Box& firstBox, const Box& secondBox)
    {
        bA = firstBox;
        bB = secondBox;
    }
    
    void CreateTree(vector<Box>& boxes)
    {
        m_pMin = boxes[0].GetPMin();
        m_pMax = boxes[0].GetPMax();
        if (1 == boxes.size())
        {
            bA = BoundingBox(boxes[0]);
            return;
        }
        
        for (const Box& b : boxes)
        {
            if (m_pMin.GetX() > b.GetPMin().GetX())
            {
                m_pMin.SetX(b.GetPMin().GetX());
            }
            if (m_pMin.GetY() > b.GetPMin().GetY())
            {
                m_pMin.SetY(b.GetPMin().GetY());
            }
            if (m_pMin.GetZ() > b.GetPMin().GetZ())
            {
                m_pMin.SetZ(b.GetPMin().GetZ());
            }
            
            if (m_pMax.GetX() < b.GetPMax().GetX())
            {
                m_pMax.SetX(b.GetPMax().GetX());
            }
            if (m_pMax.GetY() < b.GetPMax().GetY())
            {
                m_pMax.SetY(b.GetPMax().GetY());
            }
            if (m_pMax.GetZ() < b.GetPMax().GetZ())
            {
                m_pMax.SetZ(b.GetPMax().GetZ());
            }
        }
        
        sort(boxes.begin(), boxes.end());
        
        m_source = boundingBoxType;
        
        vector<Box> list1stPart;
        for (int i = 0; i < boxes.size() / 2; i++)
        {
            list1stPart.push_back(boxes[i]);
        }
        
        vector<Box> list2ndPart;
        for (int i = boxes.size() / 2; i < boxes.size(); i++)
        {
            list2ndPart.push_back(boxes[i]);
        }
        
//        bA = BoundingBox(list1stPart[0], list1stPart[list1stPart.size() - 1], list1stPart);
        bA = BoundingBox(list1stPart);
        bA.SetSource(boundingBoxType);
//        bB = BoundingBox(list2ndPart[0], list2ndPart[list2ndPart.size() - 1], list2ndPart);
        bB = BoundingBox(list2ndPart);
        bB.SetSource(boundingBoxType);
    };
};

bool IntersectBBox(const Rayon& ray, const BoundingBox& bBox)
{
    if (bBox.isLeave)
    {
        cout << bBox.GetMySphere().GetName() << endl;
        Intersection inter;
        Intersect(ray, bBox.GetMySphere(), inter);
        return inter.intersect;
    }
    
    bool iA = IntersectBBox(ray, bBox.bA);
    bool iB = IntersectBBox(ray, bBox.bB);
    
    return true == iA ? iA : iB;
}

//BoundingBox CreateTree(vector<Box> boxes)
//{
//
//}
