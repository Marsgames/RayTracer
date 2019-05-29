//
//  main.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#include <Camera.hpp>
#include <gtests/UnitsTests.hpp>
#include <iostream>
#include <main.hpp>
#include <Sphere.hpp>

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    cout << endl;
    testing::InitGoogleTest(&argc, argv);
    RunTests();
    cout << endl;
    
    Vector3 mainCameraPosition = Vector3{0, 0, 0};
    Vector3 mainCameraDirection = Vector3{0, 0, 1};
    Camera mainCamera = Camera(mainCameraPosition, 1920, 1080, mainCameraDirection);
//    mainCamera.SetUseFocal(false);
//    mainCamera.SaveImage();
//    mainCamera.SetImageFormat(EImageFormat::PPM);
//    mainCamera.SaveImage();
//    
//    Sphere sp1 = Sphere(Vector3{0, 0, 0}, 10, Color{255, 255, 255});
//    Ray r1 = Ray(Vector3{-10, 0, 0}, Vector3{10, 0, 0});
//    Intersection res = Sphere::IntersectRaySphere(r1, sp1);
//    
//    cout << "result : " << res.intersect << endl;
    
    cout << endl;
    return 0;
}

int RunTests()
{
    return RUN_ALL_TESTS();
}
