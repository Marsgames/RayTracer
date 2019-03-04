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
#include "../Sphere.hpp"
#include "../Box.hpp"

TEST(IntersectFunc, SimpleIntersect)
{
    Intersection result;
    const Rayon rayon = Rayon(Vector3{0, 0, 0}, Vector3{1, 0, 0});
    const Sphere sphere = Sphere(Vector3{20, 0, 0}, 10);
    
    // Intersection avec un rayon partant de devant la sphère
    Intersect(rayon, sphere, result);
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(10, result.distance);
    EXPECT_EQ(10, result.point.GetX());
    EXPECT_EQ(0, result.point.GetY());
    EXPECT_EQ(0, result.point.GetZ());
    
    // Intersection si le rayon part de l'interieur de la sphère
    Intersect(rayon, Sphere{Vector3{0, 0, 0}, 10}, result);
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(10, result.distance);
    EXPECT_EQ(10, result.point.GetX());
    EXPECT_EQ(0, result.point.GetY());
    EXPECT_EQ(0, result.point.GetZ());
    
    // Pas d'intersection, le rayon est dans le mauvais sens
    Intersect(Rayon(Vector3{0, 0, 0}, Vector3{-1, 0, 0}), sphere, result);
    EXPECT_EQ(false, result.intersect);
    
    // Intersection tangeante
    Intersect(Rayon(Vector3{0, 10, 0}, Vector3{1, 0, 0}), sphere, result);
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(20, result.distance);
    EXPECT_EQ(20, result.point.GetX());
    EXPECT_EQ(10, result.point.GetY());
    EXPECT_EQ(0, result.point.GetZ());
    
    // Intersection derrière
    Intersect(Rayon(Vector3{40, 0, 0}, Vector3{-1, 0, 0}), sphere, result);
    EXPECT_EQ(true, result.intersect);
    
    // Intersection dessous
    Intersect(Rayon(Vector3{20, 0, 40}, Vector3{0, 0, -1}), sphere, result);
    EXPECT_EQ(true, result.intersect);

    // Intersection dessus
    Intersect(Rayon(Vector3{20, 0, -40}, Vector3{0, 0, 1}), sphere, result);
    EXPECT_EQ(true, result.intersect);
    
    // Intersection à droite
    Intersect(Rayon(Vector3(20, 40, 0), Vector3(0, -1, 0)), sphere, result);
    EXPECT_EQ(true, result.intersect);
    
    Intersect(Rayon(Vector3(500, 500, 0), Vector3(0, 0, -1)), Sphere(Vector3(500, 500, -100), 10), result);
    EXPECT_EQ(true, result.intersect);
}

TEST(IntersectFunc, TestsEva)
{
    Intersection result;
    const Rayon rayon = Rayon(Vector3(0, 0, 0), Vector3(1, 1, 1));
    Sphere sphere = Sphere{Vector3(0, 0, 0), 100};
    
    Intersect(rayon, sphere, result);
    
    EXPECT_EQ(result.intersect, true);
    EXPECT_GE(result.distance, 0);
    EXPECT_EQ(result.distance, sphere.GetRayon());
    
    sphere.SetOrigine(Vector3(-200, -200, -200));
    Intersect(rayon, sphere, result);
    EXPECT_EQ(result.intersect, false);
    
    sphere.SetOrigine(Vector3(200, 200, 200));
    Intersect(rayon, sphere, result);
    EXPECT_EQ(result.intersect, true);
    EXPECT_GE(result.distance, 0);
}

TEST(IntersectFunc, BoxSimple)
{
    const Sphere sp = Sphere(Vector3(5, 5, 5), 5);
    const Box b = Box(sp);
    const Rayon r = Rayon(Vector3(-5., 2.5, 0.), Vector3(1, 0, 0));
    const Rayon r1 = Rayon(Vector3(-1, 1, 0), Vector3(.5, -.5, 0.));
    const Rayon r2 = Rayon(Vector3(-5., 2.5, 0.), Vector3(-1, 0, 0));
    const Rayon r3 = Rayon(Vector3(5., 30., 5.), Vector3(0, -1, 0));
    const Rayon r4 = Rayon(Vector3(-5., 25., 0.), Vector3(-1, 0, 0));

    EXPECT_EQ(IntersectBox(r, b), true);
    EXPECT_EQ(IntersectBox(r1, b), true);
    EXPECT_EQ(IntersectBox(r2, b), true);
    EXPECT_EQ(IntersectBox(r3, b), true);
    EXPECT_EQ(IntersectBox(r4, b), false);
}

