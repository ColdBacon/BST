#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct Element{
    int liczba;
    Element *next; //wskaznik na nastepny element na liscie

    Element(); //konstruktor
};

Element::Element() {
    next = 0;       // konstruktor
}

struct Lista{
    Element *head;
    void dodaj (int liczba);
    void dodaj_koniec (int liczba);
    void usun_poczatek ();
    void wyswietl_liste();
    void destroy();
    Lista();
    ~Lista();
    Element * find_first(int liczba);
};

Lista::Lista(){
    head = NULL;        //konstruktor
}

Lista::~Lista()
{
   while(head) usun_poczatek(); //destruktor
}

void Lista::dodaj(int liczba){
    Element *nowy = new Element;     //tworzymy nowy element

    nowy->liczba = liczba;

    nowy->next = head;
    head = nowy;
    /*
    if (head==0)        //sprawdzamy czy to pierwszy element tablicy
    {
        //jezeli tak to nowy element jest teraz poczatkiem
        head = nowy;
    }
    else
    {
        element *temp = head;

        while (temp->next)
        {
            temp = temp->next;
        }

        temp->next = nowy;
        nowa->next = 0;
    }
    */
}

void Lista::dodaj_koniec(int liczba)
{
    Element *nowy, *nowy2;
    nowy2 = new Element;
    nowy2->next = NULL;
    nowy2->liczba = liczba;
    nowy = head;
    if (nowy){
        while (nowy->next) nowy = nowy->next;
        nowy->next = nowy2;
    }
    else head = nowy2;

}

void Lista::usun_poczatek()
{
    Element *nowy = head; //zapamietujemy poczatek
    if (nowy)
    {
        head = nowy->next;
        delete nowy;
    }

    /*
    Element *temp = head;
    Element * temp2 = temp->next;
    head = temp2;
    temp = NULL;
    */
}

void Lista::destroy()
{
    Element *temp = head;
    Element *p = temp->next;

    while (p!=NULL)
    {
        delete temp;
        temp = p;
        p = p->next;
    }
}

void Lista::wyswietl_liste()
{
    Element *temp = head;

    // przewijamy wskazniki na nastepne elementy
    while (temp)
    {
        cout << temp->liczba <<" ";
        temp=temp->next;
    }
}
//Wyszukuje pierwszy element listy o danej wartosci
Element *Lista::find_first(int liczba)
{
    Element *temp = head;
    while (temp && temp->liczba != liczba) temp = temp->next;
    return temp;
}

int main(){
    Lista L;
    Element *nowy;
    for (int i=0; i<40; i++) L.dodaj(i);
    L.wyswietl_liste();

return 0;
}

//push_front
//push_back
//insert
//pop_front
//pop_back
//size
//max_size
//empty
//remove
//sort
//reverse
