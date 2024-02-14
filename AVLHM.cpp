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
} DataStructure;


int getHeight(struct DataStructure* n) {
    if (n == NULL)
        return 0;
    return n->height;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}

int SideHeavy(struct DataStructure* n) {
    if (n == NULL) {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

struct DataStructure* rightRotate(struct DataStructure* y) {
    struct DataStructure* x = y->left;
    struct DataStructure* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

    return x;
}

struct DataStructure* leftRotate(struct DataStructure* x) {
    struct DataStructure* y = x->right;
    struct DataStructure* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

    return y;
}
/*Balance the tree(we use it while inserting and deleting)*/
struct DataStructure* MakeItBalance(struct DataStructure* ds, int quality)
{
    int factor = SideHeavy(ds);

    /* Left Left Case*/
    if (factor > 1 && quality < ds->left->quality) {
        return rightRotate(ds);
    }
    /* Right Right Case*/
    if (factor<-1 && quality > ds->right->quality) {
        return leftRotate(ds);
    }
    /* Left Right Case*/
    if (factor > 1 && quality > ds->left->quality) {
        ds->left = leftRotate(ds->left);
        return rightRotate(ds);
    }
    /* Right Left Case*/
    if (factor < -1 && quality < ds->right->quality) {
        ds->right = rightRotate(ds->right);
        return leftRotate(ds);
    }
    return ds;
}

/*insert by quality function*/
struct DataStructure* insert(struct DataStructure* node, int quality, int time) {
    if (node == NULL)
        return  Init(quality);
    if (quality == node->quality)
    {
        node->subTree = insertIntoSubTree(node->subTree, time, time);
        return node;
    }
    if (quality < node->quality)
        node->left = insert(node->left, quality, time);
    else if (quality > node->quality)
        node->right = insert(node->right, quality, time);

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    MakeItBalance(node, quality);
    return node;
}
/*function to insert into the subtree*/
struct DataStructure* insertIntoSubTree(struct DataStructure* node, int quality, int time) {
    if (node == NULL)
        return  Init(quality);
    if (quality < node->quality)
        node->left = insert(node->left, quality, time);
    else if (quality > node->quality)
        node->right = insert(node->right, quality, time);

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    MakeItBalance(node, quality);
    return node;
}
/*find min node*/
DataStructure* min(DataStructure* ds)
{
    DataStructure* temp = ds;
    if (!ds)
    {
        while (temp->left != NULL)
            temp = temp->left;
    }
    return temp;
}
/*find max node*/
DataStructure* maxval(DataStructure* ds)
{
    if (!ds->right)
        return ds;
    else
        maxval(ds->right);/**/
}
/*search in the tree by quality*/
DataStructure* avl_search(DataStructure* ds, int k)
{
    if (ds != NULL)
    {
        if (k < ds->quality)
            return avl_search(ds->left, k);

        else if (k > ds->quality)
            return avl_search(ds->right, k);

        else /*k=the quality*/
            return ds;


    }
    return NULL;
}

/*initiate the tree with defulat values*/
DataStructure* Init(int s)
{
    struct DataStructure* ds = (struct DataStructure*)malloc(sizeof(struct DataStructure));
    ds->quality = s;
    ds->time = 0;
    ds->left = NULL;
    ds->right = NULL;
    ds->height = 1;
    struct DataStructure* AVL = (struct DataStructure*)malloc(sizeof(struct DataStructure));
    return ds;
}

/*initate the new node with quality and time(overloading function)*/
DataStructure* Init(int quality, int time)
{
    struct DataStructure* ds = (struct DataStructure*)malloc(sizeof(struct DataStructure));
    ds->quality = quality;
    ds->time = time;
    ds->left = NULL;
    ds->right = NULL;
    ds->height = 1;
    struct DataStructure* AVL = (struct DataStructure*)malloc(sizeof(struct DataStructure));
    return ds;
}

void AddProduct(DataStructure* ds, int time, int quality)
{
    insert(ds, quality, time);
}

void RemoveProduct(DataStructure* ds, int time)
{
    /* IMPLEMENT */
}

void RemoveQuality(DataStructure* ds, int quality)
{
    if (ds == NULL) return;
    if (avl_search(ds, quality) != NULL)
    {
        if (ds->quality < quality)
            RemoveQuality(ds->right, quality);
        else if (ds->quality > quality)
            RemoveQuality(ds->left, quality);
        else
        {
            /*we found the node*/
            if (ds->left == NULL || ds->right == NULL)
                free(ds);

            else
            {
                int minval = min(ds->right)->quality;
                DataStructure* newRoot = Init(minval);
                RemoveQuality(ds->right, minval);
                newRoot->left = ds->left;
                newRoot->right = ds->right;
                /*update height*/
                newRoot->height = max(getHeight(newRoot->right), getHeight(newRoot->left)) + 1;
                free(ds);
                /*balance the tree:*/
                MakeItBalance(newRoot, quality);
            }

        }
    }
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


/* You may use any implementation of the main function you like. */
/* We will be deleting your main implementation and replacing it with our own implementation to test your code. */
/* You may submit the code to moodle without a main function */
/* Please test your code as thoroughly as you can. No tests have been provided for this homework. */
/* Your submitted code must not print any messages or scan any variables */
int main()
{
    return 0;
}

