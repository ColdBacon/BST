#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define rozmiar 1000

struct element{
    int wartosc;
    element *next;
};

element* head;
element* dodaj_poczatek(element *&head, int liczba);
element* add(element *&head, int liczba);
element* usun_poczatek(element *&head);
element* wyszukaj(element *&head, int liczba);
element* wyswietl(element *head);
element* niszcz(element *&head);

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

    if (liczba < head->wartosc)     //dodanie na poczatku
    {
        element *nowy = head;
        head = new element;
        head->wartosc = liczba;
        head->next = nowy;
    }
    /*
    if (liczba == head -> wartosc)
        return 0;
    */

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

int main()
{
    element *lista = NULL;

    int tablica[rozmiar];
    for (int i=0; i<rozmiar;i++)
    {
        tablica[i]=(rand()%rozmiar)+1;
        cout<<tablica[i]<<'\t';
    }
    //bez powtarzajacych sie elementow prosze
    for (int i=0; i<40; i++) add(lista,tablica[i]);
    wyswietl(lista);
    usun_poczatek(lista);
    cout<<endl;

    for (int i=0; i<40;i++) cout<<wyszukaj(lista,tablica[i])<<endl;

    //losowa lista
    srand(time(NULL));
    int liczba = rand()%(rozmiar+1);
    cout<<liczba;

    niszcz(lista);
    wyswietl(lista);

    return 0;
}

element *usun_poczatek(element *&head)
{
    element *nowy = head; //zapamietujemy poczatek
    if (nowy)
    {
        head = nowy->next; //poczatkiem bedzie kolejny element
        delete nowy;
    }
}

//Wyszukuje pierwszy element listy o danej wartosci
element* wyszukaj(element *&head, int liczba)
{
    element *temp = head;
    while (temp && temp->wartosc != liczba) temp = temp->next;
    return temp;
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

element* niszcz(element *&head)
{

    element *nowy = head; //zapamietujemy poczatek
    while (nowy)
    {
        head = nowy->next; //poczatkiem bedzie kolejny element
        delete nowy;
    }
}
