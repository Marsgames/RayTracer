//
//  Camera.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <Library/Bitmap/bitmap_image.hpp>
#include <Light.hpp>
#include <Camera.hpp>
#include <iostream>
#include <fstream>
#include <Vector3.hpp>
#include <vector>

using std::cout;
using std::endl;
using std::ofstream;
using std::vector;
using std::string;

void Camera::InitPixelsArray() {
    //    m_pixels.reserve(m_height * m_width);
    //
    //    for (int index = 0; index < m_height * m_width; index++)
    //    {
    //        int x = index % m_width;
    //        int y = index / m_width;
    //
    //        m_pixels.push_back(Pixel{Vector3{x, y, 0}, Color{255, 0, 0}});
    //    }
    
    
    
    
    
    
    
    //    ofstream pointsFile;
    //    ofstream directionsFile;
    //
    //    pointsFile.open ("/Users/Raph/Desktop/TestSynthese/points.txt");
    //    directionsFile.open("/Users/Raph/Desktop/TestSynthese/directions.txt");
    
    Vector3 baseDirection{0,0,1};
    const double thetaUnsigned = acos((Vector3::Dot(baseDirection, m_direction)));
    double thetaSigned;
    
    if (m_direction.GetX() >= 0)
    {
        thetaSigned = thetaUnsigned;
    }
    else
    {
        thetaSigned = thetaUnsigned * -1;
    }
    
    
    
    m_pixels.reserve(m_height * m_width);
    Color defaultColor {0, 0, 0};
    
    for (int index = 0; index < m_height * m_width; index++)
    {
        // Pour un écran de 1000 * 1000
        // 0 * 0  -->  1000 * 1000
        //const int x = index % m_width;
        //const int y = index / m_width;
        
        // -500, -500  -->  500, 500
        const int indexX = (index % m_width - m_width / 2);// + m_origin.GetX();
        const int indexY = (index / m_width - m_height / 2);// + m_origin.GetY();
        
        const Vector3 actualPos {indexX, indexY, static_cast<int>(m_position.GetZ())};
        //        const Vector3 newPos = Vector3{cos(thetaSigned) * actualPos.GetX() + sin(thetaSigned) * actualPos.GetZ(), actualPos.GetY(), -sin(thetaSigned) * actualPos.GetX() + cos(thetaSigned) * actualPos.GetZ()};
        
        Vector3 newPos = Vector3{cos(thetaSigned) * actualPos.GetX() + sin(thetaSigned) * 1, actualPos.GetY(), -sin(thetaSigned) * actualPos.GetX() + cos(thetaSigned) * 1};
        
        newPos.SetX(newPos.GetX() + m_position.GetX());
        newPos.SetY(newPos.GetY() + m_position.GetY());
        newPos.SetZ(newPos.GetZ() + m_position.GetZ());
        
        m_pixels.push_back(Pixel(newPos, defaultColor, index));
        
        
        //        pointsFile << newPos.ToString() << "|";
        //        directionsFile << m_direction.ToString() << "|";
    }
    
    //    pointsFile.close();
    //    directionsFile.close();
}

int Camera::GetWidth() const {
    return m_width;
}

int Camera::GetHeight() const {
    return m_height;
}

int Camera::GetFocalDist() const {
    return m_focalDist;
}

void Camera::SetUseFocal(bool value) { 
    m_useFocal = value;
}


void Camera::SetFocalDist(int focalDistance) {
    m_focalDist = focalDistance;
}

void Camera::SetImageFormat(EImageFormat format) {
    m_imageFormat = format;
}

void Camera::SaveImage() {
    switch (m_imageFormat) {
        case EImageFormat::BMP:
            SaveBMP();
            break;
        case EImageFormat::PPM:
            SavePPM();
            break;
            
        default:
            SaveBMP();
            break;
    }
}

Vector3 Camera::GetPosition() const {
    return m_position;
}

void Camera::SetPosition(Vector3 position) {
    m_position = position;
}

Vector3 Camera::GetDirection() const {
    return m_direction;
}

