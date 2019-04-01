//
//  Misc.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 31/03/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <Scene.hpp>
#include <iostream>
#include <thread>
#include <Camera.hpp>
#include <Sphere.hpp>
#include <Light.hpp>
#include <cfloat>
#include <Library/Bitmap/bitmap_image.hpp>

using std::thread;
using std::cout;
using std::endl;
using std::ref;

void Scene::LaunchThreads(const int nbImages, Camera& ecran, const Vector3& directionLight)
{
    int _nbImages = nbImages;
    while (0 != _nbImages % 50)
    {
        _nbImages++;
    }
    
    // nbImages / images par thread / nb threads
    for (int i = 0; i < (_nbImages / 5 / 10); i++)
    {
                thread t01(&Scene::GenerateImages, this, i * 50 + 00, i * 50 + 05, ref(ecran), directionLight);
                thread t02(&Scene::GenerateImages, this, i * 50 + 05, i * 50 + 10, ref(ecran), directionLight);
                thread t03(&Scene::GenerateImages, this, i * 50 + 10, i * 50 + 15, ref(ecran), directionLight);
                thread t04(&Scene::GenerateImages, this, i * 50 + 15, i * 50 + 20, ref(ecran), directionLight);
                thread t05(&Scene::GenerateImages, this, i * 50 + 20, i * 50 + 25, ref(ecran), directionLight);
        
                thread t06(&Scene::GenerateImages, this, i * 50 + 25, i * 50 + 30, ref(ecran), directionLight);
                thread t07(&Scene::GenerateImages, this, i * 50 + 30, i * 50 + 35, ref(ecran), directionLight);
                thread t08(&Scene::GenerateImages, this, i * 50 + 35, i * 50 + 40, ref(ecran), directionLight);
                thread t09(&Scene::GenerateImages, this, i * 50 + 40, i * 50 + 45, ref(ecran), directionLight);
                thread t10(&Scene::GenerateImages, this, i * 50 + 45, i * 50 + 50, ref(ecran), directionLight);
        
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
                t07.join();
                cout << "Thread 7 terminé" << endl;
                t08.join();
                cout << "Thread 8 terminé" << endl;
                t09.join();
                cout << "Thread 9 terminé" << endl;
                t10.join();
                cout << "Thread 10 terminé" << endl;
        
        cout << "Série " << i + 1 << " sur " << (_nbImages / 5 / 10) << " terminée" << endl;
    }
}

