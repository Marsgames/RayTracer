//
//  main.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#include "Library/Bitmap/bitmap_image.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "main.hpp"
#include <math.h>
#include "Rayon.hpp"
#include "Vector3.hpp"
#include <gtest/gtest.h>
#include "gtests/UnitsTests.hpp"
#include "Sphere.hpp"
#include "Color.hpp"
#include "Box.hpp"
#include "BoundingBox.hpp"
#include <iostream>
#include <thread>
#include "Material.hpp"

Light lumiere = Light{Vector3{0, 0, 0}, 1000};
//Camera ecran = Camera(Vector3{500, 500, 0}, 1000, 1000, Vector3(0, 0, -1), 1000);

//Light lumiere = Light{Vector3(0, -450, -10), 1000};
Camera ecran = Camera(Vector3(0, 0, 0), 1280, 720, Vector3(0, 0, -1), 1000);

//Light lumiere = Light{Vector3{10, 10, -10}, 1250};
//Light lumiere = Light{Vector3{-230, -230, 0}, 1050};
//Light lumiere = Light{Vector3{0, 250, 250}, 1250};
//Light lumiere = Light{Vector3{0, -730, -730}, 1250};


//Camera ecran = Camera(Vector3{500, 500, 0}, 1000, 1000, Vector3(0, 0, -1));
const float facteurLumiere = .2;


// Lampe pour la scène avec les murs
//    Light lumiere = Light{Vector3{-1000, 500, 500}, 1250};

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RunTests();
//    return 0;
//    return RUN_ALL_TESTS();
    
    
//    const Camera ecran = Camera(Vector3{0, 0, 0}, 1000, 1000);

    // Ajouter un écran (tableau 2D de pixels) (origine 0, 0->10, 0->-10)
    // ajouter une sphère (origine 0, rayon 10)
    
    // pour chaque pixels de l'ecran on fait partir un rayon
    // on récupère l'intersection et on crée une image à partir du résultat
    
    Scene spheres;
    Boxes boxes;
    

    InitSpheres(spheres);
    
    // Ajouter struct Material { Difuse (renvoie la couleur du materiaux), Mirror (rebondi et renvoi le prochain point touché), light (éclaire), glass (passe au travers (rajouter un effet "fumé" pour différentier avec "rien")}
    
    // Pour le miroir, si je tombe sur un miroir je traverse et pars dans le sens opposé
    // Pour la lumière, lui donner une intensité, diviser l'intensité par la distance
    // Désactiver le facteurLumière quand on fait l'éclairage indirect
    
    GenerateImages(0, 1, spheres, ecran, Vector3(1, 0, 0));
//    LaunchThreads(50, spheres, ecran, Vector3(10, 0, 0));
    
    return 0;
}

//void ImageFromArray(const int& width, const int& height, const Image& pixelsArray, string& source = "/Users/Raph/Desktop/", string& nomImage = "imageSynthese.bmp")
void ImageFromArray(const Image& pixelsArray, const string source, const string nomImage)
{
    bitmap_image img(ecran.GetWidth(), ecran.GetHeight());
    
    for(int y = 0; y < ecran.GetHeight(); y++)
    {
        for(int x = 0; x < ecran.GetWidth(); x++)
        {
            int index = y * ecran.GetWidth() + x;

            double r = pixelsArray[index].GetR() > 255 ? 255 : pixelsArray[index].GetR();
            double g = pixelsArray[index].GetG() > 255 ? 255 : pixelsArray[index].GetG();
            double b = pixelsArray[index].GetB() > 255 ? 255 : pixelsArray[index].GetB();
            
            if(r < 0 || g < 0 || b < 0)
            {
                cout << "color < 0 : (" << r << ", " << g << ", " << b << ")" << endl;
                exit(2);
                // EXIT CODE: 2 --> Un pixel avait une couleur < 0
            }
            
            img.set_pixel(x, y, r, g, b);
        }
    }
    
    img.save_image(source + nomImage);
//        img.save_image("imageSynthese.bmp");
//    if (nomImage.find('0') != std::string::npos)
//    {
//        cout << "image sauvegardée dans " << source + nomImage << " !" << endl;
//    }
}

