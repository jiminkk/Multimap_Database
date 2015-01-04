//
//  main.cpp
//  Project_4
//
//  Created by Jasmine on 3/8/14.
//  Copyright (c) 2014 Jasmine. All rights reserved.
//
/*
#include <iostream>
#include "MultiMap.h"
using namespace std;

int main()
{
    MultiMap myMultiMap;
    myMultiMap.insert("Andrea", 6);
    myMultiMap.insert("Bill", 2);
    myMultiMap.insert("Carey", 5);
    myMultiMap.insert("Bill", 8);
    myMultiMap.insert("Batia", 4);
    myMultiMap.insert("Larry", 7);
    myMultiMap.insert("Larry", 9);
    myMultiMap.insert("Bill", 3);
    myMultiMap.insert("Bill", 4);
    myMultiMap.insert("Larry", 3);
    
    // Start at the earliest-occurring association with key "Bill"
    MultiMap::Iterator it = myMultiMap.findEqualOrPredecessor("Carey");
    while (it.valid())
    {
        cout << it.getKey() << " " << it.getValue() << endl;
        it.next(); // advance to the next associaton
    }
    return 0;
}
*/

#include "test.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    string filename;
    
    switch (argc)
    {
        case 1:
            cout << "Enter test script file name: ";
            getline(cin, filename);
            break;
        case 2:
            filename = argv[1];
            break;
        default:
            cout << "Usage: " << argv[0] << " scriptname" << endl;
            return 1;
    }
    
    Test t;
    string problem;
    
    if (!t.loadAndRunTestScript(filename, problem))
    {
        cout << "Problem running script: " << problem << endl;
        return 1;
    }
}






