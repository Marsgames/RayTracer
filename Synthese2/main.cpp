//
//  main.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#include <Library/Bitmap/bitmap_image.hpp>
#include <Camera.hpp>
#include <Light.hpp>
#include <main.hpp>
//#include <math.h>
#include <Rayon.hpp>
#include <Vector3.hpp>
#include <gtest/gtest.h>
#include <gtests/UnitsTests.hpp>
#include <Sphere.hpp>
#include <Color.hpp>
#include <Box.hpp>
#include <BoundingBox.hpp>
#include <iostream>
#include <thread>
#include <Material.hpp>

// TODO : lumière indirecte
// TODO : rajouter intersection rayon triangle
// TODO : créer classe cube
// TODO : rotation des objets
// TODO : importation de modèles 3D
// TODO : couleur de la lumière

//Light lumiere = Light{Vector3{0, 0, 200}, 1000};
//Camera ecran = Camera(Vector3{500, 500, 0}, 1000, 1000, Vector3(0, 0, -1), 1000);

Light lumiere = Light{Vector3(0., -950., -100.), 1000};
const Vector3 origin{0, 0, 0};
Vector3 direction{0., 0., -1.};
Camera m_ecran = Camera(origin, 4096, 2160, direction, 3000);
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


const float facteurLumiere = .2;


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RunTests();
    //    return 0;
    //    return RUN_ALL_TESTS();
    
    
    //    const Camera ecran = Camera(Vector3{0, 0, 0}, 1000, 1000);
    
    // Ajouter un écran (tableau 2D de pixels) (origine 0, 0->10, 0->-10)
    // ajouter une sphère (origine 0, rayon 10)
    
    // pour chaque pixels de l'ecran on fait partir un rayon
    // on récupère l'intersection et on crée une image à partir du résultat
    
    Scene spheres;
    Boxes boxes;
    
    
    InitSpheres(spheres);
    
    // Ajouter struct Material { Difuse (renvoie la couleur du materiaux), Mirror (rebondi et renvoi le prochain point touché), light (éclaire), glass (passe au travers (rajouter un effet "fumé" pour différentier avec "rien")}
    
    // Pour le miroir, si je tombe sur un miroir je traverse et pars dans le sens opposé
    // Pour la lumière, lui donner une intensité, diviser l'intensité par la distance
    // Désactiver le facteurLumière quand on fait l'éclairage indirect
    
    
    
    
    
    
    
    
    GenerateImages(100000, 100001, spheres, m_ecran, Vector3(0, 0, 0));
    Vector3 direction{0, 0, 1};
    m_ecran.SetDirection(direction);
    GenerateImages(100001, 100002, spheres, m_ecran, Vector3(0, 0, 0));
    
    //    GenerateImages(0, 1, spheres, m_ecran2, Vector3(0, 0, 0));
    //    GenerateImages(2, 3, spheres, m_ecran3, Vector3(0, 0, 0));
    //    GenerateImages(3, 4, spheres, m_ecran4, Vector3(0, 0, 0));
    //    GenerateImages(4, 5, spheres, m_ecran5, Vector3(0, 0, 0));
    
    
    
    //        // Make camera move around a point
    ////        {
    typedef Vector3 Point;
    Point centreDeRotation = Point(0, 0, -400);
    //            float rayonRotation = 30;
    int index = 0;
    //            for (int i = -rayonRotation; i < rayonRotation; i++)
    //            {
    //                Point camPos = Point(i + 0., 0., fDeX(i, centreDeRotation, rayonRotation));
    //                m_ecran.SetPosition(camPos);
    //                m_ecran.SetDirection(centreDeRotation - camPos);
    //                GenerateImages(index, ++index, spheres, m_ecran, Vector3(0, 0, 0));
    //                cout << "(" << camPos.GetX() << "," << camPos.GetZ() << "),";
    //            }
    //
    //            for (int i = rayonRotation; i > -rayonRotation; i--)
    //            {
    //                // remplacer 100 par le Z du point autour duquel on tourne
    //                Point camPos = Point(i + 0., 0., -fDeX(i, centreDeRotation, rayonRotation) + 2 * centreDeRotation.GetZ());
    //                m_ecran.SetPosition(camPos);
    //                m_ecran.SetDirection(centreDeRotation - camPos);
    //                GenerateImages(index, ++index, spheres, m_ecran, Vector3(0, 0, 0));
    //                cout << "(" << camPos.GetX() << "," << camPos.GetZ() << "),";
    //            }
    ////        }
    
    
    
    
    
    
    //    cout << endl << endl;
    //    int nbParts = 30;
    //    for (int i = 1; i <= nbParts; i++)
    //    {
    //        const Vector3 posSphere = Vector3(0, 0, 0);
    //        const double rayonRotation = 30;
    //        const double cTeta = cos((2 * M_PI * i) / nbParts);
    //        const double sTeta = sin((2 * M_PI * i) / nbParts);
    //
    //        Vector3 camPos = Vector3(posSphere.GetX() + rayonRotation * cTeta, m_ecran.GetPosition().GetY(), posSphere.GetZ() + rayonRotation * sTeta);
    //        m_ecran.SetPosition(camPos);
    //        m_ecran.SetDirection(centreDeRotation - camPos);
    //        GenerateImages(index, index + 1, spheres, m_ecran, Vector3(0, 0, 0));
    //        index++;
    //        cout << "(" << camPos.GetX() << "," << camPos.GetZ() << "), ";
    //    }
    //    cout << endl << endl;
    
    
    
    
    //        LaunchThreads(50, spheres, ecran, Vector3(10, 0, 0));
    //        LaunchThreads(1000, spheres, ecran, Vector3(1, 0, 0));
    
    return 0;
}

