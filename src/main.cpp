#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <termios.h>


#include "Population.hpp"
#include "globals.hpp"


using namespace std;

list<Color *> poprzednie;
list<unsigned> poprzednie_dobre, poprzednie_miejsca;

#include "check.hpp"

void wyswietl_ciag(Color *p, const unsigned dlugosc)
{
	for (unsigned i = 0; i < dlugosc; i++)
		cout << p[i];
}

int main()
{
	srand((unsigned int)time(NULL));

	const unsigned short dlugosc_ciagu = 6;		//dlugosc ciagu do odganidniecia
	unsigned ilosc_poprawnych, ilosc_poprawnych_miejsc;
	Population pop(20, dlugosc_ciagu, 4, 0.4);
	Color *kod;
	Color *proba;


	kod = new Color[dlugosc_ciagu];
	proba = new Color[dlugosc_ciagu];

	cout << "Podaj kod, zlozony z 6 kolorow od 0 do 8" << endl;
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

		proba = new Color[dlugosc_ciagu];
		cout << "test" << endl;
		for (unsigned i = 0; i < dlugosc_ciagu; i++) //iteracja po kazdym kolorze
			proba[i] = (*pop.najlepszy)[i];
		cout << "test" << endl;
		check(kod, proba, dlugosc_ciagu, ilosc_poprawnych, ilosc_poprawnych_miejsc);
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
