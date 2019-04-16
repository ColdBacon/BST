#include<iostream>
#include<cstdlib>
#include<ctime>

#define rozmiar 5

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

void postorder(tree *root)
{
    if(root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        cout<<(root->info)<<'\t';
    }
    return;
}

void preorder(tree *root)
{
    if(root != NULL)
    {
        cout<<(root->info)<<'\t';
        preorder(root->left);
        preorder(root->right);
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
    cout<<"deleting node: "<<root->info<<endl;
    free(root);
}

tree *AVL=NULL;
int tablica[rozmiar];
int j=0;

void Tablica(tree* root)
{
    if(root)
    {
        if (root->left)
            Tablica(root->left);
        if(root)
        {
            //cout<<root->info<<endl;
            tablica[j]=root->info;
            j++;
        }

        Tablica(root->right);
    }
}

void AVLtworzenie(int *tab, int l, int r)
{
    if (l!=r)
    {
        int q = (l+r)/2;
        insert(&AVL,tab[q]);
        AVLtworzenie(tab,l,q);
        if(q+1<=r) AVLtworzenie(tab,q+1,r);
    }
}

int main()
{
    srand(time(NULL));
    tree *drzewo = NULL;
    int tab[rozmiar];
    for (int i=0; i<rozmiar; i++)
    {
        tab[i] = (rand()%10000)+1;
        int j=0;
        while(j<i)
        {
            if (tab[j] == tab[i])
            {
                tab[i] = (rand()%10000)+1;
                j=0;
            }
            else j++;
        }

        cout<<tab[i]<<'\t';
    }
    /*
    clock_t start1;
    double duration1,duration2,duration3,duration4;
    start1 = clock();
    */
    for(int i=0; i<rozmiar; i++)
    {
        insert(&drzewo, tab[i]);
    }

    for (int i=0; i<rozmiar; i++)
    {
        search(drzewo,tab[i]);
    }
    cout<<endl;
    cout<<"INORDER: "<<endl;
    inorder(drzewo);
    cout<<endl;
    cout<<"wysokosc BST: "<<height(drzewo)<<endl;

    while (drzewo)
    {
        if (drzewo->right) drzewo = drzewo -> right;
        else{
            cout<<"Wartosc najbardziej na prawo: "<<drzewo->info<<endl;
            break;
        }

    }
    Tablica(drzewo);
    usun(drzewo);
    cout<<endl;
    cout<<"TABLICA: "<<endl;
    for (int i=0; i<rozmiar; i++)
    {
        cout<<tablica[i]<<'\t';
    }

    AVLtworzenie(tablica,0,rozmiar);
    cout<<endl;
    cout<<"AVL: "<<endl;
    view(AVL);
    cout<<"wysokosc AVL: "<<height(AVL);

    return 0;
}
