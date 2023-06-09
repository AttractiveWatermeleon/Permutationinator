#pragma once
#include <iostream>
using namespace std;

int* convertKeyToInts(string inputKey);

int* convertTextToInts(string inputText);

int** createSquare(int toSquare[25]);

string performEncryption(string plainText);