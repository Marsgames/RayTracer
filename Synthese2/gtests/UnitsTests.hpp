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
