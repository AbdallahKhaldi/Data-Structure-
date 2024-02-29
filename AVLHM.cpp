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
	int counter;
	struct DataStructure* left;
	struct DataStructure* right;
	struct DataStructure* parent;
	int height;
	struct DataStructure* subTree;
} DataStructure;

struct DataStructure* HelpTree = (struct DataStructure*)malloc(sizeof(struct DataStructure));
int flag = 0;
int s;

DataStructure* Init(int s);
DataStructure* Init2(int quality, int time);
void AddProduct(DataStructure*& ds, int time, int quality);
DataStructure* Remove(DataStructure* Tree, int time, int quality);
int GetIthRankProduct(DataStructure* ds, int i);
struct DataStructure* insertIntoSubTree(struct DataStructure* node, int quality, int time);
void RemoveQuality(DataStructure* ds, int quality);
DataStructure* Successor_avl(DataStructure* Tree);
DataStructure* avl_search(DataStructure* ds, int k);
struct DataStructure* insertIntoHelpTree(DataStructure* ds, int time, int quality);

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
	if (ds == NULL)return;
	if (ds->left != NULL && ds->right != NULL)
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

	if (x->left == NULL && x->right == NULL) x->height = 0;
	else
		x->height = Getmax(getHeight(x->left), getHeight(x->right)) + 1;
	if (ds->left == NULL && ds->right == NULL) ds->height = 0;
	else
		ds->height = Getmax(getHeight(ds->left), getHeight(ds->right)) + 1;


	/*update ranks*/
	ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
	x->rank = getRank(x->left) + getRank(x->right) + 1;
	/*update parents*/
	x->parent = ds->parent;
	ds->parent = x;
	UpdateMinAndMax(ds);
	UpdateMinAndMax(x);

	if (T2 != NULL)
		T2->parent = ds;

	return x;
}

struct DataStructure* leftRotate(struct DataStructure* ds) {
	struct DataStructure* y = ds->right;
	struct DataStructure* T2 = y->left;

	y->left = ds;
	ds->right = T2;

	if (ds->left == NULL && ds->right == NULL) ds->height = 0;
	else
		ds->height = Getmax(getHeight(ds->left), getHeight(ds->right)) + 1;
	if (y->left == NULL && y->right == NULL) y->height = 0;
	else
		y->height = Getmax(getHeight(y->left), getHeight(y->right)) + 1;

	/*update ranks*/
	ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
	y->rank = getRank(y->left) + getRank(y->right) + 1;
	/*update parents*/
	y->parent = ds->parent;
	ds->parent = y;
	/*update min and max in the subtrees*/
	UpdateMinAndMax(ds);
	UpdateMinAndMax(y);

	if (T2 != NULL)
		T2->parent = ds;

	return y;
}
/*Balance the tree(we use it while inserting and deleting)*/
struct DataStructure* MakeItBalance(struct DataStructure*& ds, int quality)
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


/*insert by quality function and insert into helpTree the values but sorted by the time not qualtiy*/
struct DataStructure* insert(struct DataStructure* ds, int time, int quality) {
	if (quality == s)
		flag = 1;
	if (!ds || ds->time == 0)
		return Init2(time, quality);
	/* search the appropriate place to the new node */
	if (!avl_search(ds, quality))
	{
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
		if (ds->left == NULL && ds->right == NULL) ds->height = 0;
		else
			ds->height = Getmax(getHeight(ds->left), getHeight(ds->right)) + 1;
		ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
		 UpdateMinAndMax(ds);
		return MakeItBalance(ds, quality);
	}
	else {
		avl_search(ds, quality)->subTree = insertIntoSubTree(avl_search(ds, quality)->subTree, time, time);
		avl_search(ds, quality)->subTree->counter++;
		return ds;
	}

}

/*function to insert into the subtree*/
struct DataStructure* insertIntoSubTree(struct DataStructure* ds, int time, int quality) {
	if (ds == NULL)
		return  Init2(time, quality);
	if (!avl_search(ds, quality))
	{
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
		if (ds->left == NULL && ds->right == NULL) ds->height = 0;
		else
			ds->height = Getmax(getHeight(ds->left), getHeight(ds->right)) + 1;
		ds->rank = getRank(ds->left) + getRank(ds->right) + 1;
		 UpdateMinAndMax(ds);
		return MakeItBalance(ds, quality);
	}
	return MakeItBalance(ds, time);
}
struct DataStructure* insertIntoHelpTree(DataStructure* ds, int time, int quality) {
	if (ds == NULL)
		return  Init2(quality, time);
	insert(ds, quality, time);
	if (ds->left == NULL && ds->right == NULL) ds->height = 0;
	else
		ds->height = Getmax(getHeight(ds->left), getHeight(ds->right)) + 1;
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
		if (k > ds->quality)
			return avl_search(ds->right, k);

		else if (k < ds->quality)
			return avl_search(ds->left, k);

		else if (ds->quality == k)/*k=the quality*/
			return ds;
	}
	return NULL;
}

/*initiate the tree with defulat values*/
DataStructure* Init(int s)
{
	struct DataStructure* ds;
	ds = (DataStructure*)malloc(sizeof(struct DataStructure));
	ds->quality = s;
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
	ds->maxQuality = 0;
	ds->minQuality = 0;
	ds->subTree = NULL;
	if (s == quality) flag = 1;
	ds->counter = 0;
	return ds;
}

