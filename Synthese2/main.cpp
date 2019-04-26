//
//  main.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#include <Camera.hpp>
#include <Light.hpp>
#include <main.hpp>
#include <Rayon.hpp>
#include <Vector3.hpp>
#include <gtests/UnitsTests.hpp>
#include <Sphere.hpp>
#include <Color.hpp>
#include <Box.hpp>
#include <BoundingBox.hpp>
#include <iostream>
#include <thread>
#include <Material.hpp>
#include <Scene.hpp>

using std::string;
using std::vector;
using std::cout;
using std::thread;

// TODO : lumière indirecte
// TODO : rajouter intersection rayon triangle
// TODO : créer classe cube
// TODO : rotation des objets
//      newPos = (cos(teta) * actualPos.X + sin(teta) * actualPos.Z, actualPos.Y, -sin(teta) * acutalPos.X + cos(teta) * actualPos.Z)
// TODO : importation de modèles 3D
// TODO : couleur de la lumière

//Light lumiere = Light{Vector3{0, 0, 200}, 1000};
//Camera ecran = Camera(Vector3{500, 500, 0}, 1000, 1000, Vector3(0, 0, -1), 1000);

//Light lumiere = Light{Vector3(0., -950., -1000.), 10000};
//Light lumiere = Light{Vector3(0., -450., -500.), 1000};

const Vector3 camOrigin{0, 0, 0};
Vector3 camDirection{0., 0., -1.};
Camera m_ecran = Camera(camOrigin, 1000, 1000, camDirection, 1000); // 4096 * 2160
//Camera m_ecran = Camera(camOrigin, 10, 10, camDirection, 3000); // 4096 * 2160

//Camera m_ecran = Camera(Vector3(200, 0, -420), 1000, 1000, Vector3(-0., 0.,  1.), 1000);
//Camera m_ecran = Camera(Vector3(0, 0, -800), 4096, 2160, Vector3(0., 0.,  1.), 3000);
//Camera m_ecran = Camera(Vector3(0, 0, -30), 500, 500, Vector3(0., 0.,  1.), 3000);

//Camera m_ecran2 = Camera(Vector3(200, 0, 0), 4096, 2160, Vector3(-1.0, 0.,  -1.), 3000);
//Camera m_ecran3 = Camera(Vector3(-200, 0, 0), 4096, 2160, Vector3(1.0, 0.,  -1.), 3000);



//Camera m_ecran = Camera(Vector3(0, 0, 0), 1280, 720, Vector3(0., 0., -1.), 1000);
//Camera m_ecran2 = Camera(Vector3(0, 0, 0), 1280, 720, Vector3(0., 0., 1.), 1000);
//Camera m_ecran3 = Camera(Vector3(-1000, 0, -400), 4096, 2160, Vector3(1., 0., 0.), 3000);
//Camera m_ecran4 = Camera(Vector3(1000, 0, -400), 4096, 2160, Vector3(1., 0.,  0.), 3000);
//Camera m_ecran5 = Camera(Vector3(-1000, 0, -400), 4096, 2160, Vector3(-1., 0., 0.), 3000);


const float facteurLumiere = .3;


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RunTests();
    
    
    //    const Camera ecran = Camera(Vector3{0, 0, 0}, 1000, 1000);
    
    // Ajouter un écran (tableau 2D de pixels) (origine 0, 0->10, 0->-10)
    // ajouter une sphère (origine 0, rayon 10)
    
    // pour chaque pixels de l'ecran on fait partir un rayon
    // on récupère l'intersection et on crée une image à partir du résultat
    
    Light light = Light{Vector3(0., -450., 100.), 300};
    Spheres spheres;
    InitSpheres(spheres, light);
    Scene myScene(light, spheres, facteurLumiere);
    
//    myScene.LaunchThreads(1, m_ecran, Vector3{-5, 0, 0}, light);
//    myScene.GenerateImages(45, 50, m_ecran, Vector3{-5, 0, 0}, light);
    
    
    
    
    
        myScene.GenerateImages(0, 1, m_ecran, Vector3{0, 0, 0}, light);
