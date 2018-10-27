#include <iostream>
#include <cstdlib>
#include <math.h>

#include "osobnik.hpp"
#include "zmienne_globalne.hpp"


using namespace std;

extern list<Kolor *> poprzednie;
extern list<unsigned> poprzednie_dobre, poprzednie_miejsca;


double osobnik::odkoduj()
{
	int odleglosc = 0;
	unsigned dobre_miejsce, dobry_kolor;

	list<unsigned>::iterator it1 = poprzednie_dobre.begin();
	list<unsigned>::iterator it2 = poprzednie_miejsca.begin();
	for (list<Kolor *>::iterator it = poprzednie.begin(); it != poprzednie.end(); it++, it1++, it2++)
	{
		sprawdz(*it, allele, rozmiar, dobre_miejsce, dobry_kolor);
		odleglosc -= abs((int)(*it1 - dobre_miejsce)) + abs((int)(*it2 - dobry_kolor));
	}
	return odleglosc;
}

double osobnik::oblicz_przystosowanie()
{
	return przystosowanie = odkoduj();
}

osobnik &osobnik::operator = (osobnik &osob)
{
	for (unsigned i = 0; i < rozmiar; i++)
		allele[i] = osob[i];

	przystosowanie = osob.get_przystosowanie();
	return osob;
}

Kolor osobnik::operator[] (unsigned index) const
{
	if (index < 0 || index > rozmiar - 1)
	{
		std::cerr << "Osobnik: operator[]: Podano zly indeks!" << std::endl;
		return allele[0];
	}
	else
		return allele[index];
}

Kolor &osobnik::operator[] (unsigned index)
{
	if(index < 0 || index > rozmiar-1)
	{
		std::cerr << "Osobnik: operator[]: Podano zly indeks!" << std::endl;
		return allele[0];
	}
	else
		return allele[index];
}

osobnik::osobnik(unsigned rozmiar_ciagu) : rozmiar(rozmiar_ciagu)
{
	allele = new Kolor[rozmiar];
	if (allele != NULL)
	{
		for (unsigned i = 0; i < rozmiar; i++) //losowe przydzielenie bitow
			allele[i] = static_cast<kolor>(std::rand() % ILOSC_DOSTEPNYCH);
		oblicz_przystosowanie();
	}
	else
		std::cerr << "Osobnik: konstrutor: nie mozna przydzielic pamieci!" << std::endl;
}
