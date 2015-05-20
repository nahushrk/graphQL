//
//  main.cpp
//  graphQl
//
//  Created by Nahush Kulkarni on 3/22/15.
//  Copyright (c) 2015 Nahush Kulkarni. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "globalDataStore.h"
#include "graphLoader.h"
#include "feasibleMates.h"
#include "edgeMatching.h"

using namespace std;


int main(int argc, const char * argv[])
{
	loadGraphFromFile();
    printGraph();
    
    loadPatternFromFile();
    printPattern();
	
//    findFeasibleMates();
	findFeasibleMatesUsingLabel();
    printFeasibleMates();
	
	
	initializeFeasibleMappings();
	
	searchFunction(0);
	
	
    return 0;
}