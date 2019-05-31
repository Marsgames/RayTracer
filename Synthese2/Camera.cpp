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
    
    /* // decommenter ça pour refaire la rotation de camera
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
     */
    
    
    
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
        
        /* // Décommenter ici pour refaire la rotation de caméra
         Vector3 newPos = Vector3{cos(thetaSigned) * actualPos.GetX() + sin(thetaSigned) * 1, actualPos.GetY(), -sin(thetaSigned) * actualPos.GetX() + cos(thetaSigned) * 1};
         
         newPos.SetX(newPos.GetX() + m_position.GetX());
         newPos.SetY(newPos.GetY() + m_position.GetY());
         newPos.SetZ(newPos.GetZ() + m_position.GetZ());
         
         m_pixels.push_back(Pixel(newPos, defaultColor));
         */
        
        m_pixels.push_back(Pixel(actualPos, defaultColor));
        
        //        pointsFile << newPos.ToString() << "|";
        //        directionsFile << m_direction.ToString() << "|";
    }
    
    //    pointsFile.close();
    //    directionsFile.close();
}

//int Camera::GetWidth() const {
//    return m_width;
//}
//
//int Camera::GetHeight() const {
//    return m_height;
//}

//int Camera::GetFocalDist() const {
//    return m_focalDist;
//}

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

//Vector3 Camera::GetPosition() const {
//    return m_position;
//}

void Camera::SetPosition(Vector3 position) {
    m_position = position;
}

//Vector3 Camera::GetDirection() const {
//    return m_direction;
//}

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
        
        if(r < 0 || g < 0 || b < 0)
        {
            cout << "color < 0 : (" << r << ", " << g << ", " << b << ")" << endl;
            exit(2);
            // EXIT CODE: 2 --> Un pixel avait une couleur < 0
        }
        
        img.set_pixel(x, y, r, g, b);
    }
    
    img.save_image(m_source + m_name + ".bmp");
    //        img.save_image("imageSynthese.bmp");
    //    if (nomImage.find('0') != std::string::npos)
    //    {
    //        cout << "image sauvegardée dans " << source + nomImage << " !" << endl;
    //    }
}

void Camera::DrawImage(const vector<Sphere> &spheres, const vector<Light>& lights) {
    
    const Vector3 rayDirection = GetRayDirection();
    Ray ray = Ray(Vector3{0, 0, 0}, rayDirection);
    double distance = __DBL_MAX__;
    Color sphereColor = Color(0, 0, 0);
    Vector3 pointOnSphere = Vector3(0, 0, 0);
    Pixel pixel = Pixel();
    
    for (int index = 0; index < m_height * m_width; index++)
    {
        pixel = m_pixels[index];
        
        ray.SetOrigin(m_pixels[index].GetPosition());
        if (m_useFocal)
        {
            ray.SetDirection(GetRayDirection(pixel.GetPosition()));
        }
        
        for (Sphere sphere : spheres)
        {
            Intersection intersection = Sphere::IntersectRaySphere(ray, sphere);
            
            if (intersection.intersect && intersection.distance <= distance)
            {
                distance = intersection.distance;
                sphereColor = sphere.GetColor();
                pointOnSphere = intersection.pointCoordonate;
            }
        }
        
        if (distance < __DBL_MAX__)
        {
            for (const Light& light : lights)
            {
                bool canSeeLight = Sphere::CanSeeLight(pixel.GetPosition(), light, spheres);
                //                sphereColor.Print();
                
                if (canSeeLight)
                {
                    m_pixels[index].SetColor(Light::GetLightning(light, sphereColor, Vector3::GetDistance(pointOnSphere, light.GetPosition())));
                }
                else
                {
                    m_pixels[index].SetColor(Color{255, 0, 255} * 0.3f);
                    //                    m_pixels[index].SetColor(sphereColor * 0.2f);
                }
            }
        }
        distance = __DBL_MAX__;
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
