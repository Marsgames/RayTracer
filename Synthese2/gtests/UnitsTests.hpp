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

TEST(Vector3, SimpleTests)
{
    const Vector3 v1 = Vector3(12, 128, -132);
    EXPECT_EQ(12, v1.GetX());
    EXPECT_EQ(128, v1.GetY());
    EXPECT_EQ(-132, v1.GetZ());
    
    const Vector3 v2 = v1 + Vector3(18, -100, 132);
    EXPECT_EQ(Vector3(30, 28, 0), v2);
    
    const Vector3 v3 = v2 * 2;
    EXPECT_EQ(Vector3(60, 56, 0), v3);
    
    const Vector3 v4 = Negate(v3);
    EXPECT_EQ(Vector3(-60, -56, 0), v4);
}
TEST(Vector3, NormalizeFunc)
{
    const Vector3 v1 = Vector3(-8., 8., -8.).Normalize();
    EXPECT_EQ(Vector3(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3)), v1);
    
    const Vector3 v2 = Vector3(3., -4., 0.).Normalize();
    EXPECT_EQ(Vector3(.6, -.8, .0), v2);
    EXPECT_EQ(Vector3(3 / sqrt(25), -4 / sqrt(25), 0 / sqrt(25)), v2);
    
    const Vector3 v3 = Vector3(128., -12., 31.).Normalize();
    EXPECT_EQ(Vector3(128 / sqrt(17489), -12 / sqrt(17489), 31 / sqrt(17489)), v3);
}
TEST(Vector3, DotFunc)
{
    const Vector3 v1 = Vector3(0, 0, 0);
    const Vector3 v2 = Vector3(0, 0, 0);
    EXPECT_EQ(0, Vector3::Dot(v1, v2));
    
    const Vector3 v3 = Vector3(564, 12, 12);
    const Vector3 v4 = Vector3(-53, 23, 45);
    EXPECT_EQ(-29076, Vector3::Dot(v3, v4));
    
    const Vector3 v5 = Vector3(10, 10, 10);
    const Vector3 v6 = Vector3(-31, 21, 12);
    EXPECT_EQ(20, Vector3::Dot(v5, v6));
    
    const Vector3 v7 = Vector3(18, -3, -7);
    const Vector3 v8 = Vector3(521, 86, 39);
    EXPECT_EQ(8847, Vector3::Dot(v7, v8));
    
    const Vector3 v9 = Vector3(521, 86, 39);
    const Vector3 v10 = Vector3(18, -3, -7);
    EXPECT_EQ(8847, Vector3::Dot(v9, v10));
    
    const Vector3 v11 = Vector3(-521, -86, -39);
    const Vector3 v12 = Vector3(-18, 3, 7);
    EXPECT_EQ(8847, Vector3::Dot(v11, v12));
    
    const Vector3 v13 = Vector3(7, 3, 18);
    const Vector3 v14 = Vector3(39, -86, 521);
    EXPECT_EQ(9393, Vector3::Dot(v13, v14));
    
    const Vector3 v15 = Vector3(1, 2, 3);
    const Vector3 v16 = Vector3(4, 5, 6);
    EXPECT_EQ(32, Vector3::Dot(v15, v16));
    
    const Vector3 v17 = Vector3(346, 87654, 235);
    const Vector3 v18 = Vector3(-23, -634, -643);
    EXPECT_EQ(-55731699, Vector3::Dot(v17, v18));
    
    const Vector3 v19 = Vector3(12, 12, 12);
    const Vector3 v20 = Vector3(100, 100, 100);
    EXPECT_EQ(3600, Vector3::Dot(v19, v20));
}
TEST(Vector3, Dist2Func)
{
    EXPECT_EQ(1954, Dist2(Vector3(12, 21, 37)));
    EXPECT_EQ(564601, Dist2(Vector3(741, 124, 12)));
    EXPECT_EQ(3, Dist2(Vector3(1, 1, 1)));
    EXPECT_EQ(3, Dist2(Vector3(-1, -1, -1)));
    EXPECT_EQ(10101, Dist2(Vector3(100, 10, 1)));
    EXPECT_EQ(10101, Dist2(Vector3(1, 10, 100)));
    EXPECT_EQ(845586, Dist2(Vector3(123, 456, 789)));
    EXPECT_EQ(1000674, Dist2(Vector3(-25, 7, 1000)));
    EXPECT_EQ(6002, Dist2(Vector3(-23, -73, 12)));
    EXPECT_EQ(2387, Dist2(Vector3(37, 27, 17)));
}
TEST(Vector3, Distance)
{
    EXPECT_EQ(sqrt(105), GetDistance(Vector3(7, 4, 3), Vector3(17, 6, 2)));
    EXPECT_EQ(sqrt(25437), GetDistance(Vector3(-21, 77, 21), Vector3(37, -71, 8)));
    EXPECT_EQ(sqrt(8), GetDistance(Vector3(1, 2, 3), Vector3(3, 2, 1)));
    EXPECT_EQ(sqrt(27), GetDistance(Vector3(4, 5, 6), Vector3(7, 8, 9)));
    EXPECT_EQ(sqrt(120000), GetDistance(Vector3(100, 100, 100), Vector3(-100, -100, -100)));
}