void Camera::SetDirection(Vector3 direction) {
    m_direction = direction;
}

inline void Camera::SavePPM() {
    ofstream myfile;
    myfile.open (m_source + m_name + ".ppm");
    myfile << "P3" << endl;
    myfile << "# " << m_name << ".ppm" << endl;
    myfile << m_width << " " << m_height << endl;
    myfile << "255" << endl;
    
    for (int index = 0; index < m_height * m_width; index++)
    {
        double r = m_pixels[index].GetColorR() > 255 ? 255 : m_pixels[index].GetColorR();
        double g = m_pixels[index].GetColorG() > 255 ? 255 : m_pixels[index].GetColorG();
        double b = m_pixels[index].GetColorB() > 255 ? 255 : m_pixels[index].GetColorB();
        
        if (r < 0 || g < 0 || b < 0)
        {
            cout << "color < 0 : (" << r << ", " << g << ", " << b << ")" << endl;
            myfile.close();
            exit(2);
            // EXIT CODE: 2 --> Un pixel avait une couleur < 0
        }
        
        myfile << r << " " << g << " " << b << " ";
        //        }
        myfile << endl;
    }
    
    myfile.close();
}

inline void Camera::SaveBMP() {
    bitmap_image img(m_width, m_height);
    
    for (int index = 0; index < m_height * m_width; index++)
    {
        int x = index % m_width;
        int y = index / m_width;
        
        double r = m_pixels[index].GetColorR() > 255 ? 255 : m_pixels[index].GetColorR();
        double g = m_pixels[index].GetColorG() > 255 ? 255 : m_pixels[index].GetColorG();
        double b = m_pixels[index].GetColorB() > 255 ? 255 : m_pixels[index].GetColorB();
        
        //        if(r < 0 || g < 0 || b < 0)
        //        {
        //            cout << "color < 0 : (" << r << ", " << g << ", " << b << ")" << endl;
        //            exit(2);
        //            // EXIT CODE: 2 --> Un pixel avait une couleur < 0
        //        }
        if (r < 0)
            r = 0;
        if (g < 0)
            g = 0;
        if (b < 0)
            b = 0;
        
        img.set_pixel(x, y, r, g, b);
    }
    
    img.save_image(m_source + m_name + ".bmp");
    //        img.save_image("imageSynthese.bmp");
    //    if (nomImage.find('0') != std::string::npos)
    //    {
    //        cout << "image sauvegardée dans " << source + nomImage << " !" << endl;
    //    }
}

