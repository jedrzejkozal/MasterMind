#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Individual.hpp"
#include "globals.hpp"


using namespace std;

extern list<Color *> poprzednie;
extern list<unsigned> poprzednie_dobre, poprzednie_miejsca;


double Individual::odkoduj()
{
	int odleglosc = 0;
	unsigned dobre_miejsce, dobry_kolor;

	list<unsigned>::iterator it1 = poprzednie_dobre.begin();
	list<unsigned>::iterator it2 = poprzednie_miejsca.begin();
	for (list<Color *>::iterator it = poprzednie.begin(); it != poprzednie.end(); it++, it1++, it2++)
	{
		check(*it, allele, rozmiar, dobre_miejsce, dobry_kolor);
		odleglosc -= abs((int)(*it1 - dobre_miejsce)) + abs((int)(*it2 - dobry_kolor));
	}
	return odleglosc;
}

double Individual::oblicz_przystosowanie()
{
	return przystosowanie = odkoduj();
}

Individual &Individual::operator = (Individual &osob)
{
	for (unsigned i = 0; i < rozmiar; i++)
		allele[i] = osob[i];

	przystosowanie = osob.get_przystosowanie();
	return osob;
}

Color Individual::operator[] (unsigned index) const
{
	if (index < 0 || index > rozmiar - 1)
	{
		std::cerr << "Individual: operator[]: Podano zly indeks!" << std::endl;
		return allele[0];
	}
	else
		return allele[index];
}

Color &Individual::operator[] (unsigned index)
{
	if(index < 0 || index > rozmiar-1)
	{
		std::cerr << "Individual: operator[]: Podano zly indeks!" << std::endl;
		return allele[0];
	}
	else
		return allele[index];
}

Individual::Individual(unsigned rozmiar_ciagu) : rozmiar(rozmiar_ciagu)
{
	allele = new Color[rozmiar];
	if (allele != NULL)
	{
		for (unsigned i = 0; i < rozmiar; i++) //losowe przydzielenie bitow
			allele[i] = static_cast<color>(std::rand() % ILOSC_DOSTEPNYCH);
		oblicz_przystosowanie();
	}
	else
		std::cerr << "Individual: konstrutor: nie mozna przydzielic pamieci!" << std::endl;
}
