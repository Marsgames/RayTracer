//
//  UnitsTests.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 11/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <Camera.hpp>
#include <Color.hpp>
#include <gtest/gtest.h>
#include <Light.hpp>
#include <Material.hpp>
#include <math.h>
#include <Ray.hpp>
#include <Sphere.hpp>
#include <ToolBox.hpp>
#include <Vector3.hpp>

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
    
    const Vector3 v4 = Vector3::Negate(v3);
    EXPECT_EQ(Vector3(-60, -56, 0), v4);
}
TEST(Vector3, Operator)
{
    const Vector3 v0 = Vector3{0, 0, 0};
    const Vector3 v1 = Vector3{1, 1, 1};
    const Vector3 v2 = Vector3{2, 2, 2};
    const Vector3 v5 = Vector3{5, 5, 5};
    
    const Vector3 res1p0 = v1 + v0;
    const Vector3 res2x5 = v2 * v5;
    const Vector3 res5m2 = v5 - v2;
    const Vector3 res10d2 = res2x5 * 2;
    
    EXPECT_EQ(Vector3(1, 1, 1), res1p0);
    EXPECT_EQ(Vector3(10, 10, 10), res2x5);
    EXPECT_EQ(Vector3(3, 3, 3), res5m2);
    EXPECT_EQ(Vector3(20, 20, 20), res10d2);
    
    EXPECT_TRUE(v1 == Vector3(1, 1, 1));
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v5 > v0);
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
    EXPECT_EQ(1954, Vector3::Dist2(Vector3(12, 21, 37)));
    EXPECT_EQ(564601, Vector3::Dist2(Vector3(741, 124, 12)));
    EXPECT_EQ(3, Vector3::Dist2(Vector3(1, 1, 1)));
    EXPECT_EQ(3, Vector3::Dist2(Vector3(-1, -1, -1)));
    EXPECT_EQ(10101, Vector3::Dist2(Vector3(100, 10, 1)));
    EXPECT_EQ(10101, Vector3::Dist2(Vector3(1, 10, 100)));
    EXPECT_EQ(845586, Vector3::Dist2(Vector3(123, 456, 789)));
    EXPECT_EQ(1000674, Vector3::Dist2(Vector3(-25, 7, 1000)));
    EXPECT_EQ(6002, Vector3::Dist2(Vector3(-23, -73, 12)));
    EXPECT_EQ(2387, Vector3::Dist2(Vector3(37, 27, 17)));
}
TEST(Vector3, Distance)
{
    EXPECT_EQ(sqrt(105), Vector3::GetDistance(Vector3(7, 4, 3), Vector3(17, 6, 2)));
    EXPECT_EQ(sqrt(25437), Vector3::GetDistance(Vector3(-21, 77, 21), Vector3(37, -71, 8)));
    EXPECT_EQ(sqrt(8), Vector3::GetDistance(Vector3(1, 2, 3), Vector3(3, 2, 1)));
    EXPECT_EQ(sqrt(27), Vector3::GetDistance(Vector3(4, 5, 6), Vector3(7, 8, 9)));
    EXPECT_EQ(sqrt(120000), Vector3::GetDistance(Vector3(100, 100, 100), Vector3(-100, -100, -100)));
}
TEST(Vector3, Direction)
{
    const Vector3 pA = Vector3{0, 0, 0};
    const Vector3 pB = Vector3{10, 10, 10};
    
    EXPECT_EQ(Vector3(-10).Normalize(), Vector3::GetDirection(pB, pA));
    EXPECT_EQ(Vector3(10).Normalize(), Vector3::GetDirection(pA, pB));
}

TEST(Light, SimpleTest)
{
    const Light light = Light(Vector3(10, 10, 10), 1000);
//    const Color black = Color(0, 0, 0);
    
    EXPECT_EQ(Vector3(10, 10, 10), light.GetPosition());
    EXPECT_EQ(1000, light.GetPower());
    
//    EXPECT_TRUE(Color::GetColor(EColor::Black) == Light::GetLightning(light, black, 1000000000, Vector3(-10, -10, -10)));
}

