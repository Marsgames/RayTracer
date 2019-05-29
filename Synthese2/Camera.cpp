//
//  Camera.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <Library/Bitmap/bitmap_image.hpp>
#include <Camera.hpp>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;

void Camera::InitPixelsArray() {
    m_pixels.reserve(m_height * m_width);
    
    for (int index = 0; index < m_height * m_width; index++)
    {
        int x = index % m_width;
        int y = index / m_width;
        
        m_pixels.push_back(Pixel{Vector3{x, y, 0}, Color{255, 0, 0}});
    }
}

inline int Camera::GetWidth() const { 
    return m_width;
}

inline int Camera::GetHeight() const { 
    return m_height;
}

inline int Camera::GetFocalDist() const { 
    return m_focalDist;
}

void Camera::SetUseFocal(bool value) { 
    m_useFocal = value;
}

inline void Camera::SetFocalDist(int focalDistance) {
    m_focalDist = focalDistance;
}

void Camera::SetImageFormat(EImageFormat format) {
    m_imageFormat = format;
}

void Camera::SaveImage() {
    if (m_useFocal)
    {
        SaveImageWithFocal();
    }
    else
    {
        SaveImageWithoutFocal();
    }
}

inline void Camera::SaveImageWithFocal() {
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
    cout << "Camera::SaveImageWithFocal called" << endl;
}

inline void Camera::SaveImageWithoutFocal() {
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
    
    cout << "Camera::SaveImageWithoutFocal called" << endl;
}

Vector3 Camera::GetPosition() const {
    return m_position;
}

void Camera::SetPosition(Vector3 position) {
    m_position = position;
}

Vector3 Camera::GetDirection() const {
    return m_dir;
}

void Camera::SetDirection(Vector3 direction) {
    m_dir = direction;
}

inline void Camera::SavePPM() {
    ofstream myfile;
    myfile.open (source + nomImage + ".ppm");
    myfile << "P3" << endl;
    myfile << "# " << nomImage << ".ppm" << endl;
    myfile << m_width << " " << m_height << endl;
    myfile << "255" << endl;
    
    for (int index = 0; index < m_height * m_width; index++)
    {
            double r = m_pixels[index].GetColorR() > 255 ? 255 : m_pixels[index].GetColorR();
            double g = m_pixels[index].GetColorG() > 255 ? 255 : m_pixels[index].GetColorG();
            double b = m_pixels[index].GetColorB() > 255 ? 255 : m_pixels[index].GetColorB();
            
            if(r < 0 || g < 0 || b < 0)
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
    
    cout << "Camera::SavePPM called" << endl;
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
    
    img.save_image(source + nomImage + ".bmp");
    //        img.save_image("imageSynthese.bmp");
    //    if (nomImage.find('0') != std::string::npos)
    //    {
    //        cout << "image sauvegardée dans " << source + nomImage << " !" << endl;
    //    }
}