//void Camera::DrawImage(const vector<Sphere> &spheres, const vector<Light>& lights) {
//
//    const Vector3 rayDirection = GetRayDirection();
//    Ray ray = Ray(Vector3{0, 0, 0}, rayDirection);
//    double distance = __DBL_MAX__;
//    Material sphereMaterial = Material(Color(0, 0, 0), EMaterials::DarkFloor);
//    Vector3 pointOnSphere = Vector3(0, 0, 0);
//    Pixel pixel = Pixel();
//
//    for (int index = 0; index < m_height * m_width; index++)
//    {
//        pixel = m_pixels[index];
//
//        ray.SetOrigin(m_pixels[index].GetPosition());
//        if (m_useFocal)
//        {
//            ray.SetDirection(GetRayDirection(pixel.GetPosition()));
//        }
//
//        for (Sphere sphere : spheres)
//        {
//            Intersection intersection = Sphere::IntersectRaySphere(ray, sphere);
//
//            if (intersection.intersect && intersection.distance <= distance)
//            {
//                distance = intersection.distance;
//                sphereMaterial = sphere.GetMaterial();
//                pointOnSphere = intersection.pointCoordonate;
//            }
//        }
//
//        if (distance < __DBL_MAX__)
//        {
//            for (const Light& light : lights)
//            {
//                cout << "index : " << index << endl;
//                int nbBounce = 0;
//                Color finalColor;
//                Color gotColor;
//                do
//                {
////                    cout << "albedo : " << sphereMaterial.GetAlbedo() << endl;
//                    bool canSeeLight = Light::CanSeeLight(pointOnSphere, light, spheres);
//                    if (canSeeLight)
//                    {
//                        gotColor = Light::GetLightning(light, sphereMaterial.GetColor(), Vector3::GetDistance(pointOnSphere, light.GetPosition()));
//                        gotColor = gotColor * (1 - sphereMaterial.GetAlbedo());
//
//
//
////                        cout << "gotColor : " << gotColor.ToString() << endl;
//
//                        finalColor += gotColor;
//                    }
//                    else
//                    {
//                        finalColor += Color(0, 0, 0);
//                    }
//
//
//                    nbBounce++;
//                }while (nbBounce < 10 && 0 != sphereMaterial.GetAlbedo());
//
////                cout << "finalColor : " << finalColor.ToString() << endl << endl;
//
//                m_pixels[index].SetColor(finalColor / nbBounce);
//                finalColor = Color(0, 0, 0);
//
//
//                //                                sphereColor.Print();
//
////                if (canSeeLight)
////                {
////                    Color newColor = Light::GetLightning(light, sphereMaterial.GetColor(), Vector3::GetDistance(pointOnSphere, light.GetPosition()));
////                    newColor = newColor * (1 - sphereMaterial.GetAlbedo());
//////                    newColor = newColor +
////
////                    m_pixels[index].SetColor(newColor);
////                }
////                else
////                {
////                    //                    m_pixels[index].SetColor(Color{200, 200, 200} * 0.3f);
////                    m_pixels[index].SetColor(sphereMaterial.GetColor() * 0.000002);
////                }
//            }
//        }
//        distance = __DBL_MAX__;
//        //        sphereColor = Color{0, 0, 0};
//    }
//}


void Camera::DrawImage() {
    
    if (nullptr == m_scene)
    {
        exit(4); // m_scene n'est pas set !
    }
    
    const vector<Sphere> spheres = m_scene->GetSpheres();
    const vector<Light> lights = m_scene->GetLights();
    
    const Vector3 rayDirection = GetRayDirection();
    Ray ray = Ray(Vector3{0, 0, 0}, rayDirection);
    // double distance = __DBL_MAX__;
    // Material sphereMaterial = Material(Color(0, 0, 0), EMaterials::DarkFloor);
    // Vector3 pointOnSphere = Vector3(0, 0, 0);
    Color pixelColor = Color(100, 100, 100);
    
    for (Pixel& pixel : m_pixels)
    {
        ray.SetOrigin(pixel.GetPosition());
        if (m_useFocal)
        {
            ray.SetDirection(GetRayDirection(pixel.GetPosition()));
        }
        
        cout << "index : " << pixel.index << endl;
        //        int nbBounce = 0;
        //        Reflexion reflexion;
        ////        Material mat = Material(Color(), EMaterials::DarkFloor);
        //        do
        //        {
        
        
        
        
        Intersection intersection = GetNearestIntersection(ray);
        pixelColor = GetColor(intersection);//, m_maxBounce);
        
        
        
//        for (const Sphere& sp : spheres)
//        {
//            pixelColor = SendRay(ray, sp, 10, spheres, lights, 10);
//        }

        
        
        
        
        //            reflexion = GetMaterial(spheres, ray, lights);
        ////            mat = reflexion.material;
        ////            pixelColor += reflexion.material.GetColor();
        //
        //            pixelColor += reflexion.material.GetColor();
        //
        //            ray = Ray::GetReflectDirection(ray, reflexion.intersection, reflexion.sphere);
        //
        ////            cout << "pixel" << pixelColor.ToString() << endl;
        ////            cout << "get" << reflexion.material.GetColor().ToString() << endl;
        //
        //            nbBounce++;
        //        }while(nbBounce <= m_maxBounce && 0 != reflexion.material.GetAlbedo());
        //        cout << endl;
        
        //            pixelColor = pixelColor / nbBounce;
        
        pixel.SetColor(pixelColor);
        
        
        //        pixel.SetColor(GetColor(spheres, ray, lights));
        
        if (pixel.index % 1000000 == 0)
            SaveImage();
        
    }
}