TEST(Color, SimpleTest)
{
    const Color noir = Color(0, 0, 0);
    const Color blanc = Color(255, 255, 255);
    Color autre = Color(90, 90, 90);
    autre += Color(10, 10, 10);
    const Color autre2 = autre / 10;
    
    EXPECT_EQ(Color::GetColor(EColor::Black), noir);
    EXPECT_EQ(Color::GetColor(EColor::White), blanc);
    EXPECT_EQ(Color(0, 0, 0), blanc * 0);
    EXPECT_EQ(Color(100, 100, 100), autre);
    EXPECT_EQ(Color(10, 10, 10), autre2);
}

TEST(Ray, SimpleTest)
{
    Ray rayon = Ray(Vector3(0, 0, 0), Vector3(0, 0, 100));
    
    EXPECT_EQ(Vector3(0, 0, 1), rayon.GetDirection());
    
    rayon.SetOrigin(Vector3(10, 1, 2));
    rayon.SetDirection(Vector3(0, 0, -1));
    
    EXPECT_EQ(Vector3(10, 1, 2), rayon.GetOrigin());
    EXPECT_EQ(Vector3(0, 0, -1), rayon.GetDirection());
}
TEST(Ray, Reflexion)
{
    const Ray ray1 = Ray(Vector3(-10, -10, 0), Vector3(10, 10, 0));
    const Intersection intersect = Intersection(true, Vector3::GetDistance(ray1.GetOrigin(), Vector3(0, 0, 0)), Vector3(0, 0, 0));
    const Ray ray2 = Ray::GetReflectDirection(ray1, intersect, Sphere(Vector3(0, 10, 0), 10, Material(Color(0, 0, 0))));
    
    const Vector3 res = Vector3(10, 10, 0).Normalize();
    
    EXPECT_EQ(res.ToString(), ray2.GetDirection().ToString());
}

TEST(Sphere, SimpleTest)
{
    Sphere sphere = Sphere(Vector3(10, 0, 0), 10, Material(Color(255, 0, 0)));
    sphere.SetCenter(0, 0, 0);
    
    EXPECT_EQ(Vector3(0, 0, 0), sphere.GetCenter());
    EXPECT_EQ(Color::GetColor(EColor::Red), sphere.GetMaterial().GetDiffuseColor());
    EXPECT_EQ(10, sphere.GetRayon());
}

TEST(Pixel, SimpleTest)
{
    const Pixel deadPixel = Pixel(Vector3(0, 0, 0), Color(0, 0, 0), 0);
    
    EXPECT_EQ(Vector3(0, 0, 0), deadPixel.GetPosition());
    EXPECT_EQ(Color(0, 0, 0), deadPixel.GetColor());
}

