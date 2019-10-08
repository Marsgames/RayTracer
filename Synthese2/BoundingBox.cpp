////
////  BoundingBox.cpp
////  Synthese2
////
////  Created by Raphaël Daumas on 08/10/2019.
////  Copyright © 2019 Marsgames. All rights reserved.
////
//
//#include "BoundingBox.hpp"
//#include <Box.hpp>
//#include <Ray.hpp>
//#include <Sphere.hpp>
//#include <vector>
//
//using std::vector;
//
//void BoundingBox::CreateTree(vector<Box> &boxes)
//{
//    cout << "size : " << boxes.size() << endl;
//    
//        m_pMin = boxes[0].GetPMin();
//        m_pMax = boxes[0].GetPMax();
//        if (1 == boxes.size())
//        {
//            boxL = BoundingBox(true);
//            return;
//        }
//        
//        for (const Box& b : boxes)
//        {
//            if (m_pMin.GetX() > b.GetPMin().GetX())
//            {
//                m_pMin.SetX(b.GetPMin().GetX());
//            }
//            if (m_pMin.GetY() > b.GetPMin().GetY())
//            {
//                m_pMin.SetY(b.GetPMin().GetY());
//            }
//            if (m_pMin.GetZ() > b.GetPMin().GetZ())
//            {
//                m_pMin.SetZ(b.GetPMin().GetZ());
//            }
//            
//            if (m_pMax.GetX() < b.GetPMax().GetX())
//            {
//                m_pMax.SetX(b.GetPMax().GetX());
//            }
//            if (m_pMax.GetY() < b.GetPMax().GetY())
//            {
//                m_pMax.SetY(b.GetPMax().GetY());
//            }
//            if (m_pMax.GetZ() < b.GetPMax().GetZ())
//            {
//                m_pMax.SetZ(b.GetPMax().GetZ());
//            }
//        }
//        
//        sort(boxes.begin(), boxes.end());
//        
//        m_source = BoundingBoxType;
//        
//        vector<Box> list1stPart;
//        for (unsigned long i = 0; i < boxes.size() / 2; i++)
//        {
//            list1stPart.push_back(boxes[i]);
//        }
//        
//        vector<Box> list2ndPart;
//        for (unsigned long i = static_cast<int>(boxes.size() / 2); i < boxes.size(); i++)
//        {
//            list2ndPart.push_back(boxes[i]);
//        }
//        
////        bA = BoundingBox(list1stPart[0], list1stPart[list1stPart.size() - 1], list1stPart);
//        boxL = BoundingBox(list1stPart);
//        boxL.SetSource(BoundingBoxType);
////        bB = BoundingBox(list2ndPart[0], list2ndPart[list2ndPart.size() - 1], list2ndPart);
//        boxR = BoundingBox(list2ndPart);
//        boxR.SetSource(BoundingBoxType);
//    }
//
//bool BoundingBox::IntersectBBox(const Ray &ray, Box &bBox)
//{
//    BoundingBox box = static_cast<BoundingBox&>(bBox);
//
//    if (box.isLeaf)
//    {
////        cout << bBox.GetMySphere().GetName() << endl;
//        Intersection inter = Sphere::IntersectRaySphere(ray, bBox.GetMySphere());
//        return inter.intersect;
//    }
//
//    bool iA = IntersectBBox(ray, box.boxL);
//    bool iB = IntersectBBox(ray, box.boxR);
//
//    return true == iA ? iA : iB;
//}