Vector3 Camera::GetRayDirection() {
    return GetRayDirection(m_direction);
}

Vector3 Camera::GetRayDirection(const Vector3& toThatPoint) const {
    if (m_useFocal)
    {
        const Vector3 startPoint = m_position + toThatPoint;// Vector3(toThatPoint.GetX(), toThatPoint.GetY(), m_position.GetZ());
        const Vector3 focalStart = m_position + Vector3::Negate(m_direction * m_focalDist);
        
        return (startPoint - focalStart).Normalize();
    }
    else
    {
        return toThatPoint;
    }
}

void Camera::SetImageName(string name) {
    m_name = name;
}

bool Camera::GetUseFocal() {
    return m_useFocal;
}

Color Camera::GetColor(const Intersection& intersection) const {
    Color returnedColor;
    
    const vector<Sphere> spheres = m_scene->GetSpheres();
    const vector<Light> lights = m_scene->GetLights();
    
    if (intersection.intersect)
    {
        // Si la sphère est un miroir
        if (intersection.touchedSphere.GetMaterial().GetAlbedo() == 1)
        {
            // on rebondi
        }
        else if (intersection.touchedSphere.GetMaterial().GetAlbedo() > 0)
        {
            // blabla
        }
        else
        {
//            returnedColor = intersection.touchedSphere.GetMaterial().GetDiffuseColor();
            for (const Light& light : lights)
            {
                bool canSeeLight = Light::CanSeeLight(intersection.pointCoordonate, light, spheres);

                if (canSeeLight)
                {
                    returnedColor = returnedColor + Light::GetLightning(light, intersection.touchedSphere.GetMaterial().GetDiffuseColor(), Vector3::GetDistance(intersection.pointCoordonate, light.GetPosition()));
                }
//
            }
            // full diffuse mat
        }
    }
    
    
    return returnedColor;
}

Intersection Camera::GetNearestIntersection(const Ray &ray) const {
    
    Intersection intersection, nearestIntersection;
    double distanceIntersection = __DBL_MAX__;
    Sphere nearestSphere = Sphere(Vector3(0), -1, Material(Color(0, 0, 0)));
    
    for (const Sphere& sphere : m_scene->GetSpheres())
    {
        intersection = Sphere::IntersectRaySphere(ray, sphere);
        
        if (intersection.intersect && intersection.distance <= distanceIntersection)
        {
            distanceIntersection = intersection.distance;
            nearestSphere = sphere;
            nearestIntersection = intersection;
        }
    }
    
    return nearestIntersection;
}





//Reflexion Camera::GetMaterial(const vector<Sphere> spheres, const Ray &ray, const vector<Light> lights) const {
//
//    Intersection intersection;
//    double distanceIntersection = __DBL_MAX__;
//    Sphere nearestSphere = Sphere(Vector3(0, 0, 0), 0, Material(Color(), EMaterials::DarkFloor));
//    Vector3 pointOnSphere;
//
//    for (const Sphere& sphere : spheres)
//    {
//        intersection = Sphere::IntersectRaySphere(ray, sphere);
//
//        if (intersection.intersect && intersection.distance <= distanceIntersection)
//        {
//            distanceIntersection = intersection.distance;
//            nearestSphere = sphere;
//            pointOnSphere = intersection.pointCoordonate;
//        }
//    }
//
//    if (distanceIntersection < __DBL_MAX__)
//    {
////        for (const Light& light : lights)
////        {
//        const Light light = lights[0];
//
//            const bool canSeeLight = Light::CanSeeLight(pointOnSphere, light, spheres);
//
////        cout << "pointOnSphere : " << pointOnSphere.ToString() << endl;
//
//            if (canSeeLight)
//            {
//                Color returnedColor = Light::GetLightning(light, nearestSphere.GetMaterial().GetColor(), Vector3::GetDistance(pointOnSphere, light.GetPosition()));
//                returnedColor = returnedColor * (1 -  nearestSphere.GetMaterial().GetAlbedo());
//
////                cout << "see light" << endl;
//
//                return Reflexion(Material(returnedColor, nearestSphere.GetMaterial().GetMaterialType()), Intersection(true, distanceIntersection, pointOnSphere), nearestSphere);
//            }
//            else
//            {
//                cout << "cannot see light" << endl;
//                return Reflexion(Material(Color(), nearestSphere.GetMaterial().GetMaterialType()), Intersection(false, -1, Vector3(0)), nearestSphere);
//            }
//        }
////    }
//
//    cout << "distanceIntersection >= __DBL_MAX__" << endl;
//
//        return Reflexion(Material(Color(), nearestSphere.GetMaterial().GetMaterialType()), Intersection(false, -1, Vector3(0)), nearestSphere);
//}