//void ImageFromArray(const int& width, const int& height, const Image& pixelsArray, string& source = "/Users/Raph/Desktop/", string& nomImage = "imageSynthese.bmp")
void ImageFromArray(const Image& pixelsArray, const string source, const string nomImage, const Camera& ecran)
{
    bitmap_image img(ecran.GetWidth(), ecran.GetHeight());
    
    for (int index = 0; index < ecran.GetHeight() * ecran.GetWidth(); index++)
    {
        int x = index % ecran.GetWidth();
        int y = index / ecran.GetWidth();
        //        int index = y * ecran.GetWidth() + x;
        
        double r = pixelsArray[index].GetColor().GetR() > 255 ? 255 : pixelsArray[index].GetColor().GetR();
        double g = pixelsArray[index].GetColor().GetG() > 255 ? 255 : pixelsArray[index].GetColor().GetG();
        double b = pixelsArray[index].GetColor().GetB() > 255 ? 255 : pixelsArray[index].GetColor().GetB();
        
        if(r < 0 || g < 0 || b < 0)
        {
            cout << "color < 0 : (" << r << ", " << g << ", " << b << ")" << endl;
            exit(2);
            // EXIT CODE: 2 --> Un pixel avait une couleur < 0
        }
        
        img.set_pixel(x, y, r, g, b);
    }
    
    img.save_image(source + nomImage);
    //        img.save_image("imageSynthese.bmp");
    //    if (nomImage.find('0') != std::string::npos)
    //    {
    //        cout << "image sauvegardée dans " << source + nomImage << " !" << endl;
    //    }
}

