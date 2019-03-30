#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define rozmiar 1000

struct element{
    int wartosc;
    element *next;

    element();
};

element::element(){
    next = NULL;
}

element* head;
element* dodaj_poczatek(int liczba);
element* usun_poczatek();
element* wyszukaj(int liczba);
element* wstawianie(int liczba, element *head);
element* wyswietl();


int main()
{
    for (int i=0; i<40; i++) dodaj_poczatek(i);
    wyswietl();

    //losowa lista
    srand(time(NULL));
    int liczba = rand()%(rozmiar+1);
    cout<<liczba;
    return 0;
}

element *dodaj_poczatek(int liczba)
{
    element *nowy = new element;     //tworzymy nowy element

    nowy->wartosc = liczba;

    nowy->next = head;
    head = nowy; //adres nowego elementu
}

element *usun_poczatek()
{
    element *nowy = head; //zapamietujemy poczatek
    if (nowy)
    {
        head = nowy->next; //poczatkiem bedzie kolejny element
        delete nowy;
    }
}

//Wyszukuje pierwszy element listy o danej wartosci
element* wyszukaj(int liczba)
{
    element *temp = head;
    while (temp && temp->wartosc != liczba) temp = temp->next;
    return temp;
}

//dodawanie wg kryteriow
element* wstawianie(int liczba, element *head)
{
    element *wsk, *poprzednik, *nastepnik;
    wsk = new element;
    wsk->wartosc = liczba;
    poprzednik = NULL;
    nastepnik = head;
    while (nastepnik!=NULL)
        if (nastepnik->wartosc>=liczba)
        {
            wsk->next=nastepnik;
            if(poprzednik!=NULL)//dolaczenie wewnatrz listy
            {
                poprzednik->next = wsk;
                return head;
            }
            else return wsk; //dolaczenie na poczatku listy
        }
        else
        {
            poprzednik = nastepnik;
            nastepnik = poprzednik ->next;
        }
     wsk -> next = NULL;    //dolaczenie na koncu listy
     poprzednik -> next = wsk;
     return head;
}


element* wyswietl()
{
    element *temp = head;

    // przewijamy wskazniki na nastepne elementy
    while (temp)
    {
        cout << temp->wartosc <<" ";
        temp=temp->next;
    }
}