//Color Camera::GetColor(const vector<Sphere> &spheres, const Ray &ray, const vector<Light> &lights, int bounce) const {
//    Intersection intersection, nearestIntersection;
//    double distanceIntersection = __DBL_MAX__;
//    Sphere nearestSphere = Sphere(Vector3(0), -1, Material(Color(0, 0, 0)));
//    //    Vector3 pointOnSphere;
//
//    for (const Sphere& sphere : spheres)
//    {
//        intersection = Sphere::IntersectRaySphere(ray, sphere);
//
//        if (intersection.intersect && intersection.distance <= distanceIntersection)
//        {
//
//            distanceIntersection = intersection.distance;
//            nearestSphere = sphere;
//            //            pointOnSphere = intersection.pointCoordonate;
//            nearestIntersection = intersection;
//        }
//    }
//
//    if (distanceIntersection < __DBL_MAX__)
//    {
//        if (nearestSphere.GetMaterial().GetAlbedo() == 1 && bounce > 0)
//        {
//            const Ray newRay = Ray::GetReflectDirection(ray, nearestIntersection, nearestSphere);
//            Color newColor = GetColor(spheres, newRay, lights, --bounce);// * (1. - nearestSphere.GetMaterial().GetAlbedo());
//            return newColor;
//
//
//            //            returnedColor = GetColor(spheres, newRay, lights, --bounce, returnedColor);
//
//            //            Color newColor;
//            //            GetColor(spheres, newRay, lights, --bounce, newColor);
//
//            //            cout << "new" << newColor.ToString() << endl;
//            //            return newColor;
//
//
//
//            //        if (nearestSphere.GetMaterial().GetAlbedo() < 1 && bounce <= m_maxBounce)
//            //        {
//            //            if (bounce == m_maxBounce)
//            //            {
//            //                for (const Light& light : lights)
//            //                {
//            //                    const bool canSeeLight = Light::CanSeeLight(goodIntersection.pointCoordonate, light, spheres);
//            //
//            //                    if (canSeeLight)
//            //                    {
//            //                        returnedColor = Light::GetLightning(light, nearestSphere.GetMaterial().GetColor(), Vector3::GetDistance(goodIntersection.pointCoordonate, light.GetPosition()));
//            //                        //                                                        returnedColor = returnedColor * nearestSphere.GetMaterial().GetAlbedo();
//            //                    }
//            //                }
//            //
//            //                const Ray newRay = Ray::GetReflectDirection(ray, goodIntersection, nearestSphere);
//            ////                cout << "returnedColor avant : " << returnedColor.ToString() << endl;
//            //                returnedColor = returnedColor + ((GetColor(spheres, newRay, lights, --bounce, returnedColor)));
//            //            }
//            //            else if (bounce > 0)
//            //            {
//            //                const Ray newRay = Ray::GetReflectDirection(ray, goodIntersection, nearestSphere);
//            //                //
//            //                //                cout << "returnedColor avant : " << returnedColor.ToString() << endl;
//            //                returnedColor = returnedColor + ((GetColor(spheres, newRay, lights, --bounce, returnedColor)));// * (1 - nearestSphere.GetMaterial().GetAlbedo()));
//            //                //                cout << "returnedColor après : " << returnedColor.ToString() << endl;
//            //            }
//            //            else
//            //            {
//            ////                cout << "returnedColor après avant : " << returnedColor.ToString() << endl;
//            ////                cout << "divisé par " << (m_maxBounce - bounce) << endl;
//            //                returnedColor = returnedColor / (m_maxBounce - bounce);
//            //                //                returnedColor.Print();
//            ////                cout << "returnedColor après après : " << returnedColor.ToString() << endl;
//            //                return returnedColor;
//            //            }
//            //        }
//            //        else if (bounce < m_maxBounce)
//            //        {
//            //          return returnedColor / (m_maxBounce - bounce);
//        }
//        //        else if (bounce < m_maxBounce)
//        //        {
//        ////            cout << "on return de la merde !" << endl;
//        ////            returnedColor = Color(255, 0,0);
//        ////            return;// Color(155, 17,92);
//        ////            return returnedColor;
//        //        }
//        else
//        {
//            Color returnedColor;
//            for (const Light& light : lights)
//            {
//                const bool canSeeLight = Light::CanSeeLight(nearestIntersection.pointCoordonate, light, spheres);
//
//                if (canSeeLight)
//                {
//                    returnedColor += Light::GetLightning(light, nearestSphere.GetMaterial().GetDiffuseColor(), Vector3::GetDistance(nearestIntersection.pointCoordonate, light.GetPosition()));
//
////                    returnedColor = nearestSphere.GetMaterial().GetDiffuseColor() * acos(Vector3::Dot(nearestSphere.GetNormal(nearestIntersection.pointCoordonate), Vector3::GetDirection(light.GetPosition(), nearestIntersection.pointCoordonate)));
//
//
////                    if (returnedColor.GetR() > 255 || returnedColor.GetG() > 255 || returnedColor.GetB() > 255)
////                    {
////                        returnedColor.Print();
////                    }
//                    //                                returnedColor = returnedColor * nearestSphere.GetMaterial().GetAlbedo();
//
//                    //                    return returnedColor;
//                }
//                else
//                {
//                    returnedColor += Color{0, 0, 0};
//                }
//            }
//            returnedColor = returnedColor;// / static_cast<double>(lights.size());
//            return returnedColor;
//        }
//
//
//    }
//    return Color(45, 255, 45);
//    //    else
//    //    {
//    //        return Color(0, 0, 0);
//    //    }
//
//    //        return Color(0, 0, 0);
//}
//
//Color Camera::SendRay(const Ray &ray, const Sphere& sphere, int nbRay, const vector<Sphere>& spheres, const vector<Light>& lights, int bounce) {
//    Intersection intersection = Sphere::IntersectRaySphere(ray, sphere);
//    Color indirectLight;
//
//    if (intersection.intersect) {
//        nbRay++;
//
//        if (nbRay < 5)
//        {
//            Vector3 newDirection;
//
//            // Si c'est un miroir
//            if (sphere.GetMaterial().GetAlbedo() == 1)
//            {
//                //On calcule la direction de réflexion
//                const Vector3 temp1 = 2 * -Vector3::Dot(ray.GetDirection(), intersection.pointCoordonate);
//                const Vector3 temp2 = temp1 * intersection.pointCoordonate;
//
//                newDirection = temp2;
//
//                ////////
//
//                indirectLight = GetIndirectLightning(intersection.pointCoordonate, newDirection, sphere, nbRay, spheres, lights, bounce) * sphere.GetMaterial().GetAlbedo();
//            }
//            else
//            {
//                return GetColor(spheres, ray, lights, 1);
//            }
//        }
//    }
//
//    return indirectLight;
//}
//
//Color Camera::GetIndirectLightning(const Vector3 &point, const Vector3 &direction, const Sphere &sphere, const int nbRay, const vector<Sphere>& spheres, const vector<Light>& lights, int bounce) {
//    const Ray mirrorRay = Ray(point, direction);
//
//    return SendRay(mirrorRay, sphere, nbRay, spheres, lights, bounce) * sphere.GetMaterial().GetAlbedo();
//}










void Camera::SetScene(Scene* scene) {
    m_scene = scene;
}