void InitSpheres(Scene& spheres)
{
    // Enlever un 0 à 7000, 4000 et 15000
    Sphere leftWall = Sphere(Vector3(-4e5 - 7000., 0., -00.), 4e5, Material(EMaterialType::DifuseType, Vector3(0.2f, 0.8f, 0.2f)), "Vert");
    Sphere rightWall = Sphere(Vector3(4e5 + 7000., 0., -00.), 4e5, Material(EMaterialType::DifuseType, Vector3(0.2f, 0.8f, 0.8f)), "Bleu");
    Sphere topWall = Sphere(Vector3(0., -4e5 - 4000., -00.), 4e5, Material(EMaterialType::DifuseType, Vector3(0.8f, 0.2f, 0.8f)), "Rose");
    Sphere bottomWall = Sphere(Vector3(0., 4e5 + 4000., -00.), 4e5, Material(EMaterialType::DifuseType, Vector3(0.9f, 0.9f, 0.9f)), "Blanc");
    Sphere backWall = Sphere(Vector3(0., 0., 4e5 + 15000), 4e5, Material(EMaterialType::DifuseType, Vector3(0.8f, 0.2f, 0.2f)), "Rouge");
    Sphere frontWall = Sphere(Vector3(0., 0., -4e5 - 15000), 4e5, Material(EMaterialType::DifuseType, Vector3(0.8f, 0.8f, 0.2f)), "Jaune");
    
    
    
    //    spheres.push_back(Sphere(Vector3(500 - 500, 500 - 500, -150), 75, Material(DifuseType, Color{255, 0, 0}), "rouge")); // Rouge
    //    spheres.push_back(Sphere(Vector3(100 - 350, 800 - 500, -550), 50, Material(DifuseType, Color{0, 255, 0}), "verte")); // Verte
    //    spheres.push_back(Sphere(Vector3(800 - 500, 150 - 500, -250), 50, Material(DifuseType, Color{0, 0, 255}), "bleu")); // Bleu
    //    spheres.push_back(Sphere(Vector3(100 - 500, 800 - 1500, -850), 150, Material(DifuseType, Color{255, 0, 255}), "rose")); // Bleu éléctrique
    //    spheres.push_back(Sphere(Vector3(600 - 500, 600 - 500, -400), 100, Material(DifuseType, Color{0, 255, 255}), "bleuCiel")); // Bleu ciel
    //    spheres.push_back(Sphere(Vector3(500 - 500, 500 - 1500, -950), 200, Material(DifuseType, Color{255, 255, 0}), "jaune")); // Jaune
    //
    //
    //        spheres.push_back(Sphere(Vector3(-1000, 0, -400), 200, Material(EMaterialType::DifuseType, Color{0, 0, 255}), "Bleu")); // Bleu
    //    spheres.push_back(Sphere(Vector3(0, 0, -400), 200, Material(EMaterialType::DifuseType, Color{255, 255, 255}), "Blanc")); // Blanc
    //        spheres.push_back(Sphere(Vector3(1000, 0, -400), 200, Material(EMaterialType::DifuseType, Color{255, 0, 0}), "Rouge")); // Rouge
    //
    //    spheres.push_back(Sphere(Vector3(0, -800, -400), 200, Material(EMaterialType::DifuseType, Color{255, 0, 255}), "Rose")); // Rose
    //    spheres.push_back(Sphere(Vector3(0, 800, -400), 200, Material(EMaterialType::DifuseType, Color{255, 255, 0}), "Jaune")); // Jaune
    
    
    spheres.push_back(Sphere(Vector3(0, 0, 0), 10, Material(EMaterialType::DifuseType, Color{255, 0, 0}), "Rouge")); // Bleu
    
    //
    spheres.push_back(leftWall);
    spheres.push_back(rightWall);
    spheres.push_back(topWall);
    spheres.push_back(bottomWall);
    spheres.push_back(frontWall);
    spheres.push_back(backWall);
    
    spheres.push_back(Sphere(Vector3(lumiere.GetPosition()), 20, Material(EMaterialType::LightType, Color{255 * (1 / facteurLumiere), 0, 0}), "lampe")); // blanc
    
    
    //    spheres.push_back(Sphere(Vector3(lumiere.position.x, lumiere.position.y, lumiere.position.z), 5, Color{255, 255, 255}, "lampe", 0)); // blanc
}

int RunTests()
{
    return RUN_ALL_TESTS();
}

void MoveLight (Light& lumiere, const Vector3 direction, Sphere& lightSphere)
{
    //    lumiere.SetPosition(lumiere.GetPosition() + direction);
    //    lightSphere.SetCenter(lumiere.GetPosition());
}

//void MoveLight (Light& lumiere, const Vector3 direction, Scene spheres)
//{
//    lumiere.SetPosition(lumiere.GetPosition() + direction);
//    spheres[0].SetOrigine(spheres[0].GetOrigine() + Vector3(1, 0, 0));
//}

void ClearImage (Image& imageArray, const Camera& ecran)
{
    for (int i = 0; i < ecran.GetHeight(); i++)
    {
        for (int j = 0; j < ecran.GetWidth(); j++)
        {
            imageArray[i * j].SetColor(Color(0, 0, 0));
        }
    }
}