TEST(Camera, SimpleTest)
{
    const Vector3 camPos = Vector3(0, 0, 0);
    const Vector3 camDir = Vector3(0, 0, 100);
    Camera cam = Camera(camPos, 1920, 1080, camDir, 800);
    
    EXPECT_EQ(1920, cam.GetWidth());
    EXPECT_EQ(1080, cam.GetHeight());
    EXPECT_EQ(800, cam.GetFocalDist());
    EXPECT_EQ(Vector3(0, 0, 1), cam.GetDirection());
    EXPECT_EQ(Vector3(0, 0, 0), cam.GetPosition());
    EXPECT_EQ(true, cam.GetUseFocal());
    
    cam.SetFocalDist(1000);
    cam.SetDirection(Vector3(0, 0, -1));
    cam.SetPosition(Vector3(0, 0, 10));
    cam.SetUseFocal(false);
    
    EXPECT_EQ(1000, cam.GetFocalDist());
    EXPECT_EQ(Vector3(0, 0, -1), cam.GetDirection());
    EXPECT_EQ(Vector3(0, 0, 10), cam.GetPosition());
    EXPECT_EQ(false, cam.GetUseFocal());
}
//
//TEST(Camera, Rotation)
//{
//    srand(0);
//
//    // Ecran regarde en face
//    Vector3 camDir = Vector3{0, 0, 1};
//    Camera cam = Camera(Vector3(0, 0, 0), 100, 100, camDir, 0);
//    double dot = DBL_MAX;
//    bool result = false;
//    int randNum = 0;
//
//    int pixelsToTest = (cam.GetHeight() * cam.GetWidth()) * .1;
//    const int min = 0;
//    int max = (cam.GetHeight() * cam.GetWidth());
//    for (int i = 0; i < pixelsToTest; i++)
//    {
//        randNum = rand()%(max-min + 1) + min;
//
//        Vector3 point = cam.GetImage()[randNum].GetPosition() - cam.GetPosition();
//        dot = Vector3::Dot(camDir, point);
//
//        if (cam.GetPosition() == Vector3::Negate(point))
//        {
//            continue;
//        }
//
//        result = (0 == dot || 1 == dot || -1 == dot);
//
//        EXPECT_TRUE(result);
//    }
//    dot = DBL_MAX;
//
//
//    camDir = Vector3{0, 0, 1};
//    cam = Camera(Vector3(100, 0, 0), 100, 100, camDir, 0);
//
//    pixelsToTest = (cam.GetHeight() * cam.GetWidth()) * .1;
//    max = (cam.GetHeight() * cam.GetWidth());
//    for (int i = 0; i < pixelsToTest; i++)
//    {
//        randNum = rand()%(max-min + 1) + min;
//
//        Vector3 point = cam.GetImage()[randNum].GetPosition() - cam.GetPosition();
//        dot = Vector3::Dot(camDir, point);
//
//        if (cam.GetPosition() == Vector3::Negate(point))
//        {
//            continue;
//        }
//
//        result = (0 == dot || 1 == dot || -1 == dot);
//
//        EXPECT_TRUE(result);
//    }
//    dot = DBL_MAX;
//
//
//    camDir = Vector3{0, 0, 1};
//    cam = Camera(Vector3(0, 100, 0), 100, 100, camDir, 0);
//
//    pixelsToTest = (cam.GetHeight() * cam.GetWidth()) * .1;
//    max = (cam.GetHeight() * cam.GetWidth());
//    for (int i = 0; i < pixelsToTest; i++)
//    {
//        randNum = rand()%(max-min + 1) + min;
//
//        Vector3 point = cam.GetImage()[randNum].GetPosition() - cam.GetPosition();
//        dot = Vector3::Dot(camDir, point);
//
//        if (cam.GetPosition() == Vector3::Negate(point))
//        {
//            continue;
//        }
//
////        cout << endl << "point : " << point.ToString() << endl;
////        cout << "camDir : " << camDir.ToString() << endl;
////        cout << "dot : " << dot << endl;
//
//        result = (0 == dot || 1 == dot || -1 == dot);
//
//        EXPECT_TRUE(result);
//    }
//    dot = DBL_MAX;
//
//
////    camDir = Vector3{0, 0, 1};
////    cam = Camera(Vector3(0, 0, 100), 100, 100, camDir, 0);
////
////    pixelsToTest = (cam.GetHeight() * cam.GetWidth()) * .1;
////    max = (cam.GetHeight() * cam.GetWidth());
////    for (int i = 0; i < pixelsToTest; i++)
////    {
////        randNum = rand()%(max-min + 1) + min;
////
////        Vector3 point = cam.GetImage()[randNum].GetPosition() - cam.GetPosition();
////        dot = Vector3::Dot(camDir, point);
////
////        if (cam.GetPosition() == Vector3::Negate(point))
////        {
////            continue;
////        }
////
//////        cout << endl << "point : " << point.ToString() << endl;
//////        cout << "camDir : " << camDir.ToString() << endl;
//////        cout << "dot : " << dot << endl;
////
////        result = (0 == dot || 1 == dot) || -1 == dot;
////
////        EXPECT_TRUE(result);
////    }
////    dot = DBL_MAX;
//
//
////    // Ecran regarde à droite
////    camDir = Vector3{1, 0, 0};
////    cam = Camera(Vector3(7, 0, -28), 100, 100, camDir, 0);
////
////    pixelsToTest = (cam.GetHeight() * cam.GetWidth()) * .1;
////    max = (cam.GetHeight() * cam.GetWidth());
////    for (int i = 0; i < pixelsToTest; i++)
////    {
////        Vector3 point = cam.GetImage()[randNum].GetPosition() - cam.GetPosition();
////        dot = Vector3::Dot(camDir, point);
////
////        if (cam.GetPosition() == Vector3::Negate(point))
////        {
////            continue;
////        }
////
//////        cout << endl << "point : " << point.ToString() << endl;
//////        cout << "dot : " << dot << endl;
////
////        result = (0 == dot || 1 == dot) || -1 == dot;
////
////        EXPECT_TRUE(result);
////    }
////    dot = DBL_MAX;
//
//
////    // Ecran regarde en diagonale à droite
////    camDir = Vector3{-1, 0, 0};
////    cam = Camera(Vector3(34, 0, 67), 100, 100, camDir, 0);
////
////    pixelsToTest = (cam.GetHeight() * cam.GetWidth()) * .1;
////    max = (cam.GetHeight() * cam.GetWidth());
////    for (int i = 0; i < pixelsToTest; i++)
////    {
////        Vector3 point = cam.GetImage()[randNum].GetPosition() - cam.GetPosition();
////        dot = Vector3::Dot(camDir, point);
////
////        if (cam.GetPosition() == Vector3::Negate(point))
////        {
////            continue;
////        }
////
//////        cout << endl << "point : " << point.ToString() << endl;
//////        cout << "dot : " << dot << endl;
////
////        result = (0 == dot || 1 == dot) || -1 == dot;
////
////        EXPECT_TRUE(result);
////    }
////    dot = DBL_MAX;
//
////    camDir = Vector3{-1, 0, 1};
////    cam = Camera(Vector3(34, 0, 67), 100, 100, camDir, 0);
////
////    pixelsToTest = (cam.GetHeight() * cam.GetWidth()) * .1;
////    max = (cam.GetHeight() * cam.GetWidth());
////    for (int i = 0; i < pixelsToTest; i++)
////    {
////        Vector3 point = cam.GetImage()[randNum].GetPosition() - cam.GetPosition();
////        dot = Vector3::Dot(camDir, point);
////
////        if (cam.GetPosition() == Vector3::Negate(point))
////        {
////            continue;
////        }
////
//////                cout << endl << "point : " << point.ToString() << endl;
//////                cout << "dot : " << dot << endl;
////
////        result = (0 == dot || 1 == dot) || -1 == dot;
////
////        EXPECT_TRUE(result);
////    }
////    dot = DBL_MAX;
//
//
////    camDir = Vector3{.487, 0., -.751};
////    cam = Camera(Vector3(34, 0, 67), 100, 100, camDir, 0);
////
////    pixelsToTest = (cam.GetHeight() * cam.GetWidth()) * .1;
////    max = (cam.GetHeight() * cam.GetWidth());
////    for (int i = 0; i < pixelsToTest; i++)
////    {
////        Vector3 point = cam.GetImage()[randNum].GetPosition() - cam.GetPosition();
////        dot = Vector3::Dot(camDir, point);
////
////        if (cam.GetPosition() == Vector3::Negate(point))
////        {
////            continue;
////        }
////
//////        cout << endl << "point : " << point.ToString() << endl;
//////        cout << "dot : " << dot << endl;
////
////        result = (0 == dot || 1 == dot) || -1 == dot;
////
////        EXPECT_TRUE(result);
////    }
////    dot = DBL_MAX;
//
//
////    camDir = Vector3{-.487, 0., -.751};
////    cam = Camera(Vector3(34, 0, 67), 100, 100, camDir, 0);
////
////    pixelsToTest = (cam.GetHeight() * cam.GetWidth()) * .1;
////    max = (cam.GetHeight() * cam.GetWidth());
////    for (int i = 0; i < pixelsToTest; i++)
////    {
////        Vector3 point = cam.GetImage()[randNum].GetPosition() - cam.GetPosition();
////        dot = Vector3::Dot(camDir, point);
////
////        if (cam.GetPosition() == Vector3::Negate(point))
////        {
////            continue;
////        }
////
//////        cout << endl << "point : " << point.ToString() << endl;
//////        cout << "dot : " << dot << endl;
////
////        result = (0 == dot || 1 == dot) || -1 == dot;
////
////        EXPECT_TRUE(result);
////    }
////    dot = DBL_MAX;
//}

