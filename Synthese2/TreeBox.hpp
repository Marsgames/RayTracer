//
//  TreeBox.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Box.hpp>
//#include <iostream>
#include <map>
#include <Ray.hpp>
#include <Sphere.hpp>
//#include <variant>
#include <vector>

using std::vector;
using std::map;

class TreeBox {
private:
    
    //    std::variant<TreeBox*, Sphere> m_nodeLeft;
    //    std::variant<TreeBox*, Sphere> m_nodeRight;
    
    Box m_box;
    bool m_isLeaf = false;
    Sphere m_sphere;
    //    std::variant<TreeBox*, Sphere> m_nodeLeft;
    
    //    std::map<Box, Sphere> m_boxesSpheresDic;
    
    TreeBox GenerateTree(vector<Box> boxes) const;
    
public:
    TreeBox* m_nodeLeft = nullptr;
    TreeBox* m_nodeRight = nullptr;
    
//    TreeBox(){};
    
//    TreeBox(const vector<Box> boxes)
//    {
//        GenerateTree(boxes);
//    }
    
    TreeBox(Box box, Sphere sphere)
    {
        m_box = box;

        m_sphere = sphere;
        m_isLeaf = true;
    }
    
    TreeBox(TreeBox* leftBox, TreeBox* rightBox, const Box box)
    {
        m_nodeLeft = leftBox;
        m_nodeRight = rightBox;

        m_box = box;

        m_isLeaf = false;
    }
    
    Box GetBox() const;
    bool GetIsLeaf() const;
    
    static map<Sphere, Box> InitDictionary(const vector<Sphere>& spheres);
//    void GenerateTree(vector<Box> boxes);
    
    static TreeBox* GenerateTree(const vector<Sphere>& spheres);
    
    Intersection IntersectSphere(const Ray& ray) const;
};
