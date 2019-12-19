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

using std::default_random_engine;

class Toolbox { 
    static const int K_SEED = 0;
    static default_random_engine K_GENERATOR;
    
public:    
    static double GenerateRandomNumber(const double min = 0.0, const double max = 1.0);
    static Vector3 GetRandomDirectionOnHemisphere(const Vector3& normal);
    static Vector3 GetRandomDirectionInAngle(const Vector3& normal, const float angleMax);
    static Vector3 GetRandomPointOnSphere(const Sphere& sphere);
    static bool CanSeeLight(const Vector3& point, const Light& light, const vector<Sphere>& spheres);
};