void GenerateImages(const int firstImage, const int lastImage, Scene spheres, Camera& ecran, const Vector3& MoveLightDirection)
{
    Light theLight = lumiere;
    
    
    //    if (!(MoveLightDirection == Vector3(0,0,0)))
    //    {
    //        for (Sphere& sphere : spheres)
    //        {
    //            if (EMaterialType::LightType != sphere.GetMaterial().m_materialType)
    //            {
    //                continue;
    //            }
    //
    //            for (int i = 0; i < firstImage; i++)
    //            {
    //                MoveLight(theLight, MoveLightDirection, sphere);
    //            }
    //        }
    //    }
    
    //    Image image(ecran.GetWidth() * ecran.GetHeight(), Pixel(Vector3(0, 0, 0), Color{0, 0, 0}));
    Image image = ecran.GetImage();
    
    for (int i = firstImage; i < lastImage; i++)
    {
        //        Image image(ecran.GetWidth() * ecran.GetHeight(), Color{44, 117, 255});
        
        
        for (int i = 0; i < ecran.GetHeight() * ecran.GetWidth(); i++)
        {
            // Pour un écran de 1000 * 1000
            // 0 * 0  -->  1000 * 1000
            const int x = i % ecran.GetWidth();
            const int y = i / ecran.GetWidth();
            
            // -500, -500  -->  500, 500
            const int indexX = x - ecran.GetWidth() / 2;
            const int indexY = y - ecran.GetHeight() / 2;
            
            // distance to intersection, to keep only the first one
            double dist = DBL_MAX;
            Sphere sphereTouchee;
            Intersection result;
            
            for (const Sphere& sphereEnTest : spheres)
            {
                // Position of the center of the camera + the x & y shift
                //                    const Vector3 pointOnScreen = Vector3(indexX + .0, indexY + .0, ((- ecran.GetDirection().GetX()) * indexX) / (ecran.GetDirection().GetZ()));
                //                    pointOnScreen.Print();
                
                const Vector3 pointOnScreen = image[i].GetPosition();
                
                //                const Vector3 pointOnScreen = ecran.GetPosition() + Vector3(indexX + 0., indexY + 0., ecran.GetPosition().GetZ());
                const Vector3 dir{indexX, indexY, 0};
                Vector3 focalDir = ecran.GetFocalDirection(dir);
                const Rayon rayon = Rayon(pointOnScreen, focalDir);
                //                    const Rayon rayon = Rayon(pointOnScreen, ecran.GetDirection());
                
                
                //                const Rayon rayon = Rayon(pointOnScreen, ecran.GetDirection());
                Intersect(rayon, sphereEnTest, result);
                
                if (!result.intersect || result.distance >= dist)
                {
                    continue;
                }
                
                dist = result.distance;
                sphereTouchee = sphereEnTest;
            }
            
            if (DBL_MAX != dist)
            {
                //                const int index = y * ecran.GetWidth() + x;
                
                //                image[index].SetColor(sphereTouchee.GetMaterial().GetColor());
                
                
                image[i].SetColor(sphereTouchee.GetMaterial().GetColor());
                
                
                
                // Vérifier CanSeeLight <-- !!!
                if (CanSeeLight(result.point, theLight, spheres))
                {
                    SetLightning(result.point, i, theLight, image);
                }
                else
                {
                    Color col = image[i].GetColor();
                    image[i].SetColor(Color(col.GetR() * facteurLumiere, col.GetG() * facteurLumiere, col.GetB() * facteurLumiere));
                    //                        image[index].GetColor().SetR(image[index].GetColor().GetR() * facteurLumiere);
                    //                        image[index].GetColor().SetG(image[index].GetColor().GetG() * facteurLumiere);
                    //                        image[index].GetColor().SetB(image[index].GetColor().GetB() * facteurLumiere);
                }
            }
            
            //            if (y % 10 == 0)
            //            {
            ////                const string nomImage = "01Scene" + to_string(i + 1 + y + ecran.GetWidth() / 2) + ".bmp";
            //                const string nomImage = "image" + to_string(i) + ".bmp";
            //                const string source = "/Users/Raph/Desktop/TestSynthese/";
            //                ImageFromArray(image, source, nomImage);
            //            }
        }
        
        
        //        CreateSpheresBoxes(boxes, spheres);
        //        BoundingBox bBox = BoundingBox(boxes);
        //        bBox.source = superBBType;
        //        bBox.Print();
        //
        //        for (int y = 0; y < ecran.height; y++)
        //        {
        //            for (int z = 0; z < ecran.width; z++)
        //            {
        //                //            for (const Box& b : boxes)
        //                //            {
        //                const Rayon rayon = Rayon(ecran.position + Vector3(static_cast<int>(ecran.position.x), y, z), Vector3(1, 0, 0));
        //                if (IntersectBBox(rayon, bBox))
        //                {
        //                    if (sphereType == bBox.source)
        //                    {
        //                        // vert == chaques boxes
        //                        image[y * ecran.height + z] = Color{0, 255, 0};
        //                    }else if (boundingBoxType == bBox.source)
        //                    {
        //                        // rouge == bounding box
        //                        image[y * ecran.height + z] = Color{255, 0, 0};
        //                    }else if (superBBType == bBox.source)
        //                    {
        //                        // bleu == la boite unique
        //                        image[y * ecran.height + z] = Color{0, 0, 255};
        //                    }else
        //                    {
        //                        // jaune == on ne sait pas
        //                        image[y * ecran.height + z] = Color{0, 255, 255};
        //                    }
        //                }
        //                //            }
        //            }
        //        }
        
        
        
        
        const string nomImage = "image" + to_string(i) + ".bmp";
        const string source = "/Users/Raph/Desktop/TestSynthese/";
        ImageFromArray(image, source, nomImage, ecran);
        
        MoveLight(theLight, MoveLightDirection, spheres[spheres.size() - 1]);
        spheres[6].GetCenter() = theLight.GetPosition();
        ClearImage(image, ecran);
    }
    
}

