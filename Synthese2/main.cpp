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
#include <Toolbox.hpp>

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
    
    double widthOffset = 30000 + (10 * (0.1 * (mainCamera.GetWidth() / 2)));
    double heightOffset = 30000 + (10 * (0.1 * (mainCamera.GetHeight() / 2)));
//    Sphere sp1 = Sphere(Vector3{-400., -400., 200.}, 180, Material(Color(45, 45, 155)));
//    Sphere sp1 = Sphere(Vector3{-400., -400., 200.}, 400, Material(Color{45, 45, 155}, EMaterials::Wall)); // TESTER AVEC CETTE SPHERE QUAND TOUT MARCHERA
    Sphere sp1 = Sphere(Vector3(-300, -300, 500), 200, MaterialList::BlancMat);
    
//////    Sphere sp1 = Sphere(Vector3{0, 0, 2000}, 1000, Color{45, 45, 45});
//////    Sphere sp2 = Sphere(Vector3{0, 0, 25}, 20, Color{255, 0, 255});
//////    Sphere sp3 = Sphere(Vector3{-960, -540, 200}, 300, Color{45, 45, 155});

////    // Enlever un 0 à 7000, 4000 et 15000
    Sphere leftWall = Sphere(Vector3(-widthOffset, 0., 0.), 3e4,  MaterialList::VertMat, "Vert");
    Sphere rightWall = Sphere(Vector3(widthOffset, 0., 0.), 3e4, MaterialList::BleuMat, "Bleu");
    Sphere topWall = Sphere(Vector3(0., -heightOffset, 0.), 3e4, MaterialList::RoseMat, "Rose");
    Sphere bottomWall = Sphere(Vector3(0., heightOffset, 0.), 3e4, MaterialList::BlancMat, "Blanc");
////    //    Sphere bottomWall = Sphere(Vector3(0., 4e5 + 4000., -00.), 4e5, Material(EMaterialType::DifuseType, Vector3(255 / 75, 255 / 140, 255 / 225)), "Rouge chelou");
Sphere backWall = Sphere(Vector3(0., 0., -3e4 - 1000), 3e4, MaterialList::BleuCielMat, "Bleu ciel");
    Sphere frontWall = Sphere(Vector3(0., 0., 3e4 + 1000), 3e4, MaterialList::JauneMat, "Jaune");
    
    leftWall.GetMaterial().SetAlbedo(0);
    rightWall.GetMaterial().SetAlbedo(0);
    topWall.GetMaterial().SetAlbedo(0);
    bottomWall.GetMaterial().SetAlbedo(0);
    frontWall.GetMaterial().SetAlbedo(0);

    
//    Sphere sp1 = Sphere(Vector3(-2000, 0, 5000), 800, Color(45, 45, 255), "bleue");
//    Sphere sp2 = Sphere(Vector3(0, 0, 4000), 800, Color(145, 45, 210), "blanc");
//    Sphere sp3 = Sphere(Vector3(2000, 0, 3000), 800, Color(255, 45, 45), "rouge");
//    Sphere sp4 = Sphere(Vector3(0, 0, 3000), 400, Color(255, 210, 255), "devant");
//    Sphere sp5 = Sphere(Vector3(0, 0, 6000), 200, Color(210, 210, 255), "derrière");
    
    /*
     angle 90 : 0
     angle < 90 : 1
     angle > 90 : -1
     */
    
//    Vector3 v1 = Vector3(1 , 1, 0);
//    Vector3 v2 = Vector3(1, -1, 0);
//
//    cout << "angle 90 : " << Vector3::Dot(v1, v2) << endl;
//
//    Vector3 v3 = Vector3(2., 1.8, 0.);
//
//    cout << "angle < 90 : " << Vector3::Dot(v1, v3) << endl;
//
//    Vector3 v4 = Vector3(17., -3.14, 1.);
//
//    cout << "angle > 90 : " << Vector3::Dot(v1, v4) << endl;
    
    
    Scene myScene = Scene();
    mainCamera.SetScene(&myScene);
    myScene.AddCamera(mainCamera);
    myScene.AddSphere(sp1);
//    myScene.AddSphere(sp2);
//    myScene.AddSphere(sp3);
//    myScene.AddSphere(sp4);
//    myScene.AddSphere(sp5);

    myScene.AddSphere(leftWall);
    myScene.AddSphere(rightWall);
    myScene.AddSphere(topWall);
    myScene.AddSphere(bottomWall);
    myScene.AddSphere(backWall);
    myScene.AddSphere(frontWall);

    //        myScene.AddLight(Light(Vector3(2000, -900, 900), 500));
//    myScene.AddLight(Light(Vector3(0, 500, 0), 500, Material(Color(255, 255, 255), Color(255, 0, 0))));
    
    
    
//    myScene.AddLight(Light(Vector3(-0, 0, 0), 500));
    myScene.AddLight(Light(Vector3(-0, 500, 0), 1000));
//    myScene.AddLight(Light(Vector3(-700, 500, 0), 1000, Material(Color(255, 255, 255), Color(0, 0, 255))));
//    myScene.AddLight(Light(Vector3(700, 500, 0), 1000, Material(Color(255, 255, 255), Color(255, 0, 0))));

    
    
//    myScene.AddLight(Light(Vector3(-2000, 0, 0), 500));
//    myScene.AddLight(Light(Vector3(1600, -800, 0), 500));
//    myScene.AddLight(Light(Vector3(2800, 0, 0), 3000));
//    myScene.AddLight(Light(Vector3(1900, -900, 800), 2000));
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
