#include <iostream>
#include <stdlib.h>
#include <algorithm>

#include "Population.hpp"
#include "globals.hpp"

using namespace std;


unsigned lista_zwroc(list<int> *l, unsigned index)
{
	if (index > l->size())
	{
		cerr << "Funkcja lista_zwroc(): Podany indeks wykracza poza rozmiar listy" << endl;
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
	cerr << "Funkcja lista_zwroc(): nie znaleziono i-tego elementu listy!" << endl;
	return 0;
}

//TWORZENIE NOWEJ POPULACJI

bool compareosobnik1(const Individual * a, const Individual * b)
{
	return (a->getFitness() < b->getFitness());
}

void Population::selekcja_elitarna()
{
	//selekcja elitarna
	prawd_wybrania = new double[rozm_populacji/2]; //prawd_wybrania + poprzednie, zeby mozna bylo jakos normalnie losowac nowa populacje
	sort(osobniki, osobniki + rozm_populacji, compareosobnik1);

	suma = 0;
	for (unsigned i = rozm_populacji / 2 + 1; i < rozm_populacji; i++)
		suma += osobniki[i]->getFitness();

	unsigned j = 1;
	prawd_wybrania[0] = osobniki[rozm_populacji/2]->getFitness() * 100 / suma;
	for (unsigned i = rozm_populacji/2+1; i < rozm_populacji; i++, j++)
		prawd_wybrania[j] = osobniki[i]->getFitness() * 100 / suma + prawd_wybrania[i - 1];
}

void Population::oblicz_przystosowania()
{
	for (unsigned i = 0; i < rozm_populacji; i++)
		osobniki[i]->calcFitness();
}

void Population::nieujemne_przystosowania()
{
	for (unsigned i = 0; i < rozm_populacji; i++)
		osobniki[i]->set_przystosowanie(osobniki[i]->getFitness() - min_przystosowanie);
}

void Population::nowa_tablica_inicjalizuj()
{
	nowa = new Individual*[rozm_populacji];
	if (nowa == NULL)
	{
		cerr << "nowa_Population(): Nie mozna przydzielic pamieci!" << endl;
		return;
	}
	else
		for (unsigned i = 0; i < rozm_populacji; i++)
		{
			nowa[i] = new Individual(rozmiar_ciagu);
			if (nowa[i] == NULL)
			{
				cerr << "nowa_Population(): Nie mozna przydzielic pamieci!" << endl;
				for (i--; (int)i > -1; i--)
					delete nowa[i];
				return;
			}
		}
}

void Population::losuj_nowych_osobnikow()
{
	double losowana;

	for (unsigned i = 0; i < rozm_populacji; i++)
	{
		//TUTAJ MOZNA TO ZASTAPIC PRZESZUKIWANIEM POLOWKOWYM (TYM Z DZIELENIEM TABLICY)
		losowana = ((double)(std::rand() % 10000)) / 100;
		for (unsigned j = rozm_populacji/2; j < rozm_populacji; j++)
		{
			if (losowana < prawd_wybrania[j])
			{
				*nowa[i] = (*(osobniki[j]));
				break;
			}
		}
	}
}

//krzyzuje po kolei wszystkie osobniki, po tym jak mamy juz wybrana populacje
//double prawd - prawdopodobienstwo wystepowania krzyzowania
void Population::krzyzuj()
{
	list<int> indeksy;
	for (unsigned i = 0; i < rozm_populacji; i++)
		indeksy.push_back(i);

	unsigned tmp1, tmp2;
	while (indeksy.size() != 0)
	{
		//wybieranie pierwszego indeksu do krzyzowania
		tmp1 = lista_zwroc(&indeksy, std::rand() % indeksy.size());
		indeksy.remove(tmp1); //bylo indeksy.pop(tmp1); nie czy to samo

		//wybranie drugiego indeksu do krzyzowania
		tmp2 = lista_zwroc(&indeksy, std::rand() % indeksy.size());
		indeksy.remove(tmp2);

		if ((rand() % 1000) / 1000 < prawd_krzyzowania)
			for (unsigned j = std::rand() % (rozmiar_ciagu - 1) + 1; j < rozmiar_ciagu; j++) //punkt krzyzowania poczatku krzyzowania zawiera sie w przedziale od 1 do ostatniego elementu
				std::swap((*osobniki[tmp1])[j], (*osobniki[tmp2])[j]); //zamiana miejscami kolorow
	}
}

//Mutacja - prawd - prawdopodobienstwo mutacji w %
void Population::mutuj()
{
	for (unsigned i = 0; i < rozm_populacji; i++)
		for (unsigned j = 0; j < rozmiar_ciagu; j++)
			if ((std::rand() % 100000) / 1000 < prawd_mutacji) //prawodopodobienstwo wyrazone w %, powinno troszke pomoc
				(*osobniki[i])[j] = (color) (std::rand() % ILOSC_DOSTEPNYCH);
}

void Population::nowa_populacja()
{
	oblicz_przystosowania();
	nieujemne_przystosowania();
	oblicz_statystyki();
	selekcja_elitarna();
	//wyswietl_statystyki();
	nowa_tablica_inicjalizuj();
	losuj_nowych_osobnikow();

	delete[] prawd_wybrania;
	for (unsigned i = 0; i < rozm_populacji; i++)
	{
		osobniki[i]->zwolnij_pamiec();
		delete osobniki[i];
	}
	delete[] osobniki;
	osobniki = nowa;
	nowa = NULL;
	//wyswietl();
	krzyzuj();
	mutuj();
	oblicz_przystosowania();
}

//STATYSTYKI

void Population::oblicz_statystyki()
{
	suma = 0;
	max_przystosowanie = -9999999999;
	min_przystosowanie = 9999999999;
	for (unsigned i = 0; i < rozm_populacji; i++)
	{
		//zbieranie wszystkich statystyk
		suma += osobniki[i]->getFitness();
		if (osobniki[i]->getFitness() > max_przystosowanie)
		{
			max_przystosowanie = osobniki[i]->getFitness();
			najlepszy = osobniki[i];
		}
		if (osobniki[i]->getFitness() < min_przystosowanie)
		{
			min_przystosowanie = osobniki[i]->getFitness();
			najgorszy = osobniki[i];
		}
	}
	srednie_przystosowanie = suma / rozm_populacji; //obliczenie sredniej
}

void Population::wyswietl_statystyki() const
{
	cout <<
		//"Suma wszystkich przystosowan: " << suma << endl <<
		"Srednie przystosowanie: " << srednie_przystosowanie << endl <<
		//"Liczba dobrych rozwiazan: " << l_dobrych_rozwiazan << endl << endl;
		"Maksymalne przystosowanie: " << max_przystosowanie << endl;
	//"Minimalne przystosowanie: " << min_przystosowanie << endl;

	//wyswietl();
}

//DEBUGOWANIE

void Population::reinicjalizuj()
{
	for (unsigned i = 0; i < rozm_populacji; i++)
		for (unsigned j = 0; j < rozmiar_ciagu; j++)
			(*osobniki[i])[j] = std::rand() % 2;
}

void Population::wyswietl() const
{
	unsigned ile_w_kolumnie = 1;
	cout << "Wartosci wszystkich osobnikow:" << endl;
	cout << "Nr.  przyst.  ciag bitowy" << endl;
	for (unsigned i = 0; i < rozm_populacji; i += ile_w_kolumnie)
	{
		for (unsigned j = 0; j < ile_w_kolumnie; j++)
			if (i < rozm_populacji)
			{
				cout << i+j << " \t" << osobniki[i+j]->getFitness() << " \t";
				osobniki[i+j]->wyswietl();
				cout << "\t";
			}
		cout << endl;
	}
	cout << endl << endl;
}


Population::Population(unsigned lpop, unsigned rozm_alleli, double p_mutacji, double p_krzyozwania) : rozm_populacji(lpop), rozmiar_ciagu(rozm_alleli), prawd_mutacji(p_mutacji * 100), prawd_krzyzowania(p_krzyozwania)
{
	osobniki = new Individual*[lpop];
	if (osobniki == NULL)
		cerr << "Population: konstruktor: Nie mozna przydzielic pamieci!" << endl;
	for (unsigned i = 0; i < lpop; i++)
	{
		osobniki[i] = new Individual(rozm_alleli);
		if (osobniki[i] == NULL)
			cerr << "Population: konstruktor: Nie mozna przydzielic pamieci!" << endl;
	}
}

Population::~Population()
{
	if (osobniki != NULL)
	{
		for (unsigned i = 0; i < rozm_populacji; i++)
		{
			osobniki[i]->zwolnij_pamiec();
			delete osobniki[i];
		}
		delete[] osobniki;
	}
}
