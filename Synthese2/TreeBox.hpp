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
    Box m_box;
    bool m_isLeaf = false;
    Sphere m_sphere;
    TreeBox* m_nodeLeft = nullptr;
    TreeBox* m_nodeRight = nullptr;
    
public:
    TreeBox() = delete;
    ~TreeBox()
    {
        delete m_nodeLeft;
        delete m_nodeRight;
    }
    
    TreeBox(const Box& box, const Sphere& sphere):
    m_box{box},
    m_sphere{sphere}
    {
        m_isLeaf = true;
    }
    
    TreeBox(TreeBox* leftBox, TreeBox* rightBox, const Box& box):
    m_box{box},
    m_sphere{Sphere(Vector3(0, 0, 0), 0)}
    {
        m_nodeLeft = leftBox;
        m_nodeRight = rightBox;

        m_isLeaf = false;
    }
    
    Box GetBox() const;
    bool GetIsLeaf() const;
    
    TreeBox* GetLeftNode() const;
    TreeBox* GetRightNode() const;

//    static map<Sphere, Box> InitDictionary(const vector<Sphere>& spheres);
    
    static TreeBox* GenerateTree(const vector<Sphere> spheres);
    
    bool IntersectBox(const Ray& ray) const;
    Intersection IntersectSphere(const Ray& ray) const;
};
