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
    int minQuality, maxQuality;
    struct DataStructure* left;
    struct DataStructure* right;
    struct DataStructure* parent;
    int height;
    struct DataStructure* subTree;
} DataStructure;

struct DataStructure* HelpTree = (struct DataStructure*)malloc(sizeof(struct DataStructure));
int flag = 0;
int S;

DataStructure* Init(int s);
DataStructure* Init2(int quality, int time);
void  AddProduct(DataStructure* ds, int time, int quality);
DataStructure* Remove(DataStructure* Tree, int time);
int GetIthRankProduct(DataStructure* ds, int i);
struct DataStructure* insertIntoSubTree(struct DataStructure* node, int quality, int time);
void RemoveQuality(DataStructure* ds, int quality);
DataStructure* Successor_avl(DataStructure* Tree);
DataStructure* avl_search(DataStructure* ds, int k);
struct DataStructure* insertIntoHelpTree(DataStructure* ds, int time, int quality);
void insert(DataStructure *pStructure, int time, int quality);
void insertMain(struct DataStructure* ds, int time, int quality);

int getHeight(struct DataStructure* n) {
    if (n == NULL)
        return 0;
    return n->height;
}


int Getmax(int a, int b) {
    return (a > b) ? a : b;
}
int Getmin(int a, int b) {
    return (a > b) ? b : a;
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
void UpdateMinAndMax(DataStructure* ds)
{
    if (ds->left != NULL && HelpTree->right != NULL)
    {
        ds->minQuality = Getmin(ds->quality, Getmin(ds->left->minQuality, ds->right->minQuality));
        ds->maxQuality = Getmax(ds->quality, Getmax(ds->left->maxQuality, ds->right->maxQuality));
    }
    else if (ds->left == NULL && ds->right != NULL) {
        ds->minQuality = Getmin(ds->quality, ds->right->minQuality);
        ds->maxQuality = Getmax(ds->quality, ds->right->maxQuality);
    }
    else if (ds->left != NULL && ds->right == NULL) {
        ds->minQuality = Getmin(ds->quality, ds->left->minQuality);
        ds->maxQuality = Getmax(ds->quality, ds->left->maxQuality);
    }
    else
    {
        ds->minQuality = ds->quality;
        ds->maxQuality = ds->quality;
    }
}

struct DataStructure* rightRotate(struct DataStructure* ds) {
    struct DataStructure* x = ds->left;
    struct DataStructure* T2 = x->right;

    x->right = ds;
    ds->left = T2;

    x->height = Getmax(getHeight(x->right), getHeight(x->left)) + 1;
    ds->height = Getmax(getHeight(ds->right), getHeight(ds->left)) + 1;


    /*update ranks*/
    ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
    x->rank = getRank(x->left) + getRank(x->right) + 1;
    /*update parents*/
    x->parent = ds->parent;
    ds->parent = x;
    //UpdateMinAndMax(ds);
    //UpdateMinAndMax(x);

    if (T2 != NULL)
        T2->parent = ds;

    return x;
}

struct DataStructure* leftRotate(struct DataStructure* ds) {
    struct DataStructure* y = ds->right;
    struct DataStructure* T2 = y->left;

    y->left = ds;
    ds->right = T2;

    ds->height = Getmax(getHeight(ds->right), getHeight(ds->left)) + 1;
    y->height = Getmax(getHeight(y->right), getHeight(y->left)) + 1;

    /*update ranks*/
    ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
    y->rank = getRank(y->left) + getRank(y->right) + 1;
    /*update parents*/
    y->parent = ds->parent;
    ds->parent = y;
    /*update min and max in the subtrees*/
    //UpdateMinAndMax(ds);
    //UpdateMinAndMax(y);

    if (T2 != NULL)
        T2->parent = ds;

    return y;
}
/*Balance the tree(we use it while inserting and deleting)*/
struct DataStructure* MakeItBalance(struct DataStructure* ds, int quality)
{

    int factor = SideHeavy(ds);

    /* Left Left Case*/
    if (factor > 1 && SideHeavy(ds->left) >= 0) {
        return rightRotate(ds);
    }
    /* Right Right Case*/
    if (factor < -1 && SideHeavy(ds->right) <= 0) {
        return leftRotate(ds);
    }
    /* Left Right Case*/
    if (factor > 1 && SideHeavy(ds->left)) {
        ds->left = leftRotate(ds->left);
        return rightRotate(ds);
    }
    /* Right Left Case*/
    if (factor < -1 && SideHeavy(ds->right) > 0) {
        ds->right = rightRotate(ds->right);
        return leftRotate(ds);
    }
    return ds;
}
void  AddProduct(DataStructure* ds, int time, int quality) {
    if (quality == S)
        flag == 1;
    insertMain(ds, time, quality);
    insert(HelpTree, quality, time);
}
void insertMain(struct DataStructure* ds, int time, int quality) {
    if (ds == NULL) {
        ds = Init2(time, quality);
        ds->height = Getmax(getHeight(ds->left), getHeight(ds->right)) + 1;
        ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
        insert(ds->subTree , time , time);
        // UpdateMinAndMax(ds);
        MakeItBalance(ds, quality);
    }
    /* search the appropriate place to the new node */
    if (ds != NULL)
    {
        if(quality == ds->quality)
        {
            insert(ds->subTree, time, time);
        }
        if (quality < ds->quality)
        {
            insert(ds->left, time, quality);

        }

        else if (quality > ds->quality)
        {
            insert(ds->right, time, quality);

        }
        ds->height = Getmax(getHeight(ds->left), getHeight(ds->right)) + 1;
        ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
        // UpdateMinAndMax(ds);
        MakeItBalance(ds, quality);
    }

}

/*insert by quality function and insert into helpTree the values but sorted by the time not qualtiy*/
void insert(struct DataStructure* ds, int time, int quality) {
    if (ds == NULL) {
        ds = Init2(time, quality);
        ds->height = Getmax(getHeight(ds->left), getHeight(ds->right)) + 1;
        ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
        // UpdateMinAndMax(ds);
         MakeItBalance(ds, quality);
    }
    /* search the appropriate place to the new node */
    if (ds != NULL)
    {
        if (quality < ds->quality)
            insert(ds->left, time, quality);
        else if (quality > ds->quality)
            insert(ds->right, time, quality);
    }

}

/*function to insert into the subtree*/
struct DataStructure* insertIntoSubTree(struct DataStructure* node, int time, int quality) {
    if (node == NULL)
        return  Init2(time, quality);
    node->height = Getmax(getHeight(node->left), getHeight(node->right)) + 1;
    node->rank = getRank(node->left) + getRank(node->right) + 1;
    return MakeItBalance(node, time);
}
struct DataStructure* insertIntoHelpTree(DataStructure* ds, int time, int quality) {
    if (ds == NULL)
        return  Init2(quality, time);
    insert(ds, quality, time);
    HelpTree->height = Getmax(getHeight(HelpTree->left), getHeight(HelpTree->right)) + 1;
    return MakeItBalance(HelpTree, time);
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

        else if (ds->quality == k)/*k=the quality*/
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
    ds->rank = 1;
    ds->subTree = NULL;
    HelpTree = NULL;
    s = s;
    return ds;
}

/*initate the new node with quality and time(overloading function)*/
DataStructure* Init2(int time, int quality)
{
    struct DataStructure* ds = (struct DataStructure*)malloc(sizeof(struct DataStructure));
    ds->quality = quality;
    ds->time = time;
    ds->left = NULL;
    ds->right = NULL;
    ds->parent = NULL;
    ds->height = 0;
    ds->rank = 1;
    /*becuase i use it only for the helpTree*/
    ds->maxQuality = 0;
    ds->minQuality = 0;
    ds->subTree = NULL;
    if (S == quality) flag = 1;
    return ds;
}

void RemoveProduct(DataStructure* ds, int time)
{
    int q;
    if (ds == NULL) return;
    DataStructure* Wanted = avl_search(HelpTree, time);
    int ToRemoveInMain = Wanted->time;
    if (Wanted != NULL)
    {
        HelpTree = Remove(HelpTree, time);
        DataStructure* WantedQ = avl_search(ds, ToRemoveInMain);
        WantedQ->subTree = Remove(WantedQ->subTree,time);
        if (WantedQ->subTree == NULL)
            RemoveQuality(ds, WantedQ->quality);

    }
}
DataStructure* Remove(DataStructure* Tree, int time)
{
    if (Tree == NULL)
        return NULL;
    DataStructure* Wanted = avl_search(Tree, time);
    if (Wanted->left == NULL && Wanted->right == NULL)
    {
        if(Wanted->parent !=NULL)
                 Wanted->parent= MakeItBalance(Wanted->parent, Wanted->parent->quality);
        free(Wanted);
       
    }
    else
    {
        DataStructure* Suc = Successor_avl(Wanted);
        Suc->parent->left = Suc->right;
        int ToBalance = Suc->parent->quality;
        Suc->parent = Wanted->parent;
        if (Wanted->parent != NULL)
        {
            if (Wanted->parent->left != Wanted)
                Wanted->parent->right = Wanted;
            else  Wanted->parent->left = Wanted;
        }
        Suc->left = Wanted->left;
        Suc->right = Wanted->right;
        if (Wanted->left)
            Wanted->left->parent = Suc;
        else Suc->left = NULL;
        if (Wanted->right)
            Wanted->right->parent = Suc;
        else Wanted->right = NULL;
        Suc->height = Getmax(getHeight(Suc->right), getHeight(Suc->left)) + 1;
        Suc->rank = getRank(Suc->left) + getRank(Suc->right) + 1;
        //UpdateMinAndMax(Suc);
        MakeItBalance(Suc->parent, ToBalance);
        free(Wanted);
    }
    return Tree;

}
DataStructure* Successor_avl(DataStructure* Tree)
{
    if (Tree->right != NULL)
        return min(Tree->right);
    if (Tree->left != NULL)
        return Tree->left;
    return  Tree;
}
void RemoveQuality(DataStructure* ds, int quality)
{
    DataStructure* WantedQ = avl_search(ds, quality);
    while (WantedQ->subTree != NULL)
    {
        HelpTree = Remove(HelpTree, WantedQ->subTree->quality);
        WantedQ->subTree = Remove(WantedQ->subTree, WantedQ->subTree->quality);
    }
    ds = Remove(ds, quality);
    if (S == quality) flag = 0;
}


int GetIthRankProduct(DataStructure* ds, int i)
{

    int root_rank;

    if (ds == NULL)
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
/*returns all the values in the tree in the range x1-x2*/
DataStructure* return_LCA(DataStructure* root, int x1, int x2)
{
    if (root == NULL)
        return NULL;

    if (root->quality > x1 && root->quality > x2)
        return return_LCA(root->right, x1, x2);

    else if (root->quality < x2 && root->quality < x1)
        return return_LCA(root->left, x1, x2);

    return root;

}

/*returns the Ith best product in the range time1-time2*/
int GetIthRankBetween(DataStructure* ds, int time1, int time2, int i)
{

    DataStructure* LCATreeTime;
    DataStructure* LCATreeQuality;
    int minValue, maxValue;
    if (ds == NULL) return -1;
    LCATreeTime = return_LCA(HelpTree, time1, time2);
    minValue = LCATreeTime->minQuality;
    maxValue = LCATreeTime->maxQuality;
    LCATreeQuality = return_LCA(ds, minValue, maxValue);
    return GetIthRankProduct(LCATreeQuality, i);
}

int Exists(DataStructure* ds)
{
    return flag;
}


/* You may use any implementation of the main function you like. */
/* We will be deleting your main implementation and replacing it with our own implementation to test your code. */
/* You may submit the code to moodle without a main function */
/* Please test your code as thoroughly as you can. No tests have been provided for this homework. */
/* Your submitted code must not print any messages or scan any variables */
int main()
{
    DataStructure* ds = Init(11);
    AddProduct(ds, 4, 11);
    AddProduct(ds, 6, 12);
    AddProduct(ds, 2, 13);
    AddProduct(ds, 1, 14);
    AddProduct(ds, 3, 15);
    AddProduct(ds, 5, 17);
    AddProduct(ds, 7, 17);
    RemoveProduct(ds, 4);
    GetIthRankProduct(ds, 1);
    GetIthRankProduct(ds, 2);
    GetIthRankProduct(ds, 6);
    GetIthRankProduct(ds, 7);
    GetIthRankBetween(ds, 2, 6, 3);
    Exists(ds);
    Exists(ds);

    return 0;
}
