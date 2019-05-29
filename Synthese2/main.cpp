//
//  main.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#include <main.hpp>
#include <gtests/UnitsTests.hpp>

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RunTests();
    
    
    return 0;
}

int RunTests()
{
    return RUN_ALL_TESTS();
}