//    Vector3 newDirEcran{0, 0, 1};
//    m_ecran.SetDirection(newDirEcran);
//    Vector3 newPosEcran{0, 0, -800};
//    m_ecran.SetPosition(newPosEcran);
//    myScene.GenerateImages(1, 2, m_ecran, Vector3{0, 0, 0}, light);
    
    
    
    
    

    //    double cosTheta = cos((2 * M_PI * 0) / 6);
    //    double sinTheta = sin((2 * M_PI * 0) / 6);
    //    Vector3 camPos{0 + 100 * cosTheta, 0., 0 + 100 * sinTheta};
    //    Vector3 camDir{Vector3{0, 0, 0} - camPos};
    //    cout << camPos.ToString() << ", ";
    //
    //    m_ecran.SetPosition(camPos);
    //    m_ecran.SetDirection(camDir);
    //
    //    myScene.GenerateImages(0, 1, m_ecran, Vector3{0, 0, 0});
    //
    //    cosTheta = cos((2 * M_PI * 1) / 6);
    //    sinTheta = sin((2 * M_PI * 1) / 6);
    //    camPos = Vector3(0 + 100 * cosTheta, 0., 0 + 100 * sinTheta);
    //    camDir = Vector3(0, 0, 0) - camPos;
    //    cout << camPos.ToString() << ", ";
    //
    //    m_ecran.SetPosition(camPos);
    //    m_ecran.SetDirection(camDir);
    //    myScene.GenerateImages(1, 2, m_ecran, Vector3{0, 0, 0});
    //
    //    cosTheta = cos((2 * M_PI * 2) / 6);
    //    sinTheta = sin((2 * M_PI * 2) / 6);
    //    camPos = Vector3(0 + 100 * cosTheta, 0., 0 + 100 * sinTheta);
    //    camDir = Vector3(0, 0, 0) - camPos;
    //    cout << camPos.ToString() << ", ";
    //
    //
    //    m_ecran.SetPosition(camPos);
    //    m_ecran.SetDirection(camDir);
    //    myScene.GenerateImages(2, 3, m_ecran, Vector3{0, 0, 0});
    //
    //    cosTheta = cos((2 * M_PI * 3) / 6);
    //    sinTheta = sin((2 * M_PI * 3) / 6);
    //    camPos = Vector3(0 + 100 * cosTheta, 0., 0 + 100 * sinTheta);
    //    camDir = Vector3(0, 0, 0) - camPos;
    //    cout << camPos.ToString() << ", ";
    //
    //
    //    m_ecran.SetPosition(camPos);
    //    m_ecran.SetDirection(camDir);
    //    myScene.GenerateImages(3, 4, m_ecran, Vector3{0, 0, 0});
    //
    //    cosTheta = cos((2 * M_PI * 4) / 6);
    //    sinTheta = sin((2 * M_PI * 4) / 6);
    //    camPos = Vector3(0 + 100 * cosTheta, 0., 0 + 100 * sinTheta);
    //    camDir = Vector3(0, 0, 0) - camPos;
    //    cout << camPos.ToString() << ", ";
    //
    //
    //    m_ecran.SetPosition(camPos);
    //    m_ecran.SetDirection(camDir);
    //    myScene.GenerateImages(4, 5, m_ecran, Vector3{0, 0, 0});
    //
    //    cosTheta = cos((2 * M_PI * 5) / 6);
    //    sinTheta = sin((2 * M_PI * 5) / 6);
    //    camPos = Vector3(0 + 100 * cosTheta, 0., 0 + 100 * sinTheta);
    //    camDir = Vector3(0, 0, 0) - camPos;
    //    cout << camPos.ToString() << endl;
    //
    //
    //    m_ecran.SetPosition(camPos);
    //    m_ecran.SetDirection(camDir);
    //    myScene.GenerateImages(5, 6, m_ecran, Vector3{0, 0, 0});
    
    
    //    Boxes boxes;
    
    
    
    
    
    // Ajouter struct Material { Difuse (renvoie la couleur du materiaux), Mirror (rebondi et renvoi le prochain point touché), light (éclaire), glass (passe au travers (rajouter un effet "fumé" pour différentier avec "rien")}
    
    // Pour le miroir, si je tombe sur un miroir je traverse et pars dans le sens opposé
    // Pour la lumière, lui donner une intensité, diviser l'intensité par la distance
    // Désactiver le facteurLumière quand on fait l'éclairage indirect
    
    
    
    //    GenerateImages(100000, 100001, spheres, m_ecran, Vector3(0, 0, 0));
    //    Vector3 direction{0, 0, 1};
    //    m_ecran.SetDirection(direction);
    //    GenerateImages(100001, 100002, spheres, m_ecran, Vector3(0, 0, 0));
    
    //    GenerateImages(0, 1, spheres, m_ecran2, Vector3(0, 0, 0));
    //    GenerateImages(2, 3, spheres, m_ecran3, Vector3(0, 0, 0));
    //    GenerateImages(3, 4, spheres, m_ecran4, Vector3(0, 0, 0));
    //    GenerateImages(4, 5, spheres, m_ecran5, Vector3(0, 0, 0));
    
    
    
