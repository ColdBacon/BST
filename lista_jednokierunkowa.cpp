#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#define rozmiar 1000

//W strukturze statycznej odwo³uj¹c siê do pól u¿ywaliœmy kropki (.).
//W strukturze dynamicznej odwo³uj¹c siê do pól korzystamy z operatora strza³ki (->).

struct Element{
    int wartosc;
    Element *next; //wskaznik na nastepny element na liscie

    Element(); //konstruktor
};

Element::Element() {
    next = NULL;       // konstruktor
}

struct Lista{
    Element *head;
    void dodaj_poczatek (int liczba);
    void dodaj_koniec (int liczba);
    void dodaj_srodek (Element *&head, Element *granica , int liczba);
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

void Lista::dodaj_poczatek(int liczba){
    Element *nowy = new Element;     //tworzymy nowy element

    nowy->wartosc = liczba;

    nowy->next = head;
    head = nowy; //adres nowego elementu
}

void Lista::dodaj_koniec(int liczba)
{
    Element *nowy, *koniec;
    koniec = new Element;
    koniec->next = NULL;
    koniec->wartosc = liczba;
    nowy = head;
    if (nowy){
        while (nowy->next) nowy = nowy->next;
        nowy->next = koniec;
    }
    else head = koniec;

}

void Lista::usun_poczatek()
{
    Element *nowy = head; //zapamietujemy poczatek
    if (nowy)
    {
        head = nowy->next; //poczatkiem bedzie kolejny element
        delete nowy;
    }

    /*
    Element *temp = head;
    Element * temp2 = temp->next;
    head = temp2;
    temp = NULL;
    */
}

void Lista::dodaj_srodek(Element *&head, Element *granica, int liczba)
{
    Element *nowy = head;
    //sprawdzenie czy nie wstawiamy na pierwsze mniejsce listy

    while (nowy->next != granica) nowy = nowy ->next;
    nowy -> next = new Element;
    nowy -> next -> next = granica;
    nowy -> next -> wartosc = liczba;
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
        cout << temp->wartosc <<" ";
        temp=temp->next;
    }
}
//Wyszukuje pierwszy element listy o danej wartosci
Element *Lista::find_first(int liczba)
{
    Element *temp = head;
    while (temp && temp->wartosc != liczba) temp = temp->next;
    return temp;
}

//dodawanie wg kryteriow
Element *wstawianie(int liczba, Element *head)
{
    Element *wsk, *poprzednik, *nastepnik;
    wsk = new Element;
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

int main(){
    Lista L;
    //Element *nowy;
    for (int i=0; i<40; i++) L.dodaj_poczatek(i);
    L.wyswietl_liste();

    //losowa lista
    srand(time(NULL));
    int liczba = rand()%(rozmiar+1);
    cout<<liczba;

return 0;
}