TEST(IntersectFunc, SimpleIntersect)
{
    Intersection result;
    const Vector3 rayOrigin{0, 0, 0};
    Vector3 rayDirection{1, 0, 0};

    Ray ray = Ray(rayOrigin, rayDirection);
    const Sphere sphere = Sphere(Vector3{20, 0, 0}, 10);
    
    // Intersection avec un rayon partant de devant la sphère
    result = Sphere::IntersectRaySphere(ray, sphere);
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(10, result.distance);
    EXPECT_EQ(10, result.pointCoordonate.GetX());
    EXPECT_EQ(0, result.pointCoordonate.GetY());
    EXPECT_EQ(0, result.pointCoordonate.GetZ());
    
    // Intersection si le rayon part de l'interieur de la sphère
    result = Sphere::IntersectRaySphere(ray, Sphere{Vector3{0, 0, 0}, 10});
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(10, result.distance);
    EXPECT_EQ(10, result.pointCoordonate.GetX());
    EXPECT_EQ(0, result.pointCoordonate.GetY());
    EXPECT_EQ(0, result.pointCoordonate.GetZ());
    
    // Pas d'intersection, le rayon est dans le mauvais sens
    rayDirection = Vector3{-1, 0, 0};
    result = Sphere::IntersectRaySphere(Ray(rayOrigin, rayDirection), sphere);
    EXPECT_EQ(false, result.intersect);
    
    // Intersection tangeante
    const Vector3 rayOrigin2{0, 10, 0};
    rayDirection = Vector3{1, 0, 0};
    result = Sphere::IntersectRaySphere(Ray(rayOrigin2, rayDirection), sphere);
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(20, result.distance);
    EXPECT_EQ(20, result.pointCoordonate.GetX());
    EXPECT_EQ(10, result.pointCoordonate.GetY());
    EXPECT_EQ(0, result.pointCoordonate.GetZ());
    
    // Intersection derrière
    const Vector3 rayOrigin3{40, 0, 0};
    rayDirection = Vector3{-1, 0, 0};
    result = Sphere::IntersectRaySphere(Ray(rayOrigin3, rayDirection), sphere);
    EXPECT_EQ(true, result.intersect);
    
    // Intersection dessous
    const Vector3 rayOrigin4{20, 40, 0};
    rayDirection = Vector3{0, -1, 0};
    result = Sphere::IntersectRaySphere(Ray(rayOrigin4, rayDirection), sphere);
    EXPECT_EQ(true, result.intersect);
    
    // Intersection dessus
    const Vector3 rayOrigin5{20, -40, 0};
    rayDirection = Vector3{0, 1, 0};
    result = Sphere::IntersectRaySphere(Ray(rayOrigin5, rayDirection), sphere);
    EXPECT_EQ(true, result.intersect);
    
    // Intersection à droite
    const Vector3 rayOrigin6{20, 0, 40};
    rayDirection = Vector3{0, 0, -1};
    result = Sphere::IntersectRaySphere(Ray(rayOrigin6, rayDirection), sphere);
    EXPECT_EQ(true, result.intersect);
    
    const Vector3 rayOrigin7{500, 500, 0};
    rayDirection = Vector3{0, 0, -1};
    result = Sphere::IntersectRaySphere(Ray(rayOrigin7, rayDirection), Sphere(Vector3{500, 500, -100}, 10));
    EXPECT_EQ(true, result.intersect);
    
    const Vector3 rayOrigin8{0, 0, 0};
    rayDirection = Vector3{1, 0, 1};
    result = Sphere::IntersectRaySphere(Ray(rayOrigin8, rayDirection), Sphere(Vector3{10, 0, 0}, 1));
    EXPECT_EQ(false, result.intersect);
    
    // Vérifier manuellement ce test
    //    Intersect(Ray(Vector3(0, 0, 0), Vector3(1, 0, 1)), Sphere(Vector3(5.75, 0., 5.), 1), result);
    //    EXPECT_EQ(false, result.intersect);
}

