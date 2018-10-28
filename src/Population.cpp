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
	chossingProbability = new double[populationSize/2]; //chossingProbability + poprzednie, zeby mozna bylo jakos normalnie losowac nowa populacje
	sort(individuals, individuals + populationSize, compareosobnik1);

	fitnessSum = 0;
	for (unsigned i = populationSize / 2 + 1; i < populationSize; i++)
		fitnessSum += individuals[i]->getFitness();

	unsigned j = 1;
	chossingProbability[0] = individuals[populationSize/2]->getFitness() * 100 / fitnessSum;
	for (unsigned i = populationSize/2+1; i < populationSize; i++, j++)
		chossingProbability[j] = individuals[i]->getFitness() * 100 / fitnessSum + chossingProbability[i - 1];
}

void Population::calcFitness()
{
	for (unsigned i = 0; i < populationSize; i++)
		individuals[i]->calcFitness();
}

void Population::nonnegativeFitness()
{
	for (unsigned i = 0; i < populationSize; i++)
		individuals[i]->setFitness(individuals[i]->getFitness() - minFitness);
}

void Population::nowa_tablica_inicjalizuj()
{
	nowa = new Individual*[populationSize];
	if (nowa == NULL)
	{
		cerr << "nowa_Population(): Nie mozna przydzielic pamieci!" << endl;
		return;
	}
	else
		for (unsigned i = 0; i < populationSize; i++)
		{
			nowa[i] = new Individual(seriesSize);
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

	for (unsigned i = 0; i < populationSize; i++)
	{
		//TUTAJ MOZNA TO ZASTAPIC PRZESZUKIWANIEM POLOWKOWYM (TYM Z DZIELENIEM TABLICY)
		losowana = ((double)(std::rand() % 10000)) / 100;
		for (unsigned j = populationSize/2; j < populationSize; j++)
		{
			if (losowana < chossingProbability[j])
			{
				*nowa[i] = (*(individuals[j]));
				break;
			}
		}
	}
}

//krzyzuje po kolei wszystkie individuals, po tym jak mamy juz wybrana populacje
//double prawd - prawdopodobienstwo wystepowania krzyzowania
void Population::krzyzuj()
{
	list<int> indeksy;
	for (unsigned i = 0; i < populationSize; i++)
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

		if ((rand() % 1000) / 1000 < crossOverProbability)
			for (unsigned j = std::rand() % (seriesSize - 1) + 1; j < seriesSize; j++) //punkt krzyzowania poczatku krzyzowania zawiera sie w przedziale od 1 do ostatniego elementu
				std::swap((*individuals[tmp1])[j], (*individuals[tmp2])[j]); //zamiana miejscami kolorow
	}
}

//Mutacja - prawd - prawdopodobienstwo mutacji w %
void Population::mutuj()
{
	for (unsigned i = 0; i < populationSize; i++)
		for (unsigned j = 0; j < seriesSize; j++)
			if ((std::rand() % 100000) / 1000 < mutationProbablity) //prawodopodobienstwo wyrazone w %, powinno troszke pomoc
				(*individuals[i])[j] = (color) (std::rand() % ILOSC_DOSTEPNYCH);
}

void Population::newPopulation()
{
	calcFitness();
	nonnegativeFitness();
	calcStats();
	selekcja_elitarna();
	//printStats();
	nowa_tablica_inicjalizuj();
	losuj_nowych_osobnikow();

	delete[] chossingProbability;
	for (unsigned i = 0; i < populationSize; i++)
	{
		individuals[i]->freeMemory();
		delete individuals[i];
	}
	delete[] individuals;
	individuals = nowa;
	nowa = NULL;
	//wyswietl();
	krzyzuj();
	mutuj();
	calcFitness();
}

//STATYSTYKI

void Population::calcStats()
{
	fitnessSum = 0;
	maxFitness = -9999999999;
	minFitness = 9999999999;
	for (unsigned i = 0; i < populationSize; i++)
	{
		//zbieranie wszystkich statystyk
		fitnessSum += individuals[i]->getFitness();
		if (individuals[i]->getFitness() > maxFitness)
		{
			maxFitness = individuals[i]->getFitness();
			najlepszy = individuals[i];
		}
		if (individuals[i]->getFitness() < minFitness)
		{
			minFitness = individuals[i]->getFitness();
			najgorszy = individuals[i];
		}
	}
	avrageFitness = fitnessSum / populationSize; //obliczenie sredniej
}

void Population::printStats() const
{
	cout <<
		//"Fitness sum: " << fitnessSum << endl <<
		"avrageFitness: " << avrageFitness << endl <<
		//"Liczba dobrych rozwiazan: " << l_dobrych_rozwiazan << endl << endl;
		"Max fitness: " << maxFitness << endl;
	//"Minimal fitness: " << minFitness << endl;

	//wyswietl();
}

//DEBUGOWANIE

void Population::reinitialize()
{
	for (unsigned i = 0; i < populationSize; i++)
		for (unsigned j = 0; j < seriesSize; j++)
			(*individuals[i])[j] = std::rand() % 2;
}

void Population::print() const
{
	unsigned ile_w_kolumnie = 1;
	cout << "Wartosci wszystkich osobnikow:" << endl;
	cout << "Nr.  przyst.  ciag bitowy" << endl;
	for (unsigned i = 0; i < populationSize; i += ile_w_kolumnie)
	{
		for (unsigned j = 0; j < ile_w_kolumnie; j++)
			if (i < populationSize)
			{
				cout << i+j << " \t" << individuals[i+j]->getFitness() << " \t";
				individuals[i+j]->print();
				cout << "\t";
			}
		cout << endl;
	}
	cout << endl << endl;
}


Population::Population(unsigned lpop, unsigned rozm_alleli, double p_mutacji, double p_krzyozwania) : populationSize(lpop), seriesSize(rozm_alleli), mutationProbablity(p_mutacji * 100), crossOverProbability(p_krzyozwania)
{
	individuals = new Individual*[lpop];
	if (individuals == NULL)
		cerr << "Population: konstruktor: Nie mozna przydzielic pamieci!" << endl;
	for (unsigned i = 0; i < lpop; i++)
	{
		individuals[i] = new Individual(rozm_alleli);
		if (individuals[i] == NULL)
			cerr << "Population: konstruktor: Nie mozna przydzielic pamieci!" << endl;
	}
}

Population::~Population()
{
	if (individuals != NULL)
	{
		for (unsigned i = 0; i < populationSize; i++)
		{
			individuals[i]->freeMemory();
			delete individuals[i];
		}
		delete[] individuals;
	}
}
