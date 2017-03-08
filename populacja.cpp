#include <iostream>
#include <stdlib.h>
#include <algorithm>

#include "populacja.h"
#include "zmienne_globalne.h"

using namespace std;


populacja::populacja(unsigned lpop, unsigned rozm_alleli, double p_mutacji, double p_krzyozwania) : lpopulacji(lpop), rozmiar_ciagu(rozm_alleli), prawd_krzyzowania(p_krzyozwania), prawd_mutacji(p_mutacji * 100)
{
	osob = new osobnik*[lpop];
	if (osob == NULL)
		std::cerr << "Populacja: konstruktor: Nie mozna przydzielic pamieci!" << std::endl;
	for (unsigned i = 0; i < lpop; i++)
	{
		osob[i] = new osobnik(rozm_alleli);
		if (osob[i] == NULL)
			std::cerr << "Populacja: konstruktor: Nie mozna przydzielic pamieci!" << std::endl;
	}
}

populacja::~populacja()
{
	if (osob != NULL)
	{
		for (unsigned i = 0; i < lpopulacji; i++)
		{
			osob[i]->zwolnij_pamiec();
			delete osob[i];
		}
		delete[] osob;
	}
}

void populacja::wyswietl() const
{
	unsigned ile_w_kolumnie = 1;
	std::cout << "Wartosci wszystkich osobnikow:" << endl;
	cout << "Nr.  przyst.  ciag bitowy" << endl;
	for (unsigned i = 0; i < lpopulacji; i += ile_w_kolumnie)
	{
		for (unsigned j = 0; j < ile_w_kolumnie; j++)
			if (i < lpopulacji)
			{
				cout << i+j << " \t" << osob[i+j]->get_przystosowanie() << " \t";
				osob[i+j]->wyswietl();
				cout << "\t";
			}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}

void swap_kolor(Kolor arg1, Kolor arg2)
{
	Kolor tmp;
	tmp = arg1;
	arg1 = arg2;
	arg2 = tmp;
}

unsigned zwroc(list<int> *l, unsigned index)
{
	if (index > l->size())
	{
		std::cerr << "Funkcja zwroc(): Podany indeks wykracza poza rozmiar listy" << std::endl;
		return 0;
	}
	list<int>::iterator it = l->begin();
	for (unsigned j = 0; j < l->size(); j++)
	{
		if (index == j)
			return *it;
		else
			it++;
	}
	std::cerr << "Metoda zwroc(): nie znaleziono i-tego elementu listy!" << std::endl;
	return 0;
}

//krzyzuje po kolei wszystkie osobniki, po tym jak mamy juz wybrana populacje
//double prawd - prawdopodobienstwo wystepowania krzyzowania
void populacja::krzyzuj()
{
	list<int> indeksy;
	for (unsigned i = 0; i < lpopulacji; i++)
		indeksy.push_back(i);

	unsigned tmp1, tmp2;
	while (indeksy.size() != 0)
	{
		//wybieranie pierwszego indeksu do krzyzowania
		tmp1 = zwroc(&indeksy, std::rand() % indeksy.size());
		indeksy.remove(tmp1); //bylo indeksy.pop(tmp1); nie czy to samo

		//wybranie drugiego indeksu do krzyzowania
		//tmp2 = indeksy.zwroc(tmp2);
		tmp2 = zwroc(&indeksy, std::rand() % indeksy.size());
		indeksy.remove(tmp2);

		//cout << "tmp1 = " << tmp1 << " tmp2 = " << tmp2 << endl;

		if ((rand() % 1000) / 1000 < prawd_krzyzowania)
			for (unsigned j = std::rand() % (rozmiar_ciagu - 1) + 1; j < rozmiar_ciagu; j++) //punkt krzyzowania poczatku krzyzowania zawiera sie w przedziale od 1 do ostatniego elementu
			{
				//swap(((*osob)[tmp1])[j], ((*osob)[tmp2])[j]); //zamiana miejscami bitow
				std::swap((*osob[tmp1])[j], (*osob[tmp2])[j]); //zamiana miejscami kolorow
				/*(*osob[tmp1]).wyswietl();
				cout << " ";
				(*osob[tmp2]).wyswietl();
				cout << endl;*/
			}

	}
}

/*Mutacja - prawd - prawdopodobienstwo mutacji w %*/
void populacja::mutuj()
{
	for (unsigned i = 0; i < lpopulacji; i++)
		for (unsigned j = 0; j < rozmiar_ciagu; j++)
			if ((std::rand() % 100000) / 1000 < prawd_mutacji) //prawodopodobienstwo wyrazone w %, powinno troszke pomoc
			{
				/*short int tmp = static_cast<int>((*osob[i])[j].kol);
				tmp++; //zamiana koloru na nastepny
				if (tmp == ILOSC_DOSTEPNYCH)
					tmp = 0;
				(*osob[i])[j] = (kolor)tmp;*/
				(*osob[i])[j] = (kolor) (std::rand() % ILOSC_DOSTEPNYCH);
				//cout << (*osob[i])[j] << endl;
			}
}

void populacja::skaluj_przystosowania()
{
	for (unsigned i = 0; i < lpopulacji; i++)
		osob[i]->set_przystosowanie(osob[i]->get_przystosowanie() - min_przystosowanie);
}

bool compareOsobnik1(const osobnik * a, const osobnik * b)
{
	return (a->get_przystosowanie() < b->get_przystosowanie());
}

void populacja::nowa_populacja()
{
	oblicz_przystosowania();
	statystyki(); //obliczanie sumy wszystkich przystosowan i znalezienie minimalnego przystosowania
	skaluj_przystosowania();

	//selekcja elitarna
	double *pselect = new double[lpopulacji/2]; //pselect + poprzednie, zeby mozna bylo jakos normalnie losowac nowa populacje
	sort(osob, osob + lpopulacji, compareOsobnik1);

	suma = 0;
	for (unsigned i = lpopulacji / 2 + 1; i < lpopulacji; i++)
		suma += osob[i]->get_przystosowanie();

	unsigned j = 1;
	pselect[0] = osob[lpopulacji/2]->get_przystosowanie() * 100 / suma;
	for (unsigned i = lpopulacji/2+1; i < lpopulacji; i++, j++)
		pselect[j] = osob[i]->get_przystosowanie() * 100 / suma + pselect[i - 1];

	//raport();

	osobnik** nowa = new osobnik*[lpopulacji];
	if (nowa == NULL)
	{
		std::cerr << "nowa_populacja(): Nie mozna przydzielic pamieci!" << std::endl;
		return;
	}
	else
	{
		for (unsigned i = 0; i < lpopulacji; i++)
		{
			nowa[i] = new osobnik(rozmiar_ciagu);
			if (nowa[i] == NULL)
			{
				//TUTAJ MOZE BYC WYRZUCONY WYJATEK
				//zwolnienie pamieci i zakonczenie dzialania funkcji
				std::cerr << "nowa_populacja(): Nie mozna przydzielic pamieci!" << std::endl;
				for (i--; (int)i > -1; i--)
					delete nowa[i];
				return;
			}
		}
	}
	double losowana;

	//zgodnie z wylosowanymi pselect losujemy osobnikow do nowej populacji:
	for (unsigned i = 0; i < lpopulacji; i++)
	{
		//TUTAJ MOZNA TO ZASTAPIC PRZESZUKIWANIEM POLOWKOWYM (TYM Z DZIELENIEM TABLICY)
		losowana = ((double)(std::rand() % 10000)) / 100;
		for (unsigned j = lpopulacji/2; j < lpopulacji; j++)
		{
			if (losowana < pselect[j])
			{
				//nowa[i]->operator=(*(osob[j]));
				*nowa[i] = (*(osob[j]));
				break;
			}
		}
	}

	delete[] pselect;
	for (unsigned i = 0; i < lpopulacji; i++)
	{
		osob[i]->zwolnij_pamiec();
		delete osob[i];
	}
	delete[] osob;
	osob = nowa;

	//wyswietl();
	krzyzuj();
	mutuj();

	skaluj();
	oblicz_przystosowania();
}

void populacja::oblicz_przystosowania()
{
	for (unsigned i = 0; i < lpopulacji; i++)
		osob[i]->oblicz_przystosowanie();
}

void populacja::statystyki()
{
	suma = 0;
	max_przystosowanie = -9999999999;
	min_przystosowanie = 9999999999;
	for (unsigned i = 0; i < lpopulacji; i++)
	{
		//zbieranie wszystkich statystyk
		suma += osob[i]->get_przystosowanie();
		if (osob[i]->get_przystosowanie() > max_przystosowanie)
		{
			max_przystosowanie = osob[i]->get_przystosowanie();
			najlepszy = osob[i];
		}
		if (osob[i]->get_przystosowanie() < min_przystosowanie)
		{
			min_przystosowanie = osob[i]->get_przystosowanie();
			najgorszy = osob[i];
		}
	}
	srednie_przystosowanie = suma / lpopulacji; //obliczenie sredniej
}

void populacja::raport() const
{
	cout <<
		//"Suma wszystkich przystosowan: " << suma << endl <<
		"Srednie przystosowanie: " << srednie_przystosowanie << endl <<
		//"Liczba dobrych rozwiazan: " << l_dobrych_rozwiazan << endl << endl;
		"Maksymalne przystosowanie: " << max_przystosowanie << endl;
	//"Minimalne przystosowanie: " << min_przystosowanie << endl;

	//wyswietl();
}

//Skalowanie - podejscie do problemu przedwczesnej zbieznosci
void populacja::skaluj()
{
	const double Cmultiple = 2; //wspolczynnik przez ktory sa mnozone przystosowania najlepszych
	double a, b;

	if (min_przystosowanie > (Cmultiple * srednie_przystosowanie) / (Cmultiple - 1)) //test na nieujmne
	{
		a = (Cmultiple - 1)*srednie_przystosowanie / (max_przystosowanie - srednie_przystosowanie);
		b = srednie_przystosowanie*(max_przystosowanie - Cmultiple*srednie_przystosowanie) / (max_przystosowanie - srednie_przystosowanie);
	}
	else
	{
		a = srednie_przystosowanie / (srednie_przystosowanie - min_przystosowanie);
		b = -min_przystosowanie*srednie_przystosowanie / (srednie_przystosowanie - min_przystosowanie);
	}

	//przeskalowanie wszystkich osobnikow w populacji
	for (unsigned i = 0; i < lpopulacji; i++)
		osob[i]->set_przystosowanie(a*osob[i]->get_przystosowanie() + b);
}

void populacja::reinicjalizuj()
{
	for (unsigned i = 0; i < lpopulacji; i++)
		for (unsigned j = 0; j < rozmiar_ciagu; j++)
			(*osob[i])[j] = std::rand() % 2;
}