void AddProduct(DataStructure*& ds, int time, int quality)
{
	ds = insert(ds, time, quality);
	HelpTree = insertIntoHelpTree(HelpTree, time, quality);

}
void RemoveProduct(DataStructure* ds, int time)
{
	int ToRemoveInMain;
	if (ds == NULL) return;
	DataStructure* Wanted = avl_search(HelpTree, time);
	if (Wanted != NULL)
	{
		ToRemoveInMain = Wanted->time;
		HelpTree = Remove(HelpTree, time, ToRemoveInMain);
		DataStructure* WantedQ = avl_search(ds, ToRemoveInMain);
		if (WantedQ->subTree == NULL)
		{
			RemoveQuality(ds, ToRemoveInMain);
		}
		else
		{
			WantedQ->subTree = Remove(WantedQ, time, time);
		}
	}
}


DataStructure* Remove(DataStructure* Tree, int time, int quality)
{
	DataStructure* temp;
	DataStructure* Wanted;
	if (!Tree)
	{
		return Tree;
	}

	if (time > Tree->quality)
	{
		Tree->right = Remove(Tree->right, time, quality);
	}

	else if (time < Tree->quality)
	{
		Tree->left = Remove(Tree->left, time, quality);
	}
	else /*we are in the node that have the my time*/
	{
		if (time == Tree->quality)  /*this is the node to be deleted*/
		{

			Tree->rank--;

			if (!(Tree->left) || !(Tree->right))
			{
				temp = Tree->left ? Tree->left : Tree->right;
				if (!temp) /* if the node is a leaf*/
				{
					free(Tree);
					return NULL;
				}
				else  /*if the node have one child*/
				{
					Wanted = Tree;
					temp->parent = Tree->parent;
					Tree = temp;
					free(Wanted);
				}
			}
			else  /*if the node have two child's*/
			{
				temp = Successor_avl(Tree->right); /*temp holds the successor of the node (the minimum in the right subtree)*/
				DataStructure* NewNode = Init2(temp->time, temp->quality);

				NewNode->parent = Tree->parent;

				Tree->right = Remove(Tree->right, temp->time, temp->quality);

				NewNode->left = Tree->left;
				NewNode->right = Tree->right;

				if (NewNode->left)
					NewNode->left->parent = NewNode;
				if (NewNode->right)
					NewNode->right->parent = NewNode;

				NewNode->height = Getmax(getHeight(NewNode->right), getHeight(NewNode->left)) + 1;
				NewNode->rank = getRank(NewNode->left) + getRank(NewNode->right) + 1;

				Wanted = Tree;
				Tree = NewNode;
				free(Wanted);
			}
		}
		else
			return Tree;
	}
	if (!Tree)
		return Tree;

	/*update height and rank*/
	Tree->height = Getmax(getHeight(Tree->left), getHeight(Tree->right)) + 1;
	Tree->rank = getRank(Tree->left) + getRank(Tree->right) + 1;
	UpdateMinAndMax(Tree);
	/*balance the tree*/
	return(MakeItBalance(Tree, time));

}



	DataStructure* Successor_avl(DataStructure * Tree)
	{
		if (Tree->right != NULL)
			return min(Tree->right);
		if (Tree->left != NULL)
			return Tree->left;
		return  Tree;
	}
	void RemoveQuality(DataStructure * ds, int quality)
	{
		DataStructure* WantedQ = avl_search(ds, quality);

		while (WantedQ->subTree != NULL)
		{
			HelpTree = Remove(HelpTree,WantedQ->quality ,WantedQ->time );
			WantedQ->subTree = Remove(WantedQ->subTree, WantedQ->subTree->time, WantedQ->subTree->time);
			WantedQ->subTree->counter--;
		}
		ds = Remove(ds, quality,ds->time );
		if (s == quality) flag = 0;
	}





	int GetIthRankProduct(DataStructure * ds, int i)
	{

		int root_rank;

		if (ds == NULL)
			return -1;

		/*calculate the rank of the root*/
		if (ds->left == NULL)
			root_rank = 1;
		else
			root_rank = ds->left->rank + 1;
		/*If the kth smallest node is the root node, return the root*/
		if (i == root_rank)
			return ds->quality;

		/*If the kth smallest node is in the left subtree */
		if (i < root_rank)
			GetIthRankProduct(ds->left, i);

		/*If the kth smallest node is in the right subtree */
		else if (ds->subTree!=NULL)
			GetIthRankProduct(ds->right, i - root_rank - ds->subTree->rank);
		else
		{
			GetIthRankProduct(ds->right, i - root_rank );
		}

	}
	/*returns all the values in the tree in the range x1-x2*/
	DataStructure* return_LCA(DataStructure * root, int x1, int x2)
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
	int GetIthRankBetween(DataStructure * ds, int time1, int time2, int i)
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

	int Exists(DataStructure * ds)
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
		DataStructure* ds = (DataStructure*)Init(11);
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
		GetIthRankProduct(ds, 5);
		GetIthRankProduct(ds, 6);
		GetIthRankBetween(ds, 2, 4, 1);
		Exists(ds);
		Exists(ds);

		return 0;
	}
