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
    int rank;/*number of subtrees are under include me*/
    struct DataStructure* left;
    struct DataStructure* right;
    struct DataStructure* parent;
    int height;
    struct DataStructure* subTree;
} DataStructure;

static DataStructure* HelpTree= (struct DataStructure*)malloc(sizeof(struct DataStructure));
int flag = 0;
int s;

int getHeight(struct DataStructure* n) {
    if (n == NULL)
        return 0;
    return n->height;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}

int getRank(DataStructure* node)
{
    if (!node)
    {
        return 0;
    }
    return node->rank;
}

int SideHeavy(struct DataStructure* n) {
    if (n == NULL) {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

struct DataStructure* rightRotate(struct DataStructure* ds) {
    struct DataStructure* x = ds->left;
    struct DataStructure* T2 = x->right;

    x->right = ds;
    ds->left = T2;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    ds->height = max(getHeight(ds->right), getHeight(ds->left)) + 1;
    /*update ranks*/
    ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
    x->rank = getRank(x->left) + getRank(x->right) + 1;

    x->parent = ds->parent;
    ds->parent = x;
    if (T2 != NULL)
        T2->parent = ds;

    return x;
}

struct DataStructure* leftRotate(struct DataStructure* ds) {
    struct DataStructure* y = ds->right;
    struct DataStructure* T2 = y->left;

    y->left = ds;
    ds->right = T2;

    ds->height = max(getHeight(ds->right), getHeight(ds->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    /*update ranks*/
    ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
    y->rank = getRank(y->left) + getRank(y->right) + 1;

    y->parent = ds->parent;
    ds->parent = y;
    if (T2 != NULL)
        T2->parent = ds;

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

/*insert by quality function and insert into helpTree the values but sorted by the time not qualtiy*/
struct DataStructure* insert(struct DataStructure* node, int quality, int time) {
    if(quality == s)
        flag = 1;
    if (node == NULL)
        return  Init(quality, time);
    if (quality == node->quality)
    {
        node->subTree = insertIntoSubTree(node->subTree, time, time);
        return node;
    }
    if (quality < node->quality) {
        node->left = insert(node->left, quality, time);
        node->left->parent = node;
    }
    if (time < HelpTree->time)
    {
        HelpTree->left = insert(HelpTree->left, time, quality);
    }
    if (time > HelpTree->time)
    {
        HelpTree->left = insert(HelpTree->right, time, quality);
    }
    else if (quality > node->quality){
        node->right = insert(node->right, quality, time);
        node->right->parent = node;
    }
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    node->rank = getRank(node->left) + getRank(node->right) + 1;
    MakeItBalance(node, quality);
    return node;
}
/*function to insert into the subtree*/
struct DataStructure* insertIntoSubTree(struct DataStructure* node, int quality, int time) {
    if (node == NULL)
        return  Init(quality,time);
    if (quality < node->quality) {
        node->left = insert(node->left, quality, time);
        node->left->parent = node;
    }
    else if (quality > node->quality) {
        node->right = insert(node->right, quality, time);
        node->right->parent = node;
    }
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

        else if(ds->quality == k)/*k=the quality*/
            return ds;
    }
    return NULL;
}

/*initiate the tree with defulat values*/
DataStructure* Init(int s)
{
    struct DataStructure* ds = (struct DataStructure*)malloc(sizeof(struct DataStructure));
    ds->quality = NULL;
    ds->time = NULL;
    ds->left = NULL;
    ds->right = NULL;
    ds->parent = NULL;
    ds->height = 0;
    ds->rank = 0;

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
    ds->parent = NULL;
    ds->height = 0;
    ds->rank = 0;
    struct DataStructure* AVL = (struct DataStructure*)malloc(sizeof(struct DataStructure));
    return ds;
}

void AddProduct(DataStructure* ds, int time, int quality)
{
    insert(ds, quality, time);
}
void RemoveProduct(DataStructure* ds, int time)
{
    int q;
    if(ds == NULL) return;
    DataStructure* Wanted = avl_search(HelpTree, time);
    int ToRemoveInMain = Wanted->time;
    if (Wanted != NULL)
    {
        HelpTree =  Remove( HelpTree , time);
        DataStructure* WantedQ = avl_search(ds, ToRemoveInMain);
        WantedQ->subTree =  Remove(WantedQ->subTree, WantedQ->time);
        if(WantedQ->subTree == NULL)
            RemoveQuality(ds, WantedQ->quality);
    }
}
DataStructure* Remove(DataStructure* Tree, int time)
{
    if(Tree == NULL)
        return NULL;
    DataStructure* Wanted = avl_search(Tree, time);
    if(Wanted->left == NULL && Wanted->right == NULL)
    {
        free(Wanted);
        MakeItBalance(Wanted->parent , Wanted->parent->quality );
    }
    DataStructure* Suc = Successor_avl(Wanted);
    Suc->parent->left = Suc->right;
    int ToBalance = Suc->parent->quality;
    Suc->parent = Wanted->parent;
    if(Wanted->parent->left != Wanted)
        Wanted->parent->right = Wanted;
    else  Wanted->parent->left = Wanted;
    Suc->left = Wanted->left;
    Suc->right = Wanted-> right;
    if (Wanted->left)
        Wanted->left->parent = Suc;
    else Suc-> left = NULL;
    if (Wanted->right)
        Wanted->right->parent = Suc;
    else Wanted->right = NULL;
    Suc->height = max(getHeight(Suc->right), getHeight(Suc->left)) + 1;
    Suc->rank = getRank(Suc->left) + getRank(Suc->right) + 1;
    free(Wanted);
    MakeItBalance(Suc->parent , ToBalance );
    return Tree;

}
DataStructure* Successor_avl(DataStructure* Tree)
{
    if(Tree->right != NULL)
        return min( Tree->right);
    if(Tree->left != NULL)
        return Tree->left;
    return  Tree;
}
void RemoveQuality(DataStructure* ds, int quality)
{
    DataStructure* WantedQ = avl_search( ds,  quality);
    while(WantedQ->subTree != NULL)
    {
        HelpTree = Remove(HelpTree, WantedQ->subTree->quality);
        WantedQ->subTree =  Remove(WantedQ->subTree, WantedQ->subTree->quality);
    }
    ds = Remove(ds, quality);
}
/*
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
            /*we found the node
            ds->rank--;
            if (ds->left == NULL || ds->right == NULL)
                free(ds);

            else
            {
                int MinValue = min(ds->right)->quality;
                DataStructure* NewRoot = Init(MinValue);
                RemoveQuality(ds->right, MinValue);
                NewRoot->left = ds->left;
                NewRoot->right = ds->right;
                if (NewRoot->left)
                    NewRoot->left->parent = NewRoot;
                if (NewRoot->right)
                    NewRoot->right->parent = NewRoot;
                /*update height*/
                NewRoot->height = max(getHeight(NewRoot->right), getHeight(NewRoot->left)) + 1;
                NewRoot->rank = getRank(NewRoot->left) + getRank(NewRoot->right) + 1;
                free(ds);
                /*balance the tree:
                MakeItBalance(NewRoot, quality);
            }

        }
    }
}*/

int GetIthRankProduct(DataStructure* ds, int i)
{

        int root_rank;

        if (ds==NULL)
            return NULL;

        /*calculate the rank of the root*/
        if (ds->left == NULL)
            root_rank = 1;
        else
            root_rank = ds->left->height + 1;

        /*If the kth smallest node is the root node, return the root*/
        if (i == root_rank)
            return ds->quality;

        /*If the kth smallest node is in the left subtree */
        if (i < root_rank)
            GetIthRankProduct(ds->left, i);

        /*If the kth smallest node is in the right subtree */
        else
            GetIthRankProduct(ds->right, i - root_rank);

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