TEST(IntersectFunc, TestsEva)
{
    Intersection result;
    const Vector3 rayOrigin{0, 0, 0};
    const Vector3 rayDirection{1, 1, 1};
    const Ray ray = Ray(rayOrigin, rayDirection);
    Sphere sphere = Sphere{Vector3(0, 0, 0), 100};
    
    result = Sphere::IntersectRaySphere(ray, sphere);
    
    EXPECT_EQ(result.intersect, true);
    EXPECT_GE(result.distance, 0);
    EXPECT_EQ(result.distance, sphere.GetRayon());
    
    sphere.SetCenter(Vector3(-200, -200, -200));
    result = Sphere::IntersectRaySphere(ray, sphere);
    EXPECT_EQ(result.intersect, false);
    
    sphere.SetCenter(Vector3(200, 200, 200));
    result = Sphere::IntersectRaySphere(ray, sphere);
    EXPECT_EQ(result.intersect, true);
    EXPECT_GE(result.distance, 0);
}

//TEST(IntersectFunc, BoxSimple)
//{
//    const Sphere sp = Sphere(Vector3(5, 5, 5), 5);
//    const Box b = Box(sp);
//    const Vector3 v1{-5., 2.5, 0.};
//    Vector3 v2{1, 0, 0};
//
//    const Ray r = Ray(v1, v2);
//
//    const Vector3 v3{-1, 1, 0};
//    Vector3 v4{.5, -.5, 0.};
//
//    const Ray r1 = Ray(v3, v4);
//    const Vector3 v5{-5., 2.5, 0.};
//    Vector3 v6{-1, 0, 0};
//    const Ray r2 = Ray(v5, v6);
//    const Vector3 v7{5., 30., 5.};
//    Vector3 v8{0, -1, 0};
//    const Ray r3 = Ray(v7, v8);
//    const Vector3 v9{-5., 25., 0.};
//    Vector3 v10{-1, 0, 0};
//    const Ray r4 = Ray(v9, v10);
//
//    EXPECT_EQ(IntersectBox(r, b), true);
//    EXPECT_EQ(IntersectBox(r1, b), true);
//    EXPECT_EQ(IntersectBox(r2, b), true);
//    EXPECT_EQ(IntersectBox(r3, b), true);
//    EXPECT_EQ(IntersectBox(r4, b), false);
//}
//
//// @TODO: Add units tests from camera that isn't faceing forward or any "natural" direction
//
////TEST(IntersectFunc, RandomTest)
////{
////    srand(static_cast<unsigned int>(time(0)));
////    Intersection result;
////    for (int i = 0; i < 100000; i++)
////    {
////        Ray r = Ray(Vector3(rand(), rand(), rand()), Vector3(rand(),rand(),rand()));
////        Sphere s = Sphere{Vector3(rand(), rand(), rand()), static_cast<double>(rand())};
////        Intersect(r, s, result);
////        if (result.intersect)
////        {
////            EXPECT_GE(result.distance, 0);
////        }
////    }
////}

