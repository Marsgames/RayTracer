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
#include <Scene.hpp>
#include <Sphere.hpp>

using std::cout;
using std::endl;

// Image 4K : 4096 * 2160 | focale --> 4000

int main(int argc, char* argv[])
{
    cout << endl;
    testing::InitGoogleTest(&argc, argv);
    RunTests();
    cout << endl;
    
    Vector3 mainCameraPosition = Vector3{0, 0, 0};
    Vector3 mainCameraDirection = Vector3{0, 0, 1};
    Camera mainCamera = Camera(mainCameraPosition, 4096, 2160, mainCameraDirection, 3000);
//    mainCamera.SetUseFocal(false);
    
//    double widthOffset = 30000 + (10 * (0.1 * (mainCamera.GetWidth() / 2)));
//    double heightOffset = 30000 + (10 * (0.1 * (mainCamera.GetHeight() / 2)));
//    Sphere sp1 = Sphere(Vector3{0., 0., 200.}, 100, Color{45, 45, 155});
//////    Sphere sp1 = Sphere(Vector3{0, 0, 2000}, 1000, Color{45, 45, 45});
//////    Sphere sp2 = Sphere(Vector3{0, 0, 25}, 20, Color{255, 0, 255});
//////    Sphere sp3 = Sphere(Vector3{-960, -540, 200}, 300, Color{45, 45, 155});
////
//////    // Enlever un 0 à 7000, 4000 et 15000
//    Sphere leftWall = Sphere(Vector3(-widthOffset, 0., 0.), 3e4,  Color::GetColor(EColor::Green), "Vert");
//    Sphere rightWall = Sphere(Vector3(widthOffset, 0., 0.), 3e4, Color::GetColor(EColor::Blue), "Bleu");
//    Sphere topWall = Sphere(Vector3(0., -heightOffset, 0.), 3e4, Color::GetColor(EColor::Pink), "Rose");
//    Sphere bottomWall = Sphere(Vector3(0., heightOffset, 0.), 3e4, Color::GetColor(EColor::White), "Blanc");
//////    //    Sphere bottomWall = Sphere(Vector3(0., 4e5 + 4000., -00.), 4e5, Material(EMaterialType::DifuseType, Vector3(255 / 75, 255 / 140, 255 / 225)), "Rouge chelou");
////////    Sphere backWall = Sphere(Vector3(0., 0., 20000.), 4e5, Color(255, 0, 0), "Rouge");
//    Sphere frontWall = Sphere(Vector3(0., 0., 3e4 + 1000), 3e4, Color::GetColor(EColor::Yellow), "Jaune");
    
    
    Sphere sp1 = Sphere(Vector3(-2000, 0, 5000), 800, Color(45, 45, 255));
    Sphere sp2 = Sphere(Vector3(0, 0, 4000), 800, Color(145, 45, 210));
    Sphere sp3 = Sphere(Vector3(2000, 0, 3000), 800, Color(255, 45, 45));
    Sphere sp4 = Sphere(Vector3(0, 0, 3000), 400, Color(255, 210, 255));
    Sphere sp5 = Sphere(Vector3(0, 0, 6000), 200, Color(210, 210, 255));
    
    
    
    
    
    Scene myScene = Scene();
    myScene.AddCamera(mainCamera);
    myScene.AddSphere(sp1);
    myScene.AddSphere(sp2);
    myScene.AddSphere(sp3);
    myScene.AddSphere(sp4);
    myScene.AddSphere(sp5);

//    myScene.AddSphere(leftWall);
//    myScene.AddSphere(rightWall);
//    myScene.AddSphere(topWall);
//    myScene.AddSphere(bottomWall);
////////    myScene.AddSphere(backWall);
//    myScene.AddSphere(frontWall);

    
    myScene.AddLight(Light(Vector3(0, 0, 0), 3000));
//    myScene.AddLight(Light(Vector3(2000, -1000, 999), 1000));
//    myScene.AddLight(Light(Vector3(6500, -3000, 10000), 100000));
//    myScene.AddLight(Light(Vector3(5000, -5000, -5000), 10000));

    myScene.DrawImages();
    
    myScene.SaveImages();
    
    cout << endl;
    return 0;
}

int RunTests()
{
    return RUN_ALL_TESTS();
}
