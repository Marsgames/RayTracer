//
//  Toolbox.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 17/09/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Light.hpp>
#include <random>
#include <vector>
#include <Vector3.hpp>

class Toolbox {
    
public:
//    static std::default_random_engine K_GENERATOR;
    
    static double GenerateRandomNumber(std::default_random_engine& generator, const double min = 0.0, const double max = 1.0);
    static Vector3 GetRandomDirectionOnHemisphere(const Vector3& normal, std::default_random_engine& generator);
    static Vector3 GetRandomPointOnSphere(const Sphere& sphere, std::default_random_engine& generator);
    static bool CanSeeLight(const Vector3& point, const Light& light, const vector<Sphere>& spheres);
};
