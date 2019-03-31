#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define rozmiar 15

struct element{
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

int add(element *&head, int liczba)
{
    if (head == NULL)           //pusta lista
    {
        head = new element;
        head -> wartosc = liczba;
        head -> next = NULL;
        return 1;
    }

    if (liczba < head->wartosc)     //dodanie na poczatku
    {
        element *nowy = head;
        head = new element;
        head->wartosc = liczba;
        head->next = nowy;
        return 1;
    }

    if (liczba == head -> wartosc)
        return 0;

    element *wsk = head;
    while (wsk -> next && wsk -> next -> wartosc < liczba)
        wsk = wsk -> next;

    if (wsk -> next == NULL)           //dodanie na koncu
    {
        wsk -> next = new element;
        wsk -> next -> wartosc = liczba;
        wsk -> next -> next = NULL;
        return 1;
    }
    else
    {
        if (liczba == wsk -> next -> wartosc)
            return 0;
        element *temp = wsk-> next;
        wsk -> next = new element;
        wsk -> next -> wartosc = liczba;
        wsk -> next -> next = temp;
        return 1;
    }
}

//Wyszukuje pierwszy element listy o danej wartosci
element* wyszukaj(element *&head, int liczba)
{
    element *temp = head;
    while (temp -> wartosc != liczba) temp = temp->next;
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
        }else if(liczba == temp -> wartosc) return true;
        else return false;

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

element* niszcz(element *&head)
{
    element *nowy = head; //zapamietujemy poczatek
    while (nowy)
    {
        head = nowy->next; //poczatkiem bedzie kolejny element
        delete nowy;
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
    for (int i=0; i<rozmiar; i++) add(lista,tablica[i]);
    wyswietl(lista);
    usun_poczatek(lista);
    cout<<endl;

    for (int i=0; i<rozmiar;i++) cout<<search(lista,tablica[i])<<" ";

    cout<<endl;
    usun_poczatek(lista);
    wyswietl(lista);

    return 0;
}
