#include<iostream>
#include<cstdlib>
#include<ctime>

#define rozmiar 20000

using namespace std;

struct tree
{
    int info;
    tree *left;
    tree *right;
};

//--------------------------------------------------budowa drzewa
tree *insert(tree** root, int liczba)
{

    if(!(*root))
    {
        *root = new tree;
        (*root)->info = liczba;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    if((*root)->info > liczba)
        insert(&(*root)->left,liczba);
    else
    {
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
        if (root -> info == liczba)
            return true;
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
void inorder(tree *root)
{
    if(root != NULL)
    {
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

void usun(tree* root)
{
    if(root==NULL)
        return;
    usun(root->left);
    usun(root->right);
    //cout<<"deleting node: "<<root->info<<endl;
    free(root);
}

int main()
{
    srand(time(NULL));
    tree *drzewo = NULL;
    int tab[rozmiar];
    for (int i=0; i<rozmiar; i++)
    {
        tab[i] = (rand()%1000000)+1;
        for (int j=0; j<i; j++)
        {
            while (tab[i] == tab[j])
                tab[i] = (rand()%1000000)+1;
        }

        //cout<<tab[i]<<'\t';
    }

    clock_t start1;
    double duration1,duration2,duration3,duration4;
    start1 = clock();

    for(int i=0; i<rozmiar; i++)
    {
        insert(&drzewo, tab[i]);
    }

    duration1 = ( clock() - start1 ) / (double) CLOCKS_PER_SEC;
    cout<<"1: "<< duration1 <<endl;

    clock_t start2;
    start2 = clock();

    for (int i=0; i<rozmiar; i++)
    {
        search(drzewo,tab[i]);
    }

    duration2 = ( clock() - start2 ) / (double) CLOCKS_PER_SEC;
    cout<<"2: "<< duration2 <<endl;

    //cout<<endl<<height(drzewo)<<endl;

    clock_t start3;
    start3 = clock();
    usun(drzewo);
    duration3 = ( clock() - start3 ) / (double) CLOCKS_PER_SEC;
    cout<<"3: "<< duration3 <<endl;

    return 0;
}