//TEST(IntersectFunc, RandomTest)
//{
//    srand(static_cast<unsigned int>(time(0)));
//    Intersection result;
//    for (int i = 0; i < 100000; i++)
//    {
//        Rayon r = Rayon(Vector3(rand(), rand(), rand()), Vector3(rand(),rand(),rand()));
//        Sphere s = Sphere{Vector3(rand(), rand(), rand()), static_cast<double>(rand())};
//        Intersect(r, s, result);
//        if (result.intersect)
//        {
//            EXPECT_GE(result.distance, 0);
//        }
//    }
//}

//TEST(IntersectFunc, TestScene)
//{
//    Scene spheres;
//    InitSpheres(spheres);
//    Intersection result;
//    const Rayon r = Rayon(Vector3(150, 500, 500), Vector3(0, 1, 1));
//
//    Intersect(r, spheres[0], result);
//    EXPECT_EQ(true, result.intersect);
//    EXPECT_EQ(75, result.distance);
//    EXPECT_EQ(150, result.point.x);
//    EXPECT_DOUBLE_EQ(553.03300858899104, result.point.y);
//    EXPECT_DOUBLE_EQ(553.03300858899104, result.point.z);
//    
////    const Rayon r1 = Rayon(Vector3(0, 500, 500), Vector3(845, 541, 398));
////    cout << "direction : (" << r1.direction.x << ", " << r1.direction.y << ", " << r1.direction.z << ")" << endl;
////    Intersect(r1, spheres[0], result);
////    EXPECT_EQ(true, result.intersect);
////    EXPECT_EQ(75, result.distance);
////    EXPECT_EQ(75, result.point.x);
////    EXPECT_EQ(575, result.point.y);
////    EXPECT_EQ(500, result.point.z);
//
////    Intersect(Rayon(Vector3{300, -200, 600}, Vector3{-1, 1, 1}), spheres[1], result);
////    EXPECT_EQ(true, result.intersect);
////    EXPECT_DOUBLE_EQ(139.67221921331486, result.distance);
////    EXPECT_DOUBLE_EQ(160.32778078668514, result.point.x);
////    EXPECT_DOUBLE_EQ(-60.327780786685139, result.point.y);
////    EXPECT_DOUBLE_EQ(739.67221921331486, result.point.z);
//
////    DebugIntersect(result);
//}

TEST(CanSeeLightFunc, SimpleTest)
{
    Scene scene;
    Sphere sp1 = Sphere{Vector3{0, 0, 0}, 10};
    Light lum = Light{Vector3{20, 0, 0}, 1000};
    scene.push_back(sp1);


    // Le rayon est intersepté par une sphère
    Vector3 point1 = Vector3{-20, 0, 0};
    EXPECT_EQ(false, CanSeeLight(point1, lum, scene));

    // le rayon n'est pas intersepté par la sphère
    Vector3 point2 = Vector3{15, 0, 0};
    EXPECT_EQ(true, CanSeeLight(point2, lum, scene));

    // Le rayon part de l'intérieur de la sphère
    Vector3 point3 = Vector3{0, 0, 0};
    EXPECT_EQ(false, CanSeeLight(point3, lum, scene));

    // La lumière est dans la sphère, le rayon non
    EXPECT_EQ(false, CanSeeLight(point1, Light{Vector3(0, 0, 0)}, scene));

    // La lumière est dans la sphère, le rayon aussi
    Vector3 point4 = Vector3(2, 0, 0);
    EXPECT_EQ(true, CanSeeLight(point4, Light{Vector3(8, 0, 0)}, scene));

    // Le point est après la lumière
    Vector3 point5 = Vector3(30, 0, 0);
    EXPECT_EQ(true, CanSeeLight(point5, lum, scene));
}

TEST(CanSeeLightFunc, ComplexeTest)
{
    Scene scene;
    Sphere sp1 = Sphere{Vector3(21, 36, -28), 20};
    Light lum = Light{Vector3(57, 13, 100)};
    scene.push_back(sp1);

    Vector3 p1 = Vector3(0, 0, 0);
    EXPECT_EQ(true, CanSeeLight(p1, lum, scene));
    p1 = Vector3(76, 54, -48);
    EXPECT_EQ(true, CanSeeLight(p1, lum, scene));
    p1 = Vector3(11, 40, -70);
    EXPECT_EQ(false, CanSeeLight(p1, lum, scene));
    p1 = Vector3(-100, 40, -27);
    EXPECT_EQ(true, CanSeeLight(p1, lum, scene));
}
