//
//  main.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#include "main.hpp"
#include <math.h>
#include "Library/Bitmap/bitmap_image.hpp"
#include "Vector3.hpp"

int main()
{
    
    // Ajouter un écran (tableau 2D de pixels) (origine 0, 0->10, 0->-10)
    // ajouter une sphère (origine 0, rayon 10)
    
    // pour chaque pixels de l'ecran on fait partir un rayon
    // on récupère l'intersection et on crée une image à partir du résultat
    const int tailleMap = 1000;
    V3Tab ecran(tailleMap, vector<Vector3>(tailleMap));
    vector<Sphere> spheres;
    const Vector3 lumiere = Vector3{0, 0, 0};
    const float facteurLumiere = 0.5;
    
    // Pour le miroir, si je tombe sur un miroir je traverse et pars dans le sens opposé
    // Pour la lumière, lui donner une intensité, diviser l'intensité par la distance
    // Désactiver le facteurLumière quand on fait l'éclairage indirect
    
    
    
    InitSpheres(spheres);
    
    // Initialisation de l'écran
    for (float y = 0; y < tailleMap; y++)
    {
        for (float z = 0; z < tailleMap; z++)
        {
            ecran[y][z] = Vector3{.x = 0 , .y = y, .z = z};
        }
    }
    
    vector<vector<Color>> image(tailleMap, vector<Color>(tailleMap, Color{255, 20, 147}));
    
    
    for (int y = 0; y < tailleMap; y++)
    {
        for (int z = 0; z < tailleMap; z++)
        {
            int dist = INT_MAX;
            int coordX = 0;
            Sphere sphere;
            for(const Sphere &sphereEnTest : spheres)
            {
                Intersection result;
                Intersect(ecran[y][z], Vector3{.x =  1,.y = 0,.z = 0}, sphereEnTest, result);
                if(!result.intersect || result.distance >= dist)
                {
                    continue;
                }
                
                dist = result.distance;
                sphere = sphereEnTest;
                coordX = static_cast<int>(ecran[y][z].x + result.distance);
            }
            if (INT_MAX != dist)
            {
                
                const Vector3 pointOnSphere = Vector3{static_cast<double>(coordX), static_cast<double>(y), static_cast<double>(z)};
                
                image[y][z] = sphere.couleur;
                if (!CanSeeLight(pointOnSphere, lumiere, spheres))
                {
                    image[y][z].r = image[y][z].r * facteurLumiere;
                    image[y][z].g = image[y][z].g * facteurLumiere;
                    image[y][z].b = image[y][z].b * facteurLumiere;
                    
                }
                
            }
            
        }
    }
    
    ImageFromArray(tailleMap, tailleMap, image);
    
    return 0;
}

void Intersect(const Vector3& point, const Vector3& direction, const Sphere& sphere, Intersection& myRes)
{
    Vector3 dirNorm = Normalize(direction);

    const double B = 2 * (Dot(point, direction) - Dot(sphere.origine, direction));
    const double C = Dist2(sphere.origine - point) - (sphere.rayon * sphere.rayon);
    const double delta = (B * B) - 4 * C;
    
    myRes.intersect = true;
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
        myRes.distance = inter1;
    }else if (inter2 > 0)
    {
            myRes.distance = inter2;
    }
    
    //Intersection must be positive to be in the right direction
    if (myRes.distance <= 0)
    {
        myRes.intersect = false;
        return;
    }

    myRes.point = point + dirNorm * myRes.distance;
}


void ImageFromArray(const int& width, const int& height, const vector<vector<Color>>& pixelsArray)
{
    bitmap_image img(width, height);
    
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            img.set_pixel(x, y, pixelsArray[x][y].r, pixelsArray[x][y].g, pixelsArray[x][y].b);
        }
    }
    
    img.save_image("/Users/Raph/Desktop/imageSynthese.bmp");
    //    img.save_image("imageSynthese.bmp");
    cout << "image sauvegardée sur le bureau !" << endl;
}

void InitSpheres(vector<Sphere>& spheres)
{
    ///////// TEST SPHÈRES ////////
    // Sphere(position, rayon, couleur, nom)
    // Sphere(Vector3(), int, colorStruct, string)
        spheres.push_back(Sphere{.origine = Vector3{.x = 150, .y = 500, .z = 500}, .rayon = 75, .couleur =  Color{.r = 255, .g = 0, .b = 0}, .nom = "sp1"}); // Rouge
        spheres.push_back(Sphere{.origine = Vector3{.x = 100, .y = 100, .z = 850}, .rayon = 50, .couleur =  Color{.r = 0, .g = 255, .b = 0}, .nom = "sp2"}); // Verte
        spheres.push_back(Sphere{.origine = Vector3{.x = 850, .y = 800, .z =  100}, .rayon = 50, .couleur =  Color{.r = 0, .g = 0, .b = 255}, .nom = "sp3"}); // Bleu
        spheres.push_back(Sphere{.origine = Vector3{.x = 250, .y = 150, .z = 800}, .rayon = 150, .couleur =  Color{.r = 44, .g = 117, .b = 255}, .nom = "sp4"}); // Bleu éléctrique
        spheres.push_back(Sphere{.origine = Vector3{.x = 400, .y = 600, .z = 600}, .rayon = 100, .couleur =  Color{.r = 0, .g = 255, .b = 255}, .nom = "sp5"}); // Bleu ciel
        spheres.push_back(Sphere{.origine = Vector3{.x = 950, .y = 500, .z = 500}, .rayon = 200, .couleur =  Color{.r = 255, .g = 255, .b = 0}, .nom = "sp6"}); // Jaune
    
//    spheres.push_back(Sphere{.origine = Vector3{.x = 500, .y = 500, .z = 500}, .rayon = 100, .couleur =  Color{.r = 255, .g = 255, .b = 0}, .nom = "Sphère test"}); // Jaune
}

bool CanSeeLight(const Vector3& point, const Vector3& lightPos, const vector<Sphere>& scene)
{
    const Vector3 dirLampe = Normalize(lightPos - point);
    const Vector3 pointToTest = point + (dirLampe * .01);
    
    
    for (const Sphere& sphere : scene)
    {
        Intersection result;
        Intersect(pointToTest, dirLampe, sphere, result);
        
        if (result.intersect)
        {
            return true;
        }
    }
    
    return false;
}




// radiance(rayon, scene) -> couleur

// intensité lumineuse sauvegardée dans l'image ^1/2.2
