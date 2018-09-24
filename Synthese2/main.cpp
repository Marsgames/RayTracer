//
//  main.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#include <iostream>
#include "main.hpp"
#include <math.h>
#include "Library/Bitmap/bitmap_image.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    // Ajouter un écran (tableau 2D de pixels) (origine 0, 0->10, 0->-10)
    // ajouter une sphère (origine 0, rayon 10)
    
    // pour chaque pixels de l'ecran on fait partir un rayon
    // on récupère l'intersection et on crée une image à partir du résultat
    
    vector<vector<Vector3>> ecran(200, vector<Vector3>(200));
    
    // Initialisation de l'écran
    for (float y = 0; y < 200; y += 1){
        for (float z = 0; z < 200; z += 1){
            ecran[y][z] = Vector3{-200 , y, z};
        }
    }
    
    vector<vector<colorStruct>> pixelsArray(200, vector<colorStruct>(200, colorStruct{0, 0, 0}));

    for (int y = 0; y < 200; y++){
        for (int z = 0; z < 200; z++){
            intersection res = Intersect(ecran[y][z], Vector3{1, 0, 0}, {0, 100, 100}, 50);
            if(res.intersect){
                continue;
            }
            pixelsArray[y][z] = colorStruct{0, 255, 0};
        }
    }
    
    for (int y = 0; y < 200; y++){
        for (int z = 0; z < 200; z++){
            intersection res = Intersect(ecran[y][z], Vector3{1, 0, 0}, {0, 25, 25}, 50);
            if(!res.intersect){
                continue;
            }
            pixelsArray[y][z] = colorStruct{255, 0, 0};
        }
    }
    
    
    for (int y = 0; y < 200; y++){
        for (int z = 0; z < 200; z++){
            intersection res = Intersect(ecran[y][z], Vector3{1, 0, 0}, {0, 150, 150}, 50);
            if(!res.intersect){
                continue;
            }
            pixelsArray[y][z] = colorStruct{0, 0, 255};
        }
    }
    
    ImageFromArray(200, 200, pixelsArray);
    
//    intersection res = Intersect(Vector3{0, 0, 0}, Vector3{1, 0, 0}, Vector3{0, 0, 0}, 10);
//
//    if(!res.intersect){
//        cout << endl << endl << "Il n'y a pas d'intersection" << endl << endl << endl;
//        return 0;
//    }
//    cout << endl << endl << "Il y a intersection : " << res.inter << endl << endl << endl;
    
    return 0;
}

intersection Intersect(Vector3 point, Vector3 dirrection, Vector3 origineCercle, float rayon){
    double A = Dist2(dirrection);
    double B = 2 * (Dot(point, dirrection) - Dot(origineCercle, dirrection));
    double C = Dist2(Minus(origineCercle, point)) - (rayon * rayon);
    
    double delta = (B * B) - (4 * A * C);
    
    intersection result = intersection(false, 0);
    
    
    if (0 == int(delta)){
        result.intersect = true;
        result.inter = (-B) / (2 * A);
    }
    if(delta >= 0){
        double inter1 = ((-B) - sqrt(delta)) / (2 * A);
        double inter2 = ((-B) + sqrt(delta)) / (2 * A);
        
        double res = 0;
        
        if(inter1 >= 0 && inter2 >= 0){
            res = inter1 < inter2 ? inter1 : inter2;
        }
        
        result = intersection(true, res);
    }
    return result;
}

double Dot(Vector3 pA, Vector3 pB){
    return pA.x * pB.x + pA.y * pB.y + pA.z * pB.z;
}

double Dist2(Vector3 pA){
    return Dot(pA, pA);
}

Vector3 Minus(Vector3 A, Vector3 B){
    return Vector3{A.x - B.x, A.y - B.y, A.z - B.z};
}

void ImageFromArray(int width, int height, vector<vector<colorStruct>> pixelsArray){
    bitmap_image img(width, height);
        
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                img.set_pixel(x, y, pixelsArray[x][y].r, pixelsArray[x][y].g, pixelsArray[x][y].b);
                cout << "r : " << pixelsArray[x][y].r << " - g : " << pixelsArray[x][y].g << " - b : " << pixelsArray[x][y].b << endl;
            }
        }
    
    img.save_image("/Users/Raph/Desktop/imageSynthese.bmp");
    cout << "image sauvegardée sur le bureau !" << endl;
}

