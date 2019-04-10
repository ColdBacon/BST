#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define rozmiar 150000

struct element
{
    int wartosc;
    element *next;
};

element* head;

element* dodaj_poczatek(element *&head, int liczba)
{
    element *nowy = new element;     //tworzymy nowy element

    nowy->wartosc = liczba;

    nowy->next = head;
    head = nowy; //adres nowego elementu
}

element* add(element *&head, int liczba)
{
    if (head == NULL)           //pusta lista
    {
        head = new element;
        head -> wartosc = liczba;
        head -> next = NULL;
    }

    else if (liczba < head->wartosc)     //dodanie na poczatku
    {
        element *nowy = head;
        head = new element;
        head->wartosc = liczba;
        head->next = nowy;
    }
    else
    {
        element *wsk = head;
        while (wsk -> next && wsk -> next -> wartosc < liczba)
            wsk = wsk -> next;

        if (wsk -> next == NULL)           //dodanie na koncu
        {
            wsk -> next = new element;
            wsk -> next -> wartosc = liczba;
            wsk -> next -> next = NULL;
        }
        else
        {
            element *temp = wsk-> next;
            wsk -> next = new element;
            wsk -> next -> wartosc = liczba;
            wsk -> next -> next = temp;
        }
    }
}

//Wyszukuje pierwszy element listy o danej wartosci
element* wyszukaj(element *&head, int liczba)
{
    element *temp = head;
    while (temp -> wartosc != liczba)
        temp = temp->next;
    return temp;
}

bool search (element *&head, int liczba)
{
    element *temp = head;
    while (temp)
    {
        if(liczba > temp -> wartosc)
        {
            temp = temp -> next;
        }
        else if(liczba == temp -> wartosc)
            return true;
        else
            return false;
    }
}

element* wyswietl(element *head)
{
    element *temp = head;

    // przewijamy wskazniki na nastepne elementy
    while (temp)
    {
        cout << temp->wartosc <<" ";
        temp=temp->next;
    }
}

element* usun_poczatek(element *&head)
{
    element *nowy = head; //zapamietujemy poczatek
    if (nowy)
    {
        head = nowy->next; //poczatkiem bedzie kolejny element
        delete nowy;
    }
}

element* usuwanie(element *&head)
{
    element *help = new element;
    help = head;

    while(help!= NULL)
    {
        head = help -> next;
        delete help;
        help = head;
    }
    head = NULL;
}

int main()
{
    element *lista = NULL;
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

    cout<<endl;

    clock_t start1, stop1;
    double duration1,duration2,duration3;
    cout.setf(ios::fixed);
    cout.precision(5);
    start1 = clock();

    for (int i=0; i<rozmiar; i++)
        add(lista,tab[i]);

    stop1 = clock();
    duration1 = ( stop1 - start1 ) / (double) CLOCKS_PER_SEC;
    cout<<"1: "<< duration1 <<endl;

    clock_t start2, stop2;
    start2 = clock();

    for (int i=0; i<rozmiar; i++)
        search(lista,tab[i]);

    stop2 = clock();
    duration2 = ( stop2 - start2 ) / (double) CLOCKS_PER_SEC;
    cout<<"2: "<< duration2 <<endl;

    clock_t start3, stop3;
    start3 = clock();

    //niszczenie listy
    for (int i=0; i<rozmiar;i++)
        usun_poczatek(lista);

    //usuwanie(lista);
    stop3 = clock();
    duration3 = ( stop3 - start3 ) / (double) CLOCKS_PER_SEC;
    cout<<"3: "<< duration3 <<endl;

    wyswietl(lista);

    return 0;
}

