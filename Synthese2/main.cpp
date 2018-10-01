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

int main(int argc, const char * argv[])
{
    
    // Ajouter un écran (tableau 2D de pixels) (origine 0, 0->10, 0->-10)
    // ajouter une sphère (origine 0, rayon 10)
    
    // pour chaque pixels de l'ecran on fait partir un rayon
    // on récupère l'intersection et on crée une image à partir du résultat
    const int tailleMap = 1000;
    V3Tab ecran(tailleMap, vector<Vector3>(tailleMap));
    vector<Sphere> spheres;
    
    ///////// TEST SPHÈRES ////////
    // Sphere(position, rayon, couleur, nom)
    // Sphere(Vector3(), int, colorStruct, string)
    spheres.push_back(Sphere{.position = Vector3{.x = 1000, .y = 800, .z = 550}, .rayon = 150, .couleur =  Color{.r = 255, .g = 0, .b = 0}, .nom = "sp1"});
    spheres.push_back(Sphere{.position = Vector3{.x = 1100, .y = 200, .z = 900}, .rayon = 100, .couleur =  Color{.r = 0, .g = 255, .b = 0}, .nom = "sp2"});
    spheres.push_back(Sphere{.position = Vector3{.x = 1200, .y = 250, .z = 300}, .rayon = 100, .couleur =  Color{.r = 0, .g = 0, .b = 255}, .nom = "sp3"});
    spheres.push_back(Sphere{.position = Vector3{.x = 1600, .y = 250, .z = 800}, .rayon = 300, .couleur =  Color{.r = 44, .g = 117, .b = 255}, .nom = "sp4"});
    spheres.push_back(Sphere{.position = Vector3{.x = 1700, .y = 750, .z = 250}, .rayon = 200, .couleur =  Color{.r = 0, .g = 255, .b = 255}, .nom = "sp5"});
    spheres.push_back(Sphere{.position = Vector3{.x = 1900, .y = 500, .z = 500}, .rayon = 400, .couleur =  Color{.r = 129, .g = 20, .b = 83}, .nom = "sp6"});

    // Initialisation de l'écran
    for (float y = 0; y < tailleMap; y += 1)
    {
        for (float z = 0; z < tailleMap; z += 1)
        {
            ecran[y][z] = Vector3{.x = 0 , .y = y, .z = z};
        }
    }
    
    vector<vector<Color>> pixelsArray(tailleMap, vector<Color>(tailleMap, Color{0, 0, 0}));
    
    
    for (int y = 0; y < tailleMap; y++)
    {
        for (int z = 0; z < tailleMap; z++)
        {
            int dist = INT_MAX;
            Sphere sph;
            for(const Sphere &sp : spheres)
            {
                Intersection res = Intersection{false, 0};
                Intersect(ecran[y][z], Vector3{.x =  1,.y = 0,.z = 0}, sp.position, sp.rayon, res);
                if(!res.intersect)
                {
                    continue;
                }
                if(res.inter < dist)
                {
                    dist = res.inter;
                    sph = sp;
                }
            }
            if(INT_MAX != dist){
                pixelsArray[y][z] = sph.couleur;
                //                cout << "on affiche : " << sph.name << endl;
            }
        }
    }
    
    //    for (int y = 0; y < 200; y++){
    //        for (int z = 0; z < 200; z++){
    //            intersection res = Intersect(ecran[y][z], Vector3{1, 0, 0}, {0, 25, 25}, 50);
    //            if(!res.intersect){
    //                continue;
    //            }
    //            pixelsArray[y][z] = colorStruct{255, 0, 0};
    //        }
    //    }
    //
    //
    //    for (int y = 0; y < 200; y++){
    //        for (int z = 0; z < 200; z++){
    //            intersection res = Intersect(ecran[y][z], Vector3{1, 0, 0}, {0, 150, 150}, 50);
    //            if(!res.intersect){
    //                continue;
    //            }
    //            pixelsArray[y][z] = colorStruct{0, 0, 255};
    //        }
    //    }
    
    ImageFromArray(tailleMap, tailleMap, pixelsArray);
    
    //    intersection res = Intersect(Vector3{0, 0, 0}, Vector3{1, 0, 0}, Vector3{0, 0, 0}, 10);
    //
    //    if(!res.intersect){
    //        cout << endl << endl << "Il n'y a pas d'intersection" << endl << endl << endl;
    //        return 0;
    //    }
    //    cout << endl << endl << "Il y a intersection : " << res.inter << endl << endl << endl;
    
    return 0;
}

void Intersect(const Vector3& point, const Vector3& direction, const Vector3& origineCercle, const float rayon, Intersection& myRes)
{
    const double A = Dist2(direction);
    const double B = 2 * (Dot(point, direction) - Dot(origineCercle, direction));
    const double C = Dist2(Minus(origineCercle, point)) - (rayon * rayon);
    
    const double delta = (B * B) - (4 * A * C);
    
    myRes = Intersection{false, 0};
    
    if (0 == static_cast<int>(delta))
    {
        myRes.intersect = true;
        myRes.inter = (-B) / (2 * A);
    }
    if(delta >= 0)
    {
        const double inter1 = ((-B) - sqrt(delta)) / (2 * A);
        const double inter2 = ((-B) + sqrt(delta)) / (2 * A);
        
        double res = 0;
        
        if(inter1 >= 0 && inter2 >= 0)
        {
            res = inter1 < inter2 ? inter1 : inter2;
        }
        
        myRes = Intersection{true, res};
    }
}

void ImageFromArray(int width, int height, vector<vector<Color>> pixelsArray)
{
    bitmap_image img(width, height);
    
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            img.set_pixel(x, y, pixelsArray[x][y].r, pixelsArray[x][y].g, pixelsArray[x][y].b);
            //                cout << "r : " << pixelsArray[x][y].r << " - g : " << pixelsArray[x][y].g << " - b : " << pixelsArray[x][y].b << endl;
        }
    }
    
    img.save_image("/Users/Raph/Desktop/imageSynthese.bmp");
    //    img.save_image("imageSynthese.bmp");
    cout << "image sauvegardée sur le bureau !" << endl;
}