TEST(IntersectFunc, SimpleIntersect)
{
    Intersection result;
    const Vector3 a{0, 0, 0};
    Vector3 b{1, 0, 0};

    const Rayon rayon = Rayon(a, b);
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
    const Vector3 v1{0, 0, 0};
    Vector3 v2{-1, 0, 0};
    Intersect(Rayon(v1, v2), sphere, result);
    EXPECT_EQ(false, result.intersect);
    
    // Intersection tangeante
    const Vector3 v3{0, 10, 0};
    Vector3 v4{1, 0, 0};
    Intersect(Rayon(v3, v4), sphere, result);
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(20, result.distance);
    EXPECT_EQ(20, result.point.GetX());
    EXPECT_EQ(10, result.point.GetY());
    EXPECT_EQ(0, result.point.GetZ());
    
    // Intersection derrière
    const Vector3 v5{40, 0, 0};
    Vector3 v6{-1, 0, 0};
    Intersect(Rayon(v5, v6), sphere, result);
    EXPECT_EQ(true, result.intersect);
    
    // Intersection dessous
    const Vector3 v7{20, 0, 40};
    Vector3 v8{0, 0, -1};
    Intersect(Rayon(v7, v8), sphere, result);
    EXPECT_EQ(true, result.intersect);
    
    // Intersection dessus
    const Vector3 v9{20, 0, -40};
    Vector3 v10{0, 0, 1};
    Intersect(Rayon(v9, v10), sphere, result);
    EXPECT_EQ(true, result.intersect);
    
    // Intersection à droite
    const Vector3 v11{20, 40, 0};
    Vector3 v12{0, -1, 0};
    Intersect(Rayon(v11, v12), sphere, result);
    EXPECT_EQ(true, result.intersect);
    
    const Vector3 v13{500, 500, 0};
    Vector3 v14{0, 0, -1};
    const Vector3 v15{500, 500, -100};
    Intersect(Rayon(v13, v14), Sphere(v15, 10), result);
    EXPECT_EQ(true, result.intersect);
    
    const Vector3 v16{0, 0, 0};
    Vector3 v17{1, 0, 1};
    const Vector3 v18{10, 0, 0};
    Intersect(Rayon(v16, v17), Sphere(v18, 1), result);
    EXPECT_EQ(false, result.intersect);
    
    // Vérifier manuellement ce test
    //    Intersect(Rayon(Vector3(0, 0, 0), Vector3(1, 0, 1)), Sphere(Vector3(5.75, 0., 5.), 1), result);
    //    EXPECT_EQ(false, result.intersect);
}

TEST(IntersectFunc, TestsEva)
{
    Intersection result;
    const Vector3 v1{0, 0, 0};
    Vector3 v2{1, 1, 1};
    const Rayon rayon = Rayon(v1, v2);
    Sphere sphere = Sphere{Vector3(0, 0, 0), 100};
    
    Intersect(rayon, sphere, result);
    
    EXPECT_EQ(result.intersect, true);
    EXPECT_GE(result.distance, 0);
    EXPECT_EQ(result.distance, sphere.GetRayon());
    
    sphere.SetCenter(Vector3(-200, -200, -200));
    Intersect(rayon, sphere, result);
    EXPECT_EQ(result.intersect, false);
    
    sphere.SetCenter(Vector3(200, 200, 200));
    Intersect(rayon, sphere, result);
    EXPECT_EQ(result.intersect, true);
    EXPECT_GE(result.distance, 0);
}

TEST(IntersectFunc, BoxSimple)
{
    const Sphere sp = Sphere(Vector3(5, 5, 5), 5);
    const Box b = Box(sp);
    const Vector3 v1{-5., 2.5, 0.};
    Vector3 v2{1, 0, 0};

    const Rayon r = Rayon(v1, v2);
    
    const Vector3 v3{-1, 1, 0};
    Vector3 v4{.5, -.5, 0.};
    
    const Rayon r1 = Rayon(v3, v4);
    const Vector3 v5{-5., 2.5, 0.};
    Vector3 v6{-1, 0, 0};
    const Rayon r2 = Rayon(v5, v6);
    const Vector3 v7{5., 30., 5.};
    Vector3 v8{0, -1, 0};
    const Rayon r3 = Rayon(v7, v8);
    const Vector3 v9{-5., 25., 0.};
    Vector3 v10{-1, 0, 0};
    const Rayon r4 = Rayon(v9, v10);
    
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
    
    //    scene.push_back(Sphere(Vector3(21, 36, -28), 25));
    //
    //    p1 = Vector3(0, 0, 0);
    //    EXPECT_EQ(false, CanSeeLight(p1, lum, scene));
    //    p1 = Vector3(76, 54, -48);
    //    EXPECT_EQ(false, CanSeeLight(p1, lum, scene));
    //    p1 = Vector3(11, 40, -70);
    //    EXPECT_EQ(false, CanSeeLight(p1, lum, scene));
    //    p1 = Vector3(-100, 40, -27);
    //    EXPECT_EQ(false, CanSeeLight(p1, lum, scene));
}
