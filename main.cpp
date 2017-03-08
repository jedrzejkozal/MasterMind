#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <termios.h>


#include "populacja.h"
#include "zmienne_globalne.h"

using namespace std;

list<Kolor *> poprzednie;
list<unsigned> poprzednie_dobre, poprzednie_miejsca;

/*argumenty
kod - kod, ktory trzeba odgadnac, odlegosc do niego bedzie sprawdzana
proba - kombinacja, ktora ma byc oceniania
dlugosc - dlugosc lancuchow zmiennych
poprawne - ilosc kulek na swoim miejscu i o odpowiednim kolorze w proponowanej kombinacji
poprawne_miejsca - ilosc kulek na poprawnym miejscu, ale z innym kolorem*/
void sprawdz(Kolor *kod, Kolor *proba, const unsigned dlugosc, unsigned &poprawne, unsigned &poprawne_miejsca)
{
	poprawne = poprawne_miejsca = 0;

	//tablica flag do sprawdzenia czy cos ma dobry kolor ale jest na nieswoim miejscu
	bool *bylo_na_dobrym;
	bylo_na_dobrym = new bool[dlugosc];
	for (unsigned i = 0; i < dlugosc; i++)
		bylo_na_dobrym[i] = false;

	//sprawdzenie czy jest cos na swoim miejscu
	for (unsigned i = 0; i < dlugosc; i++)
	{
		if (proba[i] == kod[i])
		{
			poprawne++;
			bylo_na_dobrym[i] = true; //tutaj zaznaczamy ze bylo na dobrym miejscu
		}
	}
	//sprawdzenie czy jest dobry kolor na nieswoim miejscu
	for (unsigned i = 0; i < dlugosc; i++)
			for (unsigned j = 0; j < dlugosc; j++)
				if (proba[i] == kod[j] && bylo_na_dobrym[j] == false)
				{
					poprawne_miejsca++;
					bylo_na_dobrym[j] = true; //tutaj zaznaczamy ze bylo wykorzystane, na wypadek gdyby ten sam kolor mialby byc
											  //sprawdzany w przyszlosci (nie trzeba deklarowac nowej tablicy)
					break;
				}

	delete[] bylo_na_dobrym;
}

void wyswietl_ciag(Kolor *p, const unsigned dlugosc)
{
	for (unsigned i = 0; i < dlugosc; i++)
		cout << p[i];
}

int main()
{
	srand((unsigned int)time(NULL));

	const unsigned short dlugosc_ciagu = 6;		//dlugosc ciagu do odganidniecia
	unsigned ilosc_poprawnych, ilosc_poprawnych_miejsc;
	populacja pop(20, dlugosc_ciagu, 4, 0.4);
	Kolor *kod; Kolor *proba;


	kod = new Kolor[dlugosc_ciagu];
	proba = new Kolor[dlugosc_ciagu];

	cout << "Podaj kod, zlozony z 6 kolorow od 0 do 8" << endl;
	/*
	for (unsigned i = 0; i < dlugosc_ciagu; i++)
	{
		do
		{
			cin >> kod[i];
		} while(kod[i].kol < 0 || kod[i].kol > ILOSC_DOSTEPNYCH - 1);
	}*/
	for (unsigned i = 0; i < dlugosc_ciagu; i++)
		kod[i] = 0;

	//gra przechodzi do drugiego gracza
	cout << endl << "Odgadnij ciag podany wczesniej:" << endl;

	cout << "Podane propozycje: " << endl;

	do
	{
			pop.nowa_populacja();
			cout << "test" << endl;
			pop.oblicz_statystyki();
			cout << "test" << endl;
			//pop.wyswietl();

		proba = new Kolor[dlugosc_ciagu];
		cout << "test" << endl;
		for (unsigned i = 0; i < dlugosc_ciagu; i++) //iteracja po kazdym kolorze
			proba[i] = (*pop.najlepszy)[i];
		cout << "test" << endl;
		sprawdz(kod, proba, dlugosc_ciagu, ilosc_poprawnych, ilosc_poprawnych_miejsc);
		//cout << endl << "Ilosc poprawnych: " << ilosc_poprawnych << endl << "Ilosc na dobrych miejscach: " << ilosc_poprawnych_miejsc << endl << endl;

		poprzednie.push_back(proba);
		poprzednie_dobre.push_back(ilosc_poprawnych);
		poprzednie_miejsca.push_back(ilosc_poprawnych_miejsc);

		wyswietl_ciag(poprzednie.back(), dlugosc_ciagu);
		cout << "\t" << poprzednie_dobre.back() << "\t" << poprzednie_miejsca.back() << endl;
	} while (ilosc_poprawnych != dlugosc_ciagu);

	cout << "Koniec gry, wygrales!" << endl;
	return 0;
}