//                // Make camera move around a point
//                {
//                    const Vector3 posSphere = Vector3(0, 0, 0);
//                    const double rayonRotation = 100;
//                    int index = 0;
//                    cout << endl << endl;
//                    int nbParts = 120;
//                    for (int i = 0; i < nbParts; i++)
//                    {
//                        const double cosTheta = cos((2 * M_PI * i) / nbParts);
//                        const double sinTheta = sin((2 * M_PI * i) / nbParts);
//                        Vector3 camPos = Vector3(posSphere.GetX() + rayonRotation * cosTheta, m_ecran.GetPosition().GetY(), posSphere.GetZ() + rayonRotation * sinTheta);
//                        Vector3 dirCam = Vector3(posSphere - camPos);
//
//
//                        m_ecran.SetPosition(camPos);
//                        m_ecran.SetDirection(dirCam);
//                        myScene.GenerateImages(index, index + 1, m_ecran, Vector3(0, 0, 0), light);
//                        index++;
//                        cout << "(" << camPos.GetX() << "," << camPos.GetZ() << "), ";
//                    }
//                    cout << endl << endl;
//                }
    
    
    
    //        LaunchThreads(50, spheres, ecran, Vector3(10, 0, 0));
    //        LaunchThreads(1000, spheres, ecran, Vector3(1, 0, 0));
    
    return 0;
}

