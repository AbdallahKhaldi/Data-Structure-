/* Relevant includes, you may not use any other includes */
#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------------*/
/* My full name: Daniel ABC*/
/* My friend's full name: Rose CBA*/

/* My Id: 123456789 */
/* My friend's Id: 987654321 */
/*--------------------------------------------*/

/* Make sure to use good names for your functions and variables. */
/* Make sure to use functions whenever possible to write readable, reliable and easy to understand code. */
/* This will yield a bonus of up to +10 points */

/* Please read the instructions in the PDF file carefully. */


/* You may not change the name "DataStructure" */
/* You may not change the function names and their signatures.*/
typedef struct DataStructure {
    int quality;
    int time;
    struct DataStructure* left;
    struct DataStructure* right;
    int height;
    struct DataStructure* subTree;
    /* IMPLEMENT, you may add any fields and data structures of your choosing */
} DataStructure;


DataStructure Init(int s)
{
    /* IMPLEMENT */
}

void AddProduct(DataStructure* ds, int time, int quality)
{
    /* IMPLEMENT */
}

void RemoveProduct(DataStructure* ds, int time)
{
    /* IMPLEMENT */
}

void RemoveQuality(DataStructure* ds, int quality)
{
    /* IMPLEMENT */
}

int GetIthRankProduct(DataStructure ds, int i)
{
    /* IMPLEMENT */
}

int GetIthRankProductBetween(DataStructure ds, int time1, int time2, int i)
{
    /* IMPLEMENT */
}

int Exists(DataStructure ds)
{
    /* IMPLEMENT */
}

int Search(DataStructure ds, int x)
{
    if(x > ds.quality)
       return Search(ds.right,x);
    else if (x < ds.quality)
}


/* You may use any implementation of the main function you like. */
/* We will be deleting your main implementation and replacing it with our own implementation to test your code. */
/* You may submit the code to moodle without a main function */
/* Please test your code as thoroughly as you can. No tests have been provided for this homework. */
/* Your submitted code must not print any messages or scan any variables */
int main()
{
    return 0;
}