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
    
    // Intersectino avec un rayon partant de devant la sphère
    Intersect(rayon, sphere, result);
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(10, result.distance);
    EXPECT_EQ(10, result.point.x);
    EXPECT_EQ(0, result.point.y);
    EXPECT_EQ(0, result.point.z);
    
    // Intersection si le rayon part de l'interieur de la sphère
    Intersect(rayon, Sphere{Vector3{0, 0, 0}, 10}, result);
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(10, result.distance);
    EXPECT_EQ(10, result.point.x);
    EXPECT_EQ(0, result.point.y);
    EXPECT_EQ(0, result.point.z);
    
    // Pas d'intersection, le rayon est dans le mauvais sens
    Intersect(Rayon(Vector3{0, 0, 0}, Vector3{-1, 0, 0}), sphere, result);
    EXPECT_EQ(false, result.intersect);
    
    // Intersection tangeante
    Intersect(Rayon(Vector3{0, 10, 0}, Vector3{1, 0, 0}), sphere, result);
    EXPECT_EQ(true, result.intersect);
    EXPECT_EQ(20, result.distance);
    EXPECT_EQ(20, result.point.x);
    EXPECT_EQ(10, result.point.y);
    EXPECT_EQ(0, result.point.z);
    
    // Pas d'intersection derrière
    Intersect(Rayon(Vector3{40, 0, 0}, Vector3{-1, 0, 0}), sphere, result);
    EXPECT_EQ(false, result.intersect);
    
    // Pas d'intersection dessous
    Intersect(Rayon(Vector3{0, 40, 0}, Vector3{0, -1, 0}), sphere, result);
    EXPECT_EQ(false, result.intersect);

    // Pas d'intersection dessus
    Intersect(Rayon(Vector3{0, -40, 0}, Vector3{0, 1, 0}), sphere, result);
    EXPECT_EQ(false, result.intersect);


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
    EXPECT_DOUBLE_EQ(139.67221921331486, result.distance);
    EXPECT_DOUBLE_EQ(160.32778078668514, result.point.x);
    EXPECT_DOUBLE_EQ(-60.327780786685139, result.point.y);
    EXPECT_DOUBLE_EQ(739.67221921331486, result.point.z);

//    cout << "intersect : " << result.intersect << endl;
//    cout << "distance : " << result.distance << endl;
//    cout << "x : " << result.point.x << endl;
//    cout << "y : " << result.point.y << endl;
//    cout << "z : " << result.point.z << endl;
}

TEST(CanSeeLightFunc, SimpleTest)
{
    Scene scene;
    Sphere sp1 = Sphere{Vector3{0, 0, 0}, 10};
    scene.push_back(sp1);
    Light lum = Light{Vector3{20, 0, 0}, 1000};
    
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
    
}
