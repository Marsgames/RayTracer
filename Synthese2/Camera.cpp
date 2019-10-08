//
//  Camera.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <Camera.hpp>
#include <fstream>
#include <iostream>
#include <Library/Bitmap/bitmap_image.hpp>
#include <Light.hpp>
#include <random>
#include <thread>
#include <Toolbox.hpp>
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
    
    #pragma omp parallel for
    for (int index = 0; index < m_height * m_width; index++)
    {
        // Pour un écran de 1000 * 1000
        // 0 * 0  -->  1000 * 1000
        //const int x = index % m_width;
        //const int y = index / m_width;
        
        // -500, -500  -->  500, 500
        const int indexX = (index % m_width - m_width / 2);// + m_origin.GetX();
        const int indexY = (index / m_width - m_height / 2);// + m_origin.GetY();
        
        const Vector3 actualPos {indexX * 1., indexY * 1., m_position.GetZ()};
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
//    ofstream myfile;
//    myfile.open (m_source + m_name + ".ppm");
//    myfile << "P3" << endl;
//    myfile << "# " << m_name << ".ppm" << endl;
//    myfile << m_width << " " << m_height << endl;
//    myfile << "255" << endl;
//    
//    for (int index = 0; index < m_height * m_width; index++)
//    {
//        double r = m_pixels[index].GetColorR() > 255 ? 255 : m_pixels[index].GetColorR();
//        double g = m_pixels[index].GetColorG() > 255 ? 255 : m_pixels[index].GetColorG();
//        double b = m_pixels[index].GetColorB() > 255 ? 255 : m_pixels[index].GetColorB();
//        
//        if (r < 0 || g < 0 || b < 0)
//        {
//            cout << "color < 0 : (" << r << ", " << g << ", " << b << ")" << endl;
//            myfile.close();
//            exit(2);
//            // EXIT CODE: 2 --> Un pixel avait une couleur < 0
//        }
//        
//        myfile << r << " " << g << " " << b << " ";
//        //        }
//        myfile << endl;
//    }
//    
//    myfile.close();
}

inline void Camera::SaveBMP() {
    bitmap_image img(m_width, m_height);
    
#pragma omp parallel for
    for (int index = 0; index < m_height * m_width; index++)
    {
        const int x = index % m_width;
        const int y = index / m_width;
        
//        double r = m_pixels[index].GetColorR() * 255;
//        r = r > 255 ? 255 : r;
//
//        double g = m_pixels[index].GetColorG() * 255;
//        g = g > 255 ? 255 : g;
//
//        double b = m_pixels[index].GetColorB() * 255;
//        b = b > 255 ? 255 : b;
        
        double r = pow(m_pixels[index].GetColorR(), (1/2.2));
        r = r > 1 ? 1 : r;
        r *= 255;
        
        double g = pow(m_pixels[index].GetColorG(), (1/2.2));
        g = g > 1 ? 1 : g;
        g *= 255;
        
        double b = pow(m_pixels[index].GetColorB(), (1/2.2));
        b = b > 1 ? 1 : b;
        b *= 255;
        
        
        
        
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
        
        img.set_pixel(x, y, static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b));
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
//
//    if (nullptr == m_scene)
//    {
//        exit(4); // m_scene n'est pas set !
//    }
//
//    const vector<Sphere> spheres = m_scene->GetSpheres();
//    const vector<Light> lights = m_scene->GetLights();
//
//    const Vector3 rayDirection = GetRayDirection();
//    Ray ray = Ray(Vector3{0, 0, 0}, rayDirection);
//    // double distance = __DBL_MAX__;
//    // Material sphereMaterial = Material(Color(0, 0, 0), EMaterials::DarkFloor);
//    // Vector3 pointOnSphere = Vector3(0, 0, 0);
//
//    Color pixelColor = Color(1, 0, 1);
//
//    const int sampling = 64;
//
//    for (int i = 0; i < sampling; i++)
//    {
//        cout << "pass nb " << i << endl;
//        #pragma omp parallel for
//        for (Pixel& pixel : m_pixels)
//        {
//            ray.SetOrigin(pixel.GetPosition());
//            if (m_useFocal)
//            {
//                ray.SetDirection(GetRayDirection(pixel.GetPosition()));
//            }
//
//            ray.SetDirection(Toolbox::GetRandomDirectionInAngle(ray.GetDirection(), 1));
//
//            if (pixel.index % 100000 == 0)
//            cout << "index : " << pixel.index << endl;
//
//
//
//
//            Intersection intersection = GetNearestIntersection(ray);
//
//                pixelColor += GetColor(intersection, ray);
//
//
//
//            pixel.SetColor(pixelColor);
//
//
//
//            if (pixel.index % 1000000 == 0)
//            {
//                SaveImage();
//            }
//        }
//    }
//
//    for(Pixel& pixel : m_pixels)
//    {
//        pixel.SetColor(pixel.GetColor() / sampling);
//    }
//
//    SaveImage();
//
////    #pragma omp parallel for
////    for (Pixel& pixel : m_pixels)
////    {
////        ray.SetOrigin(pixel.GetPosition());
////        if (m_useFocal)
////        {
////            ray.SetDirection(GetRayDirection(pixel.GetPosition()));
////        }
////
////        if (pixel.index % 100000 == 0)
////        cout << "index : " << pixel.index << endl;
////
////
////
////
////        Intersection intersection = GetNearestIntersection(ray);
////
////        for (int i = 1; i < 32; i++)
////        {
////            pixelColor += GetColor(intersection, ray);
////        }
////        pixelColor = pixelColor / 32;
////
////
////
////        pixel.SetColor(pixelColor);
////
////
////
////        if (pixel.index % 1000000 == 0)
////        {
////            SaveImage();
////        }
////    }
}

