//
//  UnitsTests.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 11/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <gtest/gtest.h>
#include "../main.hpp"
#include "../Rayon.hpp"

TEST(IntersectFunc, SimpleIntersect)
{
    Intersection result;
    const Rayon rayon = Rayon(Vector3{0, 0, 0}, Vector3{1, 0, 0});
    const Sphere sphere = Sphere{Vector3{20, 0, 0}, 10};
    Intersect(rayon, sphere, result);
    
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(10, result.distance);
    EXPECT_EQ(10, result.point.x);
    EXPECT_EQ(0, result.point.y);
    EXPECT_EQ(0, result.point.z);
}

TEST(IntersectFunc, TestScene)
{
    Scene spheres;
    InitSpheres(spheres);
    Intersection result;
    
    Intersect(Rayon(Vector3{0, 500, 500}, Vector3{1, 1, 0}), spheres[0], result);
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(75, result.distance);
    EXPECT_EQ(75, result.point.x);
    EXPECT_EQ(575, result.point.y);
    EXPECT_EQ(500, result.point.z);
    
    Intersect(Rayon(Vector3{300, -200, 600}, Vector3{-1, 1, 1}), spheres[1], result);
    EXPECT_EQ(true, result.intersect);
    EXPECT_GT(140, result.distance);
    EXPECT_GT(161, result.point.x);
    EXPECT_GT(-59, result.point.y);
    EXPECT_GT(740, result.point.z);
    EXPECT_LT(139, result.distance);
    EXPECT_LT(159, result.point.x);
    EXPECT_LT(-61, result.point.y);
    EXPECT_LT(739, result.point.z);
//    cout << "intersect : " << result.intersect << endl;
//    cout << "distance : " << result.distance << endl;
//    cout << "x : " << result.point.x << endl;
//    cout << "y : " << result.point.y << endl;
//    cout << "z : " << result.point.z << endl;
}

TEST(CanSeeLightFunc, RandomTest)
{
    Scene scene;
    Sphere sp1 = Sphere{Vector3{0, 0, 0}, 10};
    scene.push_back(sp1);
    Light lum = Light{Vector3{20, 0, 0}, 1000};
    Vector3 point1 = Vector3{-20, 0, 0};
    Vector3 point2 = Vector3{15, 0, 0};
    
    // Les returns de la fonction CanSeeLight() sont inversés
    EXPECT_EQ(false, CanSeeLight(point1, lum, scene));
    EXPECT_EQ(true, CanSeeLight(point2, lum, scene));
    
}
