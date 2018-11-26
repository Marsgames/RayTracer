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
    
    BoundingBox(){};
    BoundingBox(const Box& leave)
    {
        isLeave = true;
    };
    BoundingBox(vector<Box>& boxes)
    {
       CreateTree(boxes);
    };
    BoundingBox(const Box& firstBox, const Box& secondBox)
    {
        bA = firstBox;
        bB = secondBox;
    };
    
    void CreateTree(vector<Box>& boxes)
    {
        pMin = boxes[0].pMin;
        pMax = boxes[0].pMax;
        cout << boxes.size() << endl;
        if (1 == boxes.size())
        {
            bA = BoundingBox(boxes[0]);
            cout << "on a une feuille" << endl;
            return;
        }
        
        for (const Box& b : boxes)
        {
            if (pMin.x > b.pMin.x)
            {
                pMin.x = b.pMin.x;
            }
            if (pMin.y > b.pMin.y)
            {
                pMin.y = b.pMin.y;
            }
            if (pMin.z > b.pMin.z)
            {
                pMin.z = b.pMin.z;
            }
            
            if (pMax.x < b.pMax.x)
            {
                pMax.x = b.pMax.x;
            }
            if (pMax.y < b.pMax.y)
            {
                pMax.y = b.pMax.y;
            }
            if (pMax.z < b.pMax.z)
            {
                pMax.z = b.pMax.z;
            }
        }
        
        sort(boxes.begin(), boxes.end());
        
        source = boundingBoxType;
        
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
        bA.source = boundingBoxType;
//        bB = BoundingBox(list2ndPart[0], list2ndPart[list2ndPart.size() - 1], list2ndPart);
        bB = BoundingBox(list2ndPart);
        bB.source = boundingBoxType;
        cout << "subdivision !" << endl;
    };
};

//BoundingBox CreateTree(vector<Box> boxes)
//{
//
//}
