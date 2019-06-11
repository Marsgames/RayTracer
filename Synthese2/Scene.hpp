//
//  Scene.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 30/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Camera.hpp>
#include <Light.hpp>
#include <Sphere.hpp>
#include <vector>

using std::vector;

class Scene {
    vector<class Camera> m_cameras;
    vector<Light> m_lights;
    vector<Sphere> m_spheres;
    
public:
    Scene(){};
    
    void AddCamera(const class Camera& camera);
    void AddCamera(const vector<class Camera>& cameras);
    
    void AddLight(const Light& light);
    void AddLight(const vector<Light>& lights);
    
    void AddSphere(const Sphere& sphere);
    void AddSphere(const vector<Sphere>& spheres);
    
    vector<Light> GetLights() const;
    vector<Sphere> GetSpheres() const;
    
    void DrawImages();
    void SaveImages();
};