void InitSpheres(Scene& spheres)
{
    Sphere leftWall = Sphere(Vector3(-1e5 - 700., 0., -00.), 1e5, Material(EMaterialType::DifuseType, Vector3(0.2f, 0.8f, 0.2f)), "Vert");
    Sphere rightWall = Sphere(Vector3(1e5 + 700., 0., -00.), 1e5, Material(EMaterialType::DifuseType, Vector3(0.2f, 0.8f, 0.8f)), "Bleu");
    Sphere topWall = Sphere(Vector3(0., -1e5 - 600., -00.), 1e5, Material(EMaterialType::DifuseType, Vector3(0.8f, 0.2f, 0.8f)), "Rose");
    Sphere bottomWall = Sphere(Vector3(0., 1e5 + 600., -00.), 1e5, Material(EMaterialType::DifuseType, Vector3(0.9f, 0.9f, 0.9f)), "Blanc");
    Sphere backWall = Sphere(Vector3(0., 0., 1e5 + 1500), 1e5, Material(EMaterialType::DifuseType, Vector3(0.8f, 0.2f, 0.2f)), "Rouge");
    Sphere frontWall = Sphere(Vector3(0., 0., -1e5 - 1500), 1e5, Material(EMaterialType::DifuseType, Vector3(0.8f, 0.8f, 0.2f)), "Jaune");
    
    
    
//    spheres.push_back(Sphere(Vector3(500 - 500, 500 - 500, -150), 75, Material(DifuseType, Color{255, 0, 0}), "rouge")); // Rouge
//    spheres.push_back(Sphere(Vector3(850 - 500, 100 - 500, -100), 50, Material(DifuseType, Color{0, 255, 0}), "verte")); // Verte
//    spheres.push_back(Sphere(Vector3(100 - 500, 800 - 500, -850), 50, Material(DifuseType, Color{0, 0, 255}), "bleu")); // Bleu
//    spheres.push_back(Sphere(Vector3(800 - 500, 150 - 500, -250), 150, Material(DifuseType, Color{255, 0, 255}), "rose")); // Bleu éléctrique
//    spheres.push_back(Sphere(Vector3(600 - 500, 600 - 500, -400), 100, Material(DifuseType, Color{0, 255, 255}), "bleuCiel")); // Bleu ciel
//    spheres.push_back(Sphere(Vector3(500 - 500, 500 - 500, -950), 200, Material(DifuseType, Color{255, 255, 0}), "jaune")); // Jaune
    
    
    spheres.push_back(Sphere(Vector3(-250, 0, -100), 50, Material(EMaterialType::DifuseType, Color{0, 0, 255}), "bleu")); // Bleu
    spheres.push_back(Sphere(Vector3(0, 0, -100), 50, Material(EMaterialType::DifuseType, Color{255, 255, 255}), "blanc")); // Bleu
    spheres.push_back(Sphere(Vector3(250, 0, -100), 50, Material(EMaterialType::DifuseType, Color{255, 0, 0}), "rouge")); // Bleu
//
    spheres.push_back(leftWall);
    spheres.push_back(rightWall);
    spheres.push_back(topWall);
    spheres.push_back(bottomWall);
    spheres.push_back(frontWall);
    spheres.push_back(backWall);
    
    spheres.push_back(Sphere(Vector3(lumiere.GetPosition().GetX(), lumiere.GetPosition().GetY(), lumiere.GetPosition().GetZ()), 5, Material(EMaterialType::LightType, Color{255, 0, 0}), "lampe")); // blanc


//    spheres.push_back(Sphere(Vector3(lumiere.position.x, lumiere.position.y, lumiere.position.z), 5, Color{255, 255, 255}, "lampe", 0)); // blanc
}

bool CanSeeLight(const Vector3& point, const Light& light, const Scene& scene)
{
    const Vector3 dirLampe = (light.GetPosition() - point).Normalize();
    const double distPL = GetDistance(point, light.GetPosition());
    
    for (const Sphere& sphere : scene)
    {
        
        if (EMaterialType::LightType == sphere.GetMaterial().m_materialType)
        {
            continue;
        }

        Intersection result;
        
        const Rayon rayon = Rayon((point + (dirLampe * .01)), dirLampe);
//        const Rayon rayon = Rayon(point, dirLampe);
        Intersect(rayon, sphere, result);
        
        if (result.intersect)
        {
            const double distPI = GetDistance(point, result.point);
            
            // Si l'objet est devant la lumière return false.
            if (distPI < distPL)
            {
                return false;
            }
        }
    }
    
    // Si l'objet est derrière la lumière return true.
    return true;
}

