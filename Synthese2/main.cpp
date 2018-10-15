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


Light lumiere = Light{Vector3{0, 0, 0}, 1250};
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
    

    const float facteurLumiere = 0.5;
    
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
    
    ImageFromArray(ecran.height, ecran.width, image);
    
    return 0;
}

void Intersect(const Rayon& rayon, const Sphere& sphere, Intersection& myRes)
{
    const double B = 2 * (Dot(rayon.origine, rayon.direction) - Dot(sphere.origine, rayon.direction));
    const double C = Dist2(sphere.origine - rayon.origine) - (sphere.rayon * sphere.rayon);
    const double delta = (B * B) - 4 * C;
    
    myRes.intersect = false;
    myRes.distance = 0;
    
    if (delta < 0)
    {
        myRes.intersect = false;
        return;
    }
    
    const double sqrtDelta = sqrt(delta);
    const double inter1 = (-B - sqrtDelta) / 2;
    const double inter2 = (-B + sqrtDelta) / 2;
    
    if (inter1 > 0)
    {
        myRes.intersect = true;
        myRes.distance = inter1;
    }else if (inter2 > 0)
    {
        myRes.intersect = true;
        myRes.distance = inter2;
    }
    
    myRes.point = rayon.origine + rayon.direction * myRes.distance;
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
    spheres.push_back(Sphere{.origine = Vector3(150, 500, 500), .rayon = 75, .couleur =  Color{.r = 255, .g = 0, .b = 0}, .nom = "sp1"}); // Rouge
    spheres.push_back(Sphere{.origine = Vector3(100, 100, 850), .rayon = 50, .couleur =  Color{.r = 0, .g = 255, .b = 0}, .nom = "sp2"}); // Verte
    spheres.push_back(Sphere{.origine = Vector3(850, 800, 100), .rayon = 50, .couleur =  Color{.r = 0, .g = 0, .b = 255}, .nom = "sp3"}); // Bleu
    spheres.push_back(Sphere{.origine = Vector3(250, 150, 800), .rayon = 150, .couleur =  Color{.r = 44, .g = 117, .b = 255}, .nom = "sp4"}); // Bleu éléctrique
    spheres.push_back(Sphere{.origine = Vector3(400, 600, 600), .rayon = 100, .couleur =  Color{.r = 0, .g = 255, .b = 255}, .nom = "sp5"}); // Bleu ciel
    spheres.push_back(Sphere{.origine = Vector3(950, 500, 500), .rayon = 200, .couleur =  Color{.r = 255, .g = 255, .b = 0}, .nom = "sp6"}); // Jaune

    spheres.push_back(Sphere{.origine = Vector3(lumiere.position.x, lumiere.position.y, lumiere.position.z), .rayon = 5, .couleur =  Color{.r = 255, .g = 255, .b = 255}, .nom = "lampe", .debugSphere = true}); // blanc
    
    
    
//    spheres.push_back(Sphere{.origine = Vector3(lumiere.position.x, lumiere.position.y, lumiere.position.z), .rayon = 5, .couleur =  Color{.r = 255, .g = 255, .b = 255}, .nom = "lampe"}); // blanc
//    spheres.push_back(Sphere{Vector3{0, -9900, 500}, 10000, Color{255, 0, 0}, "Rouge"});
//    spheres.push_back(Sphere{Vector3{0, 10900, 500}, 10000, Color{0, 255, 0}, "Vert"});
//    spheres.push_back(Sphere{Vector3{0, 500, -9900}, 10000, Color{0, 0, 255}, "Bleu"});
//        spheres.push_back(Sphere{Vector3{0, 500, 10900}, 10000, Color{44, 117, 255}, "Bleu éléctrique"});
//    spheres.push_back(Sphere{Vector3{10900, 500, 500}, 10000, Color{125, 125, 125}, "Blanc"});


}

bool CanSeeLight(const Vector3& point, const Light& light, const Scene& scene)
{
    const Vector3 dirLampe = Normalize(light.position - point);
    const double distPL = GetDistance(point, light.position);
    
    for (const Sphere& sphere : scene)
    {
        if (sphere.debugSphere)
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

double GetDistance(const Vector3& pointA, const Vector3& pointB)
{
    return sqrt(((pointA.x - pointB.x) * (pointA.x - pointB.x)) + ((pointA.y - pointB.y) * (pointA.y - pointB.y)) + ((pointA.z - pointB.z) * (pointA.z - pointB.z)));
}




// radiance(rayon, scene) -> couleur

// intensité lumineuse sauvegardée dans l'image ^1/2.2
