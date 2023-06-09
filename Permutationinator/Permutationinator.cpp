/*
* I've been waiting for you! I'm here to present my greatest invention to date;
* The Permutationinator! The code is gonna be sloppy as I'm a beginner programmer but it does its job.
* You're more than welcome to use it and make adjustments wherever you need.
*/ 

#include "Helpinators.h"
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

int main()
{
    int i = 0;
    string pigpenString = { "thwoddlnfr" };
    string outputString;
    ofstream myFile;
    
    
    // Sort the string for the later next_permutation function
    sort(pigpenString.begin(), pigpenString.end());

    int size = sizeof(pigpenString) / sizeof(pigpenString[0]);

    // Open the file for writing...
    myFile.open("output.csv");

    // encrypt the string, check if the first character is S, and if it is - write it to the file. 
    // Do this for every permutation of the string. 

    cout << "Working...";
    do 
    {
        // see Helpinators.cpp for details
        outputString = performEncryption(pigpenString);
        if (outputString[0] == 'S')
        {
            myFile << outputString + "\n";
        }
        i++;
    } 
    while (next_permutation(pigpenString.begin(), pigpenString.end()));
    myFile.close();
    cout << "Done!";
}