void SetLightning(const Vector3& point, const int index, const Light& light,  Image& image)
{
    const double puissance = light.GetPuissance() * (1 / (abs((light.GetPosition().GetX() - point.GetX()) + (light.GetPosition().GetY() - point.GetY()) + (light.GetPosition().GetZ() - point.GetZ()))));
    
    image[index].SetR(image[index].GetR() * puissance);
    image[index].SetG(image[index].GetG() * puissance);
    image[index].SetB(image[index].GetB() * puissance);
}

int RunTests()
{
    return RUN_ALL_TESTS();
}

void MoveLight (Light& lumiere, const Vector3 direction)
{
    lumiere.SetPosition(lumiere.GetPosition() + direction);
}

//void MoveLight (Light& lumiere, const Vector3 direction, Scene spheres)
//{
//    lumiere.SetPosition(lumiere.GetPosition() + direction);
//    spheres[0].SetOrigine(spheres[0].GetOrigine() + Vector3(1, 0, 0));
//}

void ClearImage (Image& imageArray, const Camera& ecran)
{
    for (int i = 0; i < ecran.GetHeight(); i++)
    {
        for (int j = 0; j < ecran.GetWidth(); j++)
        {
            imageArray[i * j].SetR(0);
            imageArray[i * j].SetG(0);
            imageArray[i * j].SetB(0);
        }
    }
}

void GenerateImages(const int firstImage, const int lastImage, Scene spheres, const Camera& ecran, const Vector3& MoveLightDirection)
{
    Light theLight = lumiere;
    
    for (int i = 0; i < firstImage; i++)
    {
        MoveLight(theLight, MoveLightDirection);
    }
//    theLight.GetPosition().SetY(theLight.GetPosition().GetY() + (1 * firstImage));
    
//    lumiere.position.y += 5 * firstImage;
    for (int i = firstImage; i < lastImage; i++)
    {
        Image image(ecran.GetWidth() * ecran.GetHeight(), Color{0, 0, 0});
//        Image image(ecran.GetWidth() * ecran.GetHeight(), Color{44, 117, 255});
        for (int y = -ecran.GetHeight() / 2; y < ecran.GetHeight() / 2; y++)
        {
            for (int x = -ecran.GetWidth() / 2; x < ecran.GetWidth() / 2; x++)
            {
                // distance to intersection, to keep only the first one
                double dist = INT_MAX;
                Sphere sphereTouchee;
                Intersection result;
                
                for (const Sphere& sphereEnTest : spheres)
                {
                    // Position of the center of the camera + the x & y shift
                    const Vector3 pointOnScreen = ecran.GetPosition() + Vector3(x + 0., y + 0., ecran.GetPosition().GetZ());
                    const Rayon rayon = Rayon(pointOnScreen, ecran.GetFocalDirection(Vector3(x, y)));
                    Intersect(rayon, sphereEnTest, result);
                    
                    if (!result.intersect || result.distance >= dist)
                    {
                        continue;
                    }
                    
                        dist = result.distance;
                        sphereTouchee = sphereEnTest;
                }
                
                if (INT_MAX != dist)
                {
//                    cout << "GetColor r : " << sphere.m_material.GetColor().ToString() << endl;

//                    image[y * ecran.GetHeight() + z] = sphere.m_material.GetColor();
                    
                    const int indexY = y + ecran.GetHeight() / 2;
                    const int indexX = x + ecran.GetWidth() / 2;
                    const int index = indexY * ecran.GetWidth() + indexX;
//                    cout << "-ecran.GetHeight() / 2 : " << -ecran.GetHeight() / 2 << endl;
//                    cout << "y : "  << y << " | z : " << z << endl;
//                    cout << "indexY : " << indexY << " | indexZ : " << indexZ << endl;
//                    cout << "index : " << (indexY * ecran.GetHeight() + indexZ) << endl;
//                    cout << "indexMax : " << ecran.GetHeight() * ecran.GetWidth() << endl;
//                    cout << "index <= indexMax : " << ((indexY * ecran.GetHeight() + indexZ) <= ecran.GetHeight() * ecran.GetWidth()) << endl << endl;
                    
                    
//                    cout << "1 : " << indexY * ecran.GetHeight() + indexZ << endl;
//                    cout << "2 : " << y * ecran.GetHeight() + z << endl << endl;
                    
                    image[index] = sphereTouchee.GetMaterial().GetColor();
                    
                    if (CanSeeLight(result.point, theLight, spheres))
                    {
                        SetLightning(result.point, index, theLight, image);
                    }
                    else
                    {
//                        cout << "result.point : " << result.point.ToString() << " | theLight : " << theLight.position.ToString() << endl;
//                        image[y * ecran.GetHeight() + z].r = image[y * ecran.GetHeight() + z].r * facteurLumiere;
//                        image[y * ecran.GetHeight() + z].g = image[y * ecran.GetHeight() + z].g * facteurLumiere;
//                        image[y * ecran.GetHeight() + z].b = image[y * ecran.GetHeight() + z].b * facteurLumiere;
                        image[index].SetR(image[index].GetR() * facteurLumiere);
                        image[index].SetG(image[index].GetG() * facteurLumiere);
                        image[index].SetB(image[index].GetB() * facteurLumiere);
                    }
                    
                }
                
            }
        }

        
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
        
        
        
        
        const string nomImage = "image" + to_string(i) + ".bmp";
        const string source = "/Users/Raph/Desktop/TestSynthese/";
        ImageFromArray(image, source, nomImage);
        //        ImageFromArray(ecran.height, ecran.width, image, source, nomImage);
        
//        cout << "position light : " << theLight.position.y << endl;
        
        MoveLight(theLight, MoveLightDirection);
        spheres[6].GetOrigine() = theLight.GetPosition();
        ClearImage(image, ecran);
    }
    
}

