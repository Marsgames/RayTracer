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


//TEST(IntersectFunc, IntersectWork)
//{
//    Intersection result;
//    const Rayon rayon = Rayon(Vector3{0, 0, 0}, Vector3{1, 0, 0});
//    const Sphere sphere = Sphere{Vector3{20, 0, 0}, 10};
//    Intersect(rayon, sphere, result);
//    
//    EXPECT_EQ(true, result.intersect);
//    EXPECT_EQ(10, result.distance);
//    EXPECT_EQ(10, result.point.x);
//    EXPECT_EQ(0, result.point.y);
//    EXPECT_EQ(0, result.point.z);
//}


//Light lumiere = Light{Vector3{0, 0, 0}, 1250};
Light lumiere = Light{Vector3{-230, -230, 0}, 1050};
//Light lumiere = Light{Vector3{0, 250, 250}, 1250};
//Light lumiere = Light{Vector3{0, -730, -730}, 1250};


// Lumière scene guillaume
//Light lumiere = Light{Vector3(200, 600, 150)};

Camera ecran = Camera(Vector3{0, 0, 0}, 800, 400, Vector3(0, 0, -1));

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
    
    const float facteurLumiere = 0.2;
    
    InitSpheres(spheres);
    
    // Ajouter struct Material { Difuse (renvoie la couleur du materiaux), Mirror (rebondi et renvoi le prochain point touché), light (éclaire), glass (passe au travers (rajouter un effet "fumé" pour différentier avec "rien")}
    
    // Pour le miroir, si je tombe sur un miroir je traverse et pars dans le sens opposé
    // Pour la lumière, lui donner une intensité, diviser l'intensité par la distance
    // Désactiver le facteurLumière quand on fait l'éclairage indirect
    GenerateImages(0, 1, spheres, ecran, facteurLumiere);
    
//    LaunchThreads(100, spheres, ecran, facteurLumiere);
    
    return 0;
}

