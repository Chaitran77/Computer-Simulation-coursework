#include <stdio.h>

// calculates the squares of all the numbers between 0 and 200 without a multiply operation
// Constructs used:
// Initialising (to zeros) and writing to an array
// for loop with a loop nested inside. => iterator assigment, compare operations, increment operations.

// Written by Kiran

int squares[201] = {0};

int main() {

    for (int i = 0; i <= 200; i++)
    {

        // IF array not initialised to zeros, can run the following here, makes use of this loop
        // squares[i] = 0;

        // Add i to the current element in the array i(=j) times 
        for (int j = 0; j < i; j++) {
            squares[i] = squares[i] + i;
        }
    
        printf("%d \n", squares[i]);
    }

    return 0;
}
