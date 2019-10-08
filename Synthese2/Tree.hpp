////
////  Tree.hpp
////  Synthese2
////
////  Created by Raphaël Daumas on 08/10/2019.
////  Copyright © 2019 Marsgames. All rights reserved.
////
//
//#pragma once
//
//#include <Box.hpp>
//#include <Ray.hpp>
//#include <Sphere.hpp>
//#include <variant>
//
////class Tree {
////public:
////    virtual Intersection Intersect(Ray ray) = 0;
////};
////
////
////class Leaf : public Tree {
////public:
////    Sphere sphere;
////
////    virtual Intersection Intersect(Ray ray) override
////    {
////        return Sphere::IntersectRaySphere(ray, sphere);
////    }
////};
////
////
////class Node : Tree{
////public:
////    Box box;
////
////    Node* nodeLeft;
////    Node* nodeRight;
////
////    virtual Intersection Intersect(Ray ray) override
////    {
////        Intersection inter = Intersection(Box::IntersectBox(ray, box), 0, Vector3(0));
////        return inter;
////    }
////};
//
//
//class Arbre {
//    std::variant<Arbre, Sphere> m_nodeLeft;
//    std::variant<Arbre, Sphere> m_nodeRight;
//    
//public:
//    Arbre()
//};