void Camera::DrawImageWithThread() {
    
    if (nullptr == m_scene)
    {
        exit(4); // m_scene n'est pas set !
    }
    
    const vector<Sphere> spheres = m_scene->GetSpheres();
    const vector<Light> lights = m_scene->GetLights();
    
    const Vector3 rayDirection = GetRayDirection();
    Ray ray = Ray(Vector3{0, 0, 0}, rayDirection);
    
//    Color pixelColor = Color(100, 100, 100);
    
    const unsigned long diviseur = m_pixels.capacity() / 5;
    const int reste = m_pixels.capacity() % 5;
    
    Pixel p1;
    Pixel p2;
    Pixel p3;
    Pixel p4;
    Pixel p5;
    Pixel pReste;
    
    std::thread t01(&Camera::GeneratePartImage, this, 0, (int)diviseur, ray);
    std::thread t02(&Camera::GeneratePartImage, this, (int)diviseur, (int)diviseur * 2, ray);
    std::thread t03(&Camera::GeneratePartImage, this, (int)diviseur * 2, (int)diviseur * 3, ray);
    std::thread t04(&Camera::GeneratePartImage, this, (int)diviseur * 3, (int)diviseur * 4, ray);
    std::thread t05(&Camera::GeneratePartImage, this, (int)diviseur * 4, (int)diviseur * 5, ray);
    std::thread t06(&Camera::GeneratePartImage, this, (int)diviseur * 5, (int)diviseur * 5 + reste, ray);
    
    t01.join();
    cout << "Thread 1 terminé" << endl;
    t02.join();
    cout << "Thread 2 terminé" << endl;
    t03.join();
    cout << "Thread 3 terminé" << endl;
    t04.join();
    cout << "Thread 4 terminé" << endl;
    t05.join();
    cout << "Thread 5 terminé" << endl;
    t06.join();
    cout << "Thread 6 terminé" << endl;
}

