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
Light lumiere = Light{Vector3{0, 0, 0}, 1050};
//Light lumiere = Light{Vector3{0, 250, 250}, 1250};

// Lampe pour la scène avec les murs
//    Light lumiere = Light{Vector3{-1000, 500, 500}, 1250};

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RunTests();
//    return 0;
//    return RUN_ALL_TESTS();
    
    
    const Camera ecran = Camera(Vector3{0, 0, 0}, 1000, 1000);
    
    // Ajouter un écran (tableau 2D de pixels) (origine 0, 0->10, 0->-10)
    // ajouter une sphère (origine 0, rayon 10)
    
    // pour chaque pixels de l'ecran on fait partir un rayon
    // on récupère l'intersection et on crée une image à partir du résultat
    
    Scene spheres;
    Boxes boxes;
    

    const float facteurLumiere = 0.2;
    
    // Pour le miroir, si je tombe sur un miroir je traverse et pars dans le sens opposé
    // Pour la lumière, lui donner une intensité, diviser l'intensité par la distance
    // Désactiver le facteurLumière quand on fait l'éclairage indirect
    
    
    
    InitSpheres(spheres);
    
    // Initialisation de l'écran
//    for (float y = 0; y < ecran.height; y++)
//    {
//        for (float z = 0; z < ecran.width; z++)
//        {
////            ecran[y][z] = Vector3{.x = 0 , .y = y, .z = z};
//            ecran[y][z] = Vector3{.x = 0 , .y = y , .z = z};
//        }
//    }
    
//    vector<vector<Color>> image(tailleMap, vector<Color>(tailleMap, Color{255, 20, 147}));
    Image image(ecran.height * ecran.width, Color{0, 0, 0});


    for (int y = 0; y < ecran.height; y++)
    {
        for (int z = 0; z < ecran.width; z++)
        {
            double dist = INT_MAX;
            Sphere sphere;
            Intersection result;
            for(const Sphere& sphereEnTest : spheres)
            {
                const Rayon rayon = Rayon(ecran.position + Vector3(static_cast<int>(ecran.position.x), y, z), Vector3(1, 0, 0));
                Intersect(rayon, sphereEnTest, result);
                if(!result.intersect || result.distance >= dist)
                {
                    continue;
                }

                dist = result.distance;
                sphere = sphereEnTest;
            }
            if (INT_MAX != dist)
            {

                image[y * ecran.height + z] = sphere.couleur;

                if (CanSeeLight(result.point, lumiere, spheres))
                {
                    SetLightning(result.point, lumiere, image);
                }else
                {
                    image[y * ecran.height + z].r = image[y * ecran.height + z].r * facteurLumiere;
                    image[y * ecran.height + z].g = image[y * ecran.height + z].g * facteurLumiere;
                    image[y * ecran.height + z].b = image[y * ecran.height + z].b * facteurLumiere;
                }

            }

        }
    }
    
    
    CreateSpheresBoxes(boxes, spheres);
    BoundingBox bBox = BoundingBox(boxes);
    bBox.source = superBBType;
    bBox.Print();

    for (int y = 0; y < ecran.height; y++)
    {
        for (int z = 0; z < ecran.width; z++)
        {
//            for (const Box& b : boxes)
//            {
                const Rayon rayon = Rayon(ecran.position + Vector3(static_cast<int>(ecran.position.x), y, z), Vector3(1, 0, 0));
            if (IntersectBBox(rayon, bBox))
                {
                    if (sphereType == bBox.source)
                    {
                        // vert == chaques boxes
                        image[y * ecran.height + z] = Color{0, 255, 0};
                    }else if (boundingBoxType == bBox.source)
                    {
                        // rouge == bounding box
                        image[y * ecran.height + z] = Color{255, 0, 0};
                    }else if (superBBType == bBox.source)
                    {
                        // bleu == la boite unique
                        image[y * ecran.height + z] = Color{0, 0, 255};
                    }else
                    {
                        // jaune == on ne sait pas
                        image[y * ecran.height + z] = Color{0, 255, 255};
                    }
                }
//            }
        }
    }
    
    
    
    

    
    ImageFromArray(ecran.height, ecran.width, image);
    
    return 0;
}

void ImageFromArray(const int& width, const int& height, const Image& pixelsArray)
{
    bitmap_image img(width, height);
    
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width ; x++)
        {
            double r = pixelsArray[x * width + y].r > 255 ? 255 : pixelsArray[x * width + y].r;
            double g = pixelsArray[x * width + y].g > 255 ? 255 : pixelsArray[x * width + y].g;
            double b = pixelsArray[x * width + y].b > 255 ? 255 : pixelsArray[x * width + y].b;
            
            if(r < 0 || g < 0 || b < 0)
            {
                cout << "color < 0 : (" << r << ", " << g << ", " << b << ")" << endl;
                exit(2);
                // EXIT CODE: 2 --> Un pixel avait une couleur < 0
            }
            
            img.set_pixel(x, y, r, g, b);
        }
    }
    
    img.save_image("/Users/Raph/Desktop/imageSynthese.bmp");
//        img.save_image("imageSynthese.bmp");
    cout << "image sauvegardée sur le bureau !" << endl;
}

void InitSpheres(Scene& spheres)
{
//    ///////// TEST SPHÈRES ////////
    // Sphere(position, rayon, couleur, nom)
    // Sphere(Vector3(), int, colorStruct, string)
    spheres.push_back(Sphere(Vector3(150, 500, 500), 75, Color{255, 0, 0}, "rouge")); // Rouge
    spheres.push_back(Sphere(Vector3(100, 100, 850), 50, Color{0, 255, 0}, "verte")); // Verte
    spheres.push_back(Sphere(Vector3(850, 800, 100), 50, Color{0, 0, 255}, "bleu")); // Bleu
    spheres.push_back(Sphere(Vector3(250, 150, 800), 150, Color{255, 0, 255}, "rose")); // Bleu éléctrique
    spheres.push_back(Sphere(Vector3(400, 600, 600), 100, Color{0, 255, 255}, "bleuCiel")); // Bleu ciel
    spheres.push_back(Sphere(Vector3(950, 500, 500), 200, Color{255, 255, 0}, "jaune")); // Jaune

    spheres.push_back(Sphere(Vector3(lumiere.position.x, lumiere.position.y, lumiere.position.z), 5, Color{255, 255, 255}, "lampe", 0)); // blanc
}

bool CanSeeLight(const Vector3& point, const Light& light, const Scene& scene)
{
    const Vector3 dirLampe = Normalize(light.position - point);
    const double distPL = GetDistance(point, light.position);
    
    for (const Sphere& sphere : scene)
    {
        if (lumiereType == sphere.type)
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

void SetLightning(const Vector3& point, const Light& light,  Image& image)
{
    const double puissance = light.puissance * (1 / (abs((light.position.x - point.x) + (light.position.y - point.y) + (light.position.z - point.z))));
    
//    double r = image[point.y][point.z].r * puissance;
//    double g = image[point.y][point.z].g * puissance;
//    double b = image[point.y][point.z].b * puissance;
    
    image[point.y * 1000 + point.z].r = image[point.y * 1000 + point.z].r * puissance;
    image[point.y * 1000 + point.z].g = image[point.y * 1000 + point.z].g * puissance;
    image[point.y * 1000 + point.z].b = image[point.y * 1000 + point.z].b * puissance;
}

int RunTests()
{
    return RUN_ALL_TESTS();
}








// radiance(rayon, scene) -> couleur

// intensité lumineuse sauvegardée dans l'image ^1/2.2
