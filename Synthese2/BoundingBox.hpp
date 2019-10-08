//
//  BoundingBox.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Box.hpp>
#include <Ray.hpp>
#include <vector>

class BoundingBox : public Box {
    
    
public:
    Box boxL, boxR;
    bool isLeaf = false;
    
    BoundingBox(){};
    
    BoundingBox(bool isALeaf)
    {
        isLeaf = isALeaf;
    }
    
    BoundingBox(std::vector<Box>& boxes)
    {
       CreateTree(boxes);
    }
    
    BoundingBox(const Box& firstBox, const Box& secondBox)
    {
        boxL = firstBox;
        boxR = secondBox;
    }
    
    void CreateTree(std::vector<Box>& boxes);
    
    static bool IntersectBBox(const Ray& ray, Box& bBox);
};
