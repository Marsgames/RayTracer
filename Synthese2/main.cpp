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
//#include "Library/glm/vec3.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    intersection res = Intersect(Vector3(0, 0, 0), Vector3(1, 0, 0), Vector3(10, 0, 0), 1);
    
    if(!res.intersect){
        cout << endl << endl << "Il n'y a pas d'intersection" << endl << endl << endl;
        return 0;
    }
    cout << endl << endl << "Il y a intersection : " << res.inter << endl << endl << endl;
    
    return 0;
}

intersection Intersect(Vector3 point, Vector3 dirrection, Vector3 origineCercle, float rayon){
    double A = Dist2(dirrection);
    double B = 2 * (Dot(point, dirrection) - Dot(origineCercle, dirrection));
    double C = Dist2(Minus(origineCercle, point)) - (rayon * rayon);
    
    double delta = (B * B) - (4 * A * C);
    
    intersection result = intersection(false, 0);
    
    // if(delta < 0){
    //     result = new Tuple<bool, double>(false, 0);
    // }
    
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
        
        result.intersect = true;
        result.inter = res;
//        result = intersection(true, res);
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
    return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}

