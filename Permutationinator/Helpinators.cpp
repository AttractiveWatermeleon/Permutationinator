#include "Helpinators.h"
#include <iostream>
#include <algorithm>
//using namespace std;



// Helper function to convert keys into their integer values for easier calculation. Not strictly necessary,
// But I find it easier to work with than the ASCII values.

int* convertKeyToInts(std::string inputKey)
{
    static int resultArray[25];
    int result;
    transform(inputKey.begin(), inputKey.end(), inputKey.begin(), std::toupper);
    for (int i = 0; i < 25; i++)
    {
        result = inputKey[i];
        resultArray[i] = result - 64;
    }
    return resultArray;
}

// I have no doubt having two functions that do the exact same thing is stupid. 
// Regardless, C++ yelled at me when I tried to pass it a const variable for the array size,
// And I'm scared of confrontation (really lazy) and so I just did this instead. 
// Still works c: 

int* convertTextToInts(std::string inputText)
{
    static int resultArray[10];
    int result;
    transform(inputText.begin(), inputText.end(), inputText.begin(), std::toupper);
    for (int i = 0; i < 10; i++)
    {
        result = inputText[i];
        resultArray[i] = result - 64;
    }
    return resultArray;
}


// Create a 2D Array representing the four square cipher using the keys (hardcoded below, I'm still lazy). 
int** createSquare(int toSquare[25])
{
    int i = 0;
    int** arr = new int* [5];
    for (int row = 0; row < 5; ++row)
    {
        arr[row] = new int[5];
        for (int column = 0; column < 5; ++column)
        {
            arr[row][column] = toSquare[i];
            i++;
        }

    }
    return arr;
}


// The big boy function
std::string performEncryption(std::string plainText)
{
    // Key setting
    std::string square1key = "OUTCASBDEFGHIKLMNPQRVWXYZ";
    std::string square2key = "TWOFACEDBGHIKLMNPQRSUVXYZ";
    std::string square3key = "GRUDEABCFHIKLMNOPQSTVWXYZ";
    std::string square4key = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    // Creating squares for decoding - converting to ints first to make it easier to work with.
    int* square1Ints = convertKeyToInts(square1key);
    int** square1 = createSquare(square1Ints);

    int* square2Ints = convertKeyToInts(square2key);
    int** square2 = createSquare(square2Ints);

    int* square3Ints = convertKeyToInts(square3key);
    int** square3 = createSquare(square3Ints);

    int* square4Ints = convertKeyToInts(square4key);
    int** square4 = createSquare(square4Ints);

    // Convert the plaintext into ints to make everything easier to work with. 
    int* newText = convertTextToInts(plainText);

    int coordsSquare2[2] = { 0,0 };
    int coordsSquare3[2] = { 0,0 };
    int i = 0;
    std::string output;


    // This section is responsible for performing the actual encryption. It treats the four squares like a 10x10 grid,
    // searching squares 2 and 3 for the first pair of letters in the plaintext and getting their coordinates.
    // It is hardcoded to use a 10 character string here for our purposes. Easy to make modular if you want. 
    while (i < 10)
    {
        for (int a = 0; a < 5; a++)
        {
            for (int b = 0; b < 5; b++)
            {
                if (square2[a][b] == newText[i])
                {
                    coordsSquare2[0] = a;               // Stays 0, grid goes top-down
                    coordsSquare2[1] = b + 5;           // Add 5 to add space for Square 1 
                }
            }
        }
        i++;
        for (int a = 0; a < 5; a++)
        {
            for (int b = 0; b < 5; b++)
            {
                if (square3[a][b] == newText[i])
                {
                    coordsSquare3[0] = a + 5;
                    coordsSquare3[1] = b;
                }
            }
        }
        i++;

        // This section calculates the coordinates of the encrypted pairs on squares 1 and 4 using the min and max 
        // coordinates from squares 2 and 3, finishing the encryption.
        int coordsSquare1[2] = { std::min(coordsSquare2[0], coordsSquare3[0]), std::min(coordsSquare2[1], coordsSquare3[1]) };
        int coordsSquare4[2] = { std::max(coordsSquare2[0], coordsSquare3[0]), std::max(coordsSquare2[1], coordsSquare3[1]) };

        // The result is then converted back from int to char by adding 64 creating the ASCII code for the respective
        // capitalised letter, then adding it to a string. This ends the while loop. 
        output.push_back(char(square1[coordsSquare1[0]][coordsSquare1[1]] + 64));
        output.push_back(char(square4[coordsSquare4[0] - 5][coordsSquare4[1] - 5] + 64));
    }

    return output;
}