//TEST(IntersectFunc, TestScene)
//{
//    Scene spheres;
//    InitSpheres(spheres);
//    Intersection result;
//    const Ray r = Ray(Vector3(150, 500, 500), Vector3(0, 1, 1));
//
//    Intersect(r, spheres[0], result);
//    EXPECT_EQ(true, result.intersect);
//    EXPECT_EQ(75, result.distance);
//    EXPECT_EQ(150, result.point.x);
//    EXPECT_DOUBLE_EQ(553.03300858899104, result.point.y);
//    EXPECT_DOUBLE_EQ(553.03300858899104, result.point.z);
//
////    const Ray r1 = Ray(Vector3(0, 500, 500), Vector3(845, 541, 398));
////    cout << "direction : (" << r1.direction.x << ", " << r1.direction.y << ", " << r1.direction.z << ")" << endl;
////    Intersect(r1, spheres[0], result);
////    EXPECT_EQ(true, result.intersect);
////    EXPECT_EQ(75, result.distance);
////    EXPECT_EQ(75, result.point.x);
////    EXPECT_EQ(575, result.point.y);
////    EXPECT_EQ(500, result.point.z);
//
////    Intersect(Ray(Vector3{300, -200, 600}, Vector3{-1, 1, 1}), spheres[1], result);
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
    vector<Sphere> scene;
    const Sphere sp1 = Sphere{Vector3{0, 0, 0}, 10};
    const Light lum = Light{Vector3{20, 0, 0}, 1000};
    scene.push_back(sp1);
    
    
    // Le Ray est intersepté par une sphère
    const Vector3 point1 = Vector3{-20, 0, 0};
    EXPECT_EQ(false, Toolbox::CanSeeLight(point1, lum, scene));

    // le Ray n'est pas intersepté par la sphère
    const Vector3 point2 = Vector3{15, 0, 0};
    EXPECT_EQ(true, Toolbox::CanSeeLight(point2, lum, scene));
    
    // Le Ray part de l'intérieur de la sphère
    const Vector3 point3 = Vector3{0, 0, 0};
    EXPECT_EQ(false, Toolbox::CanSeeLight(point3, lum, scene));
    
    // La lumière est dans la sphère, le Ray non
    const Light& lightInsideSphere = Light{Vector3(0, 0, 0), 1000};
    EXPECT_EQ(false, Toolbox::CanSeeLight(point1, lightInsideSphere, scene));

    // La lumière est dans la sphère, le Ray aussi
    const Vector3 point4 = Vector3(2, 0, 0);
    const Light& lightInsideSphere2 = Light{Vector3(8, 0, 0), 1000};
    EXPECT_EQ(true, Toolbox::CanSeeLight(point4, lightInsideSphere2, scene));

    // Le point est après la lumière
    const Vector3 point5 = Vector3(30, 0, 0);
    EXPECT_EQ(true, Toolbox::CanSeeLight(point5, lum, scene));
    
    
    
    const Vector3 point6 = Vector3(0, 0, 1000);
    const Vector3 point7 = Vector3(0, 600, 1000);
    const Vector3 point8 = Vector3(0, 750, 1000);
    const Vector3 point9 = Vector3(0, 751, 1000);

    const Light light = Light(Vector3(0, 0, 0), 1000);
    vector<Sphere> sp2;
    sp2.push_back(Sphere(Vector3(0, 0, 500), 300, Material(Color(0, 0, 0))));
    
    EXPECT_EQ(false, Toolbox::CanSeeLight(point6, light, sp2));
    EXPECT_EQ(false, Toolbox::CanSeeLight(point7, light, sp2));
    EXPECT_EQ(false, Toolbox::CanSeeLight(point8, light, sp2));
    EXPECT_EQ(true, Toolbox::CanSeeLight(point9, light, sp2));
}

TEST(CanSeeLightFunc, ComplexeTest)
{
    vector<Sphere> scene;
    const Sphere sp1 = Sphere{Vector3(21, 36, -28), 20};
    const Light lum = Light{Vector3(57, 13, 100), 0};
    scene.push_back(sp1);
    
    Vector3 p1 = Vector3(0, 0, 0);
    EXPECT_EQ(true, Toolbox::CanSeeLight(p1, lum, scene));
    p1 = Vector3(76, 54, -48);
    EXPECT_EQ(true, Toolbox::CanSeeLight(p1, lum, scene));
    p1 = Vector3(11, 40, -70);
    EXPECT_EQ(false, Toolbox::CanSeeLight(p1, lum, scene));
    p1 = Vector3(-100, 40, -27);
    EXPECT_EQ(true, Toolbox::CanSeeLight(p1, lum, scene));
    
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
