//
//  main.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

struct Vector3 {
    //const Vector3 One = Vector3(1, 1, 1);
    float x, y, z;
};

struct intersection{
    bool intersect;
    float inter;
    intersection(bool intersectt, float interr){
        intersect = intersectt;
        inter = interr;
    }
};

struct colorStruct {
    int r, g, b;
};

intersection Intersect(Vector3, Vector3, Vector3, float);
double Dot(Vector3, Vector3);
double Dist2(Vector3);
Vector3 Minus(Vector3, Vector3);
void ImageFromArray(int, int, std::vector<std::vector<colorStruct>>);