void Scene::GenerateImages(const int firstImage, const int lastImage, Camera& ecran, const Vector3& MoveLightDirection)
{
    //    if (!(MoveLightDirection == Vector3(0,0,0)))
    //    {
    //        for (Sphere& sphere : spheres)
    //        {
    //            if (EMaterialType::LightType != sphere.GetMaterial().m_materialType)
    //            {
    //                continue;
    //            }
    //
    //            for (int i = 0; i < firstImage; i++)
    //            {
    //                MoveLight(theLight, MoveLightDirection, sphere);
    //            }
    //        }
    //    }
    
    //    Image image(ecran.GetWidth() * ecran.GetHeight(), Pixel(Vector3(0, 0, 0), Color{0, 0, 0}));
    Image image = ecran.GetImage();
    
    for (int i = firstImage; i < lastImage; i++)
    {
        //        Image image(ecran.GetWidth() * ecran.GetHeight(), Color{44, 117, 255});
        
        
        for (int i = 0; i < ecran.GetHeight() * ecran.GetWidth(); i++)
        {
            // Pour un écran de 1000 * 1000
            // 0 * 0  -->  1000 * 1000
            //            const int x = i % ecran.GetWidth();
            //            const int y = i / ecran.GetWidth();
            
            //            // -500, -500  -->  500, 500
            //            const int indexX = x - ecran.GetWidth() / 2;
            //            const int indexY = y - ecran.GetHeight() / 2;
            
            // distance to intersection, to keep only the first one
            double dist = DBL_MAX;
            Sphere sphereTouchee;
            Intersection result;
            
            for (const Sphere& sphereEnTest : *m_spheres)
            {
                // Position of the center of the camera + the x & y shift
                //                    const Vector3 pointOnScreen = Vector3(indexX + .0, indexY + .0, ((- ecran.GetDirection().GetX()) * indexX) / (ecran.GetDirection().GetZ()));
                //                    pointOnScreen.Print();
                
                const Vector3 pointOnScreen = image[i].GetPosition();
                
                //                const Vector3 pointOnScreen = ecran.GetPosition() + Vector3(indexX + 0., indexY + 0., ecran.GetPosition().GetZ());
                const Vector3 dir{pointOnScreen.GetX(), pointOnScreen.GetY(), 0.};
                //                Vector3 focalDir = ecran.GetFocalDirection(dir);
                Vector3 focalDir = ecran.GetDirection();
                const Rayon rayon = Rayon(pointOnScreen, focalDir);
                //                    const Rayon rayon = Rayon(pointOnScreen, ecran.GetDirection());
                
                
                //                const Rayon rayon = Rayon(pointOnScreen, ecran.GetDirection());
                Sphere::Intersect(rayon, sphereEnTest, result);
                
                if (!result.intersect || result.distance >= dist)
                {
                    continue;
                }
                
                dist = result.distance;
                sphereTouchee = sphereEnTest;
            }
            
            if (DBL_MAX != dist)
            {
                image[i].SetColor(sphereTouchee.GetMaterial().GetColor());
                
                // Vérifier CanSeeLight <-- !!!
                if (Light::CanSeeLight(result.point, m_light, m_spheres))
                {
                    Light::SetLightning(result.point, i, m_light, image);
                }
                else
                {
                    Color col = image[i].GetColor();
                    image[i].SetColor(Color(col.GetR() * facteurLumiere, col.GetG() * facteurLumiere, col.GetB() * facteurLumiere));
                }
            }
            
            //            if (y % 10 == 0)
            //            {
            ////                const string nomImage = "01Scene" + to_string(i + 1 + y + ecran.GetWidth() / 2) + ".bmp";
            //                const string nomImage = "image" + to_string(i) + ".bmp";
            //                const string source = "/Users/Raph/Desktop/TestSynthese/";
            //                ImageFromArray(image, source, nomImage);
            //            }
        }
        
        {
            //        CreateSpheresBoxes(boxes, spheres);
            //        BoundingBox bBox = BoundingBox(boxes);
            //        bBox.source = superBBType;
            //        bBox.Print();
            //
            //        for (int y = 0; y < ecran.height; y++)
            //        {
            //            for (int z = 0; z < ecran.width; z++)
            //            {
            //                //            for (const Box& b : boxes)
            //                //            {
            //                const Rayon rayon = Rayon(ecran.position + Vector3(static_cast<int>(ecran.position.x), y, z), Vector3(1, 0, 0));
            //                if (IntersectBBox(rayon, bBox))
            //                {
            //                    if (sphereType == bBox.source)
            //                    {
            //                        // vert == chaques boxes
            //                        image[y * ecran.height + z] = Color{0, 255, 0};
            //                    }else if (boundingBoxType == bBox.source)
            //                    {
            //                        // rouge == bounding box
            //                        image[y * ecran.height + z] = Color{255, 0, 0};
            //                    }else if (superBBType == bBox.source)
            //                    {
            //                        // bleu == la boite unique
            //                        image[y * ecran.height + z] = Color{0, 0, 255};
            //                    }else
            //                    {
            //                        // jaune == on ne sait pas
            //                        image[y * ecran.height + z] = Color{0, 255, 255};
            //                    }
            //                }
            //                //            }
            //            }
            //        }
        }
        
        const string nomImage = "image" + to_string(i) + ".bmp";
        const string source = "/Users/Raph/Desktop/TestSynthese/";
        ImageFromArray(image, source, nomImage, ecran);
        
//        MoveLight(theLight, MoveLightDirection, spheres[spheres.size() - 1]);
        
//        Sphere lightSphere = m_spheres[6];
        
//        m_spheres[6].SetCenter(m_light->GetPosition());
//        &m_spheres[6].SetCenter(m_light->GetPosition());
//        *m_spheres[6].SetCenter(m_light->GetPosition());
//        **m_spheres[6].SetCenter(m_light->GetPosition());
////        m_spheres[6].GetCenter() = m_light->GetPosition();
        ClearImage(image, ecran);
    }
}

void Scene::ClearImage (Image& imageArray, const Camera& ecran)
{
    for (int i = 0; i < ecran.GetWidth() * ecran.GetHeight(); i++)
    {
        imageArray[i].SetColor(Color{0, 0, 0});
    }
}

void Scene::ImageFromArray(const Image& pixelsArray, const string source, const string nomImage, const Camera& ecran)
{
    bitmap_image img(ecran.GetWidth(), ecran.GetHeight());
    
    for (int index = 0; index < ecran.GetHeight() * ecran.GetWidth(); index++)
    {
        int x = index % ecran.GetWidth();
        int y = index / ecran.GetWidth();
        //        int index = y * ecran.GetWidth() + x;
        
        double r = pixelsArray[index].GetColor().GetR() > 255 ? 255 : pixelsArray[index].GetColor().GetR();
        double g = pixelsArray[index].GetColor().GetG() > 255 ? 255 : pixelsArray[index].GetColor().GetG();
        double b = pixelsArray[index].GetColor().GetB() > 255 ? 255 : pixelsArray[index].GetColor().GetB();
        
        if(r < 0 || g < 0 || b < 0)
        {
            cout << "color < 0 : (" << r << ", " << g << ", " << b << ")" << endl;
            exit(2);
            // EXIT CODE: 2 --> Un pixel avait une couleur < 0
        }
        
        img.set_pixel(x, y, r, g, b);
    }
    
    img.save_image(source + nomImage);
    //        img.save_image("imageSynthese.bmp");
    //    if (nomImage.find('0') != std::string::npos)
    //    {
    //        cout << "image sauvegardée dans " << source + nomImage << " !" << endl;
    //    }
}