void LaunchThreads(const int nbImages, Scene& spheres, const Camera& ecran, const Vector3& directionLight)
{
    int _nbImages = nbImages;
    while (0 != _nbImages % 50)
    {
        _nbImages++;
    }
    
    // nbImages / images par thread / nb threads
    for (int i = 0; i < (_nbImages / 5 / 10); i++)
    {
        /*std::thread t1(GenerateImages, i * 50 + 0, i * 50 + 5, spheres, std::ref(ecran), directionLight);
        std::thread t2(GenerateImages, i * 50 + 5, i * 50 + 10, spheres, std::ref(ecran), directionLight);
        std::thread t3(GenerateImages, i * 50 + 10, i * 50 + 15, (spheres), std::ref(ecran), directionLight);
        std::thread t4(GenerateImages, i * 50 + 15, i * 50 + 20, (spheres), std::ref(ecran), directionLight);
        std::thread t5(GenerateImages, i * 50 + 20, i * 50 + 25, (spheres), std::ref(ecran), directionLight);
        
        std::thread t6(GenerateImages, i * 50 + 25, i * 50 + 30, (spheres), std::ref(ecran), directionLight);
        std::thread t7(GenerateImages, i * 50 + 30, i * 50 + 35, (spheres), std::ref(ecran), directionLight);
        std::thread t8(GenerateImages, i * 50 + 35, i * 50 + 40, (spheres), std::ref(ecran), directionLight);
        std::thread t9(GenerateImages, i * 50 + 40, i * 50 + 45, (spheres), std::ref(ecran), directionLight);
        std::thread t10(GenerateImages, i * 50 + 45, i * 50 + 50, (spheres), std::ref(ecran), directionLight);
        
        t1.join();
        cout << "Thread 1 terminé" << endl;
        t2.join();
        cout << "Thread 2 terminé" << endl;
        t3.join();
        cout << "Thread 3 terminé" << endl;
        t4.join();
        cout << "Thread 4 terminé" << endl;
        t5.join();
        cout << "Thread 5 terminé" << endl;
        
        t6.join();
        cout << "Thread 6 terminé" << endl;
        t7.join();
        cout << "Thread 7 terminé" << endl;
        t8.join();
        cout << "Thread 8 terminé" << endl;
        t9.join();
        cout << "Thread 9 terminé" << endl;
        t10.join();
        cout << "Thread 10 terminé" << endl;
        
        cout << "Série " << i + 1 << " sur " << (_nbImages / 5 / 10) << " terminée" << endl;*/
    }
    
}





// radiance(rayon, scene) -> couleur

// intensité lumineuse sauvegardée dans l'image ^1/2.2
