#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>

#define rozmiar 15000

using namespace std;

int TAB[rozmiar];
int j=0;

struct tree {
	int value;
	tree *left;
	tree *right;
};

tree *AVL=NULL;

//--------------------------------------------------budowa drzewa
void insert(tree **root, int number) {
	if(*root==NULL) {
		*root=new tree;
		(*root)->value = number;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}
	else
    {
        if((*root)->value > number)
            insert(&(*root)->left, number);
        else {
            insert(&(*root)->right, number);
        }
    }
}

void view(tree *root) {
	if(root != NULL) {
		view(root->left);
		cout<<(root->value)<<'\t';
		view(root->right);
	}
	return;
}

void Tablica(tree *root)
{
    if(root)
    {
        if (root->left)
            Tablica(root->left);
        if(root)
        {
            TAB[j]=root->value;
            j++;
        }
        Tablica(root->right);
    }
}

void AVLtworzenie(int* Tab,int p, int r)
{
    if(p!=r)
    {
        int q=(p+r)/2;
        insert(&AVL, Tab[q]);
        AVLtworzenie(Tab,p, q);
        if(q+1<=r)
            AVLtworzenie(Tab,q+1,r);
    }
}

int height(tree *root)
{
    int left, right;
    if(root != NULL)
    {
        left = height(root->left);
        right = height(root->right);
        if(left>right)
            return left+1;
        else
            return right+1;
    }
    else
        return 0;
}

int main()
{
    srand(time(0));
    tree *drzewo=NULL;
    int tab[rozmiar];

    for(int i=0; i<rozmiar; i++)
    {
        tab[i]=(rand()%10000)+1;
        for(int j=0; j<i; j++)
        {
            while(tab[j]==tab[i])
                tab[i]=(rand()%10000)+1;
        }
        //cout<<tab[i]<<'\t';
    }

    for(int i=0; i<rozmiar; i++)
        insert(&drzewo, tab[i]);

    ofstream plik;
    plik.open("wysokoœæ.txt", ios::app);

    //view(drzewo);

    Tablica(drzewo);
    AVLtworzenie(TAB, 0, rozmiar);
    //view(AVL);

    plik<<rozmiar<<'\t'<<height(drzewo)<<'\t'<<height(AVL)<<endl;

    return 0;
}