//void ImageFromArray(const int& width, const int& height, const Image& pixelsArray, string& source = "/Users/Raph/Desktop/", string& nomImage = "imageSynthese.bmp")
void ImageFromArray(const Image& pixelsArray, const string source, const string nomImage)
{
    bitmap_image img(ecran.GetWidth(), ecran.GetHeight());
    
    for(int y = 0; y < ecran.GetHeight(); y++)
    {
        for(int x = 0; x < ecran.GetWidth() ; x++)
        {
            if (!((x * ecran.GetWidth() + y) < (ecran.GetWidth() * ecran.GetHeight())))
            {
                continue;
            }
            
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
    Sphere leftWall = Sphere(Vector3(-1e5 - 100.0, 360.0, 500.0), 1e5, Material(EMaterialType::DifuseType, Color{255, 255, 0}), "Jaune");
    Sphere rightWall = Sphere(Vector3(-1e5 + 1380, 360.0, 500.0), 1e5, Material(EMaterialType::DifuseType, Color{0, 0, 255}), "Bleu");
    Sphere topWall = Sphere(Vector3(640.0, -1e5 - 100, 500.0), 1e5, Material(EMaterialType::DifuseType, Color{255, 20, 147}), "Rose");
    Sphere bottomWall = Sphere(Vector3(640.0, 1e5 + 820, 500.0), 1e5, Material(EMaterialType::DifuseType, Color{255, 0, 0}), "Rouge");
    Sphere backWall = Sphere(Vector3(640.0, 360.0, 1e5 + 1100), 1e5, Material(EMaterialType::DifuseType, Color{255, 255, 255}), "Blanc");
    Sphere frontWall = Sphere(Vector3(640.0, 360.0, -1e5 - 1), 1e5, Material(EMaterialType::DifuseType, Color{255, 255, 255}), "Blanc");
    
//    spheres.push_back(Sphere(Vector3(500, 500, -150), 75, Material(EMaterials::DifuseType, Color{255, 0, 0}), "rouge")); // Rouge
//    spheres.push_back(Sphere(Vector3(850, 100, -100), 50, Material(EMaterials::DifuseType, Color{0, 255, 0}), "verte")); // Verte
//    spheres.push_back(Sphere(Vector3(100, 800, -850), 50, Material(EMaterials::DifuseType, Color{0, 0, 255}), "bleu")); // Bleu
//    spheres.push_back(Sphere(Vector3(800, 150, -250), 150, Material(EMaterials::DifuseType, Color{255, 0, 255}), "rose")); // Bleu éléctrique
//    spheres.push_back(Sphere(Vector3(600, 600, -400), 100, Material(EMaterials::DifuseType, Color{0, 255, 255}), "bleuCiel")); // Bleu ciel
//    spheres.push_back(Sphere(Vector3(500, 500, -950), 200, Material(EMaterials::DifuseType, Color{255, 255, 0}), "jaune")); // Jaune
    
    
    spheres.push_back(Sphere(Vector3(-250, 0, -100), 50, Material(EMaterialType::DifuseType, Color{0, 0, 255}), "bleu")); // Bleu
    spheres.push_back(Sphere(Vector3(0, 0, -100), 50, Material(EMaterialType::DifuseType, Color{255, 255, 255}), "blanc")); // Bleu
    spheres.push_back(Sphere(Vector3(250, 0, -100), 50, Material(EMaterialType::DifuseType, Color{255, 0, 0}), "rouge")); // Bleu
    
    
//    spheres.push_back(leftWall);
//    spheres.push_back(rightWall);
//    spheres.push_back(topWall);
//    spheres.push_back(bottomWall);
//    spheres.push_back(backWall);
//    spheres.push_back(frontWall);

    spheres.push_back(Sphere(Vector3(lumiere.GetPosition().GetX(), lumiere.GetPosition().GetY(), lumiere.GetPosition().GetZ()), 5, Material(EMaterialType::LightType, Color{255, 255, 255}), "lampe")); // blanc


//    spheres.push_back(Sphere(Vector3(lumiere.position.x, lumiere.position.y, lumiere.position.z), 5, Color{255, 255, 255}, "lampe", 0)); // blanc
}

bool CanSeeLight(const Vector3& point, const Light& light, const Scene& scene)
{
    const Vector3 dirLampe = Normalize(light.GetPosition() - point);
    const double distPL = GetDistance(point, light.GetPosition());
    
    for (const Sphere& sphere : scene)
    {
        
//        cout << "Le type de " << sphere.nom << " est : " << sphere.m_material.GetMaterial() << endl;
        
        if (EMaterialType::LightType == sphere.GetMaterial().GetMaterialType())
        {
            continue;
        }
//        cout << "--------------" << endl;
//        cout << "avant : (" << point.x << ", " << point.y << ", " << point.z << ")" << endl;
//        cout << "après : (" << (point + (dirLampe * .01)).x << ", " << (point + (dirLampe * .01)).y << ", " << (point + (dirLampe * .01)).z << ")" << endl;
        Intersection result;
        const Rayon rayon = Rayon((point + (dirLampe * .01)), dirLampe);
        Intersect(rayon, sphere, result);
        
        if (result.intersect)
        {
            const double distPI = GetDistance(point, result.point);
            
//                    cout << "lum pos : (" << light.position.x << ", " << light.position.y << ", " << light.position.z << ")" << endl;
//            cout << "distPL : " << distPL << endl;
//            cout << "distPI : " << distPI << endl;
            
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
    
//    double r = image[point.y][point.z].r * puissance;
//    double g = image[point.y][point.z].g * puissance;
//    double b = image[point.y][point.z].b * puissance;
    
    //x + ecran.GetHeight() * y
//    image[point.y * ecran.GetHeight()  + point.z].r = image[point.y * ecran.GetHeight() + point.z].r * puissance;
    
    // point : le point d'intersection sur la sphère ?
    // light la lumière
    
    
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
    lumiere.GetPosition().SetX(lumiere.GetPosition().GetX() + direction.GetX());
    lumiere.GetPosition().SetY(lumiere.GetPosition().GetY() + direction.GetY());
    lumiere.GetPosition().SetZ(lumiere.GetPosition().GetZ() + direction.GetZ());
}

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



void GenerateImages(const int firstImage, const int lastImage, Scene spheres, const Camera& ecran, const float facteurLumiere)
{
//    for (int i = 0; i < firstImage; i++)
//    {
//        MoveLight(lumiere);
//    }
    Light theLight = lumiere;
    
    theLight.GetPosition().SetY(theLight.GetPosition().GetY() + (1 * firstImage));
    
//    lumiere.position.y += 5 * firstImage;
    for (int i = firstImage; i < lastImage; i++)
    {
        Image image(ecran.GetWidth() * ecran.GetHeight(), Color{0, 0, 0});
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
                    // Rayon(Vector3 origine, Vector3 direction)
                    const Rayon rayon = Rayon(ecran.GetPosition() + Vector3(x + 0., y + 0., ecran.GetPosition().GetZ()), ecran.GetDirection());
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
        
        MoveLight(theLight, Vector3(0, 1, 0));
        spheres[6].GetOrigine() = theLight.GetPosition();
        ClearImage(image, ecran);
    }
    
}

void LaunchThreads(const int nbImages, Scene& spheres, const Camera& ecran, const float facteurLumiere)
{
    int _nbImages = nbImages;
    while (0 != _nbImages % 100)
    {
        _nbImages++;
    }

    for (int i = 0; i < (_nbImages / 25 / 4); i++)
    {
        std::thread t1(GenerateImages, i * 100 + 0, i * 100 + 25, std::ref(spheres), std::ref(ecran), facteurLumiere);
        std::thread t2(GenerateImages, i * 100 + 25, i * 100 + 50, std::ref(spheres), std::ref(ecran), facteurLumiere);
        std::thread t3(GenerateImages, i * 100 + 50, i * 100 + 75, std::ref(spheres), std::ref(ecran), facteurLumiere);
        std::thread t4(GenerateImages, i * 100 + 75, i * 100 + 100, std::ref(spheres), std::ref(ecran), facteurLumiere);
        
        t1.join();
        cout << "t1 fini" << endl;
        t2.join();
        cout << "t2 fini" << endl;
        t3.join();
        cout << "t3 fini" << endl;
        t4.join();
        cout << "t4 fini" << endl;
        
        cout << "Série " << i << " terminée" << endl;
    }
    
}





// radiance(rayon, scene) -> couleur

// intensité lumineuse sauvegardée dans l'image ^1/2.2