void LaunchThreads(const int nbImages, Scene& spheres, const Camera& ecran, const Vector3& directionLight)
{
    int _nbImages = nbImages;
    while (0 != _nbImages % 50)
    {
        _nbImages++;
    }
    
    // nbImages / images par thread / nb threads
    for (int i = 0; i < (_nbImages / 5 / 10); i++)
    {
        std::thread t1(GenerateImages, i * 50 + 0, i * 50 + 5, std::ref(spheres), std::ref(ecran), directionLight);
        std::thread t2(GenerateImages, i * 50 + 5, i * 50 + 10, std::ref(spheres), std::ref(ecran), directionLight);
        std::thread t3(GenerateImages, i * 50 + 10, i * 50 + 15, std::ref(spheres), std::ref(ecran), directionLight);
        std::thread t4(GenerateImages, i * 50 + 15, i * 50 + 20, std::ref(spheres), std::ref(ecran), directionLight);
        std::thread t5(GenerateImages, i * 50 + 20, i * 50 + 25, std::ref(spheres), std::ref(ecran), directionLight);
        
        std::thread t6(GenerateImages, i * 50 + 25, i * 50 + 30, std::ref(spheres), std::ref(ecran), directionLight);
        std::thread t7(GenerateImages, i * 50 + 30, i * 50 + 35, std::ref(spheres), std::ref(ecran), directionLight);
        std::thread t8(GenerateImages, i * 50 + 35, i * 50 + 40, std::ref(spheres), std::ref(ecran), directionLight);
        std::thread t9(GenerateImages, i * 50 + 40, i * 50 + 45, std::ref(spheres), std::ref(ecran), directionLight);
        std::thread t10(GenerateImages, i * 50 + 45, i * 50 + 50, std::ref(spheres), std::ref(ecran), directionLight);
        
        t1.join();
        cout << "Thread 1 terminé" << endl;
        t2.join();
        cout << "Thread 2 terminé" << endl;
t3.join();
        cout << "Thread 3 terminé" << endl;
t4.join();
        cout << "Thread 4 terminé" << endl;
t5.join();
        cout << "Thread 5 terminé" << endl;

        t6.join();
        cout << "Thread 6 terminé" << endl;
t7.join();
        cout << "Thread 7 terminé" << endl;
t8.join();
        cout << "Thread 8 terminé" << endl;
t9.join();
        cout << "Thread 9 terminé" << endl;
t10.join();
        cout << "Thread 10 terminé" << endl;

        cout << "Série " << i + 1 << " sur " << (_nbImages / 5 / 10) << " terminée" << endl;
    }
    
}





// radiance(rayon, scene) -> couleur

// intensité lumineuse sauvegardée dans l'image ^1/2.2
