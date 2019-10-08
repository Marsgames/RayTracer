//
//  Scene.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 30/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <iostream>
#include <Box.hpp>
#include <Light.hpp>
#include <Scene.hpp>
#include <vector>

using std::cout;
using std::endl;
using std::to_string;
using std::vector;

void Scene::AddSphere(const Sphere& sphere) {
    m_spheres.push_back(sphere);
}

void Scene::AddSphere(const vector<Sphere>& spheres) {
    for (const Sphere& sphere : spheres)
    {
        m_spheres.push_back(sphere);
    }
}

void Scene::AddLight(const Light &light) {
    m_lights.push_back(light);
}

void Scene::AddLight(const vector<Light> &lights) {
    for (const Light& light : lights)
    {
        m_lights.push_back(light);
    }
}

void Scene::AddCamera(const Camera &camera) {
    m_cameras.push_back(camera);
}

void Scene::AddCamera(const vector<Camera> &cameras) {
    for (const Camera& camera : cameras)
    {
        m_cameras.push_back(camera);
    }
}

void Scene::AddBoxes(const vector<Box> &boxes) {
    for (const Box& box : boxes)
    {
        m_boxes.push_back(box);
    }
}

void Scene::DrawImages() {
    for (Camera& camera : m_cameras)
    {
//        camera.DrawImage();
        camera.DrawImageWithThread();
    }
}

void Scene::DrawScene()
{
    for (Camera& camera : m_cameras)
    {
//        camera.DrawImage();
        camera.DrawSceneWithThread();
    }
}

void Scene::DrawBB()
{
    for (Camera& camera : m_cameras)
        {
    //        camera.DrawImage();
            camera.DrawBB();
        }
}

void Scene::SaveImages() {
    int index = 0;
    
    for (Camera& camera : m_cameras)
    {
        camera.SetImageName("theImage" + to_string(index));
        camera.SaveImage();
        cout << "BMP saved for cam" << index << endl;
//        camera.SetImageFormat(EImageFormat::PPM);
//        camera.SaveImage();
//        cout << "PPM saved for cam" << index << endl;
        index++;
    }
}



vector<Light> Scene::GetLights() const {
    return m_lights;
}

vector<Sphere> Scene::GetSpheres() const {
    return m_spheres;
}

vector<Box> Scene::GetBoxes() const {
    return m_boxes;
}
