#include<iostream>
#include<cstdlib>
#include<ctime>

#define rozmiar 100

using namespace std;

struct tree {
	int info;
	tree *left;
	tree *right;
};

//--------------------------------------------------budowa drzewa
tree *insert(tree** root, int liczba) {

	if(!(*root)) {
		*root = new tree;
		(*root)->info = liczba;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}
	if((*root)->info > liczba)
	     insert(&(*root)->left,liczba);
    else {
		if((*root)->info < liczba)
            insert(&(*root)->right,liczba);
	}
}
//--------------------------------------------------szukanie wartosci
bool search(tree* root, int liczba)
{
    tree *ptr = root;
    while (ptr)
    {
        if (root -> info == liczba) return true;
        else if (liczba < root -> info )
        {
            ptr = ptr -> left;
            return search(root -> left, liczba);
        }
        else if (liczba > root -> info )
        {
            ptr = ptr -> right;
            return search(root -> right, liczba);
        }
        //else break;
    }
    return false;
}

//---------------------------------------------------wyswetlenie
tree* view(tree* root)
{
    if (root)
    {
        if (root->left !=NULL)
            view(root->left);
        cout<<root -> info <<'\t';
        view( root -> right);
    }
}

//------------------------------- 3 porzadki przechodzenia drzew / usuwanie podobnie jak postorder
void inorder(tree *root) {
	if(root != NULL) {
		inorder(root->left);
		cout<<(root->info)<<'\t';
		inorder(root->right);
	}
	return;
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
    srand(time(NULL));
    tree *drzewo = NULL;
    int tab[rozmiar];
    for(int i=0; i<rozmiar; i++){
        tab[i]=(rand()%10000)+1;
        cout<<tab[i]<<'\t';
    }

    for(int i=0; i<rozmiar; i++){
        insert(&drzewo, tab[i]);
    }
    cout<<endl;
    cout<<endl;
    view(drzewo);

    for (int i=0; i<rozmiar;i++)
    {
        cout<<search(drzewo,tab[i]);
    }

    cout<<endl<<height(drzewo);
    return 0;
}