void InitSpheres(Spheres& spheres, const Light& lumiere)
{
    // Enlever un 0 à 7000, 4000 et 15000
    Sphere leftWall = Sphere(Vector3(-4e5 - 7000., 0., -00.), 4e5, Material(EMaterialType::DifuseType, Vector3(0.2f, 0.8f, 0.2f)), "Vert");
    Sphere rightWall = Sphere(Vector3(4e5 + 7000., 0., -00.), 4e5, Material(EMaterialType::DifuseType, Vector3(0.2f, 0.8f, 0.8f)), "Bleu");
    Sphere topWall = Sphere(Vector3(0., -4e5 - 4000., -00.), 4e5, Material(EMaterialType::DifuseType, Vector3(0.8f, 0.2f, 0.8f)), "Rose");
    Sphere bottomWall = Sphere(Vector3(0., 4e5 + 4000., -00.), 4e5, Material(EMaterialType::DifuseType, Vector3(0.9f, 0.9f, 0.9f)), "Blanc");
//    Sphere bottomWall = Sphere(Vector3(0., 4e5 + 4000., -00.), 4e5, Material(EMaterialType::DifuseType, Vector3(255 / 75, 255 / 140, 255 / 225)), "Rouge chelou");
    Sphere backWall = Sphere(Vector3(0., 0., 4e5 + 15000), 4e5, Material(EMaterialType::DifuseType, Vector3(0.8f, 0.2f, 0.2f)), "Rouge");
    Sphere frontWall = Sphere(Vector3(0., 0., -4e5 - 15000), 4e5, Material(EMaterialType::DifuseType, Vector3(0.8f, 0.8f, 0.2f)), "Jaune");
    
    
    
//        spheres.push_back(Sphere(Vector3(500 - 500, 500 - 500, -150), 75, Material(DifuseType, Color{255, 0, 0}), "rouge")); // Rouge
//        spheres.push_back(Sphere(Vector3(100 - 350, 800 - 500, -550), 50, Material(DifuseType, Color{0, 255, 0}), "verte")); // Verte
//        spheres.push_back(Sphere(Vector3(800 - 500, 150 - 500, -250), 50, Material(DifuseType, Color{0, 0, 255}), "bleu")); // Bleu
//        spheres.push_back(Sphere(Vector3(100 - 500, 800 - 1500, -850), 150, Material(DifuseType, Color{255, 0, 255}), "rose")); // Bleu éléctrique
//        spheres.push_back(Sphere(Vector3(600 - 500, 600 - 500, -400), 100, Material(DifuseType, Color{0, 255, 255}), "bleuCiel")); // Bleu ciel
//        spheres.push_back(Sphere(Vector3(500 - 500, 500 - 1500, -950), 200, Material(DifuseType, Color{255, 255, 0}), "jaune")); // Jaune
    
    
    
//    spheres.push_back(Sphere{Vector3{450, 0, -300}, 300, Material{DifuseType, Color{255, 0, 0}}, "Rouge"});
//    spheres.push_back(Sphere{Vector3{0, 0, -1000}, 300, Material{DifuseType, Color{0, 255, 0}}, "Vert"});
//    spheres.push_back(Sphere{Vector3{-450, 0, -2000}, 300, Material{DifuseType, Color{0, 0, 255}}, "Bleu"});
    
    
//    spheres.push_back(Sphere(Vector3(-1000, 0, -400), 200, Material(EMaterialType::DifuseType, Color{0, 0, 255}), "Bleu")); // Bleu
//    spheres.push_back(Sphere(Vector3(    0, 0, -400), 200, Material(EMaterialType::DifuseType, Color{255, 255, 255}), "Blanc")); // Blanc
//    spheres.push_back(Sphere(Vector3( 1000, 0, -400), 200, Material(EMaterialType::DifuseType, Color{255, 0, 0}), "Rouge")); // Rouge
    
    //    spheres.push_back(Sphere(Vector3(0, -800, -400), 200, Material(EMaterialType::DifuseType, Color{255, 0, 255}), "Rose")); // Rose
    //    spheres.push_back(Sphere(Vector3(0, 800, -400), 200, Material(EMaterialType::DifuseType, Color{255, 255, 0}), "Jaune")); // Jaune
    
    
//        spheres.push_back(Sphere(Vector3(0, 0, 0), 80, Material(EMaterialType::DifuseType, Color{255, 255, 255}), "Rouge")); // Bleu
    
    //
    spheres.push_back(leftWall);
    spheres.push_back(rightWall);
    spheres.push_back(topWall);
    spheres.push_back(bottomWall);
    spheres.push_back(frontWall);
    spheres.push_back(backWall);
    
    // Lumière
    spheres.push_back(Sphere(Vector3(lumiere.GetPosition()), 20, Material(EMaterialType::LightType, Color{255 * (1 / facteurLumiere), 0, 0}), "lampe")); // blanc
}

int RunTests()
{
    return RUN_ALL_TESTS();
}





// radiance(rayon, scene) -> couleur

// intensité lumineuse sauvegardée dans l'image ^1/2.2
