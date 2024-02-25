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

static DataStructure* HelpTree = (struct DataStructure*)malloc(sizeof(struct DataStructure));
int flag = 0;
int s;


DataStructure* Init(int quality, int time);
void AddProduct(DataStructure* ds, int time, int quality);
DataStructure* Remove(DataStructure* Tree, int time);
int GetIthRankProduct(DataStructure* ds, int i);
struct DataStructure* insertIntoSubTree(struct DataStructure* node, int quality, int time);
void RemoveQuality(DataStructure* ds, int quality);
DataStructure* Successor_avl(DataStructure* Tree);
DataStructure* avl_search(DataStructure* ds, int k);
struct DataStructure* insertIntoHelpTree(DataStructure* ds,int time, int quality);

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
        ds->minQuality = ds->right->minQuality;
        ds->maxQuality = ds->right->maxQuality;
    }
    else if (ds->left != NULL && ds->right == NULL) {
        ds->minQuality = ds->left->minQuality;
        ds->maxQuality = ds->left->maxQuality;
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

    /*update min and max in the subtrees*/
    UpdateMinAndMax(ds);
    UpdateMinAndMax(x);
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

    ds->height = Getmax(getHeight(ds->right), getHeight(ds->left)) + 1;
    y->height = Getmax(getHeight(y->right), getHeight(y->left)) + 1;
    /*update min and max in the subtrees*/
    UpdateMinAndMax(ds);
    UpdateMinAndMax(y);
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
struct DataStructure* insert(struct DataStructure* ds, int time, int quality) {
    if (quality == s)
        flag = 1;
    if (!ds)
        return Init(time, quality);

    /* search the appropriate place to the new node */
    
        if (ds->quality < quality)
        {
            ds->right = insert(ds->right, time, quality);
            ds->right->parent = ds;
        }

        else if (ds->quality > quality)
        {
            ds->left = insert(ds->left, time, quality);
            ds->left->parent = ds;
        }
        else if (ds->quality == quality)
        {
            ds->subTree = insertIntoSubTree(ds->subTree, time, time);;
            return ds;
        }
        insertIntoHelpTree(HelpTree,quality, time);
        /*update the node fields*/
        ds->height = Getmax(getHeight(ds->left), getHeight(ds->right)) + 1;
        ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
        HelpTree->height= Getmax(getHeight(HelpTree->left), getHeight(HelpTree->right)) + 1;
        MakeItBalance(HelpTree, time);
        return MakeItBalance(ds,quality);
    

        return ds;
    

   /* if (node == NULL)
    {
        return  Init(time, quality);
    }
        
    if (quality == node->quality)
    {
        node->subTree = insertIntoSubTree(node->subTree, time, time);
        return node;
    }
    if (quality < node->quality) {
        node->left = insert(node->right, quality, time);
        node->left->parent = node;
    }
    else if (quality > node->quality) {
        node->right = insert(node->left, quality, time);
        node->right->parent = node;
    }
    if (time < HelpTree->time)
    {
        HelpTree->left = insert(HelpTree->left, quality, time);
        UpdateMinAndMax(HelpTree);
    }
    if (time > HelpTree->time)
    {
        HelpTree->right = insert(HelpTree->right, quality, time);
        UpdateMinAndMax(HelpTree);
    }
    node->height = 1 + Getmax(getHeight(node->left), getHeight(node->right));
    node->rank = getRank(node->left) + getRank(node->right) + 1;
    MakeItBalance(node, quality);
    return node;*/
}
/*function to insert into the subtree*/
struct DataStructure* insertIntoSubTree(struct DataStructure* node, int time, int quality) {
    if (node == NULL)
        return  Init(time, quality);
    if (quality < node->quality) {
        node->left = insertIntoSubTree(node->left, quality, time);
        node->left->parent = node;
    }
    else if (quality > node->quality) {
        node->right = insertIntoSubTree(node->right, quality, time);
        node->right->parent = node;
    }
    node->height = 1 + Getmax(getHeight(node->left), getHeight(node->right));
    MakeItBalance(node, time);
    return node;
}
struct DataStructure* insertIntoHelpTree(DataStructure* ds,int time, int quality) {
    if (ds == NULL)
        return  Init(time, quality);
    if (quality <= ds->quality) {
        ds->left = insertIntoHelpTree(ds->left, quality, time);
        ds->left->parent = ds;
    }
    else if (quality > ds->quality) {
        ds->right = insertIntoHelpTree(ds->right, quality, time);
        ds->right->parent = ds;
    }
    ds->height = 1 + Getmax(getHeight(ds->left), getHeight(ds->right));
    MakeItBalance(ds, time);
    UpdateMinAndMax(ds);
    return ds;
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
    ds->quality = s;
    ds->time = NULL;
    ds->left = NULL;
    ds->right = NULL;
    ds->parent = NULL;
    ds->height = 0;
    ds->rank = 0;
    ds->subTree = NULL;
    HelpTree->quality = NULL;
    HelpTree->time = NULL;
    HelpTree->left = NULL;
    HelpTree->right = NULL;
    HelpTree->parent = NULL;
    HelpTree->height = 0;
    HelpTree->rank = 0;
    s = s;
    struct DataStructure* AVL = (struct DataStructure*)malloc(sizeof(struct DataStructure));
    return ds;
}

/*initate the new node with quality and time(overloading function)*/
DataStructure* Init(int time, int quality)
{
    struct DataStructure* ds = (struct DataStructure*)malloc(sizeof(struct DataStructure));
    ds->quality = quality;
    ds->time = time;
    ds->left = NULL;
    ds->right = NULL;
    ds->parent = NULL;
    ds->height = 0;
    ds->rank = 0;
    /*becuase i use it only for the helpTree*/
    ds->maxQuality = time;
    ds->minQuality = time;
    ds->subTree = NULL;
    HelpTree->height = 0;
    HelpTree->rank = 0;
    HelpTree->time = quality;
    HelpTree->quality = time;
    if (s == quality) flag = 1;
    struct DataStructure* AVL = (struct DataStructure*)malloc(sizeof(struct DataStructure));
    return ds;
}

void AddProduct(DataStructure* ds, int time, int quality)
{
    insert(ds, time, quality);
    

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
        WantedQ->subTree = Remove(WantedQ->subTree, WantedQ->time);
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
        free(Wanted);
        MakeItBalance(Wanted->parent, Wanted->parent->quality);
    }
    DataStructure* Suc = Successor_avl(Wanted);
    Suc->parent->left = Suc->right;
    int ToBalance = Suc->parent->quality;
    Suc->parent = Wanted->parent;
    if (Wanted->parent->left != Wanted)
        Wanted->parent->right = Wanted;
    else  Wanted->parent->left = Wanted;
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
    UpdateMinAndMax(Suc);
    free(Wanted);
    MakeItBalance(Suc->parent, ToBalance);
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
    if (s == quality) flag = 0;
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
    if (!root)
        return NULL;

    if (root->quality < x1)
        return return_LCA(root->right, x1, x2);

    else if (root->quality > x2)
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
    DataStructure* ds = Init(11); // initializes an empty data structure
    AddProduct(ds, 4, 11); // Adds a product at time t=4 and quality q=11
    AddProduct(ds, 6, 12); // Adds a product at time t=6 and quality q=12
    AddProduct(ds, 2, 13); // Adds a product at time t=2 and quality q=13
    AddProduct(ds, 1, 14); // Adds a product at time t=1 and quality q=14
    AddProduct(ds, 3, 15); // Adds a product at time t=3 and quality q=15
    AddProduct(ds, 5, 17); // Adds a product at time t=5 and quality q=17
    AddProduct(ds, 7, 17); // Adds a product at time t=7 and quality q=17
    GetIthRankProduct(ds, 1);//The i=1 best product has time t=4 and quality q=11,returns 4
    GetIthRankProduct(ds, 2);//The i=2 best product has time t=6 and quality q=12,returns 6
    GetIthRankProduct(ds, 6);//The i=”6 best product” has time t=5 and quality q=17,returns 5
    GetIthRankProduct(ds, 7);//The i=”7 best product” has time t=7 and quality q=17,returns 7
    GetIthRankBetween(ds, 2, 6, 3); // looks at values with time {2,3,4,5,6} and returns the
    Exists(ds); // returns 1, since there exists a product with quality q=s=11
    RemoveProduct(ds, 4);// removes product with time t=4 from the data structure
    Exists(ds); // returns 0, since there is no product with quality q=s=11

    return 0;
}