void Camera::GeneratePartImage(const int departure, const int arrival, Ray ray)
{
    const int sampling = 2;

    if (sampling <= 0)
    {
        // EXIT CODE: 5 --> Le sampling ne peut être inférieur à 1
        exit(5);
    }

    
    Pixel p;
    Intersection intersection;
    Color finalColor;
    Ray initialRay = ray;
    
    
    for (int i = departure; i < arrival; i++)
    {
        p = m_pixels[i];
        finalColor = Color(0, 0, 0);

        ray.SetOrigin(p.GetPosition());
        if (m_useFocal)
        {
            ray.SetDirection(GetRayDirection(p.GetPosition()));
        }

        if (p.index % 100000 == 0)
//        if (p.index % 10000 == 0)
        {
            cout << "index : " << p.index << endl;
        }
        initialRay = ray;
        intersection = GetNearestIntersection(ray);
        
        for (int _ = 0; _ < sampling; _++)
        {
            if (sampling > 1)
            {
                ray.SetDirection(Toolbox::GetRandomDirectionInAngle(initialRay.GetDirection(), 1));
                intersection = GetNearestIntersection(ray);
            }
            
            finalColor += GetColor(intersection, ray);
        }
        finalColor = finalColor / sampling;
        
        
        m_pixels[i].SetColor(finalColor);

        if (p.index % 1000000 == 0)
//        if (p.index % 25000 == 0)
        {
            SaveImage();
        }
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

Color Camera::GetColor(const Intersection& intersection, const Ray& ray) const {
    // Comment stopper de manière "propre" l'effet infini ?
//    Color returnedColor = GetColor(intersection, ray, 1000);
    Color returnedColor = GetColor(intersection, ray, 1000);

    return returnedColor;
}

Color Camera::GetColor(const Intersection& intersection, const Ray& ray, int remainingBounce) const {
    Color finalColor;
    
    // Si c'est un miroir
    if (1 == intersection.touchedSphere.GetMaterial().GetAlbedo())
    {
        if (remainingBounce >= 0)
        {
            const Ray reflectionDirection = Ray::GetReflectDirection(ray, intersection, intersection.touchedSphere);
            const Intersection reflectionIntersection = GetNearestIntersection(reflectionDirection);
            
            remainingBounce--;
            
            finalColor = GetColor(reflectionIntersection, reflectionDirection, remainingBounce);
            return finalColor;
        }
        
        finalColor = Color(1, 1, 0);
//        return finalColor;
    }
    else if (intersection.touchedSphere.GetMaterial().GetAlbedo() > 0)// Si ce n'est pas un miroir
    {
        finalColor += GetLighting(intersection) * (1 -  intersection.touchedSphere.GetMaterial().GetAlbedo());
        
        if (remainingBounce >= 0)
        {
            const Ray reflectionDirection = Ray::GetReflectDirection(ray, intersection, intersection.touchedSphere);
            const Intersection reflectionIntersection = GetNearestIntersection(reflectionDirection);
            
            remainingBounce--;
            
            finalColor += (GetColor(reflectionIntersection, reflectionDirection, remainingBounce)) * (intersection.touchedSphere.GetMaterial().GetAlbedo());
        }
        
//        finalColor = Color(1, 1, 0);
        
    }
    else
    {
        finalColor += GetLighting(intersection);
        return finalColor;
    }
    
    return finalColor;
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

//double Camera::GetRandomDouble(double min, double max) const {
//    return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
//}



void Camera::SetScene(Scene* scene) {
    m_scene = scene;
}

Color Camera::GetLighting(const Intersection& intersection, int remainingBounces) const
{
//    int lightsVisible = 0;
    Color finalColor;
    
    bool canSeeLight;
    
    const int nbSurfacicLights = 1;
    Light surfacicLight = Light(Vector3(), 0);
    
    if (remainingBounces > 0)
    {
    for (const Light& light : m_scene->GetLights())
    {
//        cout << "-----------" << endl;

        for (int i = 0; i < nbSurfacicLights; i++)
        {
            surfacicLight = Light(Toolbox::GetRandomPointOnSphere(Sphere(light.GetPosition(), 10)), light.GetPower() / nbSurfacicLights, light.GetMaterial());
            
//            surfacicLight.GetPosition().Print();
            
            canSeeLight = Toolbox::CanSeeLight(intersection.pointCoordonate, surfacicLight, m_scene->GetSpheres());
            
            if (canSeeLight)
            {
                finalColor = finalColor +  GetDirectLighting(surfacicLight, intersection);
//                lightsVisible += 1;
            }
//            else
//            {
////            lightsVisible += 1; // TODO: supprimer quand on rajoute la lumière indirecte
//            
//
//                finalColor = finalColor + (GetIndirectLighting(intersection, remainingBounces));
////                lightsVisible += 1;
//            }
        }
    }
    }
    
    return finalColor;
//    return finalColor / 2;
}


Color Camera::GetDirectLighting(const Light& light, const Intersection &intersection, const float distanceToAdd) const {
            return Light::GetLighting(light, intersection, distanceToAdd);
}

Color Camera::GetIndirectLighting(const Intersection &intersection, int remainingBounces) const {
    Color finalColor;
    
remainingBounces--;
    
    const Vector3 randomDir = Toolbox::GetRandomDirectionOnHemisphere(intersection.touchedSphere.GetNormal(intersection.pointCoordonate)).Normalize();
    
        const Ray ray = Ray(intersection.pointCoordonate + (randomDir * 1.5), randomDir);
    const Intersection inter = GetNearestIntersection(ray);

//    while (finalColor == Color(0, 0, 0))
//    {
        finalColor = GetLighting(inter, remainingBounces);
//    }
    
    
//    if (finalColor == Color(0, 0, 0))
//    {
//        cout << "----------" << endl;
//        cout << "normale : " << intersection.touchedSphere.GetNormal(intersection.pointCoordonate).ToString() << endl;
//        cout << "randomDir : " << randomDir.ToString() << endl;
//    }
    
//    const Intersection reflectionIntersection = GetNearestIntersection(reflectionDirection);
    
    
//    cout << "remainingbounces : " << remainingBounces << endl;
    return finalColor;
}
